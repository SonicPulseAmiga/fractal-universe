/****h* FractalUniverse/FU-Main.c [1.68] *
*
*  NAME
*    FU-Main.c
*  COPYRIGHT
*    $VER: FU-Main.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    23.Oct.2001
*  MODIFICATION HISTORY
*    24.Oct.2001	V 1.68	most recent version
*    23.Oct.2001	V 0.00	initial version
*  NOTES
*
*******
*/

//-- includes -----------------------------------------------------------------

#define FU_MAIN_C
#include "FU-Includes.h"
//#include "FU-MainGUI.h"

//-- prototypes ---------------------------------------------------------------

UBYTE Open_MMWin(void);
void Test_MMWin(void);
void Refr_MMWin(void);
void Close_MMWin(void);

//-- globals ------------------------------------------------------------------

struct Gadget				*mm_GList=0l;
struct Gadget				*mm_Gadgets[2];

//-- definitions --------------------------------------------------------------

UBYTE Open_MMWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	struct RastPort mmrp;
	UBYTE ret=1;

	if(g=CreateContext(&mm_GList))
	{
		ng.ng_LeftEdge		=RunTime.scx[15];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[70];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="_Colors";
		ng.ng_GadgetID		=2;
		ng.ng_Flags			=PLACETEXT_IN;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="_Zoom";
		ng.ng_GadgetID		=7;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[44];
		ng.ng_GadgetText	="_Options";
		ng.ng_GadgetID		=8;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[55];
		ng.ng_GadgetText	="_Formula";
		ng.ng_GadgetID		=0;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[66];
		ng.ng_GadgetText	="_Screen";
		ng.ng_GadgetID		=1;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_LeftEdge		=RunTime.scx[90];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_GadgetText	="_Disk Op.";
		ng.ng_GadgetID		=5;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="_Prefs";
		ng.ng_GadgetID		=6;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[44];
		ng.ng_GadgetText	="_About";
		ng.ng_GadgetID		=3;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[55];
		ng.ng_GadgetText	="_Exit";
		ng.ng_GadgetID		=4;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);


		ng.ng_LeftEdge		=RunTime.scx[175];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_GadgetText	="_Render";
		ng.ng_GadgetID		=9;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="_View";
		ng.ng_GadgetID		=10;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		mm_Gadgets[0]=g;

		ng.ng_TopEdge		=RunTime.scy[44];
		ng.ng_GadgetText	="_Inspect";
		ng.ng_GadgetID		=11;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		mm_Gadgets[1]=g;

		if(g)
		{
			mmwintags[ 1].ti_Data=fuprefs_gui.fontsize+3;
			mmwintags[12].ti_Data=mmwintags[10].ti_Data=mmwintags[2].ti_Data=RunTime.scx[260];
			mmwintags[13].ti_Data=mmwintags[11].ti_Data=mmwintags[3].ti_Data=RunTime.scy[90];
			mmwintags[ 6].ti_Data=(ULONG)mm_GList;
			if(mmwin=OpenWindowTagList(0l,mmwintags))
			{
				GT_RefreshWindow(mmwin,0l);

				mmrp=*mmwin->RPort;
				DrawBox(mmrp,RunTime.scx[ 10],RunTime.scy[15],RunTime.scx[155],RunTime.scy[68],"Project");
				DrawBox(mmrp,RunTime.scx[170],RunTime.scy[15],RunTime.scx[ 80],RunTime.scy[68],"Control");

				RunTime.sig_in|=(1L<<mmwin->UserPort->mp_SigBit);
				ret=0;
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
	return(ret);
}

void Test_MMWin(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;

	while(imsg=GT_GetIMsg(mmwin->UserPort))
	{
		iclass	=imsg->Class;
		iadr	=imsg->IAddress;
		icode	=imsg->Code;
		GT_ReplyIMsg(imsg);
		switch(iclass)
		{
			case IDCMP_GADGETUP:
				switch((int)(((struct Gadget *)iadr)->GadgetID))
				{
					case 2:				/* Colors */
						if(!cowin) Open_COWin();
						else
						{
							WindowToFront(cowin);
							ActivateWindow(cowin);
						}
						break;
					case 7:				/* Zoom */
						if(!zowin) Open_ZOWin();
						else
						{
							WindowToFront(zowin);
							ActivateWindow(zowin);
						}
						break;
					case 8:				/* Options */
						if(!opwin) Open_OPWin();
						else
						{
							WindowToFront(opwin);
							ActivateWindow(opwin);
						}
						break;
					case 0:				/* Formula */
						if(!fowin) Open_FOWin();
						else
						{
							WindowToFront(fowin);
							ActivateWindow(fowin);
						}
						break;
					case 1:				/* Screen */
						mm_screen();
						break;
					case 5:				/* Disk Op. */
						if(!diwin) Open_DOWin();
						else
						{
							WindowToFront(diwin);
							ActivateWindow(diwin);
						}
						break;
					case 6:				/* Prefs */
						if(!prwin) Open_PRWin();
						else
						{
							WindowToFront(prwin);
							ActivateWindow(prwin);
						}
						break;
					case 3:				/* About */
						SwitchIDCMPOFF();
						Open_ABWin();
						SwitchIDCMPON();
						break;
					case 4:				/* Exit */
						RunTime.quitfu=Question(ques[1]);
						break;
					case 9:				/* Render */
						SwitchIDCMPOFF();
						mm_render();
						SwitchIDCMPON();
						break;
					case 10:			/* View */
						SwitchIDCMPOFF();
						mm_view();
						SwitchIDCMPON();
						break;
					case 11:			/* Inspect */
						SwitchIDCMPOFF();
						mm_inspect();
						SwitchIDCMPON();
						break;
				}
				break;
			case IDCMP_VANILLAKEY:
				switch(icode)
				{
					case 'C':			/* Colors */
					case 'c':
						if(!cowin) Open_COWin();
						else
						{
							WindowToFront(cowin);
							ActivateWindow(cowin);
						}
						break;
					case 'Z':			/* Zoom */
					case 'z':
						if(!zowin) Open_ZOWin();
						else
						{
							WindowToFront(zowin);
							ActivateWindow(zowin);
						}
						break;
					case 'O':			/* Options */
					case 'o':
						if(!opwin) Open_OPWin();
						else
						{
							WindowToFront(opwin);
							ActivateWindow(opwin);
						}
						break;
					case 'F':			/* Formula */
					case 'f':
						if(!fowin) Open_FOWin();
						else
						{
							WindowToFront(fowin);
							ActivateWindow(fowin);
						}
						break;
					case 'S':			/* Screen */
					case 's':
						mm_screen();
						break;
					case 'D':			/* DispOp.*/
					case 'd':
						if(!diwin) Open_DOWin();
						else
						{
							WindowToFront(diwin);
							ActivateWindow(diwin);
						}
						break;
					case 'P':			/* Prefs */
					case 'p':
						if(!prwin) Open_PRWin();
						else
						{
							WindowToFront(prwin);
							ActivateWindow(prwin);
						}
						break;
					case 'A':			/* About */
					case 'a':
						SwitchIDCMPOFF();
						Open_ABWin();
						SwitchIDCMPON();
						break;
					case 'E':			/* Exit */
					case 'e':
						RunTime.quitfu=Question(ques[1]);
						break;
					case 'R':			/* Render */
					case 'r':
						SwitchIDCMPOFF();
						mm_render();
						SwitchIDCMPON();
						break;
					case 'V':			/* View */
					case 'v':
						SwitchIDCMPOFF();
						mm_view();
						SwitchIDCMPON();
						break;
					case 'I':			/* Inspect */
					case 'i':
						SwitchIDCMPOFF();
						mm_inspect();
						SwitchIDCMPON();
						break;
				}
				break;
			case IDCMP_RAWKEY:
				switch(icode)
				{
					case 0x5F:
						SwitchIDCMPOFF();
						Help("fu.guide","Charpter1.1");
						SwitchIDCMPON();
						break;
				}
				break;
			case IDCMP_CLOSEWINDOW:
				RunTime.quitfu=Question(ques[1]);
				break;
		}
	}
}

void Refr_MMWin(void)
{
	if(!RunTime.picavail)
	{
		GT_SetGadgetAttrs(mm_Gadgets[0],mmwin,0l,GA_Disabled,TRUE,TAG_DONE);
		GT_SetGadgetAttrs(mm_Gadgets[1],mmwin,0l,GA_Disabled,TRUE,TAG_DONE);
	}
	else
	{
		GT_SetGadgetAttrs(mm_Gadgets[0],mmwin,0l,GA_Disabled,FALSE,TAG_DONE);
		GT_SetGadgetAttrs(mm_Gadgets[1],mmwin,0l,GA_Disabled,FALSE,TAG_DONE);
	}
}

void Close_MMWin(void)
{
	if(mmwin)			CloseWindow(mmwin);
	if(mm_GList)		FreeGadgets(mm_GList);
}
