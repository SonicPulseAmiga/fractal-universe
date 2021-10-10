/******************************************************************************
** FU-GUI.h                                                                  **
**---------------------------------------------------------------------------**
** The Basis-Include                                                         **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.66                                                          **
** Date    : 07.04.1995                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

UWORD __chip Stopwatch[(2+16)*2]={
	0x0000,0x0000,

	0x0400,0x07C0,
	0x0000,0x07C0,
	0x0100,0x0380,
	0x0000,0x07E0,
	0x07C0,0x1FF8,
	0x1FF0,0x3FEC,
	0x3FF8,0x7FDE,
	0x3FF8,0x7FBE,
	0x7FFC,0xFF7F,
	0x7EFC,0xFFFF,
	0x7FFC,0xFFFF,
	0x3FF8,0x7FFE,
	0x3FF8,0x7FFE,
	0x1FF0,0x3FFC,
	0x07C0,0x1FF8,
	0x0000,0x07E0,

	0x0000,0x0000
};

UWORD __chip Emptypointer[6]={
	0x0000,0x0000,
	0x0000,0x0000,
	0x0000,0x0000
};

struct TextAttr ScrFont={			/* wird noch belegt */
	0l,0,0x00,0x00
};
struct TextAttr SigFont={
	"TrinomicSign.font",6,0x00,0x00
};

struct TagItem IFF_Reqtags[]={
	ASLFR_TitleText,		(ULONG)"Select an IFF-File",
	ASLFR_Window,			0l,
	ASLFR_InitialLeftEdge,	180,
	ASLFR_InitialTopEdge,	60,
	ASLFR_InitialWidth,		300,
	ASLFR_InitialHeight,	184,
	ASLFR_InitialDrawer,	0l,
	ASLFR_RejectIcons,		TRUE,
	ASLFR_DoSaveMode,		FALSE,
	TAG_DONE
};

struct TagItem Col_Reqtags[]={
	ASLFR_TitleText,		(ULONG)"Select a Palette-File",
	ASLFR_Window,			0l,
	ASLFR_InitialLeftEdge,	180,
	ASLFR_InitialTopEdge,	60,
	ASLFR_InitialWidth,		300,
	ASLFR_InitialHeight,	184,
	ASLFR_InitialDrawer,	0l,
	ASLFR_RejectIcons,		TRUE,
	ASLFR_DoSaveMode,		FALSE,
	TAG_DONE
};

struct TagItem SCR_Reqtags[]={
	ASLFO_TitleText,		(ULONG)"Select a Font",
	ASLFO_Window,			0l,
	ASLFO_InitialLeftEdge,	180,
	ASLFO_InitialTopEdge,	60,
	ASLFO_InitialWidth,		300,
	ASLFO_InitialHeight,	184,
	ASLFO_InitialName,		0l,
	ASLFO_InitialSize,		0l,
	ASLFO_FixedWidthOnly,	TRUE,
	ASLFO_MinHeight,		6,
	ASLFO_MaxHeight,		32,
	ASLFO_MaxFrontPen,		1,
	ASLFO_MaxBackPen,		1,
	TAG_DONE
};

#define COL_GRAY1 0
#define COL_BLACK 1
#define COL_WHITE 2
#define COL_COLOR 3

UWORD DriPens[]={
	COL_WHITE,	/* DETAILPEN        */
	COL_BLACK,	/* BLOCKPEN         */
	COL_BLACK,	/* TEXTPEN          */
	COL_WHITE,	/* SHINEPEN         */
	COL_BLACK,	/* SHADOWPEN	    */
	COL_COLOR,	/* FILLPEN		    */
	COL_BLACK,	/* FILLTEXTPEN      */
	COL_GRAY1,	/* BACKGROUNDPEN	*/
	COL_WHITE,	/* HIGHLIGHTTEXTPEN */
	COL_BLACK,	/* BARDETAILPEN	    */
	COL_WHITE,	/* BARBLOCKPEN      */
	COL_BLACK,	/* BARTRIMPEN       */
	(unsigned short)~0			/* END OF ARRAY     */
};

struct TagItem mmscrtags[]={
	SA_Left,		0,
	SA_Top,			0,
	SA_Width,		680,
	SA_Height,		270,
	SA_Depth,		4,
	SA_Title,		(ULONG)"Fractal-Universe V1.66 ControlScreen",
	SA_Colors,		0l,
	SA_Font,		(ULONG)(&ScrFont),
	SA_Type,		CUSTOMSCREEN,
	SA_DisplayID,	PAL_MONITOR_ID|HIRES_KEY,
	SA_Pens,		(ULONG)DriPens,
	SA_AutoScroll,	FALSE,
	SA_Overscan,	0,
	SA_Interleaved,	TRUE,
	SA_MinimizeISG,	TRUE,
	TAG_DONE
};

struct TagItem mmwintags[]={
	WA_Left,		0,
	WA_Top,			0,
	WA_Width,		680,
	WA_Height,		270,
	WA_IDCMP,		BUTTONIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW,
	WA_Flags,		WFLG_SMART_REFRESH|WFLG_ACTIVATE|WFLG_DEPTHGADGET|WFLG_CLOSEGADGET|WFLG_RMBTRAP|WFLG_DRAGBAR|WFLG_NEWLOOKMENUS,
	WA_Gadgets,		0l,
	WA_Title,		(ULONG)"Fractal-Universe V1.66",
	WA_ScreenTitle,	(ULONG)"Fractal-Universe V1.66 ControlScreen",
	WA_CustomScreen,0l,
	WA_MinWidth,	680,
	WA_MinHeight,	270,
	WA_MaxWidth,	680,
	WA_MaxHeight,	270,
	TAG_DONE
};

struct TagItem smwintags[]={
	WA_Left,		50,
	WA_Top,			25,
	WA_Width,		540,
	WA_Height,		200,
	WA_IDCMP,		BUTTONIDCMP|LISTVIEWIDCMP|SLIDERIDCMP|IDCMP_MOUSEBUTTONS|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW,
	WA_Flags,		WFLG_SMART_REFRESH|WFLG_ACTIVATE|WFLG_DEPTHGADGET|WFLG_CLOSEGADGET|WFLG_RMBTRAP|WFLG_DRAGBAR|WFLG_REPORTMOUSE|WFLG_NEWLOOKMENUS,
	WA_Gadgets,		0l,
	WA_Title,		0l,
	WA_ScreenTitle,	(ULONG)"Fractal-Universe V1.66 ControlScreen",
	WA_CustomScreen,0l,
	WA_MinWidth,	540,
	WA_MinHeight,	175,
	WA_MaxWidth,	540,
	WA_MaxHeight,	175,
	TAG_DONE };

struct TagItem bdwintags[]={
	WA_Left,		0,
	WA_Top,			1,
	WA_Width,		640,
	WA_Height,		264,
	WA_IDCMP,		0l,
	WA_Flags,		WFLG_SMART_REFRESH|WFLG_RMBTRAP|WFLG_BORDERLESS|WFLG_BACKDROP|WFLG_NEWLOOKMENUS,
	WA_Gadgets,		0l,
	WA_ScreenTitle,	(ULONG)"Fractal-Universe V1.66 ControlScreen",
	WA_CustomScreen,0l,
	WA_MinWidth,	640,
	WA_MinHeight,	264,
	WA_MaxWidth,	640,
	WA_MaxHeight,	264,
	TAG_DONE
};

struct TagItem RScreenTags[]={
	SA_Left,		0,
	SA_Top,			0,
	SA_Width,		320,
	SA_Height,		256,
	SA_Depth,		5,
	SA_Title,		(ULONG)"FractalUniverse V1.66 RenderScreen",
	SA_Font,		(ULONG)(&ScrFont),
	SA_Type,		CUSTOMSCREEN,
	SA_DisplayID,	PAL_MONITOR_ID|LORES_KEY,
	SA_AutoScroll,	FALSE,
	SA_Overscan,	0,
	SA_Pens,		(ULONG)DriPens,
	TAG_IGNORE,		0,				/* für SA_ColorMapEntries */
	SA_Behind,		TRUE,
	TAG_IGNORE,		0,				/* for SA_Parent */
	TAG_DONE };

struct TagItem RWindowTags[]={
	WA_Left,		0,
	WA_Top,			0,
	WA_Width,		320,
	WA_Height,		256,
	WA_IDCMP,		IDCMP_RAWKEY,
	WA_Flags,		WFLG_ACTIVATE|WFLG_SMART_REFRESH|WFLG_BORDERLESS|WFLG_REPORTMOUSE|WFLG_RMBTRAP,
	WA_Title,		NULL,
	WA_ScreenTitle,	(ULONG)"FractalUniverse V1.66 RenderScreen",
	WA_CustomScreen,0L,
	WA_MinWidth,	320,
	WA_MinHeight,	256,
	WA_MaxWidth,	320,
	WA_MaxHeight,	256,
	TAG_DONE };

struct TagItem OWindowTags[]={
	WA_Left,		200,
	WA_Top,			155,
	WA_Width,		0,
	WA_Height,		0,
	WA_IDCMP,		NULL,
	WA_Flags,		WFLG_ACTIVATE|WFLG_SMART_REFRESH|WFLG_RMBTRAP|WFLG_DRAGBAR|WFLG_GIMMEZEROZERO,
	WA_Title,		(ULONG)"Orbit",
	WA_ScreenTitle,	(ULONG)"FractalUniverse V1.66 RenderScreen",
	WA_CustomScreen,0L,
	WA_MinWidth,	0,
	WA_MinHeight,	0,
	WA_MaxWidth,	0,
	WA_MaxHeight,	0,
	TAG_DONE };

struct TagItem IWindowTags[]={
	WA_Left,		0,
	WA_Top,			0,
	WA_Width,		140,
	WA_Height,		60,
	WA_IDCMP,		NULL,
	WA_Flags,		WFLG_ACTIVATE|WFLG_SMART_REFRESH|WFLG_RMBTRAP|WFLG_DRAGBAR|WFLG_GIMMEZEROZERO,
	WA_Title,		(ULONG)"Inspect",
	WA_ScreenTitle,	(ULONG)"FractalUniverse V1.66 RenderScreen",
	WA_CustomScreen,0L,
	WA_MinWidth,	140,
	WA_MinHeight,	60,
	WA_MaxWidth,	140,
	WA_MaxHeight,	60,
	TAG_DONE };

#include "backlogo.h"
