/****h* FractalUniverse/FU-GfxF-MT0D.h [1.68] *
*
*  NAME
*    FU-GfxF-MT0D.h
*  COPYRIGHT
*    $VER: FU-GfxF-MT0D.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#ifndef FU_GFXF_MT0D_H
#define FU_GFXF_MT0D_H

//-- prototypes ---------------------------------------------------------------

#ifdef FU_GFXF_MT0D_H
	extern void MT0D0Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D0Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D0Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D0Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D0Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D0Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D0Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D0Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D1Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D2Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D3Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
	extern void MT0D4Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_GFXF_MT0D_H */
//-- eof ----------------------------------------------------------------------
