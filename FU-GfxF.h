/****h* <project>/C_Module.c [1.68] *FractalUniverse/FU-GfxF.h [1.68] *
*
*  NAME
*    FU-GfxF.hc
*  COPYRIGHT
*    $VER: FU-GfxF.h 1.68 (24.10.01) © by Stefan Kost 2001-22001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    24.Oct.2001
*  MODIFICATION HISTORY
*    24.Oct.2001	V 1.68	most recent version
*    24.Oct.2001	V 1.68	most recent version
*    24.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

#ifndef FU_GFXF_H
#define FU_GFXF_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_GFXF_C
	extern void SetPaletteMode(void);
	extern void MakeColorPalettes(void);
	extern void SetColorPalette(void);
	extern void GetPalShape(UBYTE shtype,float *buf);
	extern void DrawPalShape(struct RastPort rp,UBYTE c,float *buf);
	extern void DrawColorRange(struct RastPort rp);
	extern void SetColorRange(UBYTE nr);
	extern UBYTE GetBrightestCol(void);
	extern UBYTE GetDarkestCol(void);
	extern void AssignGfxFuncs(void);
	extern void MyWritePixel(UWORD x,UWORD y,UBYTE c);
	extern void Zoom(UBYTE ztype,UBYTE zmode,UBYTE zsnap,UWORD *x1,UWORD *y1,UWORD *x2,UWORD *y2);
	extern void Pick(double *parx,double *pary);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

#ifndef FU_GFXF_C
	extern UWORD				colors4[11][512];
	extern struct ColorSet32	colors32[11];
	extern double derr;

	extern UBYTE D1[2][2][2];
	extern UBYTE D2[4][2][2];
	extern UBYTE D3[16][4][4];
#endif

//-- definitions --------------------------------------------------------------

#endif /* FU_GFXF_H */
//-- eof ----------------------------------------------------------------------
