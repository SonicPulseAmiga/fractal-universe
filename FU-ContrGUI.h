/******************************************************************************
** FU-CONTRGUI.h                                                             **
**---------------------------------------------------------------------------**
** The Control-Include                                                       **
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
extern struct Window		*mmwin,*smwin,*rwindow,*owindow,*iwindow;
extern APTR					VisualInfo;
extern struct ViewPort 		*rvp,*mvp;
extern struct View			*view;
extern struct RastPort 		rrp[256],orp,irp;
extern struct TagItem		smwintags[15],RScreenTags[12];
extern struct TagItem		RWindowTags[14],OWindowTags[14],IWindowTags[14];
extern PLANEPTR				planes[8];
extern UBYTE				BPR;
