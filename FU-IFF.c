/****h* FractalUniverse/FU-IFF.c [1.68] *
*
*  NAME
*    FU-IFF.c
*  COPYRIGHT
*    $VER: FU-IFF.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    The IFF-Picture Load & Save Routines
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    24.Oct.2001
*  MODIFICATION HISTORY
*    24.Oct.2001	V 1.68	most recent version
*    24.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

//-- includes -----------------------------------------------------------------

#define FU_IFF_C
#include "FU-Includes.h"

//-- defines ------------------------------------------------------------------

#define MAXCOLORS		256
#define BUFFER_SIZE  32000                /* image decompression buffer */
#define FORM	MakeID('F','O','R','M')
#define ILBM	MakeID('I','L','B','M')
#define FRUN	MakeID('F','R','U','N')
#define BMHD	MakeID('B','M','H','D')
#define CRNG	MakeID('C','R','N','G')
#define CCRT	MakeID('C','C','R','T')
#define CAMG	MakeID('C','A','M','G')
#define CMAP	MakeID('C','M','A','P')
#define BODY	MakeID('B','O','D','Y')
#define byte(n) (((n + 15) >> 4) << 1)		/* Word aligned width in bytes. */
#define TYPE	chunktype.type_long
#define STRTYPE	chunktype.type_str
#define mskNone					0			/*  Masking techniques  */
#define mskHasMask				1
#define mskHasTransparentColor	2
#define mskLasso				3
#define cmpNone					0			/*  Compression techniques  */
#define cmpByteRun1				1
#define BADFLAGS (SPRITES|VP_HIDE|GENLOCK_AUDIO|GENLOCK_VIDEO)
#define FLAGMASK (~BADFLAGS)
#define CAMGMASK (FLAGMASK & 0x0000FFFF)

#define RowBytes(w)     ((((w) + 15) >> 4) << 1)
#define RowBits(w)      ((((w) + 15) >> 4) << 4)

//-- prototypes ---------------------------------------------------------------

void LoadImage(char *filename);

void SaveImage(char *filename,UBYTE mode);

void matchnrff(UBYTE *nr,char *name);
void matchffnr(UBYTE *nr,char *name);
void matchnrsf(UBYTE *nr,char *name);
void matchsfnr(UBYTE *nr,char *name);
void matchnris(UBYTE *nr,char *name);
void matchisnr(UBYTE *nr,char *name);
void matchnros(UBYTE *nr,char *name);
void matchosnr(UBYTE *nr,char *name);

void convert15_13(struct FractalUniverse1_5 *frun1_5,struct FractalUniverse1_3 *frun1_3);

/* Some IFF parsing structs/constants */

struct BitMapHeader {
	UWORD w,h;					/* Raster width & height. */
	UWORD x,y;					/* Pixel position. */
	UBYTE nPlanes;				/* Number of source bitplanes. */
	UBYTE masking;				/* Masking... good for nothing maybe? */
	UBYTE compression;			/* Packed or unpacked? */
	UBYTE pad1;					/* We don't like odd length structures. */
	UWORD transparentColor; 	/* Maybe good for... */
	UBYTE xAspect,yAspect;		/* Kind of quotient, width / height. */
	WORD pageWidth,pageHeight;	/* Source page size. */
};	

struct FractalUniverse1_3 {
	ULONG scrmode;						/* Screenmode */
	UBYTE revpal;						/* Gespiegelte Farbpalette benutzen ? */
	UBYTE dither;						/* Welches Dithering */
	UBYTE ordscl;						/* Scaling der Palette Bei Orderd >=1 */
	UBYTE palscl;						/* Palettescaling (stretch) >=1 */
	UBYTE palmap;						/* Palettemapping */
	UBYTE gfxtyp;						/* Welche Grafikroutinen */
	UBYTE mirrorx,mirrory;				/* Grafik spiegeln */
	double x1,y1,x2,y2;					/* Koordinaten des Ausschnittes */
	double rot;							/* Winkel -> Rotation */
	complex par1,par2,par3,par4;		/* Zusatzparameter */
	double bailout;						/* Bailout */
	UBYTE tpar1,tpar2,tpar3,tpar4;		/* Trig.functions */
	int xb1,yb1,xb2,yb2;				/* Window für Berechnung */
	int z;								/* Zyclen */
	int outpar1;						/* Outsideparameter */
	int inpar1;							/* Insideparameter */
	ColorPar r,g,b;						/* Aktuelle Palette */
	UBYTE pad;							/* a small gap */
	char ffstr[20];						/* FracFunc */
	char sfstr[20];						/* SubFunc */
	char isstr[20];						/* InsideModell */
	char osstr[20];						/* OutsideModell */
};

struct FractalUniverse1_5 {
	ULONG scrmode;						/* Screenmode */
	UBYTE revpal;						/* Gespiegelte Farbpalette benutzen ? */
	UBYTE dither;						/* Welches Dithering */
	UBYTE ordscl;						/* Scaling der Palette Bei Orderd >=1 */
	UBYTE palscl;						/* Palettescaling (stretch) >=1 */
	UBYTE palmap;						/* Palettemapping */
	UBYTE gfxtyp;						/* Welche Grafikroutinen */
	UBYTE mirrorx,mirrory;				/* Grafik spiegeln */
	double x1,y1,x2,y2;					/* Koordinaten des Ausschnittes */
	double rot;							/* Winkel -> Rotation */
	complex par1,par2,par3,par4;		/* Zusatzparameter */
	double bailout;						/* Bailout */
	UBYTE tpar1,tpar2,tpar3,tpar4;		/* Trig.functions */
	UWORD xb1,yb1,xb2,yb2;				/* Window für Berechnung */
	UWORD z;							/* Zyclen */
	UWORD outpar1,outpar2;				/* Outsideparameter */
	UWORD inpar1,inpar2;				/* Insideparameter */
	ColorPar r,g,b;						/* Aktuelle Palette */
	UBYTE pad;							/* a small gap */
	char ffstr[20];						/* FracFunc */
	char sfstr[20];						/* SubFunc */
	char isstr[20];						/* InsideModell */
	char osstr[20];						/* OutsideModell */
};

/* IFF Stuff */
union typekludge {
	char type_str[4];
	long type_long;
};
struct ChunkHeader {
	union typekludge chunktype;
	long chunksize;
};

//-- definitions --------------------------------------------------------------

void LoadImage(char *filename)
{
	struct BitMapHeader bmhd;
	struct ChunkHeader ch;
	FILE *file;
	LONG formsize, subtype;
	ULONG j;
	UWORD i,n;
	register UWORD y;
	register UBYTE d;
	struct BitMap bm={0};
	PLANEPTR bpls[8];
	UBYTE fracchunk=0,cont,okay;
	UWORD frun_version;
	struct FractalUniverse1_3 frun1_3;
	struct FractalUniverse1_5 frun1_5;
	UWORD BPR2;

	MSG("loading ...");


	if(!(file=fopen(filename,"rb"))) { Message(mess[0]);return; }
	if(!fread(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[1]);fclose(file);return; }
	if(ch.TYPE!=FORM) { Message(mess[11]);fclose(file);return; }
	if(!fread(&subtype, sizeof(subtype),1,file)) { Message(mess[1]);fclose(file);return; }
	formsize=ch.chunksize-sizeof(subtype);
	if(subtype!=ILBM) { Message(mess[12]);fclose(file);return; }
	MSG("  is iff");
	while(formsize>0) {											/* solange nicht alles bearbeitet ist */
		if(!fread(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[1]);fclose(file);return; }
		formsize-=sizeof(struct ChunkHeader);

		switch(ch.TYPE) {											/* je nach Chunktyp */
			case FRUN:												/* FRactalUNiverse Chunk */
				fracchunk=1;
				if(fread(&frun_version,2,1,file)) {
					switch(frun_version) {
						case 130:
							MSG("  FRUN 1.3");
							if(fread(&frun1_3,sizeof(frun1_3),1,file)) convert15_13(&frun1_5,&frun1_3);
							else { Message(mess[1]);fclose(file);return; }
							break;
						case 150:
							MSG("  FRUN 1.5");
							if(!fread(&frun1_5,sizeof(frun1_5),1,file)) { Message(mess[1]);fclose(file);return; }
							break;
						default:
							{
								char msg[256];
								sprintf(msg,"%s : ver=%d size=%d",mess[10],frun_version,ch.chunksize);
								Message(msg);
								//Message(mess[10]);
								fclose(file);return;
							}
							break;
					}
				}
				else { Message(mess[1]);fclose(file);return; }
				GfxInfo.scrmode=frun1_5.scrmode;
				cont=0;
				for(i=0;i<RunTime.maxmodes;i++) {
					if(GfxInfo.scrmode==Modes[i].scrmode) {
						RunTime.rscreenmode=i;i=RunTime.maxmodes;
						cont=1;
					}
				}
				GfxInfo.xres=Modes[RunTime.rscreenmode].OScans[GfxInfo.oscan].MaxX;
				GfxInfo.yres=Modes[RunTime.rscreenmode].OScans[GfxInfo.oscan].MaxY;
				GfxInfo.depth=Modes[RunTime.rscreenmode].dep;
				GfxInfo.maxcol=GfxInfo.realcol=1<<GfxInfo.depth;
				GfxInfo.absmaxcol=GfxInfo.maxcol-1;
				GfxInfo.aspect=(float)(GfxInfo.xres)/(float)(GfxInfo.yres);
				GfxInfo.palbits=Modes[RunTime.rscreenmode].palbits;
				if(cont==0) {
					fracchunk=0;								/* wieder auf 0 setzen, da nur Daten wichtig  */
					RenderInfo.xb1=opxb1;RenderInfo.xb2=opxb2;
					RenderInfo.yb1=opyb1;RenderInfo.yb2=opyb2;
					cont=Question(ques[3]);
				}
				if(cont==1) {
					GfxInfo.revpal=frun1_5.revpal;				/* GfxInfo */
					GfxInfo.dither=frun1_5.dither;
					GfxInfo.ordscl=frun1_5.ordscl;
					GfxInfo.palscl=frun1_5.palscl;
					GfxInfo.palmap=frun1_5.palmap;
					GfxInfo.gfxtyp=frun1_5.gfxtyp;
					PalInfo.r[RunTime.aktpal]=frun1_5.r;				/* PalInfo */
					PalInfo.g[RunTime.aktpal]=frun1_5.g;
					PalInfo.b[RunTime.aktpal]=frun1_5.b;
					matchffnr(&RunTime.fracfunc,frun1_5.ffstr);
					matchsfnr(&RunTime.subfunc,frun1_5.sfstr);
					matchisnr(&RenderInfo.inside,frun1_5.isstr);
					matchosnr(&RenderInfo.outside,frun1_5.osstr);
					GetPalShape(PalInfo.r[RunTime.aktpal].pst,rps[RunTime.aktpal]);
					GetPalShape(PalInfo.g[RunTime.aktpal].pst,gps[RunTime.aktpal]);
					GetPalShape(PalInfo.b[RunTime.aktpal].pst,bps[RunTime.aktpal]);
					ChooseFracFunc(0);							/* ändern */
					ChooseColorFunc();
					RenderInfo.mirrorx=frun1_5.mirrorx;			/* RenderInfo */
					RenderInfo.mirrory=frun1_5.mirrory;
					RenderInfo.x1=frun1_5.x1;RenderInfo.y1=frun1_5.y1;
					RenderInfo.x2=frun1_5.x2;RenderInfo.y2=frun1_5.y2;
					RenderInfo.rot=frun1_5.rot;
					RenderInfo.par1=frun1_5.par1;RenderInfo.par2=frun1_5.par2;
					RenderInfo.par3=frun1_5.par3;RenderInfo.par4=frun1_5.par4;
					RenderInfo.bailout=frun1_5.bailout;
					RenderInfo.tpar1=frun1_5.tpar1;RenderInfo.tpar2=frun1_5.tpar2;
					RenderInfo.tpar3=frun1_5.tpar3;RenderInfo.tpar4=frun1_5.tpar4;
					RenderInfo.xb1=frun1_5.xb1;RenderInfo.yb1=frun1_5.yb1;
					RenderInfo.xb2=frun1_5.xb2;RenderInfo.yb2=frun1_5.yb2;
					RenderInfo.z=frun1_5.z;
					RenderInfo.outpar1=frun1_5.outpar1;
					RenderInfo.outpar2=frun1_5.outpar2;
					RenderInfo.inpar1=frun1_5.inpar1;
					RenderInfo.inpar2=frun1_5.inpar2;
				}
				if(fracchunk==0) { fclose(file);return;	}
				break;
			case BMHD:												/* BitMapHeader */
				if(fracchunk==0) { Message(mess[13]);fclose(file);return; }
            	fread(&bmhd,ch.chunksize,1,file);
				if(bmhd.nPlanes<1 || bmhd.nPlanes>8) { fclose(file);return;	}
				GfxInfo.xres=bmhd.w;								/* Bild-Werte eintragen */
				GfxInfo.yres=bmhd.h;
				GfxInfo.depth=bmhd.nPlanes;
				GfxInfo.maxcol=GfxInfo.realcol=1<<GfxInfo.depth;
				GfxInfo.absmaxcol=GfxInfo.maxcol-1;
				break;
			case BODY:												/* Body */
// DEBUG
				MSG("  BODY");
// DEBUG
				RunTime.picavail=1;
				opx1=RenderInfo.x1;opx2=RenderInfo.x2;				/* mit Bilddaten */
				opy1=RenderInfo.y1;opy2=RenderInfo.y2;
				opxb1=RenderInfo.xb1;opxb2=RenderInfo.xb2;
				opyb1=RenderInfo.yb1;opyb2=RenderInfo.yb2;
				if(rwindow) { CloseWindow(rwindow);rwindow=0; }
				if(rscreen) { CloseScreen(rscreen);rscreen=0; }
				RScreenTags[2].ti_Data=GfxInfo.xres;
				RScreenTags[3].ti_Data=GfxInfo.yres;
				RScreenTags[4].ti_Data=GfxInfo.depth;
				RScreenTags[8].ti_Data=GfxInfo.scrmode;
				if(GfxInfo.xres==Modes[RunTime.rscreenmode].OScans[0].MaxX && GfxInfo.yres==Modes[RunTime.rscreenmode].OScans[0].MaxY)
				{
					GfxInfo.oscan=0;
					RScreenTags[10].ti_Data=0;
					RScreenTags[9].ti_Data=FALSE;
				}
				else
				{
					if(GfxInfo.xres==Modes[RunTime.rscreenmode].OScans[1].MaxX && GfxInfo.yres==Modes[RunTime.rscreenmode].OScans[1].MaxY)
					{
						GfxInfo.oscan=1;
						RScreenTags[10].ti_Data=OSCAN_MAX;
						RScreenTags[9].ti_Data=FALSE;
					}
					else
					{
						if(GfxInfo.xres==Modes[RunTime.rscreenmode].OScans[2].MaxX && GfxInfo.yres==Modes[RunTime.rscreenmode].OScans[2].MaxY)
						{
							GfxInfo.oscan=2;
							RScreenTags[10].ti_Data=OSCAN_VIDEO;
							RScreenTags[9].ti_Data=FALSE;
						}
						else
						{
							if(GfxInfo.xres==Modes[RunTime.rscreenmode].OScans[3].MaxX && GfxInfo.yres==Modes[RunTime.rscreenmode].OScans[3].MaxY)
							{
								GfxInfo.oscan=3;
								RScreenTags[10].ti_Data=OSCAN_TEXT;
								RScreenTags[9].ti_Data=FALSE;
							}
							else
							{
								if(GfxInfo.xres==Modes[RunTime.rscreenmode].OScans[4].MaxX && GfxInfo.yres==Modes[RunTime.rscreenmode].OScans[4].MaxY)
								{
									GfxInfo.oscan=4;
									RScreenTags[10].ti_Data=OSCAN_STANDARD;
									RScreenTags[9].ti_Data=FALSE;
								}
								else
								{
									GfxInfo.oscan=1;
									RScreenTags[10].ti_Data=OSCAN_MAX;
									if(GfxInfo.xres<Modes[RunTime.rscreenmode].OScans[1].MaxX && GfxInfo.yres<Modes[RunTime.rscreenmode].OScans[1].MaxY)
										RScreenTags[9].ti_Data=FALSE;
									else RScreenTags[9].ti_Data=TRUE;
								}
							}
						}
					}
				}
				if(rscreen=OpenScreenTagList(NULL,RScreenTags))	/* und neuen auf */
				{
					rvp=&rscreen->ViewPort;
					RWindowTags[2].ti_Data=RWindowTags[ 9].ti_Data=RWindowTags[11].ti_Data=GfxInfo.xres;
					RWindowTags[3].ti_Data=RWindowTags[10].ti_Data=RWindowTags[12].ti_Data=GfxInfo.yres;
					RWindowTags[8].ti_Data=OWindowTags[8].ti_Data=IWindowTags[8].ti_Data=(ULONG)rscreen;
					if(rwindow=OpenWindowTagList(NULL,RWindowTags))
					{
						ScreenToFront(mmscr);					/* Screen verstecken */
						ActivateWindow(diwin);
						for(i=0;i<GfxInfo.realcol;i++) {
							rrp[i]=*rwindow->RPort;
							SetAPen(&rrp[i],i);
						}
						RenderInfo.xb1=0;RenderInfo.xb2=GfxInfo.xres-1;
						RenderInfo.yb1=0;RenderInfo.yb2=GfxInfo.yres-1;
						SetPaletteMode();BytesPerRow();
						MakeColorPalettes();SetColorPalette();
/* laden */
// DEBUG
						MSG("loading bitmap ...");
// DEBUG
						InitBitMap(&bm,GfxInfo.depth,GfxInfo.xres,GfxInfo.yres);
						if(GfxBase->LibNode.lib_Version >= 39) BPR2=RowBytes(GetBitMapAttr(&bm,BMA_WIDTH));
					    else BPR2=bm.BytesPerRow;
// DEBUG
						MSG2("BPR=%ld, BPR2=%ld",(ULONG)BPR,(ULONG)BPR2);
// DEBUG
						okay=TRUE;
						for(d=0;d<GfxInfo.depth;d++) {
							if(!(bm.Planes[d]=AllocRaster(GfxInfo.xres,GfxInfo.yres))) okay=FALSE;
							MSG2("planes1[%ld]=0x%08lx",(ULONG)d,(ULONG)(bm.Planes[d]));
						}
						if(okay) {
// DEBUG
							MSG("load in one go");
// DEBUG
							for(d=0;d<GfxInfo.depth;d++) bpls[d]=bm.Planes[d];
							for(y=0;y<GfxInfo.yres;y++) {
								for(d=0;d<GfxInfo.depth;d++) {
									fread(bpls[d],BPR2,1,file);
									bpls[d]+=BPR2;
								}
							}
							BltBitMap(&bm,0,0,rscreen->RastPort.BitMap,0,0,GfxInfo.xres,GfxInfo.yres,0xC0,0xFF,0l);
// DEBUG
							MSG("freeing mem");
// DEBUG
							for(d=0;d<GfxInfo.depth;d++) if(bm.Planes[d]) { FreeRaster(bm.Planes[d],GfxInfo.xres,GfxInfo.yres);bm.Planes[d]=0l; }
						}
						else {			// hat nicht geklappt -> in 32 Teile aufspalten
							for(d=0;d<GfxInfo.depth;d++) if(bm.Planes[d]) { FreeRaster(bm.Planes[d],GfxInfo.xres,GfxInfo.yres);bm.Planes[d]=0l; }
							okay=TRUE;
							n=GfxInfo.yres>>5;if((n<<5)<GfxInfo.yres) n++;
// DEBUG
							MSG1("try to load 32 segments a %d lines",(ULONG)n);
// DEBUG
							for(d=0;d<GfxInfo.depth;d++) {
								if(!(bm.Planes[d]=AllocRaster(GfxInfo.xres,n))) okay=FALSE;
								MSG2("planes1[%ld]=0x%08lx",(ULONG)d,(ULONG)(bm.Planes[d]));
							}
							if(okay) {	// und noch einmal versuchen zu speichern
								for(i=j=0;i<32;i++,j+=n) {
									for(d=0;d<GfxInfo.depth;d++) bpls[d]=bm.Planes[d];
									for(y=0;y<n;y++) {
										for(d=0;d<GfxInfo.depth;d++) {
											fread(bpls[d],BPR2,1,file);
											bpls[d]+=BPR2;
										}
									}
// DEBUG
//									MSG1("  after read %ld",(ULONG)i);
// DEBUG
									BltBitMap(&bm,0,0,rscreen->RastPort.BitMap,0,j,GfxInfo.xres,n,0xC0,0xFF,0l);
								}
							}
							else Message(mess[4]);
// DEBUG
							MSG("freeing mem");
// DEBUG
							for(d=0;d<GfxInfo.depth;d++) if(bm.Planes[d]) { FreeRaster(bm.Planes[d],GfxInfo.xres,n);bm.Planes[d]=0l; }
						}

						for(d=0;d<GfxInfo.depth;d++) planes[d]=rscreen->RastPort.BitMap->Planes[d];
						if(formsize-ch.chunksize>0) ch.chunksize+=(formsize-ch.chunksize);
// DEBUG
						MSG("ready !");
// DEBUG
					}
					else { Message(mess[5]);fclose(file);return; }
				}
				else { Message(mess[14]);fclose(file);return; }
				break;
			default:
				fseek(file,ch.chunksize,1);
			break;
		}
		formsize-=ch.chunksize;
		if(ch.chunksize&1) {			/* odd-length chunk */
			formsize--;fseek(file,1L,1);
		}
	}
	fclose(file);
// DEBUB
//	if(GfxInfo.gfxtyp==1) ScrollRaster(&rrp[0],0,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);	/* für GFX-Cards */
// DEBUB
}

/*---------------------------------------------------------------------------------------------------------*/

void SaveImage(char *filename,UBYTE mode)
{
	struct BitMapHeader bmhd;
	struct ChunkHeader ch;
	FILE *file;
	LONG subtype;
	ULONG vm,j;
	UWORD i,n;
	register UWORD y;
	register UBYTE d;
	struct BitMap bm={0};
	PLANEPTR bpls[8];
	UBYTE red,green,blue,h,okay;
	char filenote[80];
	int rth,rtm,rts;
	UWORD frun_version=150;
	struct FractalUniverse1_5 frun1_5;
	UWORD BPR2;

	if(!(file=fopen(filename, "wb"))) { Message(mess[0]);return; }

	ch.TYPE=FORM;														/* Grundstrucktur */
	ch.chunksize=(long)4L;
	if(mode==1 || mode==2)
	{
		ch.chunksize+=(long)(sizeof(frun1_5)+10L);							/* FRUN */
	}
	if(mode==0 || mode==2)
	{
		ch.chunksize+=(long)(sizeof(bmhd)+8L);								/* BMHD */
		ch.chunksize+=16L;													/* CRNG */
		ch.chunksize+=22L;													/* CCRT */
		ch.chunksize+=12L;													/* CAMG */
		ch.chunksize+=(long)(3*GfxInfo.realcol+8L);							/* CMAP */
		ch.chunksize+=(long)(BPR*GfxInfo.yres*GfxInfo.depth+8L);			/* BODY */
	}
	if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }
	subtype=ILBM;
	if(!fwrite(&subtype,sizeof(subtype),1,file)) { Message(mess[2]);fclose(file);return; }
	
	if(mode==1 || mode==2)
	{
		frun1_5.scrmode=GfxInfo.scrmode;				/* GfxInfo */
		frun1_5.revpal=GfxInfo.revpal;
		frun1_5.dither=GfxInfo.dither;
		frun1_5.ordscl=GfxInfo.ordscl;
		frun1_5.palscl=GfxInfo.palscl;
		frun1_5.palmap=GfxInfo.palmap;
		frun1_5.gfxtyp=GfxInfo.gfxtyp;
		frun1_5.r=PalInfo.r[RunTime.aktpal];					/* PalInfo */
		frun1_5.g=PalInfo.g[RunTime.aktpal];
		frun1_5.b=PalInfo.b[RunTime.aktpal];
		frun1_5.mirrorx=RenderInfo.mirrorx;				/* RenderInfo */
		frun1_5.mirrory=RenderInfo.mirrory;
		frun1_5.x1=RenderInfo.x1;frun1_5.y1=RenderInfo.y1;
		frun1_5.x2=RenderInfo.x2;frun1_5.y2=RenderInfo.y2;
		frun1_5.rot=RenderInfo.rot;
		frun1_5.par1=RenderInfo.par1;frun1_5.par2=RenderInfo.par2;
		frun1_5.par3=RenderInfo.par3;frun1_5.par4=RenderInfo.par4;
		frun1_5.bailout=RenderInfo.bailout;
		frun1_5.tpar1=RenderInfo.tpar1;frun1_5.tpar2=RenderInfo.tpar2;
		frun1_5.tpar3=RenderInfo.tpar3;frun1_5.tpar4=RenderInfo.tpar4;
		frun1_5.xb1=RenderInfo.xb1;frun1_5.yb1=RenderInfo.yb1;
		frun1_5.xb2=RenderInfo.xb2;frun1_5.yb2=RenderInfo.yb2;
		frun1_5.z=RenderInfo.z;
		frun1_5.outpar1=RenderInfo.outpar1;
		frun1_5.outpar2=RenderInfo.outpar2;
		frun1_5.inpar1=RenderInfo.inpar1;
		frun1_5.inpar2=RenderInfo.inpar2;
		for(i=0;i<19;i++) frun1_5.ffstr[i]=frun1_5.sfstr[i]=frun1_5.isstr[i]=frun1_5.osstr[i]=32;
		frun1_5.ffstr[19]=frun1_5.sfstr[19]=frun1_5.isstr[19]=frun1_5.osstr[19]=0;
		matchnrff(&RunTime.fracfunc,frun1_5.ffstr);
		matchnrsf(&RunTime.subfunc,frun1_5.sfstr);
		matchnris(&RenderInfo.inside,frun1_5.isstr);
		matchnros(&RenderInfo.outside,frun1_5.osstr);
		ch.TYPE=FRUN;														/* FRUN */
		ch.chunksize=(long)(sizeof(frun1_5)+2);
		if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }
		if(fwrite(&frun_version,2,1,file))
		{
			if(!fwrite(&frun1_5,sizeof(frun1_5),1,file)) { Message(mess[2]);fclose(file);return; }
		}
		else { Message(mess[2]);fclose(file);return; }
	}
	if(mode==0 || mode==2)
	{
		ch.TYPE=BMHD;													/* BMHD */
		ch.chunksize=(long)(sizeof(bmhd));
		if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }
		bmhd.x=bmhd.y=0;
		bmhd.masking=0;
		bmhd.compression=0;
		bmhd.pad1=0;
		bmhd.transparentColor=0;
		bmhd.w=bmhd.pageWidth=GfxInfo.xres;
		bmhd.h=bmhd.pageHeight=GfxInfo.yres;
		bmhd.nPlanes=GfxInfo.depth;
		bmhd.xAspect=(UBYTE)(((float)GfxInfo.xres/(float)GfxInfo.yres)*100.0);
		bmhd.yAspect=(UBYTE)(((float)GfxInfo.yres/(float)GfxInfo.xres)*100.0);
		if(!fwrite(&bmhd,sizeof(bmhd),1,file)) { Message(mess[2]);fclose(file);return; }

		ch.TYPE=CRNG;													/* CRNG */
		ch.chunksize=8L;
		if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }
		n=0;i=13653/(cdata.rate+1);
		fwrite(&n,2,1,file);	/* pad - not used */
		fwrite(&i,2,1,file);	/* rate */
		n=1;
		fwrite(&n,2,1,file);	/* active */
		h=0;
		fwrite(&h,1,1,file);	/* Cyclestart = 0 */
		h=GfxInfo.realcol-1;
		fwrite(&h,1,1,file);	/* Cycleend = maxcolor */

		ch.TYPE=CCRT;													/* CCRT */
		ch.chunksize=14L;
		if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }
		n=cdata.dir;
		fwrite(&n,2,1,file);	/* direction */
		h=0;
		fwrite(&h,1,1,file);	/* Cyclestart = 0 */
		h=GfxInfo.realcol-1;
		fwrite(&h,1,1,file);	/* Cycleend = maxcolor */
		j=0;
		fwrite(&j,4,1,file);	/* seconds */
		j=100/(50/cdata.rate);
		fwrite(&j,4,1,file);	/* milliseconds */
		n=0;
		fwrite(&n,2,1,file);	/* pad - not used */

		ch.TYPE=CAMG;												/* CAMG */
		ch.chunksize=4L;
		if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }
		vm=GfxInfo.scrmode;/*&CAMGMASK;*/
		if(!fwrite(&vm,4,1,file)) { Message(mess[2]);fclose(file);return; }

		ch.TYPE=CMAP;													/* CMAP */
		ch.chunksize=(long)(3*GfxInfo.realcol);
		if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }
		for(i=0;i<GfxInfo.realcol;i++)
		{
			if(GfxInfo.palbits<5)
			{
				red  =(colors4[RunTime.aktpal][i]&0x0F00)>>4;
				green=(colors4[RunTime.aktpal][i]&0x00F0);
				blue =(colors4[RunTime.aktpal][i]&0x000F)<<4;
			}
			if(GfxInfo.palbits>4)
			{
				red  =(UBYTE)(colors32[RunTime.aktpal].Entry[i].r&0xFF);
				green=(UBYTE)(colors32[RunTime.aktpal].Entry[i].g&0xFF);
				blue =(UBYTE)(colors32[RunTime.aktpal].Entry[i].b&0xFF);
			}
			if(!fwrite(&red,1,1,file)) { Message(mess[2]);fclose(file);return; }
			if(!fwrite(&green,1,1,file)) { Message(mess[2]);fclose(file);return; }
			if(!fwrite(&blue,1,1,file)) { Message(mess[2]);fclose(file);return; }
		}

		ch.TYPE=BODY;													/* BODY */
		ch.chunksize=(long)(BPR*GfxInfo.yres*GfxInfo.depth);
		if(!fwrite(&ch,sizeof(struct ChunkHeader),1,file)) { Message(mess[2]);fclose(file);return; }

/* force refresh on GFX-boards */
		if(GfxInfo.gfxtyp==1) ScrollRaster(&rrp[0],0,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);

/* speichern */
// DEBUG
		MSG("saving ...");
// DEBUG
		InitBitMap(&bm,GfxInfo.depth,GfxInfo.xres,GfxInfo.yres);
		if(GfxBase->LibNode.lib_Version >= 39) BPR2=RowBytes(GetBitMapAttr(&bm,BMA_WIDTH));
	    else BPR2=bm.BytesPerRow;
		okay=TRUE;
		for(d=0;d<GfxInfo.depth;d++) if(!(bm.Planes[d]=AllocRaster(GfxInfo.xres,GfxInfo.yres))) okay=FALSE;
		if(okay) {		// hat geklappt -> speichern
// DEBUG
			MSG("save in one go");
// DEBUG
			BltBitMap(rscreen->RastPort.BitMap,0,0,&bm,0,0,GfxInfo.xres,GfxInfo.yres,0xC0,0xFF,0l);
			for(d=0;d<GfxInfo.depth;d++) bpls[d]=bm.Planes[d];
			for(y=0;y<GfxInfo.yres;y++) {
				for(d=0;d<GfxInfo.depth;d++) {
					fwrite(bpls[d],BPR2,1,file);
					bpls[d]+=BPR2;
				}
			}
			for(d=0;d<GfxInfo.depth;d++) if(bm.Planes[d]) FreeRaster(bm.Planes[d],GfxInfo.xres,GfxInfo.yres);
		}
		else {			// hat nicht geklappt -> in 32 Teile aufspalten
			for(d=0;d<GfxInfo.depth;d++) if(bm.Planes[d]) FreeRaster(bm.Planes[d],GfxInfo.xres,GfxInfo.yres);
			okay=TRUE;
			n=GfxInfo.yres>>5;if((n<<5)<GfxInfo.yres) n++;
// DEBUG
			MSG1("try to save 32 segments a %ld lines",(ULONG)n);
// DEBUG
			for(d=0;d<GfxInfo.depth;d++) if(!(bm.Planes[d]=AllocRaster(GfxInfo.xres,n))) okay=FALSE;
			if(okay) {	// und noch einmal versuchen zu speichern
				for(i=j=0;i<32;i++,j+=n) {
					BltBitMap(rscreen->RastPort.BitMap,0,j,&bm,0,0,GfxInfo.xres,n,0xC0,0xFF,0l);
					for(d=0;d<GfxInfo.depth;d++) bpls[d]=bm.Planes[d];
					for(y=0;y<n;y++) {
						for(d=0;d<GfxInfo.depth;d++) {
							fwrite(bpls[d],BPR2,1,file);
							bpls[d]+=BPR2;
						}
					}
				}
			}
			else Message(mess[4]);
			for(d=0;d<GfxInfo.depth;d++) if(bm.Planes[d]) FreeRaster(bm.Planes[d],GfxInfo.xres,n);
// DEBUG
			MSG("ready !");
// DEBUG
		}
	}
	fclose(file);
	rtm=rendertime/60;
	rts=rendertime%60;
	rth=rtm/60;
	rtm%=60;
	sprintf(filenote,"picture by FRACTAL-UNIVERSE, Gfx : %d.%d.%d, Time : %d:%d:%d",GfxInfo.xres,GfxInfo.yres,GfxInfo.realcol,rth,rtm,rts);
	if(mode==0 || mode==2) SetComment(filename,filenote);
}

/*---------------------------------------------------------------------------------------------------------*/

void matchnrff(UBYTE *nr,char *name)					/* Zuweisungsfunktionen */
{
	strcpy(name,fflist[match_nr2ix(*nr,ffanz,fflist)].name);
}

void matchffnr(UBYTE *nr,char *name)
{
	*nr=match_name2ix(name,ffanz,fflist);
}

void matchnrsf(UBYTE *nr,char *name)
{
	switch(RunTime.fracfunc)
	{
		case 0:				/* InvCircle */
			strcpy(name,sf0list[match_nr2ix(*nr,sf0anz,sf0list)].name);break;
		case 1:				/* NormCircle */
			strcpy(name,sf1list[match_nr2ix(*nr,sf1anz,sf1list)].name);break;
		case 2:				/* Formula */
			strcpy(name,Formulas[*nr]);break;
		case 3:				/* InvNewton */
			strcpy(name,sf3list[match_nr2ix(*nr,sf3anz,sf3list)].name);break;
		case 4:				/* NormNewton */
			strcpy(name,sf4list[match_nr2ix(*nr,sf4anz,sf4list)].name);break;
		case 5:				/* InvFixPlaneC */
			strcpy(name,sf5list[match_nr2ix(*nr,sf5anz,sf5list)].name);break;
		case 6:				/* InvVarPlaneC */
			strcpy(name,sf6list[match_nr2ix(*nr,sf6anz,sf6list)].name);break;
		case 7:				/* NormFixPlaneC */
			strcpy(name,sf7list[match_nr2ix(*nr,sf7anz,sf7list)].name);break;
		case 8:				/* NormFixPlaneC */
			strcpy(name,sf8list[match_nr2ix(*nr,sf8anz,sf8list)].name);break;
	}
}

void matchsfnr(UBYTE *nr,char *name)
{
	register UBYTE i;

	switch(RunTime.fracfunc)
	{
		case 0:				/* InvCircle */
			*nr=match_name2ix(name,sf0anz,sf0list);break;
		case 1:				/* NormCircle */
			*nr=match_name2ix(name,sf1anz,sf1list);break;
		case 2:				/* Formula */
			for(i=0;i<200;i++) if(!strcmp(Formulas[i],name)) { *nr=i;i=200; }
			break;
		case 3:				/* InvNewton */
			*nr=match_name2ix(name,sf3anz,sf3list);break;
		case 4:				/* NormNewton */
			*nr=match_name2ix(name,sf4anz,sf4list);break;
		case 5:				/* InvFixPlaneC */
			*nr=match_name2ix(name,sf5anz,sf5list);break;
		case 6:				/* InvVarPlaneC */
			*nr=match_name2ix(name,sf6anz,sf6list);break;
		case 7:				/* NormFixPlaneC */
			*nr=match_name2ix(name,sf7anz,sf7list);break;
		case 8:				/* NormFixPlaneC */
			*nr=match_name2ix(name,sf8anz,sf8list);break;
	}
}

void matchnris(UBYTE *nr,char *name)
{
	strcpy(name,insidelist[match_nr2ix(*nr,isanz,insidelist)].name);
}

void matchisnr(UBYTE *nr,char *name)
{
	*nr=match_name2ix(name,isanz,insidelist);
}

void matchnros(UBYTE *nr,char *name)
{
	strcpy(name,outsidelist[match_nr2ix(*nr,osanz,outsidelist)].name);
}

void matchosnr(UBYTE *nr,char *name)
{
	*nr=match_name2ix(name,osanz,outsidelist);
}

/*---------------------------------------------------------------------------------------------------------*/

void convert15_13(struct FractalUniverse1_5 *frun1_5,struct FractalUniverse1_3 *frun1_3)
{
	frun1_5->scrmode=	frun1_3->scrmode;				/* GfxInfo */
	frun1_5->revpal=	frun1_3->revpal;
	frun1_5->dither=	frun1_3->dither;
	frun1_5->ordscl=	frun1_3->ordscl;
	frun1_5->palscl=	frun1_3->palscl;
	frun1_5->palmap=	frun1_3->palmap;
	frun1_5->gfxtyp=	frun1_5->gfxtyp;
	frun1_5->r=			frun1_3->r;						/* PalInfo */
	frun1_5->g=			frun1_3->g;
	frun1_5->b=			frun1_3->b;
	frun1_5->mirrorx=	frun1_3->mirrorx;				/* RenderInfo */
	frun1_5->mirrory=	frun1_3->mirrory;
	frun1_5->x1=		frun1_3->x1;
	frun1_5->y1=		frun1_3->y1;
	frun1_5->x2=		frun1_3->x2;
	frun1_5->y2=		frun1_3->y2;
	frun1_5->rot=		frun1_3->rot;
	frun1_5->par1=		frun1_3->par1;
	frun1_5->par2=		frun1_3->par2;
	frun1_5->par3=		frun1_3->par3;
	frun1_5->par4=		frun1_3->par4;
	frun1_5->bailout=	frun1_3->bailout;
	frun1_5->tpar1=		frun1_3->tpar1;
	frun1_5->tpar2=		frun1_3->tpar2;
	frun1_5->tpar3=		frun1_3->tpar3;
	frun1_5->tpar4=		frun1_3->tpar4;
	frun1_5->xb1=		frun1_3->xb1;
	frun1_5->yb1=		frun1_3->yb1;
	frun1_5->xb2=		frun1_3->xb2;
	frun1_5->yb2=		frun1_3->yb2;
	frun1_5->z=			frun1_3->z;
	frun1_5->outpar1=	frun1_3->outpar1;
	frun1_5->outpar2=	0;
	frun1_5->inpar1=	frun1_3->inpar1;
	frun1_5->inpar2=	0;
	strcpy(frun1_5->ffstr,frun1_3->ffstr);
	strcpy(frun1_5->sfstr,frun1_3->sfstr);
	strcpy(frun1_5->isstr,frun1_3->isstr);
	strcpy(frun1_5->osstr,frun1_3->osstr);
}
