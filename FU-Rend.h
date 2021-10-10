/****h* FractalUniverse/FU-Rend.h [1.68] *
*
*  NAME
*    FU-Rend.hc
*  COPYRIGHT
*    $VER: FU-Rend.h 1.68 (24.10.01) © by Stefan Kost 2001-22001
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

#ifndef FU_REND_H
#define FU_REND_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_REND_C
	extern UBYTE RenderSolid(void);
	extern UBYTE RenderSquare(void);
	extern UBYTE RenderFastSquare(void);
	extern UBYTE RenderPreview(void);
	extern void RenderTurbo(void);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_REND_H */
//-- eof ----------------------------------------------------------------------
