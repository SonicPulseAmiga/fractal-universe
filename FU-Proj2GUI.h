/******************************************************************************
** FU-PROJ2GUI.h                                                             **
**---------------------------------------------------------------------------**
** The Project2-Include                                                      **
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
extern struct Window		*cowin,*opwin,*zowin,*fowin,*diwin,*prwin,*abwin,*exwin;
extern struct Window		*rwindow,*owindow,*iwindow;
extern APTR					VisualInfo;
extern struct FileRequester	*IFF_FRequest,*Col_FRequest;
extern struct FontRequester *SCR_FRequest;
extern struct ViewPort 		*mvp;
extern struct TextFont		*scrfont,*sigfont;
extern struct TextAttr		ScrFont,SigFont;
extern struct TagItem		smwintags[15];
extern struct TagItem		IFF_Reqtags[8],Col_Reqtags[8],SCR_Reqtags[14];
extern UWORD 				scr_colors4[256];
extern struct ColorSet32	scr_colors32;

struct
{
	ULONG *author;
	ULONG *theme;
} thanks[]={
	(ULONG *)"Stephan Quitzsch",					(ULONG *)"IFF-Load Routine & Betatesting",
	(ULONG *)"Matthias Kost",						(ULONG *)"Ideas & Formulas & Betatesting",
	(ULONG *)"Ronny Schütz",						(ULONG *)"Formulas & Betatesting",
	(ULONG *)"Torsten Schulz",						(ULONG *)"Betatesting & lending me his A1200",
	(ULONG *)"Patrick Schlick",						(ULONG *)"Betatesting on A4000 & ideas",
	(ULONG *)"Horst Völz",							(ULONG *)"Formulas",
	(ULONG *)"H.-O.Peitgen & P.H.Richter",			(ULONG *)">The Beauty of Fractals<",
	(ULONG *)"Commodore or whatever it will be",	(ULONG *)"->»» AMIGA ««<-",
	(ULONG *)"Project Pitchfork & Depeche Mode",	(ULONG *)"Wondeful music", 
	(ULONG *)"Stefan Kost alias ENSONIC",			(ULONG *)"Main Author"
};
int thankanz=10;
