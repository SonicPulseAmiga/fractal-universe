/****h* FractalUniverse/FU-IFF.h [1.68] *
*
*  NAME
*    FU-IFF.h.c
*  COPYRIGHT
*    $VER: FU-IFF.h 1.68 (24.10.01) © by Stefan Kost 2001-202001
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

#ifndef FU_IFF_H
#define FU_IFF_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_IFF_C
	extern void LoadImage(char *filename);
	extern void SaveImage(char *filename,UBYTE mode);

	extern void matchnrff(UBYTE *nr,char *name);
	extern void matchffnr(UBYTE *nr,char *name);
	extern void matchnrsf(UBYTE *nr,char *name);
	extern void matchsfnr(UBYTE *nr,char *name);
	extern void matchnris(UBYTE *nr,char *name);
	extern void matchisnr(UBYTE *nr,char *name);
	extern void matchnros(UBYTE *nr,char *name);
	extern void matchosnr(UBYTE *nr,char *name);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_IFF_H */
//-- eof ----------------------------------------------------------------------
