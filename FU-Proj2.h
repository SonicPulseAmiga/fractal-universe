/****h* FractalUniverse/FU-Proj2.h [1.68] *
*
*  NAME
*    FU-Proj2.h
*  COPYRIGHT
*    $VER: FU-Proj2.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#ifndef FU_PROJ2_H
#define FU_PROJ2_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_PROJ2_C
	extern void Open_DOWin(void);
	extern void Test_DOWin(void);
	extern void Open_PRWin(void);
	extern void Test_PRWin(void);
	extern void Open_ABWin(void);

	extern void SavePrefs(char *fn);
	extern void LoadPrefs(char *fn);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_PROJ2_H */
//-- eof ----------------------------------------------------------------------
