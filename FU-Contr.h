/****h* FractalUniverse/FU-Contr.h [1.68] *
*
*  NAME
*    FU-Contr.h
*  COPYRIGHT
*    $VER: FU-Contr.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#ifndef FU_CONTR_H
#define FU_CONTR_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_CONTR_C
	extern void mm_render(void);
	extern void mm_view(void);
	extern void mm_inspect(void);
	extern void preprender(void);
	extern void draw_info(UWORD mx,UWORD my);
	extern void draw_orbit(void);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

#ifndef FU_CONTR_C
	extern complex (*TrigFunc1)(complex p1,complex p2);
	extern complex (*TrigFunc2)(complex p1,complex p2);
	extern complex (*TrigFunc3)(complex p1,complex p2);
	extern complex (*TrigFunc4)(complex p1,complex p2);
#endif

//-- definitions --------------------------------------------------------------

#endif /* FU_CONTR_h */
//-- eof ----------------------------------------------------------------------
