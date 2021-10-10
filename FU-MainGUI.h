/******************************************************************************
** FU-MainGUI.h                                                              **
**---------------------------------------------------------------------------**
** The Main-Include                                                          **
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
extern struct Screen		*mmscr;
extern struct Window		*mmwin,*smwin;
extern struct Window		*cowin,*opwin,*zowin,*fowin,*scwin,*diwin,*prwin,*abwin,*exwin;
extern struct Window		*rwindow,*owindow,*iwindow;
extern APTR					VisualInfo;
extern struct FileRequester	*IFF_FRequest,*Col_FRequest;
extern struct ViewPort 		*mvp;
extern struct TextFont		*scrfont,*sigfont;
extern struct TextAttr		ScrFont,SigFont;
extern struct TagItem		mmwintags[14];
extern UWORD 				scr_colors4[256];
extern struct ColorSet32	scr_colors32;
