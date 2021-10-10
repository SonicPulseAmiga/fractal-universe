/****h* FractalUniverse/FU-SHook.h [1.68] *
*
*  NAME
*    FU-SHook.h
*  COPYRIGHT
*    $VER: FU-SHook.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#ifndef FU_SHOOK_H
#define FU_SHOOK_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_SHOOK_C
	extern unsigned long __asm __saveds hookfunc1(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw);
	extern unsigned long __asm __saveds hookfunc2(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw);
	extern unsigned long __asm __saveds hookfunc3(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_SHOOK_H */
//-- eof ----------------------------------------------------------------------
