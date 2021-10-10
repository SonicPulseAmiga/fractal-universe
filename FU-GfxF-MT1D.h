/****h* FractalUniverse/FU-GfxF-MT1D.h [1.68] *
*
*  NAME
*    FU-GfxF-MT1D.h
*  COPYRIGHT
*    $VER: FU-GfxF-MT1D.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    24.Oct.2001
*  MODIFICATION HISTORY
*    24.Oct.2001	V 1.68	most recent version
*    24.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

#ifndef FU_GFXF_MT1D_H
#define FU_GFXF_MT1D_H

//-- prototypes ---------------------------------------------------------------

#ifdef FU_GFXF_MT1D_H
	extern void MT1D0Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D0Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D0Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D0Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D0Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D0Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D0Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D0Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D1Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D2Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D3Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT1D4Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_GFXF_MT1D_H */
//-- eof ----------------------------------------------------------------------
