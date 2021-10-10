/****h* FractalUniverse/FU-Tools.h [1.68] *
*
*  NAME
*    FU-Tools.h
*  COPYRIGHT
*    $VER: FU-Tools.h 1.68 (23.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    23.Oct.2001
*  MODIFICATION HISTORY
*    23.Oct.2001	V 1.68	most recent version
*    23.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

#ifndef FU_TOOLS_H
#define FU_TOOLS_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_TOOLS_C
	extern void DrawGad(struct RastPort rp,UWORD x,UWORD y,UWORD w,UWORD h,UBYTE akt);
	extern void DrawBox(struct RastPort rp,UWORD x,UWORD y,UWORD w,UWORD h,char *text);
	extern char *StringCopy(char *src);
	extern void FilterString(char *strbuf);
	extern void StripString(char *strbuf);
	extern void Help(char *guidename,char *nodename);
	extern void GetRexxStr(char *rstr,char *params);
	extern void ChangeScreen(void);
	extern void BytesPerRow(void);
	extern UWORD CheckSum1(UWORD chk);
	extern int CheckGad_int(struct Gadget *Gadget,struct Window *win,UBYTE chkrng,int minv,int maxv);
	extern double CheckGad_dbl(struct Gadget *Gadget,struct Window *win,UBYTE chkrng,double minv,double maxv);
	extern void Swap_int(int *val1,int *val2);
	extern void Swap_shr(short *val1,short *val2);
	extern void Swap_dbl(double *val1,double *val2);
	extern int GetScrModes(struct List *ModeList,struct Node *ModeNodes,ScrMd *Modes,int maxanz,int minx,int miny,int mind);
	extern void ScrMdReq(struct List *ModeList,ScrMd *Modes,SelScr *ScreenEntry);
	extern long DepthToColors(struct Gadget *gad,WORD level);
	extern UBYTE match_nr2ix(UBYTE nr,UBYTE anz,ArrangeList *alist);
	extern UBYTE match_name2ix(UBYTE *name,UBYTE anz,ArrangeList *alist);
	extern void SortAList(UBYTE anz,ArrangeList *alist);
	extern void BuildList(struct Node *Nodes,struct List *List,UBYTE anz,ArrangeList *alist);
	extern void ScanFormulas(void);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_TOOLS_H */
//-- eof ----------------------------------------------------------------------
