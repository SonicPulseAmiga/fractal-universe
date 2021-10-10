/****h* FractalUniverse/FU-GFXF.C [1.68] *
*
*  NAME
*    FU-GFXF.C
*  COPYRIGHT
*    $VER: FU-GFXF.C 1.68 (25.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    Graphical Functions
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    24.Oct.2001
*  MODIFICATION HISTORY
*    25.Oct.2001	V 1.68	most recent version
*    24.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

//-- includes -----------------------------------------------------------------

#define FU_GFXF_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void SetPaletteMode(void);
void MakeColorPalettes(void);
void SetColorPalette(void);
void GetPalShape(UBYTE shtype,float *buf);
void DrawPalShape(struct RastPort rp,UBYTE c,float *buf);
void DrawColorRange(struct RastPort rp);
void SetColorRange(UBYTE nr);
UBYTE GetBrightestCol(void);
UBYTE GetDarkestCol(void);
void AssignGfxFuncs(void);
void AssignTurboGfxFuncs(void);
void AssignSystemGfxFuncs(void);
void MyWritePixel(UWORD x,UWORD y,UBYTE c);
void Zoom(UBYTE ztype,UBYTE zmode,UBYTE zsnap,UWORD *x1,UWORD *y1,UWORD *x2,UWORD *y2);
void Pick(double *parx,double *pary);

//-- globals ------------------------------------------------------------------

UWORD				colors4[11][512];
struct ColorSet32	colors32[11];
#include "FU-GFXF-Pattern.h"
double derr;

//-- definitions --------------------------------------------------------------

void SetPaletteMode(void)
{
	register UWORD i;

	GfxInfo.maxcol=GfxInfo.realcol;

	if(!GfxInfo.revpal)
	{
		for(i=0;i<GfxInfo.maxcol;i++)
		{
			col[i]=i;
			col[GfxInfo.maxcol+i]=i;
		}
	}
	if(GfxInfo.revpal)
	{
		for(i=0;i<GfxInfo.maxcol;i++)
		{
			col[i]=i;
			col[(GfxInfo.maxcol<<1)-(i+1)]=i;
		}
		GfxInfo.maxcol<<=1;
	}
	GfxInfo.absmaxcol=GfxInfo.maxcol-1;
}

void MakeColorPalettes(void)
{
	register UWORD i;
	register UBYTE j;
	ULONG cr,cg,cb;
	double psf;
	UBYTE rscf,gscf,bscf;

	psf=256.0/(double)GfxInfo.realcol;
	for(j=0;j<10;j++) {
		rscf=PalInfo.r[j].scx*psf;
		gscf=PalInfo.g[j].scx*psf;
		bscf=PalInfo.b[j].scx*psf;
		switch(GfxInfo.palmap) {
			case 0:							/* Linear */
				for(i=0;i<GfxInfo.realcol;i++) {
					if(GfxInfo.palbits<5) {
						cr=((ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255)>>4;
						cg=((ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255)>>4;
						cb=((ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255)>>4;
						colors4[j][i]=colors4[j][i+GfxInfo.realcol]=((UWORD)cr<<8)|((UWORD)cg<<4)|(UWORD)cb;
					}
					if(GfxInfo.palbits>4) {
						cr=(ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255;
						cg=(ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255;
						cb=(ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255;
						colors32[j].Entry[i].r=(ULONG)((0xFFFFFFFF/255)*cr);
						colors32[j].Entry[i].g=(ULONG)((0xFFFFFFFF/255)*cg);
						colors32[j].Entry[i].b=(ULONG)((0xFFFFFFFF/255)*cb);
					}
					PalInfo.r[j].xoff=(PalInfo.r[j].xoff+rscf)&255;
					PalInfo.g[j].xoff=(PalInfo.g[j].xoff+gscf)&255;
					PalInfo.b[j].xoff=(PalInfo.b[j].xoff+bscf)&255;
				}
				break;
			case 1:							/* Broken1 */
				for(i=0;i<GfxInfo.realcol;i+=2) {
					if(GfxInfo.palbits<5) {
						cr=((ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255)>>4;
						cg=((ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255)>>4;
						cb=((ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255)>>4;
						colors4[j][i]=colors4[j][i+GfxInfo.realcol]=((UWORD)cr<<8)|((UWORD)cg<<4)|(UWORD)cb;
					}
					if(GfxInfo.palbits>4) {
						cr=(ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255;
						cg=(ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255;
						cb=(ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255;
						colors32[j].Entry[i].r=(ULONG)((0xFFFFFFFF/255)*cr);
						colors32[j].Entry[i].g=(ULONG)((0xFFFFFFFF/255)*cg);
						colors32[j].Entry[i].b=(ULONG)((0xFFFFFFFF/255)*cb);
					}
					PalInfo.r[j].xoff=(PalInfo.r[j].xoff+rscf)&255;
					PalInfo.g[j].xoff=(PalInfo.g[j].xoff+gscf)&255;
					PalInfo.b[j].xoff=(PalInfo.b[j].xoff+bscf)&255;
				}
				for(i=1;i<GfxInfo.realcol;i+=2) {
					if(GfxInfo.palbits<5) {
						cr=((ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255)>>4;
						cg=((ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255)>>4;
						cb=((ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255)>>4;
						colors4[j][i]=colors4[j][i+GfxInfo.realcol]=((UWORD)cr<<8)|((UWORD)cg<<4)|(UWORD)cb;
					}
					if(GfxInfo.palbits>4) {
						cr=(ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255;
						cg=(ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255;
						cb=(ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255;
						colors32[j].Entry[i].r=(ULONG)((0xFFFFFFFF/255)*cr);
						colors32[j].Entry[i].g=(ULONG)((0xFFFFFFFF/255)*cg);
						colors32[j].Entry[i].b=(ULONG)((0xFFFFFFFF/255)*cb);
					}
					PalInfo.r[j].xoff=(PalInfo.r[j].xoff+rscf)&255;
					PalInfo.g[j].xoff=(PalInfo.g[j].xoff+gscf)&255;
					PalInfo.b[j].xoff=(PalInfo.b[j].xoff+bscf)&255;
				}
				break;
			case 2:							/* Broken2 */
				for(i=0;i<GfxInfo.realcol;i+=2) {
					if(GfxInfo.palbits<5) {
						cr=((ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255)>>4;
						cg=((ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255)>>4;
						cb=((ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255)>>4;
						colors4[j][i]=colors4[j][i+GfxInfo.realcol]=((UWORD)cr<<8)|((UWORD)cg<<4)|(UWORD)cb;
					}
					if(GfxInfo.palbits>4) {
						cr=(ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255;
						cg=(ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255;
						cb=(ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255;
						colors32[j].Entry[i].r=(ULONG)((0xFFFFFFFF/255)*cr);
						colors32[j].Entry[i].g=(ULONG)((0xFFFFFFFF/255)*cg);
						colors32[j].Entry[i].b=(ULONG)((0xFFFFFFFF/255)*cb);
					}
					PalInfo.r[j].xoff=(PalInfo.r[j].xoff+rscf)&255;
					PalInfo.g[j].xoff=(PalInfo.g[j].xoff+gscf)&255;
					PalInfo.b[j].xoff=(PalInfo.b[j].xoff+bscf)&255;
				}
				for(i=(GfxInfo.realcol-1);i>0;i-=2) {
					if(GfxInfo.palbits<5) {
						cr=((ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255)>>4;
						cg=((ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255)>>4;
						cb=((ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255)>>4;
						colors4[j][i]=colors4[j][i+GfxInfo.realcol]=((UWORD)cr<<8)|((UWORD)cg<<4)|(UWORD)cb;
					}
					if(GfxInfo.palbits>4) {
						cr=(ULONG)(256*(rps[j][PalInfo.r[j].xoff]/PalInfo.r[j].scy)+PalInfo.r[j].yoff)&255;
						cg=(ULONG)(256*(gps[j][PalInfo.g[j].xoff]/PalInfo.g[j].scy)+PalInfo.g[j].yoff)&255;
						cb=(ULONG)(256*(bps[j][PalInfo.b[j].xoff]/PalInfo.b[j].scy)+PalInfo.b[j].yoff)&255;
						colors32[j].Entry[i].r=(ULONG)((0xFFFFFFFF/255)*cr);
						colors32[j].Entry[i].g=(ULONG)((0xFFFFFFFF/255)*cg);
						colors32[j].Entry[i].b=(ULONG)((0xFFFFFFFF/255)*cb);
					}
					PalInfo.r[j].xoff=(PalInfo.r[j].xoff+rscf)&255;
					PalInfo.g[j].xoff=(PalInfo.g[j].xoff+gscf)&255;
					PalInfo.b[j].xoff=(PalInfo.b[j].xoff+bscf)&255;
				}
				break;
		}
		colors32[j].NumColors=GfxInfo.realcol;
		colors32[j].FirstColor=0;
		colors32[j].Terminator=0;
		if(GfxInfo.realcol<256) {
			colors32[j].Entry[GfxInfo.realcol].r=0L;
			colors32[j].Entry[GfxInfo.realcol].g=0L;
			colors32[j].Entry[GfxInfo.realcol].b=0L;
		}
	}
	for(i=0;i<GfxInfo.realcol;i++) {
		if(GfxInfo.palbits<5) {
			cr=(ULONG)((double)i*16.0/GfxInfo.realcol);
			colors4[10][i]=((UWORD)cr<<8)|((UWORD)cr<<4)|(UWORD)cr;
		}
		if(GfxInfo.palbits>4) {
			cr=(ULONG)((double)i*256.0/GfxInfo.realcol);
			colors32[j].Entry[i].r=(ULONG)((0xFFFFFFFF/255)*cr);
			colors32[j].Entry[i].g=(ULONG)((0xFFFFFFFF/255)*cr);
			colors32[j].Entry[i].b=(ULONG)((0xFFFFFFFF/255)*cr);
		}
	}
	colors32[j].NumColors=GfxInfo.realcol;
	colors32[j].FirstColor=0;
	colors32[j].Terminator=0;
	if(GfxInfo.realcol<256) {
		colors32[j].Entry[GfxInfo.realcol].r=0L;
		colors32[j].Entry[GfxInfo.realcol].g=0L;
		colors32[j].Entry[GfxInfo.realcol].b=0L;
	}
}

void SetColorPalette(void)
{
	if(GfxInfo.palbits<5) {
		LoadRGB4(rvp,&colors4[RunTime.aktpal][0],GfxInfo.realcol);
		MakeVPort(view,rvp);MrgCop(view);LoadView(view);
	}
	if(GfxInfo.palbits>4) LoadRGB32(rvp,(ULONG *)(&colors32[RunTime.aktpal]));
}

void GetPalShape(UBYTE shtype,float *buf)
{
	register UWORD i;
	float f;

	switch(shtype) {
		case 0:						/* Triangle 1 */
			f=0.0078125;
			for(i=  0;i<128;i++) buf[i]=i*f;
			for(i=128;i<256;i++) buf[i]=(128-(i-127))*f;
			break;
		case 1:						/* Triangle 2 */
			f=0.0052088333;
			for(i=  0;i<192;i++) buf[i]=i*f;
			f=0.015625;
			for(i=192;i<256;i++) buf[i]=(64-(i-191))*f;
			break;
		case 2:						/* Triangle 3 */
			f=0.015625;
			for(i= 0;i< 64;i++) buf[i]=i*f;
			f=0.0052088333;
			for(i=64;i<256;i++) buf[i]=(192-(i-63))*f;
			break;
		case 3:						/* Sine 1 */
			f=0.012271846;
			for(i=0;i<256;i++) buf[i]=0.99999*sin(i*f);
			break;
		case 4:						/* Sine 2 */
			f=0.012271846;
			for(i=0;i<256;i++) buf[i]=0.99999-sin(i*f);
			break;
		case 5:						/* Sine 3 */
			f=0.024543692;
			for(i=0;i<256;i++) buf[i]=0.49999*(sin(i*f)+1.0);
			break;
		case 6:						/* Sine 1 Up */
			f=0.006135923;
			for(i=0;i<256;i++) buf[i]=0.99999*sin(i*f);
			break;
		case 7:						/* Sine 1 Down */
			f=0.006135923;
			for(i=0;i<256;i++) buf[i]=0.99999*sin(1.570796327+i*f);
			break;
		case 8:						/* Sine 2 Down */
			f=0.006135923;
			for(i=0;i<256;i++) buf[i]=0.99999-sin(i*f);
			break;
		case 9:						/* Sine 2 Up */
			f=0.006135923;
			for(i=0;i<256;i++) buf[i]=0.99999-sin(1.570796327+i*f);
			break;
		case 10:						/* Balken mitte */
			for(i=0;i<256;i++) buf[i]=0.5;
			break;
		case 11:					/* Ramp Up */
			f=0.00390624;
			for(i=0;i<256;i++) buf[i]=i*f;
			break;
		case 12:					/* Ramp Down */
			f=0.00390624;
			for(i=0;i<256;i++) buf[i]=0.99999-i*f;
			break;
		case 13:					/* Roof 1.1 */
			f=0.011764706;
			for(i=0;i<85;i++) buf[i]=i*f;
			for(i=85;i<171;i++) buf[i]=0.99999;
			for(i=171;i<256;i++) buf[i]=(84-(i-171))*f;
			break;
		case 14:					/* Roof 1.2 */
			f=0.011764706;
			for(i=0;i<85;i++) buf[i]=(84-i)*f;
			for(i=85;i<171;i++) buf[i]=0;
			for(i=171;i<256;i++) buf[i]=(i-171)*f;
			break;
		case 15:					/* Roof 2.1 */
			f=0.023809524;
			for(i=0;i<42;i++) buf[i]=i*f;
			for(i=42;i<214;i++) buf[i]=0.99999;
			for(i=214;i<256;i++) buf[i]=(41-(i-214))*f;
			break;
		case 16:					/* Roof 2.2 */
			f=0.023809524;
			for(i=0;i<42;i++) buf[i]=(41-i)*f;
			for(i=42;i<214;i++) buf[i]=0;
			for(i=214;i<256;i++) buf[i]=(i-214)*f;
			break;
		case 17:					/* Roof 3.1 */
			f=0.009803922;
			for(i=0;i<102;i++) buf[i]=i*f;
			for(i=102;i<154;i++) buf[i]=0.99999;
			for(i=154;i<256;i++) buf[i]=(101-(i-154))*f;
			break;
		case 18:					/* Roof 3.2 */
			f=0.009803922;
			for(i=0;i<102;i++) buf[i]=(101-i)*f;
			for(i=102;i<154;i++) buf[i]=0;
			for(i=154;i<256;i++) buf[i]=(i-154)*f;
			break;
		case 19:					/* Half Ramp Up And Hold */
			f=0.0078125;
			for(i=0;i<128;i++) buf[i]=i*f;
			for(i=128;i<256;i++) buf[i]=0.99999;
			break;
		case 20:					/* Hold And Half Ramp Down */
			f=0.0078125;
			for(i=0;i<128;i++) buf[i]=0.99999;
			for(i=128;i<256;i++) buf[i]=0.99999-(i-128)*f;
			break;
		case 21:					/* Hold And Half Ramp Up */
			f=0.0078125;
			for(i=0;i<128;i++) buf[i]=0.0;
			for(i=128;i<256;i++) buf[i]=(i-128)*f;
			break;
		case 22:					/* Half Ramp Down And Hold */
			f=0.0078125;
			for(i=0;i<128;i++) buf[i]=0.99999-(i-128)*f;
			for(i=128;i<256;i++) buf[i]=0.0;
			break;
	}
}

void DrawPalShape(struct RastPort rp,UBYTE c,float *buf)
{
	UBYTE i,xoff;
	float fc;

	switch(c) {
		case 0:		/* Red */
			SetAPen(&rp,0);RectFill(&rp,RunTime.scx[36],RunTime.scy[90],RunTime.scx[163],RunTime.scy[139]);
			SetAPen(&rp,1);
			xoff=PalInfo.r[RunTime.aktpal].xoff;
			fc=256.0/(float)PalInfo.r[RunTime.aktpal].scy;
			PalInfo.r[RunTime.aktpal].scx<<=1;
			for(i=0;i<128;i++)
			{																									/* &0xFF wird vom GlobalOptimizer wegoptimiert bzw. verändert */
				WritePixel(&rp,RunTime.scx[36+i],RunTime.scy[139-(UBYTE)((float)((PalInfo.r[RunTime.aktpal].yoff+(UBYTE)(fc*buf[xoff]))%256)/5.12)]);
				xoff=(xoff+PalInfo.r[RunTime.aktpal].scx)&255;
			}
			PalInfo.r[RunTime.aktpal].scx>>=1;
			DrawGad(rp,RunTime.scx[35],RunTime.scy[89],RunTime.scx[129],RunTime.scy[51],FALSE);
			break;
		case 1:		/* Green */
			SetAPen(&rp,0);RectFill(&rp,RunTime.scx[211],RunTime.scy[90],RunTime.scx[338],RunTime.scy[139]);
			SetAPen(&rp,1);
			xoff=PalInfo.g[RunTime.aktpal].xoff;
			fc=256.0/(float)PalInfo.g[RunTime.aktpal].scy;
			PalInfo.g[RunTime.aktpal].scx<<=1;
			for(i=0;i<128;i++)
			{
				WritePixel(&rp,RunTime.scx[211+i],RunTime.scy[139-(UBYTE)((float)((PalInfo.g[RunTime.aktpal].yoff+(UBYTE)(fc*buf[xoff]))%256)/5.12)]);
				xoff=(xoff+PalInfo.g[RunTime.aktpal].scx)&255;
			}
			PalInfo.g[RunTime.aktpal].scx>>=1;
			DrawGad(rp,RunTime.scx[210],RunTime.scy[89],RunTime.scx[129],RunTime.scy[51],FALSE);
			break;
		case 2:		/* Blue */
			SetAPen(&rp,0);RectFill(&rp,RunTime.scx[386],RunTime.scy[90],RunTime.scx[513],RunTime.scy[139]);
			SetAPen(&rp,1);
			xoff=PalInfo.b[RunTime.aktpal].xoff;
			fc=256.0/(float)PalInfo.b[RunTime.aktpal].scy;
			PalInfo.b[RunTime.aktpal].scx<<=1;
			for(i=0;i<128;i++)
			{
				WritePixel(&rp,RunTime.scx[386+i],RunTime.scy[139-(UBYTE)((float)((PalInfo.b[RunTime.aktpal].yoff+(UBYTE)(fc*buf[xoff]))%256)/5.12)]);
				xoff=(xoff+PalInfo.b[RunTime.aktpal].scx)&255;
			}
			PalInfo.b[RunTime.aktpal].scx>>=1;
			DrawGad(rp,RunTime.scx[385],RunTime.scy[89],RunTime.scx[129],RunTime.scy[51],FALSE);
			break;
	}
}

void DrawColorRange(struct RastPort rp)
{
	register UBYTE i,j,k,l;
	ULONG error=0,col=4<<8,acol,step;
	UWORD xoff=27,xt,xt2,yoff=22,yt,yt2;
	UWORD gx=RunTime.scx[14]-1,gy=RunTime.scy[4]-1;

	step=(1L<<fuprefs_gui.depth)-5;

	for(i=0;i<8;i++)					/* Farbtöpfe y */
	{
		yt2=RunTime.scy[yoff+(i*5)]+1;
		for(j=0;j<32;j++)				/* Farbtöpfe x */
		{
			yt=yt2;
			xt2=RunTime.scx[xoff+(j*15)]+1;
			for(k=0;k<gy;k++)		/* Farbtopf y */
			{
				xt=xt2;
				for(l=0;l<gx;l++)	/* Farbtopf x */
				{
					error=(acol=col+error)&0xFF;
					SetAPen(&rp,(acol>>8));WritePixel(&rp,xt++,yt);
				}
				yt++;
			}
			col+=step;
		}
	}
}

void SetColorRange(UBYTE nr)
{
	register UBYTE i;
	ULONG cr,cg,cb;
	double psf;
	UBYTE rscf,gscf,bscf;
	WORD rxoff,gxoff,bxoff;
	WORD nrcol=(1L<<fuprefs_gui.depth)-4;

	rxoff=PalInfo.r[nr].xoff;
	gxoff=PalInfo.g[nr].xoff;
	bxoff=PalInfo.b[nr].xoff;

	psf=256.0/nrcol;
	rscf=PalInfo.r[nr].scx*psf;
	gscf=PalInfo.g[nr].scx*psf;
	bscf=PalInfo.b[nr].scx*psf;

	for(i=0;i<nrcol;i++)
	{
//		if(fuprefs_gui.palbits<5)
//		{
			cr=((int)(256*(rps[nr][PalInfo.r[nr].xoff]/PalInfo.r[nr].scy)+PalInfo.r[nr].yoff)&255)>>4;
			cg=((int)(256*(gps[nr][PalInfo.g[nr].xoff]/PalInfo.g[nr].scy)+PalInfo.g[nr].yoff)&255)>>4;
			cb=((int)(256*(bps[nr][PalInfo.b[nr].xoff]/PalInfo.b[nr].scy)+PalInfo.b[nr].yoff)&255)>>4;
			scr_colors4[i+4]=((UWORD)cr<<8)|((UWORD)cg<<4)|(UWORD)cb;
//		}
//		if(fuprefs_gui.palbits>4)
//		{
//			cr=(int)(256*(rps[nr][PalInfo.r[nr].xoff]/PalInfo.r[nr].scy)+PalInfo.r[nr].yoff)&255;
//			cg=(int)(256*(gps[nr][PalInfo.g[nr].xoff]/PalInfo.g[nr].scy)+PalInfo.g[nr].yoff)&255;
//			cb=(int)(256*(bps[nr][PalInfo.b[nr].xoff]/PalInfo.b[nr].scy)+PalInfo.b[nr].yoff)&255;
//			colors32[nr].Entry[i+4].r=(ULONG)((0xFFFFFFFF/255)*cr);
//			colors32[nr].Entry[i+4].g=(ULONG)((0xFFFFFFFF/255)*cg);
//			colors32[nr].Entry[i+4].b=(ULONG)((0xFFFFFFFF/255)*cb);
//		}
		PalInfo.r[nr].xoff=(PalInfo.r[nr].xoff+rscf)&255;
		PalInfo.g[nr].xoff=(PalInfo.g[nr].xoff+gscf)&255;
		PalInfo.b[nr].xoff=(PalInfo.b[nr].xoff+bscf)&255;
	}
	PalInfo.r[nr].xoff=rxoff;
	PalInfo.g[nr].xoff=gxoff;
	PalInfo.b[nr].xoff=bxoff;

//	if(fuprefs_gui.palbits<5)
//	{
		LoadRGB4(mvp,&scr_colors4[0],nrcol+4);
		MakeVPort(view,mvp);MrgCop(view);LoadView(view);
//	}
//	if(fuprefs_gui.palbits>4) LoadRGB32(mvp,&scr_colors32);
}


UBYTE GetBrightestCol(void)
{
	register UWORD i;
	UBYTE col=0,cr,cg,cb;
	float cc,bc,bd;

	if(GfxInfo.palbits<5)
	{
		col=0;bc=bd=0.0;
		for(i=0;i<GfxInfo.realcol;i++)
		{
			cr=(UBYTE)((colors4[RunTime.aktpal][i]&3840)>>8);
			cg=(UBYTE)((colors4[RunTime.aktpal][i]&240)>>4);
			cb=(UBYTE)(colors4[RunTime.aktpal][i]&15);
			cc=(float)(cr+cg+cb)/3.0;
			if(cc>bc)
			{
				bc=cc;col=i;
				bd=cc-(float)cr;
				bd+=cc-(float)cg;
				bd+=cc-(float)cb;
			}
			else
			{
				if(cc==bc)
				{
					if(((cc-(float)cr)+(cc-(float)cr)+(cc-(float)cr))<bd)
					{
						bc=cc;col=i;
						bd=cc-(float)cr;
						bd+=cc-(float)cg;
						bd+=cc-(float)cb;
					}
				}
			}
		}
	}
	if(GfxInfo.palbits>4)
	{
		col=0;bc=bd=0.0;
		for(i=0;i<GfxInfo.realcol;i++)
		{
			cr=(UBYTE)(colors32[RunTime.aktpal].Entry[i].r);
			cg=(UBYTE)(colors32[RunTime.aktpal].Entry[i].g);
			cb=(UBYTE)(colors32[RunTime.aktpal].Entry[i].b);
			cc=(float)(cr+cg+cb)/3.0;
			if(cc>bc)
			{
				bc=cc;col=i;
				bd=cc-(float)cr;
				bd+=cc-(float)cg;
				bd+=cc-(float)cb;
			}
			else
			{
				if(cc==bc)
				{
					if(((cc-(float)cr)+(cc-(float)cr)+(cc-(float)cr))<bd)
					{
						bc=cc;col=i;
						bd=cc-(float)cr;
						bd+=cc-(float)cg;
						bd+=cc-(float)cb;
					}
				}
			}
		}
	}
	return(col);
}

UBYTE GetDarkestCol(void)
{
	register UWORD i;
	UBYTE col=0,cr,cg,cb;
	float cc,bc,bd;

	if(GfxInfo.palbits<5)
	{
		col=0;bc=bd=999.0;
		for(i=0;i<GfxInfo.realcol;i++)
		{
			cr=(UBYTE)((colors4[RunTime.aktpal][i]&3840)>>8);
			cg=(UBYTE)((colors4[RunTime.aktpal][i]&240)>>4);
			cb=(UBYTE)(colors4[RunTime.aktpal][i]&15);
			cc=(float)(cr+cg+cb)/3.0;
			if(cc<bc)
			{
				bc=cc;col=i;
				bd=cc-(float)cr;
				bd+=cc-(float)cg;
				bd+=cc-(float)cb;
			}
			else
			{
				if(cc==bc)
				{
					if(((cc-(float)cr)+(cc-(float)cr)+(cc-(float)cr))>bd)
					{
						bc=cc;col=i;
						bd=cc-(float)cr;
						bd+=cc-(float)cg;
						bd+=cc-(float)cb;
					}
				}
			}
		}
	}
	if(GfxInfo.palbits>4)
	{
		col=0;bc=bd=999.0;
		for(i=0;i<GfxInfo.realcol;i++)
		{
			cr=(UBYTE)(colors32[RunTime.aktpal].Entry[i].r);
			cg=(UBYTE)(colors32[RunTime.aktpal].Entry[i].g);
			cb=(UBYTE)(colors32[RunTime.aktpal].Entry[i].b);
			cc=(float)(cr+cg+cb)/3.0;
			if(cc<bc)
			{
				bc=cc;col=i;
				bd=cc-(float)cr;
				bd+=cc-(float)cg;
				bd+=cc-(float)cb;
			}
			else
			{
				if(cc==bc)
				{
					if(((cc-(float)cr)+(cc-(float)cr)+(cc-(float)cr))>bd)
					{
						bc=cc;col=i;
						bd=cc-(float)cr;
						bd+=cc-(float)cg;
						bd+=cc-(float)cb;
					}
				}
			}
		}
	}
	return(col);
}

void AssignGfxFuncs(void)
{
/* DEBUG */
	MSG2("dither : %d   gfxtyp : %d",GfxInfo.dither,GfxInfo.gfxtyp);
/* DEBUG */
	switch((ULONG)GfxInfo.gfxtyp) {
		case 0:			/* AmigaMode Bitmap - I hope so */
			AssignTurboGfxFuncs();
			break;
		case 1:			/* GfxExtensionMode - I better use system routines */
			AssignSystemGfxFuncs();
			break;
		default:
			MSG1("Invalid gfx-typ : %d",GfxInfo.gfxtyp);
			GfxInfo.gfxtyp=1;
			AssignSystemGfxFuncs();
			break;
	}
}

void AssignTurboGfxFuncs(void)
{
	switch((ULONG)GfxInfo.dither) {
		case 0: /* none */
			PsetFunc=MT0D0Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D0Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT0D0Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D0Pointy;
			RectFunc=MT0D0Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D0Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT0D0Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D0Rectay;
			break;
		case 1: /* small */
			PsetFunc=MT0D1Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D1Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT0D1Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D1Pointy;
			RectFunc=MT0D1Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D1Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT0D1Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D1Rectay;
			break;
		case 2: /* medium */
			PsetFunc=MT0D2Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D2Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT0D2Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D2Pointy;
			RectFunc=MT0D2Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D2Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT0D2Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D2Rectay;
			break;
		case 3: /* large */
			PsetFunc=MT0D3Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D3Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT0D3Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D3Pointy;
			RectFunc=MT0D3Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D3Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT0D3Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D3Rectay;
			break;
		case 4: /* ordered */
			PsetFunc=MT0D4Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D4Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT0D4Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D4Pointy;
			RectFunc=MT0D4Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D4Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT0D4Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D4Rectay;
			break;
		default:
			MSG1("Invalid dither-typ : %d",GfxInfo.dither);
			GfxInfo.dither=0;
			PsetFunc=MT0D0Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D0Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT0D0Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT0D0Pointy;
			RectFunc=MT0D0Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D0Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT0D0Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT0D0Rectay;
			break;			
	}
}

void AssignSystemGfxFuncs(void)
{
	switch((ULONG)GfxInfo.dither) {
		case 0:
			PsetFunc=MT1D0Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D0Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT1D0Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D0Pointy;
			RectFunc=MT1D0Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D0Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT1D0Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D0Rectay;
			break;
		case 1:
			PsetFunc=MT1D1Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D1Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT1D1Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D1Pointy;
			RectFunc=MT1D1Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D1Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT1D1Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D1Rectay;
			break;
		case 2:
			PsetFunc=MT1D2Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D2Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT1D2Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D2Pointy;
			RectFunc=MT1D2Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D2Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT1D2Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D2Rectay;
			break;
		case 3:
			PsetFunc=MT1D3Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D3Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT1D3Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D3Pointy;
			RectFunc=MT1D3Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D3Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT1D3Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D3Rectay;
			break;
		case 4:
			PsetFunc=MT1D4Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D4Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT1D4Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D4Pointy;
			RectFunc=MT1D4Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D4Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT1D4Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D4Rectay;
			break;
		default:
			MSG1("Invalid dither-typ : %d",GfxInfo.dither);
			GfxInfo.dither=0;
			PsetFunc=MT1D0Point;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D0Pointxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) PsetFunc=MT1D0Pointx;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) PsetFunc=MT1D0Pointy;
			RectFunc=MT1D0Recta;
			if(RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D0Rectaxy;
			if(RenderInfo.mirrorx && !RenderInfo.mirrory) RectFunc=MT1D0Rectax;
			if(!RenderInfo.mirrorx && RenderInfo.mirrory) RectFunc=MT1D0Rectay;
			break;			
	}
}

void MyWritePixel(UWORD x,UWORD y,UBYTE c)			/* Vorübergehend */
{
	register ULONG addr;
	register UBYTE i,rest;

	addr=BPR*y+(x>>3);
	rest=x&7;
	for(i=0;i<5;i++)
	{
		if(c&(1<<i)) *(planes[i]+addr)|=(128>>rest);
	}
}

void Zoom(UBYTE ztype,UBYTE zmode,UBYTE zsnap,UWORD *x1,UWORD *y1,UWORD *x2,UWORD *y2)
{
	UBYTE click1=0,click2=0,crflx=0,crfly=0,crflxy=0,greypal=0;
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
	LONG mx,my,ox=-1,oy=-1,dx,dy,sx,sy;

	while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort));
	ScreenToFront(rscreen);
	ActivateWindow(rwindow);
	ModifyIDCMP(rwindow,IDCMP_MOUSEBUTTONS|IDCMP_MOUSEMOVE|IDCMP_VANILLAKEY);
	SetDrMd(&rrp[0],COMPLEMENT);
	SetDrPt(&rrp[0],61680);
	while(!click1)
	{
		WaitPort(rwindow->UserPort);
		while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
		{
			iclass	=imsg->Class;
			icode	=imsg->Code;
			mx		=imsg->MouseX;
			my		=imsg->MouseY;
			ReplyMsg(imsg);
			if(!click1)
			{
				if(iclass==IDCMP_MOUSEMOVE)
				{
					if(ox!=mx)
					{
						if(crflx)
						{
							Move(&rrp[0],ox,0);Draw(&rrp[0],ox,GfxInfo.yres-1);
						}
						else crflx=1;
						Move(&rrp[0],mx,0);Draw(&rrp[0],mx,GfxInfo.yres-1);
						ox=mx;
					}
					if(oy!=my)
					{
						if(crfly)
						{
							Move(&rrp[0],0,oy);Draw(&rrp[0],GfxInfo.xres-1,oy);
						}
						else crfly=1;
						Move(&rrp[0],0,my);Draw(&rrp[0],GfxInfo.xres-1,my);
						oy=my;
					}
				}
				if(iclass==IDCMP_MOUSEBUTTONS)
				{
					if(!(icode&128))
					{
						if(crflx)
						{
							Move(&rrp[0],ox,0);Draw(&rrp[0],ox,GfxInfo.yres-1);
						}
						if(crfly)
						{
							Move(&rrp[0],0,oy);Draw(&rrp[0],GfxInfo.xres-1,oy);
						}
						*x1=mx;*y1=my;
						click1=1;
					}
				}
				if(iclass==IDCMP_VANILLAKEY)
				{
					switch(icode)
					{
						case 32:	/* Space */
							if(greypal)
							{
								greypal=0;
								if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[RunTime.aktpal][0],GfxInfo.realcol);
								if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[RunTime.aktpal]);
								MakeVPort(view,rvp);MrgCop(view);LoadView(view);
							}
							else
							{
								greypal=1;
								if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[10][0],GfxInfo.realcol);
								if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[10]);
								MakeVPort(view,rvp);MrgCop(view);LoadView(view);
							}
							break;
						case 'H':				/* Hide Mousepointer */
						case 'h':
							if(epointer) { ClearPointer(rwindow);epointer=0; }
							else { SetPointer(rwindow,Emptypointer,1,16,0,0);epointer=1; }
							break;
					}
				}
			}
		}
	}
	if(zsnap)		/* Corner */
	{
		ox=-1;oy=-1;
		while(!click2)
		{
			WaitPort(rwindow->UserPort);
			while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
			{
				iclass	=imsg->Class;
				icode	=imsg->Code;
				mx		=imsg->MouseX;
				my		=imsg->MouseY;
				ReplyMsg(imsg);
				if(!click2)
				{
					if(!zmode)
					{
						dx=abs(*x1-mx);dy=abs(*y1-my);
						if(mx<*x1) sx=-1;
						else sx=1;
						if(my<*y1) sy=-1;
						else sy=1;
// DEBUG
//						printf("dx : %4d  dy : %4d  asp : %8.6lf\n",dx,dy,GfxInfo.aspect);
// DEBUG
						if((float)dy*GfxInfo.aspect>dx) mx=*x1+sx*(float)dy*GfxInfo.aspect;
						if((float)dx/GfxInfo.aspect>dy) my=*y1+sy*(float)dx/GfxInfo.aspect;
					}
					if(iclass==IDCMP_MOUSEMOVE)
					{
						if(ox!=mx || oy!=my)
						{
							if(crflxy)
							{
								Move(&rrp[0],*x1,*y1);
								Draw(&rrp[0],*x1,oy);Draw(&rrp[0],ox,oy);
								Draw(&rrp[0],ox,*y1);Draw(&rrp[0],*x1,*y1);
							}
							else crflxy=1;
							Move(&rrp[0],*x1,*y1);
							Draw(&rrp[0],*x1,my);Draw(&rrp[0],mx,my);
							Draw(&rrp[0],mx,*y1);Draw(&rrp[0],*x1,*y1);
							ox=mx;oy=my;
						}
					}
					if(iclass==IDCMP_MOUSEBUTTONS)
					{
						if(icode&128)
						{
							if(crflxy)
							{
								Move(&rrp[0],*x1,*y1);
								Draw(&rrp[0],*x1,oy);Draw(&rrp[0],ox,oy);
								Draw(&rrp[0],ox,*y1);Draw(&rrp[0],*x1,*y1);
							}
							*x2=mx;*y2=my;
							click2=1;
						}
					}
					if(iclass==IDCMP_VANILLAKEY)
					{
						switch(icode)
						{
							case 32:	/* Space */
								if(greypal)
								{
									greypal=0;
									if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[RunTime.aktpal][0],GfxInfo.realcol);
									if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[RunTime.aktpal]);
									MakeVPort(view,rvp);MrgCop(view);LoadView(view);
								}
								else
								{
									greypal=1;
									if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[10][0],GfxInfo.realcol);
									if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[10]);
									MakeVPort(view,rvp);MrgCop(view);LoadView(view);
								}
								break;
							case 'H':				/* Hide Mousepointer */
							case 'h':
								if(epointer) { ClearPointer(rwindow);epointer=0; }
								else { SetPointer(rwindow,Emptypointer,1,16,0,0);epointer=1; }
								break;
						}
					}
				}
			}
		}
	}
	else			/* Centre */
	{
		ox=-1;oy=-1;
		while(!click2)
		{
			WaitPort(rwindow->UserPort);
			while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
			{
				iclass	=imsg->Class;
				icode	=imsg->Code;
				mx		=imsg->MouseX;
				my		=imsg->MouseY;
				ReplyMsg(imsg);
				if(!click2)
				{
					if(!zmode)
					{
						dx=abs(*x1-mx);dy=abs(*y1-my);
						if(mx<*x1) sx=-1;
						else sx=1;
						if(my<*y1) sy=-1;
						else sy=1;
// DEBUG
//						printf("dx : %4d  dy : %4d  asp : %8.6lf\n",dx,dy,GfxInfo.aspect);
// DEBUG
						if((float)dy*GfxInfo.aspect>dx) mx=*x1+sx*(float)dy*GfxInfo.aspect;
						if((float)dx/GfxInfo.aspect>dy) my=*y1+sy*(float)dx/GfxInfo.aspect;
					}
					if(iclass==IDCMP_MOUSEMOVE)
					{
						if(ox!=mx || oy!=my)
						{
							if(crflxy)
							{
								dx=*x1-ox;dy=*y1-oy;
								Move(&rrp[0],*x1+dx,*y1+dy);
								Draw(&rrp[0],*x1+dx,oy);Draw(&rrp[0],ox,oy);
								Draw(&rrp[0],ox,*y1+dy);Draw(&rrp[0],*x1+dx,*y1+dy);
							}
							else crflxy=1;
							dx=*x1-mx;dy=*y1-my;
							Move(&rrp[0],*x1+dx,*y1+dy);
							Draw(&rrp[0],*x1+dx,my);Draw(&rrp[0],mx,my);
							Draw(&rrp[0],mx,*y1+dy);Draw(&rrp[0],*x1+dx,*y1+dy);
							ox=mx;oy=my;
						}
					}
					if(iclass==IDCMP_MOUSEBUTTONS)
					{
						if(icode&128)
						{
							if(crflxy)
							{
								dx=*x1-ox;dy=*y1-oy;
								Move(&rrp[0],*x1+dx,*y1+dy);
								Draw(&rrp[0],*x1+dx,oy);Draw(&rrp[0],ox,oy);
								Draw(&rrp[0],ox,*y1+dy);Draw(&rrp[0],*x1+dx,*y1+dy);
							}
							dx=*x1-mx;dy=*y1-my;
							*x2=max(*x1+dx,*x1-dx);*y2=max(*y1+dy,*y1-dy);
							*x1=min(*x1+dx,*x1-dx);*y1=min(*y1+dy,*y1-dy);
							click2=1;
						}
					}
					if(iclass==IDCMP_VANILLAKEY)
					{
						switch(icode)
						{
							case 32:	/* Space */
								if(greypal)
								{
									greypal=0;
									if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[RunTime.aktpal][0],GfxInfo.realcol);
									if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[RunTime.aktpal]);
									MakeVPort(view,rvp);MrgCop(view);LoadView(view);
								}
								else
								{
									greypal=1;
									if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[10][0],GfxInfo.realcol);
									if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[10]);
									MakeVPort(view,rvp);MrgCop(view);LoadView(view);
								}
								break;
							case 'H':				/* Hide Mousepointer */
							case 'h':
								if(epointer) { ClearPointer(rwindow);epointer=0; }
								else { SetPointer(rwindow,Emptypointer,1,16,0,0);epointer=1; }
								break;
						}
					}
				}
			}
		}
	}
	if(greypal)
	{
		if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[RunTime.aktpal][0],GfxInfo.realcol);
		if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[RunTime.aktpal]);
		MakeVPort(view,rvp);MrgCop(view);LoadView(view);
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	ModifyIDCMP(rwindow,IDCMP_RAWKEY);
	SetDrMd(&rrp[0],JAM2);
	SetDrPt(&rrp[0],65535);
	ScreenToFront(mmscr);
	ActivateWindow(zowin);
}

void Pick(double *parx,double *pary)
{
	UBYTE click=0,crflx=0,crfly=0,greypal=0;
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
	LONG mx,my,ox=0,oy=0,sx,sy;
	double xd,yd;

	while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort));
	ScreenToFront(rscreen);
	ActivateWindow(rwindow);
	ModifyIDCMP(rwindow,IDCMP_MOUSEBUTTONS|IDCMP_MOUSEMOVE|IDCMP_VANILLAKEY);
	SetDrMd(&rrp[0],COMPLEMENT);
	SetDrPt(&rrp[0],61680);
	while(!click)
	{
		WaitPort(rwindow->UserPort);
		while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
		{
			iclass	=imsg->Class;
			icode	=imsg->Code;
			mx		=imsg->MouseX;
			my		=imsg->MouseY;
			ReplyMsg(imsg);
			if(iclass==IDCMP_MOUSEMOVE)
			{
				if(ox!=mx)
				{
					if(crflx)
					{
						Move(&rrp[0],ox,0);Draw(&rrp[0],ox,GfxInfo.yres-1);
					}
					else crflx=1;
					Move(&rrp[0],mx,0);Draw(&rrp[0],mx,GfxInfo.yres-1);
					ox=mx;
				}
				if(oy!=my)
				{
					if(crfly)
					{
						Move(&rrp[0],0,oy);Draw(&rrp[0],GfxInfo.xres-1,oy);
					}
					else crfly=1;
					Move(&rrp[0],0,my);Draw(&rrp[0],GfxInfo.xres-1,my);
					oy=my;
				}
			}
			if(iclass==IDCMP_MOUSEBUTTONS)
			{
				if(!(icode&128))
				{
					if(crflx)
					{
						Move(&rrp[0],0,oy);Draw(&rrp[0],GfxInfo.xres-1,oy);
					}
					if(crfly)
					{
						Move(&rrp[0],ox,0);Draw(&rrp[0],ox,GfxInfo.yres-1);
					}
					sx=opxb2-opxb1;
					sy=opyb2-opyb1;
					xd=(opx2-opx1)/(float)sx;
					yd=(opy2-opy1)/(float)sy;
					*parx=opx1+mx*xd;
					*pary=opy1+my*yd;
					click=1;
				}
			}
			if(iclass==IDCMP_VANILLAKEY)
			{
				switch(icode)
				{
					case 32:	/* Space */
						if(greypal)
						{
							greypal=0;
							if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[RunTime.aktpal][0],GfxInfo.realcol);
							if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[RunTime.aktpal]);
							MakeVPort(view,rvp);MrgCop(view);LoadView(view);
						}
						else
						{
							greypal=1;
							if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[10][0],GfxInfo.realcol);
							if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[10]);
							MakeVPort(view,rvp);MrgCop(view);LoadView(view);
						}
						break;
					case 'H':				/* Hide Mousepointer */
					case 'h':
						if(epointer) { ClearPointer(rwindow);epointer=0; }
						else { SetPointer(rwindow,Emptypointer,1,16,0,0);epointer=1; }
						break;
				}
			}
		}
	}
	if(greypal)
	{
		if(GfxInfo.palbits<5) LoadRGB4(rvp,&colors4[RunTime.aktpal][0],GfxInfo.realcol);
		if(GfxInfo.palbits>4 && RunTime.kickstart>2) LoadRGB32(rvp,(ULONG *)&colors32[RunTime.aktpal]);
		MakeVPort(view,rvp);MrgCop(view);LoadView(view);
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	ModifyIDCMP(rwindow,IDCMP_RAWKEY);
	SetDrMd(&rrp[0],JAM2);
	SetDrPt(&rrp[0],65535);
	ScreenToFront(mmscr);
	ActivateWindow(opwin);
}
