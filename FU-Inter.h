/****h* FractalUniverse/FU-Inter.h [1.68] *
*
*  NAME
*    FU-Inter.h
*  COPYRIGHT
*    $VER: FU-Inter.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#ifndef FU_INTER_H
#define FU_INTER_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_INTER_C
	extern int interpret(void);
	extern int GetVarIX(char *svar1);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

#ifndef FU_INTER_C
	extern uservar uv[64];							/* Formula-Vars */
	extern long rendertime;
	extern struct Custom custom;
	extern mathop mabui[256],mabus[64];
	extern UBYTE fn1bi[20],fn1pi;
	extern UBYTE fn2bi[20],fn2pi;
	extern UBYTE fn3bi[20],fn3pi;
	extern UBYTE fn4bi[20],fn4pi;
	extern UBYTE fn1bs[20],fn1ps;
	extern UBYTE fn2bs[20],fn2ps;
	extern UBYTE fn3bs[20],fn3ps;
	extern UBYTE fn4bs[20],fn4ps;
#endif

//-- definitions --------------------------------------------------------------

#endif /* FU_INTER_H */
//-- eof ----------------------------------------------------------------------
