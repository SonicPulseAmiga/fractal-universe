/******************************************************************************
** FU-PROJ1GUI.h                                                             **
**---------------------------------------------------------------------------**
** The Project1-Include                                                      **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.5                                                           **
** Date    : 26.02.1995                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

extern struct ExecBase 		*SysBase;
extern struct DosLibrary	*DOSBase;
extern struct IntuitionBase	*IntuitionBase;
extern struct GfxBase		*GfxBase;
extern struct Library 		*AslBase,*DiskfontBase,*UtilityBase,*AmigaGuideBase,*GadToolsBase;
extern struct Screen		*mmscr,*rscreen;
extern struct Window		*mmwin,*smwin;
extern struct Window		*cowin,*opwin,*zowin,*fowin,*diwin,*prwin,*abwin,*exwin;
extern struct Window		*rwindow,*owindow,*iwindow;
extern APTR					VisualInfo;
extern struct FileRequester	*Col_FRequest;
extern struct ViewPort 		*rvp,*mvp;
extern struct TextFont		*scrfont,*sigfont;
extern struct TextAttr		ScrFont,SigFont;
extern struct RastPort 		rrp[256],orp;
extern PLANEPTR				planes[8];
extern struct TagItem		smwintags[15],RScreenTags[12];
extern struct TagItem		RWindowTags[14],OWindowTags[14],IWindowTags[14];
extern struct TagItem 		Col_Reqtags[7];
extern struct List FormulaGadgetList;
extern struct Node FormulaGadgetNodes[ffanz];
extern struct List InvCircleList;
extern struct Node InvCircleNodes[sf0anz+1];
extern struct List NormCircleList;
extern struct Node NormCircleNodes[sf1anz+1];
extern struct List InvNewtonList;
extern struct Node InvNewtonNodes[sf3anz+1];
extern struct List NormNewtonList;
extern struct Node NormNewtonNodes[sf4anz+1];
extern struct List InvFixPlaneCList;
extern struct Node InvFixPlaneCNodes[sf5anz+1];
extern struct List NormFixPlaneCList;
extern struct Node NormFixPlaneCNodes[sf6anz+1];
extern struct List InvVarPlaneCList;
extern struct Node InvVarPlaneCNodes[sf7anz+1];
extern struct List NormVarPlaneCList;
extern struct Node NormVarPlaneCNodes[sf8anz+1];
extern struct List FormulaList;
extern struct Node FormulaNodes[200];
extern struct List InsideGadgetList;
extern struct Node InsideGadgetNodes[isanz];
extern struct List OutsideGadgetList;
extern struct Node OutsideGadgetNodes[osanz];

WORD OutsideDefs[18][2]={
	 -1, -1,	/*  0 BinDecomp */	
	  5, -1,	/*  1 BiomorAbs1 */	
	  5, -1,	/*  2 BiomorRel1 */	
	  5, -1,	/*  3 BiomorAbs2 */	
	  5, -1,	/*  4 BiomorRel2 */	
     50, -1,	/*  5 ContPot */		
	200, -1,	/*  6 Decomposition */
	 -1, -1,	/*  7 DiffIterImag */	
	 -1, -1,	/*  8 DiffIterReal */	
	 -1, -1,	/*  9 DiffIterReIm */	
	 10, -1,	/* 10 DiffParImag */	
	 10, -1,	/* 11 DiffParReal */	
	 10, -1,	/* 12 DiffParReIm */	
	 10, -1,	/* 13 Normal */		
	 -1, -1,	/* 14 Stripes */		
	 -1, -1,	/* 15 SummImagIt */	
	 -1, -1,	/* 16 SummRealIt */	
	 -1, -1		/* 17 SummReImIt */	
};
WORD InsideDefs[12][2]={
	200, -1,	/*  0 BoF60 */		
	 -1, -1,	/*  1 BoF61 */		
	100, -1,	/*  2 Decomposition */
	100, -1,	/*  3 DiffParImag */	
	100, -1,	/*  4 DiffParReal */	
	100, -1,	/*  5 DiffParReIm */	
	200, -1,	/*  6 MagnifyImag */	
	200, -1,	/*  7 MagnifyReal */	
	200, -1,	/*  8 MagnifyReIm */	
	  0, -1,	/*  9 Normal */		
	300,  1,	/* 10 Orbit  */	
};
