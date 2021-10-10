/****h* FractalUniverse/FU.h [1.68] *
*
*  NAME
*    FU.h
*  COPYRIGHT
*    $VER: FU.h 1.68 (24.10.01) © by Stefan Kost 2001-20010-2001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    23.Oct.2001
*  MODIFICATION HISTORY
*    24.Oct.2001	V 1.68	most recent version
*    23.Oct.2001	V 1.68	most recent version
*    23.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

#ifndef FU_H
#define FU_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_C
	extern void OpenAll(void);
	extern UBYTE Open_BDWin(void);
	extern void CloseAll(void);
	extern void SwitchIDCMPOFF(void);
	extern void SwitchIDCMPON(void);
	extern void SetDefs(void);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

extern struct ExecBase 		*SysBase;
extern struct DosLibrary	*DOSBase;

#ifndef FU_C
	extern struct IntuitionBase		*IntuitionBase;
	extern struct GfxBase	 		*GfxBase;
	extern struct Library 			*AslBase,*DiskfontBase,*UtilityBase,*AmigaGuideBase,*GadToolsBase;
	extern struct Screen			*mmscr,*rscreen;
	extern struct Window			*mmwin,*bdwin;
	extern struct Window			*cowin,*opwin,*zowin,*fowin,*diwin,*prwin,*abwin,*exwin;
	extern struct Window			*rwindow,*owindow,*iwindow;
	extern APTR						VisualInfo;
	extern struct TextFont			*scrfont,*sigfont;
	extern struct FileRequester		*IFF_FRequest,*Col_FRequest;
	extern struct FontRequester		*SCR_FRequest;
	extern struct ViewPort 			*rvp,*mvp;
	extern struct View				*view;
	extern struct RastPort 			rrp[256],orp,irp;
	extern PLANEPTR					planes[8];
	extern UWORD					BPR;
	extern UWORD 					scr_colors4[256];
	extern struct ColorSet32		scr_colors32;

	extern struct MsgPort			*arexxport;		/* Arexx-Defs */
	extern char 					*arexxname;

	extern double x,y,rx,ry;						/* Rendering */
	extern double xd,yd;
	extern UBYTE col[512];
	extern UWORD (*FracFunc)(void);
	extern UWORD (*GetOutsideColor)(double a,double b,double c,double d,UWORD n);
	extern UWORD (*GetInsideColor)(double a,double b,double c,double d);
	extern void (*PsetFunc)(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void (*RectFunc)(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void (*PixelModifier)(void);

	extern uservar uv[64];							/* FormulaInterpreter-Vars */
	extern UWORD luv,lhv;
	extern mathop mabui[256],mabus[64];
	extern UWORD lmopi,lmops;
	extern UWORD bailr,baill;
	extern UBYTE bailt;

	extern double decompho,decomphi;				/* Decomp */
	extern complex *ob;								/* OrbitBuffer */
	extern UWORD oldobsize;							/* Größe für FreeMem */
	extern UWORD obanz;
	extern sbuf sb[1000];					/* SquareBuffer */
	extern double bofabs;					/* nearest orbit */
	extern UWORD bofz;						/* zycle from ^ */

	extern GInfo GfxInfo;					/* large Datastuctures */
	extern FInfo FractalInfo;
	extern RInfo RenderInfo;
	extern PInfo PalInfo;
	extern IInfo InspectInfo;
	extern RTime RunTime;

	extern double opx1,opx2,opy1,opy2;		/* Old Picture Values */
	extern UWORD opxb1,opxb2,opyb1,opyb2;
	extern double rotx,roty;				/* Winkel ( sin,cos ) für Rotation */
	extern double rotpx,rotpy;				/* Mittelpunkt für Verschiebung */
	extern float rps[10][256],gps[10][256],bps[10][256];

	extern struct List ModeList;			/* RenderScrModes */
	extern struct Node ModeNodes[100];
	extern ScrMd Modes[100];

	extern struct List GModeList;			/* GUIScrModes */
	extern struct Node GModeNodes[100];
	extern ScrMd GModes[100];
	extern UBYTE gmaxmodes;					/* How many ScrMd`s are available */

	extern struct List FormulaGadgetList;
	extern struct Node FormulaGadgetNodes[ffanz];
	extern struct List InvCircleList;
	extern struct Node InvCircleNodes[sf0anz];
	extern struct List NormCircleList;
	extern struct Node NormCircleNodes[sf1anz];
	extern struct List InvNewtonList;
	extern struct Node InvNewtonNodes[sf3anz];
	extern struct List NormNewtonList;
	extern struct Node NormNewtonNodes[sf4anz];
	extern struct List InvFixPlaneCList;
	extern struct Node InvFixPlaneCNodes[sf5anz];
	extern struct List InvVarPlaneCList;
	extern struct Node InvVarPlaneCNodes[sf6anz];
	extern struct List NormFixPlaneCList;
	extern struct Node NormFixPlaneCNodes[sf7anz];
	extern struct List NormVarPlaneCList;
	extern struct Node NormVarPlaneCNodes[sf8anz];
	extern struct List FormulaList;
	extern struct Node FormulaNodes[sf2anz];
	extern struct List InsideGadgetList;
	extern struct Node InsideGadgetNodes[isanz];
	extern struct List OutsideGadgetList;
	extern struct Node OutsideGadgetNodes[osanz];
	extern struct Requester NullReq;
	extern char Formulas[sf2anz][40];
	extern UBYTE epointer;					/* EmptyPointer aktive ? */
	extern CycleData cdata;
	extern long rendertime;					/* RenderZeit */
	extern char fd[5][40];
	extern char buffer1[256],buffer2[256],buffer3[256];		/* für StringHooks */
	extern struct Hook hook1,hook2,hook3;
	extern struct StringExtend stringextend1,stringextend2,stringextend3;

	extern FUPrefs_Hdr		fuprefs_hdr;		/* Preferences V1.6 */
	extern FUPrefs_Ver		fuprefs_ver;
	extern FUPrefs_Path	fuprefs_path;
	extern FUPrefs_Gui		fuprefs_gui;
	extern FUPrefs_Defs	fuprefs_defs;

	extern struct TextAttr		ScrFont,SigFont;
	extern struct TagItem		mmwintags[14],smwintags[15],RScreenTags[12];
	extern struct TagItem		RWindowTags[14],OWindowTags[14],IWindowTags[14];
	extern struct TagItem		IFF_Reqtags[8],Col_Reqtags[8],SCR_Reqtags[14];

	extern UWORD __chip Emptypointer[(2+16)*2];

	extern ArrangeList fflist[ffanz];
	extern ArrangeList sf0list[sf0anz];
	extern ArrangeList sf1list[sf1anz];
	extern ArrangeList sf3list[sf3anz];
	extern ArrangeList sf4list[sf4anz];
	extern ArrangeList sf5list[sf5anz];
	extern ArrangeList sf6list[sf6anz];
	extern ArrangeList sf7list[sf7anz];
	extern ArrangeList sf8list[sf8anz];
	extern ArrangeList insidelist[isanz];
	extern ArrangeList outsidelist[osanz];
#endif

//-- definitions --------------------------------------------------------------

#endif /* FU_H */
//-- eof ----------------------------------------------------------------------
