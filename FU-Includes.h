/****h* FractalUniverse/FU-Includes.h [1.68] *
*
*  NAME
*    FU-Includes.h
*  COPYRIGHT
*    $VER: FU-Includes.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

//-- Ansi C/C++

#include <ctype.h>
#include <dos.h>
#include <math.h>
#include <m68881.h>			// include math-extensions depending on type of math beeing used
#include <mffp.h>
#include <mieeedoub.h>
#define PIM2	6.28318530717958647692
#define MAXBYTE 255
#define MAXBYTEP 127
#define MAXBYTEN -128
#define MAXWORD 65535
#define MAXWORDP 32767
#define MAXWORDN -32768
#define MAXLONG 4294967295
#define MAXLONGP 2147483647
#define MAXLONGN -2147483648
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//-- Amiga OS

#define __USE_SYSBASE
#include <exec/types.h>
#include <cmacros.h>
#include <devices/inputevent.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <exec/exec.h>
#include <exec/lists.h>
#include <exec/memory.h>
#include <exec/nodes.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <graphics/gfxmacros.h>
#include <graphics/display.h>
#include <graphics/displayinfo.h>
#include <hardware/custom.h>
#include <intuition/gadgetclass.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>
#include <intuition/screens.h>
#include <intuition/sghooks.h>
#include <libraries/amigaguide.h>
#include <libraries/asl.h>
#include <libraries/dos.h>
#include <libraries/diskfont.h>
#include <libraries/gadtools.h>
#include <utility/date.h>
#include <utility/hooks.h>
#include <utility/tagitem.h>

#include <clib/alib_protos.h>			/* Prototypes for Supportfunctions */

#include <proto/amigaguide.h>			/* Prototypes for Libraryfunctions */
#include <proto/asl.h>
#include <proto/diskfont.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/gadtools.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/utility.h>

#define __CXM33 __UCXM33				/* für Utillitie.library */
#define __CXD33 __UCXD33
#define __CXM22 __UCXM22
#define __CXD22 __UCXD22

//-- Local

#include "project.h"

//-- Debugtools

#define DEBUG_SRCPATH "project:"
#include <debug/dt_decl.h>

//-------------------------------------------------------------------------------------------------

#define	MaxCmdLen		256				/* für Arexx-Port */
#define MaxParLen		50
#define MaxParAnz		20

#define BoF60 0							/* für Colormodelle */
#define BoF61 1
#define IDecomp 2
#define ODecomp 5
#define OBDecomp 0

/*---------------------------------------------------------------------------------------------------------------*/

typedef struct							/* allgem. complex */
{
	double r,i;
} complex;

typedef struct							/* complex integer */
{
	LONG r,i;
} complex_i;

typedef struct							/* complex float */
{
	double r,i;
} complex_f;

typedef struct							/* SquareBuffer */
{
	UWORD x1,y1,x2,y2;
} sbuf;

/*---------------------------------------------------------------------------------------------------------------*/

typedef struct				/* Zuweisungsliste */
{
	char name[50];				/* unbedingt so lassen, wegen Bufferliste */
	WORD nr;
} ArrangeList;

/*---------------------------------------------------------------------------------------------------------------*/

typedef struct
{
	UWORD xres,yres;			/* X / Y Auflösung */
	UBYTE xdef,ydef;			/* XDefault,YDefault */
	UBYTE oscan;				/* OverScanType */
	UBYTE depth;				/* Farbtiefe */
	UWORD realcol;				/* reale Farbanzahl */
	UWORD maxcol;				/* Anzahl der Farben */
	UWORD absmaxcol;			/* maxcol-1 */
	ULONG scrmode;				/* Screenmode */
	float aspect;				/* Aspect x=y*aspect y=x:aspect */
	UBYTE autoscroll;			/* Autoscrollingscreen ? */
	UBYTE revpal;				/* Gespiegelte Farbpalette benutzen ? */
	UBYTE dither;				/* Welches Dithering */
	UBYTE ordscl;				/* Scaling der Palette Bei Orderd >=1 */
	UBYTE palscl;				/* Palettescaling (stretch) >=1 */
	UBYTE palmap;				/* Palettemapping */
	UBYTE gfxtyp;				/* Welche Grafikroutinen */
	UBYTE palbits;				/* 4 oder 8 ? */
} GInfo;

typedef struct
{
	UBYTE mirrorx,mirrory;						/* Grafik spiegeln */
	double x1,y1,x2,y2;							/* Grundbild */
	complex par1,par2,par3,par4;				/* Zusatzparameter */
	double bailout;								/* Bailout */
	UBYTE tpar1,tpar2,tpar3,tpar4;				/* Trig.functions */
	UBYTE parendi,pickendi,trigendi;			/* Bitfelder für Paramenter|Trigon.|Pick-Enable|Disable */
	UBYTE type;									/* 0=invfix 1=invvar 2=normfix 3=normvar */
	UBYTE init;									/* 0=ZeroInit 1=PixelInit */
} FInfo;

typedef struct
{
	UBYTE mirrorx,mirrory;						/* Grafik spiegeln */
	double x1,y1,x2,y2;							/* Koordinaten des Ausschnittes */
	double rot;									/* Winkel -> Rotation */
	complex par1,par2,par3,par4;				/* Zusatzparameter */
	double bailout;								/* Bailout */
	UBYTE tpar1,tpar2,tpar3,tpar4;				/* Trig.functions */
	UBYTE parendi,pickendi,trigendi;			/* Bitfelder für Paramenter|Trigon.|Pick-Enable|Disable */
	UWORD xb1,yb1,xb2,yb2;						/* Window für Berechnung */
	UWORD z;									/* Zyclen */
	UBYTE outside;								/* Outsidecoloring model */
	UWORD outpar1,outpar2;						/* Outsideparameter */
	UBYTE inside;								/* InsideColoring model */
	UWORD inpar1,inpar2;						/* Insideparameter */
	UBYTE rendermode;							/* Solid=0 , Square=1 , ... */
	UBYTE signal;								/* 0=disable , 1=enable -> DisplayBeep */
	UBYTE obstep;								/* Orbitschrittweite */
	UBYTE obsize;								/* 0=>0.5; 1=>0.0375; 2=>0.25 */
	UBYTE obconnect;							/* 0=> nein; 1=> ja */
} RInfo;

typedef struct
{
	UBYTE xoff,yoff;							/* Verschiebungsoffsett */
	UBYTE pst;									/* Palette Shape Typ */
	UBYTE scx,scy;								/* Scalingfactor X & Y */
} ColorPar;

typedef struct
{
	ColorPar r[10],g[10],b[10];					/* Red,Green,Blue */
} PInfo;

typedef struct
{
	UBYTE dcol,bcol;							/* Farben */
	UWORD ox,oy,obxh,obyh;						/* Max.Koords */
} IInfo;

typedef struct
{
	ULONG sig_in;								/* Signalmaske */
	UBYTE rexxactive;							/* Ist eine Funktion von einem REXX-Scripts aus aufgerufen worden ? */
	UBYTE fracfunc,subfunc;						/* Choosen Func. */
	UBYTE rscreenmode,gscreenmode;				/* ScrMd.Nr. */
	UBYTE maxmodes;								/* How many ScrMd`s are available */
	UBYTE picavail;								/* Is a picture available */
	UBYTE aktpal;								/* Which palette is currently used */
	UBYTE kickstart;							/* Which Kickstart-version is present */
	UBYTE epointer;								/* EmptyPointer aktive ? */
	UBYTE quitfu;								/* Programm beenden ? */
	UWORD xres,yres;							/* aktuelle Auflösung */
	float scalex;								/* X-Scalefactor (siehe AmigaProfi S.348) */
	float scaley;								/* Y-Scalefactor */
	char fontname[80];							/* Fontname */
	UBYTE status;								/* Status => 0=Demoversion */
	UWORD scx[700];
	UWORD scy[300];
} RTime;

/*---------------------------------------------------------------------------------------------------------------*/

typedef struct
{
	char vname[10];
	complex z;
} uservar;

typedef struct
{
	complex (*MathFunc)(complex p1,complex p2);	/* Mathemat. Funktion */
	complex *p1,*p2;							/* Parameter 1 & 2 */
	complex *e;									/* Ergebnis */
} mathop;

/*---------------------------------------------------------------------------------------------------------------*/

typedef struct
{
	UBYTE cycling;				/* Active 0 | 1 */
	UBYTE rate;					/* Pause */
	UBYTE dir;					/* Richtung 0-Vorwärts | 1-Rückwärts */
	UBYTE pos;					/* akt. Position */
} CycleData;

typedef struct
{
	struct Rectangle OScans[5];
	UBYTE dep;
	UBYTE palbits;
	ULONG scrmode;
	char name[DISPLAYNAMELEN];
} ScrMd;

typedef struct
{
	UWORD scrmdnr;
	UWORD xres,yres;
	UBYTE xdef,ydef;						/* XDefault,YDefault */
	UBYTE dep;
	UBYTE oscan;
	UBYTE palbits;
	UBYTE change;
	ULONG scrmode;
	char name[DISPLAYNAMELEN];
} SelScr;

/*---------------------------------------------------------------------------------------------------------------*/

#define ffanz 9				/* fracfunc */
#define sf0anz 8			/* InvCircle */
#define sf1anz 8			/* NormCircle */
#define sf2anz 256			/* Formula */
#define sf3anz 5			/* InvNewton */
#define sf4anz 5			/* NormNewton */
#define sf5anz 10			/* InvFixPlaneC */
#define sf6anz 11			/* InvVarPlaneC */
#define sf7anz 10			/* NormFixPlaneC */
#define sf8anz 11			/* NormVarPlaneC */
#define isanz 13			/* Inside`s */
#define osanz 18			/* Outside`s */

/*---------------------------------------------------------------------------------------------------------------*/

struct ColorEntry32
{
	ULONG	r,g,b;
};

struct ColorSet32
{
	WORD				NumColors;
	WORD				FirstColor;
	struct ColorEntry32	Entry[256];
	WORD				Terminator;
};

/*---------------------------------------------------------------------------------------------------------------*/

#define PREF_FORM		MakeID('F','O','R','M')
#define PREF_PREF		MakeID('P','R','E','F')
#define PREF_VERS		MakeID('V','E','R','S')
#define PREF_PATH		MakeID('P','A','T','H')
#define PREF_GUI_		MakeID('G','U','I','_')
#define PREF_DEFS		MakeID('D','F','S','S')
#define PREF_MISC		MakeID('M','I','S','C')

typedef struct							/* Prefs V3.1 */
{
	ULONG	id;								/* FORM,VERS,PATH,GUI_,DEFS */
	ULONG	len;							/* 4+(8+2)+(8+512)+(8+144)+(8+190)=884 */
} FUPrefs_Hdr;

typedef struct								/* VERS : 2 Bytes */
{
	UBYTE	ver;							/* Version   : 1 */
	UBYTE	rev;							/* Reversion : 6 */
} FUPrefs_Ver;

typedef struct								/* PATH : 512 Bytes */
{
	char iff_path[256];						/* Pfade für Filerequester */
	char color_path[256];
} FUPrefs_Path;

typedef struct								/* GUI_ : 144 Bytes */
{
	ULONG	scrmode;						/* ScreenMode */
	UWORD	xres,yres;						/* Auflösung */
	UBYTE 	depth;							/* Farbtiefe */
	UBYTE	oscan;							/* Overscan */
	UBYTE	autoscroll;						/* Autoscroll ? */
	UBYTE 	palbits;						/* 2,4,8 ? */
	UBYTE	xdef,ydef;						/* XDefault,YDefault */
	struct	ColorSpec ScreenColors[5];		/* Bildschirmfarben (40 Bytes) */
	char	fontname[80];					/* Fontname */
	UBYTE	fontsize;						/* Fontgröße */
	UBYTE	pad1;							/* leer */
} FUPrefs_Gui;

typedef struct								/* DEFS : 190 Bytes */
{
	ULONG	scrmode;						/* ScreenMode */				/* 20 Bytes */
	UWORD	xres,yres;						/* Auflösung */
	UBYTE 	depth;							/* Farbtiefe */
	UBYTE	oscan;							/* Overscan */
	UBYTE	autoscroll;						/* Autoscroll ? */
	UBYTE	xdef,ydef;						/* XDefault,YDefault */
	UBYTE	revpal;							/* Gespiegelte Farbpalette benutzen ? */
	UBYTE	dither;							/* Welches Dithering */
	UBYTE	ordscl;							/* Scaling der Palette Bei Orderd >=1 */
	UBYTE	palscl;							/* Palettescaling (stretch) >=1 */
	UBYTE	palmap;							/* Palettemapping */
	UBYTE 	gfxtyp;							/* Welche Grafikroutinen */
	UBYTE 	palbits;						/* 2,4,8 ? */

	UBYTE 	outside;						/* Outsidecoloring model */		/* 15 Bytes */
	UWORD 	outpar1,outpar2;				/* Outsideparameter */
	UBYTE 	inside;							/* InsideColoring model */
	UWORD 	inpar1,inpar2;					/* Insideparameter */
	UBYTE 	rendermode;						/* Solid=0 , Square=1 , ... */
	UBYTE 	signal;							/* 0=disable , 1=enable -> DisplayBeep */
	UBYTE 	obstep;							/* Orbitschrittweite */
	UBYTE 	obsize;							/* 0=>0.5; 1=>0.0375; 2=>0.25 */
	UBYTE 	obconnect;						/* 0=> nein; 1=> ja */

	UBYTE	screenmode;						/* */							/* 5 Bytes */
	UBYTE 	fracfunc;
	UBYTE	subfunc;
	UBYTE	cyclerate;						/* für Colorcycling */
	UBYTE	cycledir;

	PInfo	PalInfo;						/* akt. Palettes */				/* 150 Bytes */
} FUPrefs_Defs;

/*---------------------------------------------------------------------------------------------------------*/

#include "FU.h"
#include "FU-ColF.h"
#include "FU-Contr.h"
#include "FU-Cplx.h"
#include "FU-GfxF.h"
#include "FU-GfxF-MT0D.h"
#include "FU-GfxF-MT1D.h"
#include "FU-ErrMsg.h"
#include "FU-Func.h"
#include "FU-IFF.h"
#include "FU-Inter.h"
#include "FU-IORx.h"
#include "FU-Main.h"
#include "FU-Proj1.h"
#include "FU-Proj2.h"
#include "FU-Rend.h"
#include "FU-SHook.h"
#include "FU-Tools.h"

/*---------------------------------------------------------------------------------------------------------*/
