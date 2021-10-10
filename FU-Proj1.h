/****h* FractalUniverse/FU-Proj1.h [1.68] *
*
*  NAME
*    FU-Proj1.h
*  COPYRIGHT
*    $VER: FU-Proj1.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#ifndef FU_PROJ1_H
#define FU_PROJ1_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_PROJ1_C
	extern void Open_COWin(void);
	extern void Test_COWin(void);
	extern void Refresh_COWin(void);
	extern void Open_ZOWin(void);
	extern void Test_ZOWin(void);
	extern void Refresh_ZOWin(void);
	extern void Open_OPWin(void);
	extern void Test_OPWin(void);
	extern void Refresh_OPWin(void);
	extern void Open_FOWin(void);
	extern void Test_FOWin(void);
	extern void Refresh_FOWin(void);
	extern void mm_screen(void);

	extern void LoadPalette(char *fn);
	extern void SavePalette(char *fn);
	extern void RefreshPalShapes(struct RastPort rp,struct Gadget *Gadgets[]);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

#ifndef FU_PROJ1_C
#endif

//-- definitions --------------------------------------------------------------

#endif /* FU_PROJ1_H */
//-- eof ----------------------------------------------------------------------
