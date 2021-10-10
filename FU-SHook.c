/****h* FractalUniverse/FU-SHook.c [1.68] *
*
*  NAME
*    FU-SHook.c
*  COPYRIGHT
*    $VER: FU-SHook.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    String-Gadget-Hookfunctions
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

//-- includes -----------------------------------------------------------------

#define FU_SHOOK_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

unsigned long __asm __saveds hookfunc1(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw);
unsigned long __asm __saveds hookfunc2(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw);
unsigned long __asm __saveds hookfunc3(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw);

//-- definitions --------------------------------------------------------------

unsigned long __asm __saveds hookfunc1(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw)
{
	if(*msg==SGH_KEY)
	{
    	if((sgw->EditOp==EO_REPLACECHAR)||(sgw->EditOp==EO_INSERTCHAR))
        {
	        if((sgw->Code>='0' && sgw->Code<='9') || sgw->Code=='+' || sgw->Code=='-')
            {
	            sgw->WorkBuffer[sgw->BufferPos-1]=sgw->Code;
            }
			else
            {
	            sgw->Actions |= SGA_BEEP;
    	        sgw->Actions &= ~SGA_USE;
            }
        }
		return(-1);
	}
	return(0);
}

unsigned long __asm __saveds hookfunc2(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw)
{
	if(*msg==SGH_KEY)
	{
    	if((sgw->EditOp==EO_REPLACECHAR)||(sgw->EditOp==EO_INSERTCHAR))
        {
	        if((sgw->Code>='0' && sgw->Code<='9') || sgw->Code=='+' || sgw->Code=='-' || sgw->Code=='.')
            {
	            sgw->WorkBuffer[sgw->BufferPos-1]=sgw->Code;
            }
			else
            {
	            sgw->Actions |= SGA_BEEP;
    	        sgw->Actions &= ~SGA_USE;
            }
        }
		return(-1);
	}
	return(0);
}

unsigned long __asm __saveds hookfunc3(register __a1 unsigned long *msg,register __a2 struct SGWork *sgw)
{
	if(*msg==SGH_KEY)
	{
    	if((sgw->EditOp==EO_REPLACECHAR)||(sgw->EditOp==EO_INSERTCHAR))
        {
	        if((sgw->Code>='0' && sgw->Code<='9') || sgw->Code=='+' || sgw->Code=='.')
            {
	            sgw->WorkBuffer[sgw->BufferPos-1]=sgw->Code;
            }
			else
            {
	            sgw->Actions |= SGA_BEEP;
    	        sgw->Actions &= ~SGA_USE;
            }
        }
		return(-1);
	}
	return(0);
}
