/****h* FractalUniverse/FU.c [1.68] *
*
*  NAME
*    FU.c
*  COPYRIGHT
*    $VER: FU.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    23.Oct.2001
*  MODIFICATION HISTORY
*    24.Oct.2001	V 1.68	most recent version
*    23.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

//-- includes -----------------------------------------------------------------

#define FU_C
#include "FU-Includes.h"
#include "FU-GUI.h"
#include "FU-ArrangeList.h"

//-- prototypes ---------------------------------------------------------------

void OpenAll(void);
UBYTE Open_BDWin(void);
void CloseAll(void);
void SwitchIDCMPOFF(void);
void SwitchIDCMPON(void);
void SetDefs(void);

extern int CXBRK(void);
extern void chkabort(void);

//-- globals ------------------------------------------------------------------

//-- Versionsstring

UBYTE *VersTag="\0$VER: "PRJ_VERS;

extern struct ExecBase 		*SysBase;
extern struct DosLibrary	*DOSBase;
struct IntuitionBase		*IntuitionBase=0l;
struct GfxBase	 			*GfxBase=0l;
struct Library 				*AslBase=0l,*DiskfontBase=0l,*UtilityBase=0l,*AmigaGuideBase=0l,*GadToolsBase=0l;
struct Screen				*mmscr=0l,*rscreen=0l;
struct Window				*mmwin=0l,*bdwin=0l;
struct Window				*cowin=0l,*opwin=0l,*zowin=0l,*fowin=0l,*diwin=0l,*prwin=0l,*abwin=0l,*exwin=0l;
struct Window				*rwindow=0l,*owindow=0l,*iwindow=0l;
APTR						VisualInfo=0l;
struct TextFont				*scrfont=0l,*sigfont=0l;
struct FileRequester		*IFF_FRequest=0l,*Col_FRequest=0l;
struct FontRequenster		*SCR_FRequest=0l;
struct ViewPort 			*rvp,*mvp;
struct View					*view;
struct RastPort 			rrp[256],orp,irp;
PLANEPTR					planes[8];
UWORD						BPR;
UWORD 						scr_colors4[256];
struct ColorSet32			scr_colors32;

/* Arexx-Defs */
struct MsgPort				*arexxport=0l;
char 						*arexxname="REXX_FU";

double x,y,rx,ry;				/* Rendering */
double xd,yd;
UBYTE col[512];
UWORD (*FracFunc)(void);
UWORD (*GetOutsideColor)(double a,double b,double c,double d,UWORD n);
UWORD (*GetInsideColor)(double a,double b,double c,double d);
void (*PsetFunc)(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void (*RectFunc)(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void (*PixelModifier)(void);

uservar uv[64];					/* FormulaInterpreter-Vars */
UWORD luv,lhv;
mathop mabui[256],mabus[64];
UWORD lmopi,lmops;
UWORD bailr,baill;
UBYTE bailt;

double decompho,decomphi;		/* Decomp */
complex *ob=0L;					/* OrbitBuffer */
UWORD oldobsize;				/* Größe für FreeMem */
UWORD obanz;
sbuf sb[1000];					/* SquareBuffer */
double bofabs;					/* nearest orbit */
UWORD bofz;						/* zycle from ^ */

GInfo GfxInfo;					/* large Datastuctures */
FInfo FractalInfo;
RInfo RenderInfo;
PInfo PalInfo;
IInfo InspectInfo;
RTime RunTime;

double opx1,opx2,opy1,opy2;		/* Old Picture Values */
UWORD opxb1,opxb2,opyb1,opyb2;
double rotx,roty;				/* Winkel ( sin,cos ) für Rotation */
double rotpx,rotpy;				/* Mittelpunkt für Verschiebung */
float rps[10][256],gps[10][256],bps[10][256];

struct List ModeList;			/* RenderScrModes */
struct Node ModeNodes[100];
ScrMd Modes[100];

struct List GModeList;			/* GUIScrModes */
struct Node GModeNodes[100];
ScrMd GModes[100];
UBYTE gmaxmodes;				/* How many ScrMd`s are available */

struct List FormulaGadgetList;
struct Node FormulaGadgetNodes[ffanz];
struct List InvCircleList;
struct Node InvCircleNodes[sf0anz];
struct List NormCircleList;
struct Node NormCircleNodes[sf1anz];
struct List InvNewtonList;
struct Node InvNewtonNodes[sf3anz];
struct List NormNewtonList;
struct Node NormNewtonNodes[sf4anz];
struct List InvFixPlaneCList;
struct Node InvFixPlaneCNodes[sf5anz];
struct List InvVarPlaneCList;
struct Node InvVarPlaneCNodes[sf6anz];
struct List NormFixPlaneCList;
struct Node NormFixPlaneCNodes[sf7anz];
struct List NormVarPlaneCList;
struct Node NormVarPlaneCNodes[sf8anz];
struct List FormulaList;
struct Node FormulaNodes[sf2anz];
struct List InsideGadgetList;
struct Node InsideGadgetNodes[isanz];
struct List OutsideGadgetList;
struct Node OutsideGadgetNodes[osanz];
struct Requester NullReq;
char Formulas[sf2anz][40];
UBYTE epointer;					/* EmptyPointer aktive ? */
CycleData cdata;
long rendertime;				/* RenderZeit */
char fd[5][40];
char buffer1[256],buffer2[256],buffer3[256];		/* für StringHooks */
struct Hook hook1={	{0,0},hookfunc1,0,0 };
struct StringExtend stringextend1={ 0,1,0,1,0,0,&hook1,buffer1,{0L,0L,0L,0L} };
struct Hook hook2={	{0,0},hookfunc2,0,0 };
struct StringExtend stringextend2={	0,1,0,1,0,0,&hook2,buffer2,{0L,0L,0L,0L} };
struct Hook hook3={	{0,0},hookfunc3,0,0 };
struct StringExtend stringextend3={	0,1,0,1,0,0,&hook3,buffer3,{0L,0L,0L,0L} };

FUPrefs_Hdr		fuprefs_hdr;		/* Preferences V1.6 */
FUPrefs_Ver		fuprefs_ver;
FUPrefs_Path	fuprefs_path;
FUPrefs_Gui		fuprefs_gui;
FUPrefs_Defs	fuprefs_defs;

//-- definitions --------------------------------------------------------------

void OpenAll(void)
{
	register UBYTE i;
	register UWORD j;
	UBYTE gmaxmodes,found;					/* How many ScrMd`s are available */

	RunTime.kickstart=0;
	if(!(IntuitionBase=(struct IntuitionBase *)OpenLibrary("intuition.library",39)))
	{
		if(!(IntuitionBase=(struct IntuitionBase *)OpenLibrary("intuition.library",37))) CloseAll();
		else RunTime.kickstart=2;
	}
	else RunTime.kickstart=3;
	if(!(GfxBase=(struct GfxBase *)OpenLibrary("graphics.library",37))) CloseAll();
	if(!(DOSBase=(struct DosLibrary *)OpenLibrary("dos.library",0))) CloseAll();
	if(!(UtilityBase=OpenLibrary("utility.library",37L))) CloseAll();
	if(!(AslBase=OpenLibrary("asl.library",0L))) CloseAll();
	if(!(DiskfontBase=OpenLibrary("diskfont.library",37))) CloseAll();
	if(!(AmigaGuideBase=OpenLibrary("amigaguide.library",34L))) CloseAll();
	if(!(GadToolsBase=OpenLibrary("gadtools.library",37L))) CloseAll();

	view=ViewAddress();

	ScrFont.ta_Name=RunTime.fontname;
	ScrFont.ta_YSize=fuprefs_gui.fontsize;
	if(!(scrfont=OpenDiskFont(&ScrFont))) CloseAll();
	RunTime.scalex=(double)(scrfont->tf_XSize)/6.0;
	RunTime.scaley=(double)(scrfont->tf_YSize)/6.0;

	for(j=0;j<700;j++) RunTime.scx[j]=(UWORD)((float)j*RunTime.scalex);
	for(j=0;j<300;j++) RunTime.scy[j]=(UWORD)((float)j*RunTime.scaley);

	SigFont.ta_YSize=16;
	if(fuprefs_gui.fontsize<16) 	SigFont.ta_YSize=12;
	if(fuprefs_gui.fontsize<12) 	SigFont.ta_YSize=8;
	if(fuprefs_gui.fontsize<8)	 	SigFont.ta_YSize=6;
	if(!(sigfont=OpenDiskFont(&SigFont))) CloseAll();

	stringextend1.Font=stringextend2.Font=stringextend3.Font=scrfont;

	gmaxmodes=GetScrModes(&GModeList,GModeNodes,GModes,50,640,200,4);			/* Screenmodes für GUIScreen holen */
	found=0;
	for(i=0;i<gmaxmodes;i++) if(fuprefs_gui.scrmode==GModes[i].scrmode) { RunTime.gscreenmode=i;i=gmaxmodes;found=1; }
	if(!found)
	{
		fuprefs_gui.scrmode=HIRES_KEY;
		for(i=0;i<gmaxmodes;i++) if(fuprefs_gui.scrmode==GModes[i].scrmode) { RunTime.gscreenmode=i;i=gmaxmodes; }
	}

	RunTime.maxmodes=GetScrModes(&ModeList,ModeNodes,Modes,50,0,0,0);			/* Screenmodes für RenderScreens holen */
	found=0;
	for(i=0;i<RunTime.maxmodes;i++) if(GfxInfo.scrmode==Modes[i].scrmode) { RunTime.rscreenmode=i;i=RunTime.maxmodes;found=1; }
	if(!found)
	{
		GfxInfo.xres=320;GfxInfo.yres=256;
		GfxInfo.oscan=0;
		GfxInfo.depth=5;
		GfxInfo.realcol=GfxInfo.maxcol=1<<GfxInfo.depth;
		GfxInfo.absmaxcol=GfxInfo.maxcol-1;
		GfxInfo.scrmode=LORES_KEY;
		for(i=0;i<RunTime.maxmodes;i++) if(GfxInfo.scrmode==Modes[i].scrmode) { RunTime.rscreenmode=i;i=RunTime.maxmodes; }
	}

	ChangeScreen();										/* RenderScreen */
	RenderInfo.xb1=0;RenderInfo.xb2=GfxInfo.xres-1;
	RenderInfo.yb1=0;RenderInfo.yb2=GfxInfo.yres-1;

	fuprefs_gui.autoscroll=FALSE;
	if(!fuprefs_gui.xdef && fuprefs_gui.xres>GModes[RunTime.gscreenmode].OScans[1].MaxX) fuprefs_gui.autoscroll=TRUE;
	if(!fuprefs_gui.ydef && fuprefs_gui.yres>GModes[RunTime.gscreenmode].OScans[1].MaxY) fuprefs_gui.autoscroll=TRUE;

	if(fuprefs_gui.xdef) RunTime.xres=GModes[RunTime.gscreenmode].OScans[fuprefs_gui.oscan].MaxX;
	else RunTime.xres=fuprefs_gui.xres;
	if(fuprefs_gui.ydef) RunTime.yres=GModes[RunTime.gscreenmode].OScans[fuprefs_gui.oscan].MaxY;
	else RunTime.yres=fuprefs_gui.yres;

	mmscrtags[6].ti_Data=(ULONG)fuprefs_gui.ScreenColors;		/* UserScreen */
	mmscrtags[2].ti_Data=RunTime.xres;
	mmscrtags[3].ti_Data=RunTime.yres;
	mmscrtags[4].ti_Data=fuprefs_gui.depth;
	mmscrtags[9].ti_Data=fuprefs_gui.scrmode;
	if(!(mmscr=OpenScreenTagList(0l,mmscrtags))) CloseAll();
	mmscr->WBorBottom=4;
	mvp=&mmscr->ViewPort;
	bdwintags[8].ti_Data=mmwintags[9].ti_Data=smwintags[9].ti_Data=(ULONG)mmscr;

	if(!(VisualInfo=GetVisualInfo(mmscr,TAG_DONE))) CloseAll();

	if(Open_BDWin()) CloseAll();
	if(Open_MMWin()) CloseAll();

	IFF_Reqtags[1].ti_Data=Col_Reqtags[1].ti_Data=SCR_Reqtags[1].ti_Data=(ULONG)bdwin;
	IFF_Reqtags[6].ti_Data=(ULONG)fuprefs_path.iff_path;
	Col_Reqtags[6].ti_Data=(ULONG)fuprefs_path.color_path;
	SCR_Reqtags[6].ti_Data=(ULONG)fuprefs_gui.fontname;
	SCR_Reqtags[7].ti_Data=fuprefs_gui.fontsize;
	if(!(IFF_FRequest=AllocAslRequest(ASL_FileRequest,NULL))) CloseAll();
	if(!(Col_FRequest=AllocAslRequest(ASL_FileRequest,NULL))) CloseAll();
	if(!(SCR_FRequest=AllocAslRequest(ASL_FontRequest,NULL))) CloseAll();

	SortAList(ffanz,fflist);			/* FormulaGroupListe */
	BuildList(FormulaGadgetNodes,&FormulaGadgetList,ffanz,fflist);

	ScanFormulas();						/* FourmulaListe */

	SortAList(sf0anz,sf0list);			/* InvCircleListe */
	BuildList(InvCircleNodes,&InvCircleList,sf0anz,sf0list);

	SortAList(sf1anz,sf1list);			/* NormCircleListe */
	BuildList(NormCircleNodes,&NormCircleList,sf1anz,sf1list);

	SortAList(sf3anz,sf3list);			/* InvNewtonListe */
	BuildList(InvNewtonNodes,&InvNewtonList,sf3anz,sf3list);

	SortAList(sf4anz,sf4list);			/* NormNewtonListe */
	BuildList(NormNewtonNodes,&NormNewtonList,sf4anz,sf4list);

	SortAList(sf5anz,sf5list);			/* InvFixPlaneCListe */
	BuildList(InvFixPlaneCNodes,&InvFixPlaneCList,sf5anz,sf5list);

	SortAList(sf6anz,sf6list);			/* InvVarPlaneCListe */
	BuildList(InvVarPlaneCNodes,&InvVarPlaneCList,sf6anz,sf6list);

	SortAList(sf7anz,sf7list);			/* NormFixPlaneCListe */
	BuildList(NormFixPlaneCNodes,&NormFixPlaneCList,sf7anz,sf7list);

	SortAList(sf8anz,sf8list);			/* NormVarPlaneCListe */
	BuildList(NormVarPlaneCNodes,&NormVarPlaneCList,sf8anz,sf8list);

	SortAList(isanz,insidelist);		/* InsideListe */
	BuildList(InsideGadgetNodes,&InsideGadgetList,isanz,insidelist);

	SortAList(osanz,outsidelist);		/* OutsideListe */
	BuildList(OutsideGadgetNodes,&OutsideGadgetList,osanz,outsidelist);

	InitRequester(&NullReq);	/* BlockReq initialisieren */

	if(FindPort(arexxname))									/* testen ob Programm schon läuft */
	{
		if(!Question(ques[2])) CloseAll();
	}
	else
	{
		if(!(arexxport=CreateMsgPort())) CloseAll();		/* ArexxPort anlegen */
		arexxport->mp_Node.ln_Name=arexxname;
		AddPort(arexxport);
		RunTime.sig_in|=(1L<<arexxport->mp_SigBit);
	}
}

UBYTE Open_BDWin(void)
{
	struct RastPort bdrp;
	UBYTE ret=1;
	struct Process *ThisProcess=(struct Process *)FindTask(NULL);

	bdwintags[2].ti_Data=RunTime.xres;
	bdwintags[3].ti_Data=RunTime.yres-1;
	if(bdwin=OpenWindowTagList(0l,bdwintags))
	{
		ThisProcess->pr_WindowPtr=bdwin;
		bdrp=*bdwin->RPort;
		DrawImage(&bdrp,&backlogo,(RunTime.xres-360)>>1,(RunTime.yres-35)>>1);
		ret=0;
	}
	else Message(mess[5]);
	return(ret);
}

void CloseAll(void)
{
	if(arexxport)
	{
		RemPort(arexxport);
		DeleteMsgPort(arexxport);
	}

	if(ob)				FreeMem(ob,oldobsize);

	if(SCR_FRequest)	FreeAslRequest(SCR_FRequest);
	if(Col_FRequest)	FreeAslRequest(Col_FRequest);
	if(IFF_FRequest)	FreeAslRequest(IFF_FRequest);

	if(rwindow)			CloseWindow(rwindow);
	if(rscreen)			CloseScreen(rscreen);

	if(cowin)			CloseWindow(cowin);
	if(zowin)			CloseWindow(zowin);
	if(opwin)			CloseWindow(opwin);
	if(fowin)			CloseWindow(fowin);
	if(diwin)			CloseWindow(diwin);
	if(prwin)			CloseWindow(prwin);
	if(bdwin)			CloseWindow(bdwin);
	Close_MMWin();

	if(VisualInfo)		FreeVisualInfo(VisualInfo);
	if(mmscr)			CloseScreen(mmscr);

	if(sigfont)			CloseFont(sigfont);
	if(scrfont)			CloseFont(scrfont);

	if(GadToolsBase)	CloseLibrary(GadToolsBase);
	if(AmigaGuideBase)	CloseLibrary(AmigaGuideBase);
	if(UtilityBase)		CloseLibrary(UtilityBase);
	if(AslBase)			CloseLibrary(AslBase);
	if(DiskfontBase)	CloseLibrary(DiskfontBase);
 	if(DOSBase)			CloseLibrary((struct Library *)DOSBase);
	if(GfxBase)			CloseLibrary((struct Library *)GfxBase);
	if(IntuitionBase)	CloseLibrary((struct Library *)IntuitionBase);

	exit(0);
}

void SwitchIDCMPOFF(void)
{
	Request(&NullReq,mmwin);
	if(RunTime.kickstart==3) SetWindowPointer(mmwin,WA_BusyPointer,TRUE,WA_PointerDelay,TRUE,TAG_DONE);
	else SetPointer(mmwin,Stopwatch,16,16,-6,0);
}

void SwitchIDCMPON(void)
{
	EndRequest(&NullReq,mmwin);
	if(RunTime.kickstart==3) SetWindowPointer(mmwin,TAG_DONE);
	else ClearPointer(mmwin);
}

void SetDefs(void)
{
	register UBYTE i;

	RunTime.sig_in=0L;
	RunTime.rexxactive=0;
//	RunTime.screenmode=0;
	RunTime.gscreenmode=0;
	RunTime.quitfu=0;
	RunTime.fracfunc=8;RunTime.subfunc=0;
	RunTime.picavail=0;
	RunTime.aktpal=0;

	epointer=0;

	GfxInfo.xres=320;GfxInfo.yres=256;
	GfxInfo.oscan=0;
	GfxInfo.depth=5;
	GfxInfo.realcol=GfxInfo.maxcol=1<<GfxInfo.depth;
	GfxInfo.absmaxcol=GfxInfo.maxcol-1;
	GfxInfo.scrmode=LORES_KEY;
	GfxInfo.aspect=(float)(GfxInfo.xres)/(float)(GfxInfo.yres);
	GfxInfo.revpal=1;
	GfxInfo.dither=1;
	GfxInfo.ordscl=4;
	GfxInfo.palscl=1;
	GfxInfo.palmap=0;
	GfxInfo.gfxtyp=0;
	if(RunTime.kickstart>2) GfxInfo.palbits=8;
	else GfxInfo.palbits=4;

	RenderInfo.z=51;
	RenderInfo.rot=0;
	RenderInfo.outside=14;RenderInfo.outpar1=0;RenderInfo.outpar2=0;
	RenderInfo.inside=9;RenderInfo.inpar1=0;RenderInfo.inpar2=0;
	RenderInfo.rendermode=1;
	RenderInfo.signal=1;
	RenderInfo.obstep=4;
	RenderInfo.obsize=1;
	RenderInfo.obconnect=0;

	for(i=0;i<10;i++)
	{
		PalInfo.r[i].xoff=32;	PalInfo.g[i].xoff=0;	PalInfo.b[i].xoff=224;
		PalInfo.r[i].yoff=0;	PalInfo.g[i].yoff=0;	PalInfo.b[i].yoff=0;
		PalInfo.r[i].pst=0;		PalInfo.g[i].pst=0;		PalInfo.b[i].pst=0;
		PalInfo.r[i].scx=1;		PalInfo.g[i].scx=1;		PalInfo.b[i].scx=1;
		PalInfo.r[i].scy=1;		PalInfo.g[i].scy=1;		PalInfo.b[i].scy=1;
	}

	cdata.rate=3;
	cdata.dir=0;

	SetPaletteMode();
	for(i=0;i<10;i++)
	{
		GetPalShape(PalInfo.r[i].pst,rps[i]);
		GetPalShape(PalInfo.g[i].pst,gps[i]);
		GetPalShape(PalInfo.b[i].pst,bps[i]);
	}
	ChooseFracFunc(0);
	ChooseColorFunc();

	fuprefs_ver.ver=			1;					/* Defaults new */
	fuprefs_ver.rev=			6;

	strcpy(fuprefs_path.iff_path,"fractals/");
	strcpy(fuprefs_path.color_path,"colors/");

	fuprefs_gui.scrmode=		HIRES_KEY;
	fuprefs_gui.xres=			640;
	fuprefs_gui.yres=			265;
	fuprefs_gui.depth=			4;
	fuprefs_gui.oscan=			0;
	fuprefs_gui.autoscroll=		0;
	fuprefs_gui.xdef=			0;
	fuprefs_gui.ydef=			0;
	fuprefs_gui.ScreenColors[0].ColorIndex= 0;fuprefs_gui.ScreenColors[0].Red=0x0C;fuprefs_gui.ScreenColors[0].Green=0x0A;fuprefs_gui.ScreenColors[0].Blue=0x0A;
	fuprefs_gui.ScreenColors[1].ColorIndex= 1;fuprefs_gui.ScreenColors[1].Red=0x02;fuprefs_gui.ScreenColors[1].Green=0x00;fuprefs_gui.ScreenColors[1].Blue=0x00;
	fuprefs_gui.ScreenColors[2].ColorIndex= 2;fuprefs_gui.ScreenColors[2].Red=0x0F;fuprefs_gui.ScreenColors[2].Green=0x0D;fuprefs_gui.ScreenColors[2].Blue=0x0D;
	fuprefs_gui.ScreenColors[3].ColorIndex= 3;fuprefs_gui.ScreenColors[3].Red=0x0F;fuprefs_gui.ScreenColors[3].Green=0x00;fuprefs_gui.ScreenColors[3].Blue=0x0A;
	fuprefs_gui.ScreenColors[4].ColorIndex=-1;fuprefs_gui.ScreenColors[4].Red=0x00;fuprefs_gui.ScreenColors[4].Green=0x00;fuprefs_gui.ScreenColors[4].Blue=0x00;
	fuprefs_gui.pad1=			0;

	RunTime.status=1;								/* no keyfiles anymore (0 is demo) */

	fuprefs_gui.fontsize=		6;
	strcpy(fuprefs_gui.fontname,"trinomic.font");

	LoadPrefs("ENVARC:fu.prefs");					/* Prefs müssen nicht unbedingt ins ENV: umkopiert werden */
	LoadPrefs("ENV:fu.prefs");

	strcpy(RunTime.fontname,fuprefs_gui.fontname);

/* Farben umladen */
	scr_colors4[0]=((UWORD)fuprefs_gui.ScreenColors[0].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[0].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[0].Blue;
	scr_colors4[1]=((UWORD)fuprefs_gui.ScreenColors[1].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[1].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[1].Blue;
	scr_colors4[2]=((UWORD)fuprefs_gui.ScreenColors[2].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[2].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[2].Blue;
	scr_colors4[3]=((UWORD)fuprefs_gui.ScreenColors[3].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[3].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[3].Blue;
}

void main(void)
{
	ULONG sig_out;

	INTRO;

	SetDefs();
	OpenAll();
	if(RunTime.status==255) { RunTime.status=0;Message(mess[19]); }
	if(!RunTime.status)
	{
		Message(mess[15]);
		SwitchIDCMPOFF();
		Open_ABWin();
		SwitchIDCMPON();
	}

	while(!RunTime.quitfu) {
		// refresh windows
		Refr_MMWin();
		// wait for event
		sig_out=Wait(RunTime.sig_in);
		
		// handle events
		if(sig_out&(1L<<mmwin->UserPort->mp_SigBit))			Test_MMWin();

		if(cowin && sig_out&(1L<<cowin->UserPort->mp_SigBit))	Test_COWin();
		if(zowin && sig_out&(1L<<zowin->UserPort->mp_SigBit))	Test_ZOWin();
		if(opwin && sig_out&(1L<<opwin->UserPort->mp_SigBit))	Test_OPWin();
		if(fowin && sig_out&(1L<<fowin->UserPort->mp_SigBit))	Test_FOWin();

		if(diwin && sig_out&(1L<<diwin->UserPort->mp_SigBit))	Test_DOWin();
		if(prwin && sig_out&(1L<<prwin->UserPort->mp_SigBit))	Test_PRWin();

		if(arexxport && sig_out&(1L<<arexxport->mp_SigBit))		DoIO_Rexx();
	}
	if(!RunTime.status) Message(mess[16]);
	CloseAll();
}
