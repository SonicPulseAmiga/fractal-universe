/****h* <project>/C_Module.c [1.68] *FractalUniverse/FU-ErrMsg.h [1.68] *
*
*  NAME
*    FU-ErrMsg.h
*  COPYRIGHT
*    $VER: FU-ErrMsg.h 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#ifndef FU_ERRMSG_H
#define FU_ERRMSG_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_ERRMSG_C
	extern void Message(char *mess);
	extern long Question(char *mess);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

#ifndef FU_ERRMSG_C
	extern char *mess[];
	extern char *ques[];
#endif

//-- definitions --------------------------------------------------------------

#endif /* FU_ERRMSG_H */
//-- eof ----------------------------------------------------------------------
