/****h* FractalUniverse/FU-Proj2.c [1.68] *
*
*  NAME
*    FU-Proj2.c
*  COPYRIGHT
*    $VER: FU-Proj2.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    The Graphical User Interface - Project2
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

#define FU_PROJ2_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void Open_DOWin(void);
void Test_DOWin(void);
void Open_PRWin(void);
void Test_PRWin(void);
void Open_ABWin(void);

void SavePrefs(char *fn);
void LoadPrefs(char *fn);

//-- globals ------------------------------------------------------------------

struct Gadget *dmGList=0l;
UBYTE *dmGadget16Labels[]={ "IFF","Data","IFF+Data",0l },dm_smode=2;

struct Gadget *pmGadgets[16];
struct Gadget *pmGList=0l;
UBYTE pm_aktcol=0,pm_scroll=0;
char pm_scrname[DISPLAYNAMELEN+1];
SelScr ScreenEntry;

FUPrefs_Ver		tprefs_ver;			/* Temp Preferences */
FUPrefs_Path	tprefs_path;
FUPrefs_Gui		tprefs_gui;
FUPrefs_Defs	tprefs_defs;

struct
{
	ULONG *author;
	ULONG *theme;
} thanks[]={
	(ULONG *)"Stephan Quitzsch",					(ULONG *)"IFF-Load Routine & Betatesting",
	(ULONG *)"Matthias Kost",						(ULONG *)"Ideas & Formulas & Betatesting",
	(ULONG *)"Ronny Schütz",						(ULONG *)"Formulas & Betatesting",
	(ULONG *)"Torsten Schulz",						(ULONG *)"Betatesting & lending me his A1200",
	(ULONG *)"Patrick Schlick",						(ULONG *)"Betatesting on A4000 & ideas",
	(ULONG *)"Horst Völz",							(ULONG *)"Formulas",
	(ULONG *)"H.-O.Peitgen & P.H.Richter",			(ULONG *)">The Beauty of Fractals<",
	(ULONG *)"Commodore or whatever it will be",	(ULONG *)"->»» AMIGA ««<-",
	(ULONG *)"Project Pitchfork & Depeche Mode",	(ULONG *)"Wondeful music", 
	(ULONG *)"Stefan Kost alias ENSONIC",			(ULONG *)"Main Author"
};
int thankanz=10;

//-- definitions --------------------------------------------------------------

void Open_DOWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	struct RastPort dirp;

	if(g=CreateContext(&dmGList))
	{
		ng.ng_LeftEdge		=RunTime.scx[15];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[60];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="_Load";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=1;
		ng.ng_Flags			=PLACETEXT_IN;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="_Save";
		ng.ng_GadgetID		=2;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_LeftEdge		=RunTime.scx[80];
		ng.ng_Width			=RunTime.scx[90];
		ng.ng_GadgetText	="Save_mode";
		ng.ng_GadgetID		=0;
		ng.ng_Flags			=PLACETEXT_ABOVE;
		g=CreateGadget(CYCLE_KIND,g,&ng,GT_Underscore,'_',GTCY_Labels,dmGadget16Labels,GTCY_Active,dm_smode,TAG_DONE);

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[185])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[57])>>1;
			smwintags[2].ti_Data=RunTime.scx[185];
			smwintags[3].ti_Data=RunTime.scy[57];
			smwintags[4].ti_Data=BUTTONIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)dmGList;
			smwintags[7].ti_Data=(ULONG)"Disk Operations";
			if(diwin=OpenWindowTagList(0l,smwintags))
			{
				GT_RefreshWindow(diwin,0l);

				dirp=*diwin->RPort;
				DrawBox(dirp,RunTime.scx[10],RunTime.scy[15],RunTime.scx[165],RunTime.scy[35],"Control");

				RunTime.sig_in|=(1L<<diwin->UserPort->mp_SigBit);
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
}

void Test_DOWin(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	UBYTE quit=0;
	char fn[200];
	FILE *temp;

	while(imsg=GT_GetIMsg(diwin->UserPort))
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
					case 0:			/* Type */
						dm_smode=(UBYTE)icode;
						break;
					case 1:			/* Load */
						IFF_Reqtags[8].ti_Data=FALSE;
						if(AslRequest(IFF_FRequest,IFF_Reqtags))
						{
							strmfp(fn,IFF_FRequest->fr_Drawer,IFF_FRequest->fr_File);
							strcpy(fuprefs_path.iff_path,IFF_FRequest->fr_Drawer);
							LoadImage(fn);
							if(fowin) Refresh_FOWin();
							if(opwin) Refresh_OPWin();
							if(zowin) Refresh_ZOWin();
							quit=1;
						}
						break;
					case 2:			/* Save */
						if(RunTime.status)
						{
							IFF_Reqtags[8].ti_Data=TRUE;
							if(AslRequest(IFF_FRequest,IFF_Reqtags))
							{
								strmfp(fn,IFF_FRequest->fr_Drawer,IFF_FRequest->fr_File);
								strcpy(fuprefs_path.iff_path,IFF_FRequest->fr_Drawer);
								if((temp=fopen(fn,"rb"))!=NULL)
								{
									fclose(temp);
									if(Question(ques[0])) SaveImage(fn,dm_smode);
								}
								else SaveImage(fn,dm_smode);
								quit=1;
							}
						}
						else Message(mess[17]);
						break;
				}
				break;
			case IDCMP_VANILLAKEY:
				switch(icode)
				{
					case 'L':		/* Load */
					case 'l':
						IFF_Reqtags[8].ti_Data=FALSE;
						if(AslRequest(IFF_FRequest,IFF_Reqtags))
						{
							strmfp(fn,IFF_FRequest->fr_Drawer,IFF_FRequest->fr_File);
							strcpy(fuprefs_path.iff_path,IFF_FRequest->fr_Drawer);
							LoadImage(fn);
							quit=1;
						}
						break;
					case 'S':		/* Save */
					case 's':
						if(RunTime.status)
						{
							IFF_Reqtags[8].ti_Data=TRUE;
							if(AslRequest(IFF_FRequest,IFF_Reqtags))
							{
								strmfp(fn,IFF_FRequest->fr_Drawer,IFF_FRequest->fr_File);
								strcpy(fuprefs_path.iff_path,IFF_FRequest->fr_Drawer);
								if((temp=fopen(fn,"rb"))!=NULL)
								{
									fclose(temp);
									if(Question(ques[0])) SaveImage(fn,dm_smode);
								}
								else SaveImage(fn,dm_smode);
								quit=1;
							}
						}
						else Message(mess[17]);
						break;
					case 'M':
					case 'm':			/* Type */
						dm_smode=(UBYTE)icode;
						break;
				}
				break;
			case IDCMP_RAWKEY:
				switch(icode)
				{
					case 0x5F:
						Help("fu.guide","Project_DiskOp");
						break;
				}
				break;
			case IDCMP_CLOSEWINDOW:
				quit=1;break;
		}
	}
	if(quit)
	{
		RunTime.sig_in&=(~(1L<<diwin->UserPort->mp_SigBit));
		if(diwin) CloseWindow(diwin);
		if(dmGList) FreeGadgets(dmGList);
		diwin=0l;
		dmGList=0l;
	}
}

void Open_PRWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	struct RastPort pmrp;
	char fona[80];

	tprefs_ver	=fuprefs_ver;	
	tprefs_path	=fuprefs_path;
	tprefs_gui	=fuprefs_gui;
	tprefs_defs	=fuprefs_defs;

	strcpy(pm_scrname,GModes[RunTime.gscreenmode].name);pm_scrname[DISPLAYNAMELEN]=0;
	sprintf(fona,"%s , %d",fuprefs_gui.fontname,fuprefs_gui.fontsize);

	if(g=CreateContext(&pmGList))
	{
		ng.ng_LeftEdge		=RunTime.scx[55];						/* Control */
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[80];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="_Cancel";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=0;
		ng.ng_Flags			=PLACETEXT_IN;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		pmGadgets[0]=g;

		ng.ng_LeftEdge		=RunTime.scx[165];
		ng.ng_GadgetText	="_Okay";
		ng.ng_GadgetID		=1;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		pmGadgets[1]=g;

		ng.ng_LeftEdge		=RunTime.scx[55];
		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="_Save";
		ng.ng_GadgetID		=2;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		pmGadgets[2]=g;

		ng.ng_LeftEdge		=RunTime.scx[165];
		ng.ng_GadgetText	="_Load";
		ng.ng_GadgetID		=3;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		pmGadgets[3]=g;

		ng.ng_LeftEdge		=RunTime.scx[80];						/* Path */
		ng.ng_TopEdge		=RunTime.scy[62];
		ng.ng_Width			=RunTime.scx[15];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="¯";
		ng.ng_GadgetID		=10;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		pmGadgets[10]=g;

		ng.ng_LeftEdge		=RunTime.scx[95];
		ng.ng_Width			=RunTime.scx[185];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="";
		ng.ng_GadgetID		=4;
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,100,GTST_String,fuprefs_path.iff_path,TAG_DONE);
		pmGadgets[4]=g;

		ng.ng_LeftEdge		=RunTime.scx[80];
		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_Width			=RunTime.scx[15];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="¯";
		ng.ng_GadgetID		=11;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		pmGadgets[11]=g;

		ng.ng_LeftEdge		=RunTime.scx[95];
		ng.ng_Width			=RunTime.scx[185];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="";
		ng.ng_GadgetID		=5;
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,100,GTST_String,fuprefs_path.color_path,TAG_DONE);
		pmGadgets[5]=g;

		ng.ng_LeftEdge		=RunTime.scx[80];						/* Screen */
		ng.ng_TopEdge		=RunTime.scy[102];
		ng.ng_Width			=RunTime.scx[162];
		ng.ng_Height		=RunTime.scy[16];
		ng.ng_GadgetText	="Palette";
		ng.ng_Flags			=PLACETEXT_LEFT;
		ng.ng_GadgetID		=6;
		g=CreateGadget(PALETTE_KIND,g,&ng,GTPA_Depth,2,GTPA_Color,1,GTPA_ColorOffset,0,TAG_DONE);
		pmGadgets[6]=g;

		ng.ng_TopEdge		=RunTime.scy[120];
		ng.ng_Height		=RunTime.scy[9];
		ng.ng_GadgetText	="Red";
		ng.ng_GadgetID		=7;
		g=CreateGadget(SLIDER_KIND,g,&ng,GTSL_Min,0,GTSL_Max,15,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Red,GTSL_MaxLevelLen,2,GTSL_LevelFormat,"%ld",GTSL_LevelPlace,PLACETEXT_RIGHT,PGA_Freedom,LORIENT_HORIZ,GA_RelVerify,TRUE,GA_Immediate,TRUE,TAG_DONE);
		pmGadgets[7]=g;

		ng.ng_TopEdge		=RunTime.scy[129];
		ng.ng_GadgetText	="Green";
		ng.ng_GadgetID		=8;
		g=CreateGadget(SLIDER_KIND,g,&ng,GTSL_Min,0,GTSL_Max,15,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Green,GTSL_MaxLevelLen,2,GTSL_LevelFormat,"%ld",GTSL_LevelPlace,PLACETEXT_RIGHT,PGA_Freedom,LORIENT_HORIZ,GA_RelVerify,TRUE,GA_Immediate,TRUE,TAG_DONE);
		pmGadgets[8]=g;

		ng.ng_TopEdge		=RunTime.scy[138];
		ng.ng_GadgetText	="Blue";
		ng.ng_GadgetID		=9;
		g=CreateGadget(SLIDER_KIND,g,&ng,GTSL_Min,0,GTSL_Max,15,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Blue,GTSL_MaxLevelLen,2,GTSL_LevelFormat,"%ld",GTSL_LevelPlace,PLACETEXT_RIGHT,PGA_Freedom,LORIENT_HORIZ,GA_RelVerify,TRUE,GA_Immediate,TRUE,TAG_DONE);
		pmGadgets[9]=g;

		ng.ng_TopEdge		=RunTime.scy[149];
		ng.ng_Width			=RunTime.scx[15];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="¯";
		ng.ng_Flags			=PLACETEXT_IN;
		ng.ng_GadgetID		=12;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		pmGadgets[12]=g;

		ng.ng_LeftEdge		=RunTime.scx[95];
		ng.ng_Width			=RunTime.scx[185];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="";
		ng.ng_GadgetID		=13;
		g=CreateGadget(TEXT_KIND,g,&ng,GTTX_Border,TRUE,GTTX_Text,pm_scrname,GTTX_CopyText,TRUE,TAG_DONE);
		pmGadgets[13]=g;

		ng.ng_LeftEdge		=RunTime.scx[80];
		ng.ng_TopEdge		=RunTime.scy[160];
		ng.ng_Width			=RunTime.scx[15];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="¯";
		ng.ng_GadgetID		=14;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		pmGadgets[14]=g;

		ng.ng_LeftEdge		=RunTime.scx[95];
		ng.ng_Width			=RunTime.scx[185];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="";
		ng.ng_GadgetID		=15;
		g=CreateGadget(TEXT_KIND,g,&ng,GTTX_Border,TRUE,GTTX_Text,fona,GTTX_CopyText,TRUE,TAG_DONE);
		pmGadgets[15]=g;

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[295])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[184])>>1;
			smwintags[2].ti_Data=RunTime.scx[295];
			smwintags[3].ti_Data=RunTime.scy[184];
			smwintags[4].ti_Data=BUTTONIDCMP|SLIDERIDCMP|IDCMP_MOUSEBUTTONS|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)pmGList;
			smwintags[7].ti_Data=(ULONG)"Prefs";
			if(prwin=OpenWindowTagList(0l,smwintags))
			{
				GT_RefreshWindow(prwin,0l);
				pmrp=*prwin->RPort;

				DrawBox(pmrp,RunTime.scx[10],RunTime.scy[15],RunTime.scx[275],RunTime.scy[35],"Control");
				DrawBox(pmrp,RunTime.scx[10],RunTime.scy[55],RunTime.scx[275],RunTime.scy[35],"Path");
				DrawBox(pmrp,RunTime.scx[10],RunTime.scy[95],RunTime.scx[275],RunTime.scy[82],"Screen");

				SetFont(&pmrp,scrfont);SetAPen(&pmrp,1);
				Move(&pmrp,RunTime.scx[21],RunTime.scy[ 70]);Text(&pmrp,"Pictures",8);
				Move(&pmrp,RunTime.scx[21],RunTime.scy[ 81]);Text(&pmrp,"Palettes",8);
				Move(&pmrp,RunTime.scx[35],RunTime.scy[157]);Text(&pmrp,"Screen",6);
				Move(&pmrp,RunTime.scx[49],RunTime.scy[168]);Text(&pmrp,"Font",4);

				RunTime.sig_in|=(1L<<prwin->UserPort->mp_SigBit);
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
}

void Test_PRWin(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	UBYTE quit=0;
	register int i;
	char fona[80];
	struct RastPort *pmrp=prwin->RPort;;

	while(imsg=GT_GetIMsg(prwin->UserPort))
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
					case 0:				/* Cancel */
						fuprefs_ver		=tprefs_ver;	
						fuprefs_path	=tprefs_path;
						fuprefs_gui		=tprefs_gui;
						fuprefs_defs	=tprefs_defs;
						for(i=0;i<4;i++) SetRGB4(mvp,i,fuprefs_gui.ScreenColors[i].Red,fuprefs_gui.ScreenColors[i].Green,fuprefs_gui.ScreenColors[i].Blue);
						quit=1;break;
					case 1:				/* Okay */
						SavePrefs("ENV:FU.prefs");
						for(i=0;i<4;i++) scr_colors4[i]=((UWORD)fuprefs_gui.ScreenColors[i].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[i].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[i].Blue;
						quit=1;break;
					case 2:				/* Save */
						SavePrefs("ENV:FU.prefs");
						SavePrefs("ENVARC:FU.prefs");
						for(i=0;i<4;i++) scr_colors4[i]=((UWORD)fuprefs_gui.ScreenColors[i].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[i].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[i].Blue;
						quit=1;break;
					case 3:				/* Load */
						LoadPrefs("ENV:FU.prefs");
						pm_aktcol=0;
						GT_SetGadgetAttrs(pmGadgets[7],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Red,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[8],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Green,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[9],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Blue,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[4],prwin,0l,GTST_String,fuprefs_path.iff_path,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[5],prwin,0l,GTST_String,fuprefs_path.color_path,TAG_DONE);
						for(i=0;i<4;i++) SetRGB4(mvp,i,fuprefs_gui.ScreenColors[i].Red,fuprefs_gui.ScreenColors[i].Green,fuprefs_gui.ScreenColors[i].Blue);
						ChangeScreen();
						for(i=0;i<4;i++) scr_colors4[i]=((UWORD)fuprefs_gui.ScreenColors[i].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[i].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[i].Blue;
						if(cowin) Refresh_COWin();
						quit=1;break;
					case 10:
						if(AslRequest(IFF_FRequest,IFF_Reqtags))
						{
							strcpy(fuprefs_path.iff_path,IFF_FRequest->fr_Drawer);
							fuprefs_path.iff_path[strlen(IFF_FRequest->fr_Drawer)]=0;
							GT_SetGadgetAttrs(pmGadgets[4],prwin,0l,GTST_String,fuprefs_path.iff_path,TAG_DONE);
						}
						break;
					case 4:
						strcpy(fuprefs_path.iff_path,((struct StringInfo *)(pmGadgets[4]->SpecialInfo))->Buffer);
						break;
					case 11:
						if(AslRequest(Col_FRequest,Col_Reqtags))
						{
							strcpy(fuprefs_path.color_path,Col_FRequest->fr_Drawer);
							fuprefs_path.color_path[strlen(Col_FRequest->fr_Drawer)]=0;
							GT_SetGadgetAttrs(pmGadgets[5],prwin,0l,GTST_String,fuprefs_path.color_path,TAG_DONE);
						}
						break;
					case 5:
						strcpy(fuprefs_path.color_path,((struct StringInfo *)(pmGadgets[5]->SpecialInfo))->Buffer);
						break;
					case 6:
						pm_aktcol=icode;
						GT_SetGadgetAttrs(pmGadgets[7],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Red,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[8],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Green,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[9],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Blue,TAG_DONE);
						break;
					case 7:
						fuprefs_gui.ScreenColors[pm_aktcol].Red=icode;
						SetRGB4(mvp,pm_aktcol,fuprefs_gui.ScreenColors[pm_aktcol].Red,fuprefs_gui.ScreenColors[pm_aktcol].Green,fuprefs_gui.ScreenColors[pm_aktcol].Blue);
						pm_scroll=0;
						break;
					case 8:
						fuprefs_gui.ScreenColors[pm_aktcol].Green=icode;
						SetRGB4(mvp,pm_aktcol,fuprefs_gui.ScreenColors[pm_aktcol].Red,fuprefs_gui.ScreenColors[pm_aktcol].Green,fuprefs_gui.ScreenColors[pm_aktcol].Blue);
						pm_scroll=0;
						break;
					case 9:
						fuprefs_gui.ScreenColors[pm_aktcol].Blue=icode;
						SetRGB4(mvp,pm_aktcol,fuprefs_gui.ScreenColors[pm_aktcol].Red,fuprefs_gui.ScreenColors[pm_aktcol].Green,fuprefs_gui.ScreenColors[pm_aktcol].Blue);
						pm_scroll=0;
						break;
					case 12:
						ScreenEntry.scrmdnr	=RunTime.gscreenmode;
						ScreenEntry.xres	=fuprefs_gui.xres;
						ScreenEntry.yres	=fuprefs_gui.yres;
						ScreenEntry.xdef	=fuprefs_gui.xdef;
						ScreenEntry.ydef	=fuprefs_gui.ydef;
						ScreenEntry.oscan	=fuprefs_gui.oscan;
						ScreenEntry.dep		=fuprefs_gui.depth;
						ScreenEntry.palbits	=fuprefs_gui.palbits;
						ScrMdReq(&GModeList,GModes,&ScreenEntry);
						RunTime.gscreenmode=ScreenEntry.scrmdnr;
						strcpy(pm_scrname,GModes[RunTime.gscreenmode].name);pm_scrname[DISPLAYNAMELEN]=0;
						GT_SetGadgetAttrs(pmGadgets[13],prwin,0l,GTTX_Text,pm_scrname,GTTX_CopyText,TRUE,TAG_DONE);
						fuprefs_gui.xres	=ScreenEntry.xres;
						fuprefs_gui.yres	=ScreenEntry.yres;
						fuprefs_gui.xdef	=ScreenEntry.xdef;
						fuprefs_gui.ydef	=ScreenEntry.ydef;
						fuprefs_gui.oscan	=ScreenEntry.oscan;
						fuprefs_gui.depth	=ScreenEntry.dep;
						fuprefs_gui.scrmode	=ScreenEntry.scrmode;
						fuprefs_gui.palbits	=ScreenEntry.palbits;
						break;
					case 14:
						if(AslRequest(SCR_FRequest,SCR_Reqtags))
						{
							SetFont(pmrp,scrfont);
							strcpy(fuprefs_gui.fontname,SCR_FRequest->fo_Attr.ta_Name);
							fuprefs_gui.fontsize=SCR_FRequest->fo_Attr.ta_YSize;
							sprintf(fona,"%s , %d",fuprefs_gui.fontname,fuprefs_gui.fontsize);
							GT_SetGadgetAttrs(pmGadgets[15],prwin,0l,GTTX_Text,fona,GTTX_CopyText,TRUE,TAG_DONE);
						}
						break;
				}
				break;
			case IDCMP_GADGETDOWN:
				switch((int)(((struct Gadget *)iadr)->GadgetID))
				{
					case 7:
					case 8:
					case 9:
						pm_scroll=1;
						break;
				}
				break;
			case IDCMP_MOUSEMOVE:
				if(pm_scroll)
				{
					switch((int)(((struct Gadget *)iadr)->GadgetID))
					{
						case 7:
							fuprefs_gui.ScreenColors[pm_aktcol].Red=icode;
							SetRGB4(mvp,pm_aktcol,fuprefs_gui.ScreenColors[pm_aktcol].Red,fuprefs_gui.ScreenColors[pm_aktcol].Green,fuprefs_gui.ScreenColors[pm_aktcol].Blue);
							break;
						case 8:
							fuprefs_gui.ScreenColors[pm_aktcol].Green=icode;
							SetRGB4(mvp,pm_aktcol,fuprefs_gui.ScreenColors[pm_aktcol].Red,fuprefs_gui.ScreenColors[pm_aktcol].Green,fuprefs_gui.ScreenColors[pm_aktcol].Blue);
							break;
						case 9:
							fuprefs_gui.ScreenColors[pm_aktcol].Blue=icode;
							SetRGB4(mvp,pm_aktcol,fuprefs_gui.ScreenColors[pm_aktcol].Red,fuprefs_gui.ScreenColors[pm_aktcol].Green,fuprefs_gui.ScreenColors[pm_aktcol].Blue);
							break;
					}
				}
				break;
			case IDCMP_VANILLAKEY:
				switch(icode)
				{
					case 'C':			/* Cancel */
					case 'c':
						fuprefs_ver		=tprefs_ver;	
						fuprefs_path	=tprefs_path;
						fuprefs_gui		=tprefs_gui;
						fuprefs_defs	=tprefs_defs;
						for(i=0;i<4;i++) SetRGB4(mvp,i,fuprefs_gui.ScreenColors[i].Red,fuprefs_gui.ScreenColors[i].Green,fuprefs_gui.ScreenColors[i].Blue);
						quit=1;break;
					case 'O':				/* Okay */
					case 'o':
						SavePrefs("ENV:FU.prefs");
						for(i=0;i<4;i++) scr_colors4[i]=((UWORD)fuprefs_gui.ScreenColors[i].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[i].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[i].Blue;
						quit=1;break;
					case 'S':				/* Save */
					case 's':
						SavePrefs("ENV:FU.prefs");
						SavePrefs("ENVARC:FU.prefs");
						for(i=0;i<4;i++) scr_colors4[i]=((UWORD)fuprefs_gui.ScreenColors[i].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[i].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[i].Blue;
						quit=1;break;
					case 'L':				/* Load */
					case 'l':
						LoadPrefs("ENV:FU.prefs");
						pm_aktcol=0;
						GT_SetGadgetAttrs(pmGadgets[7],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Red,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[8],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Green,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[9],prwin,0l,GTSL_Level,fuprefs_gui.ScreenColors[pm_aktcol].Blue,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[4],prwin,0l,GTST_String,fuprefs_path.iff_path,TAG_DONE);
						GT_SetGadgetAttrs(pmGadgets[5],prwin,0l,GTST_String,fuprefs_path.color_path,TAG_DONE);
						for(i=0;i<4;i++) SetRGB4(mvp,i,fuprefs_gui.ScreenColors[i].Red,fuprefs_gui.ScreenColors[i].Green,fuprefs_gui.ScreenColors[i].Blue);
						ChangeScreen();
						for(i=0;i<4;i++) scr_colors4[i]=((UWORD)fuprefs_gui.ScreenColors[i].Red<<8)|((UWORD)fuprefs_gui.ScreenColors[i].Green<<4)|(UWORD)fuprefs_gui.ScreenColors[i].Blue;
						if(cowin) Refresh_COWin();
						quit=1;break;
				}
				break;
			case IDCMP_RAWKEY:
				switch(icode)
				{
					case 0x5F:
						Help("fu.guide","Project_Prefs");
						break;
				}
				break;
			case IDCMP_CLOSEWINDOW:
				quit=1;break;
		}
	}
	if(quit)
	{
		RunTime.sig_in&=(~(1L<<prwin->UserPort->mp_SigBit));
		if(prwin) CloseWindow(prwin);
		if(pmGList) FreeGadgets(pmGList);
		prwin=0l;
		pmGList=0l;
	}
}

void SavePrefs(char *fn)
{
	FILE *prefs;
	ULONG subtyp;

	fuprefs_defs.fracfunc		=RunTime.fracfunc;
	fuprefs_defs.subfunc		=RunTime.subfunc;
//	fuprefs_defs.screenmode		=GfxInfo.scrmode;		/* ?? */
	fuprefs_defs.xres			=GfxInfo.xres;
	fuprefs_defs.yres			=GfxInfo.yres;
	fuprefs_defs.xdef			=GfxInfo.xdef;
	fuprefs_defs.ydef			=GfxInfo.ydef;
	fuprefs_defs.oscan			=GfxInfo.oscan;
	fuprefs_defs.depth			=GfxInfo.depth;
	fuprefs_defs.scrmode		=GfxInfo.scrmode;		/* ?? */
	fuprefs_defs.autoscroll		=GfxInfo.autoscroll;
	fuprefs_defs.revpal			=GfxInfo.revpal;
	fuprefs_defs.dither			=GfxInfo.dither;
	fuprefs_defs.ordscl			=GfxInfo.ordscl;
	fuprefs_defs.palscl			=GfxInfo.palscl;
	fuprefs_defs.palmap			=GfxInfo.palmap;
	fuprefs_defs.gfxtyp			=GfxInfo.gfxtyp;
	fuprefs_defs.palbits		=GfxInfo.palbits;

	fuprefs_defs.outside		=RenderInfo.outside;
	fuprefs_defs.outpar1		=RenderInfo.outpar1;
	fuprefs_defs.outpar2		=RenderInfo.outpar2;
	fuprefs_defs.inside			=RenderInfo.inside;
	fuprefs_defs.inpar1			=RenderInfo.inpar1;
	fuprefs_defs.inpar2			=RenderInfo.inpar2;
	fuprefs_defs.rendermode		=RenderInfo.rendermode;
	fuprefs_defs.signal			=RenderInfo.signal;
	fuprefs_defs.obstep			=RenderInfo.obstep;
	fuprefs_defs.obsize			=RenderInfo.obsize;
	fuprefs_defs.obconnect		=RenderInfo.obconnect;

	fuprefs_defs.cyclerate		=cdata.rate;
	fuprefs_defs.cycledir		=cdata.dir;

	fuprefs_defs.PalInfo		=PalInfo;

	if(prefs=fopen(fn,"wb"))
	{
		fuprefs_hdr.id=PREF_FORM;
		fuprefs_hdr.len=4+(8+sizeof(fuprefs_ver))+(8+sizeof(fuprefs_path))+(8+sizeof(fuprefs_gui))+(8+sizeof(fuprefs_defs));
		if(!fwrite(&fuprefs_hdr,8,1,prefs)) { Message(mess[2]);fclose(prefs);return; }
		subtyp=PREF_PREF;
		if(!fwrite(&subtyp,4,1,prefs)) { Message(mess[2]);fclose(prefs);return; }

		fuprefs_hdr.id=PREF_VERS;
		fuprefs_hdr.len=sizeof(fuprefs_ver);
		if(!fwrite(&fuprefs_hdr,8,1,prefs)) { Message(mess[2]);fclose(prefs);return; }
		if(!fwrite(&fuprefs_ver,sizeof(fuprefs_ver),1,prefs)) { Message(mess[2]);fclose(prefs);return; }

		fuprefs_hdr.id=PREF_PATH;
		fuprefs_hdr.len=sizeof(fuprefs_path);
		if(!fwrite(&fuprefs_hdr,8,1,prefs)) { Message(mess[2]);fclose(prefs);return; }
		if(!fwrite(&fuprefs_path,sizeof(fuprefs_path),1,prefs)) { Message(mess[2]);fclose(prefs);return; }

		fuprefs_hdr.id=PREF_GUI_;
		fuprefs_hdr.len=sizeof(fuprefs_gui);
		if(!fwrite(&fuprefs_hdr,8,1,prefs)) { Message(mess[2]);fclose(prefs);return; }
		if(!fwrite(&fuprefs_gui,sizeof(fuprefs_gui),1,prefs)) { Message(mess[2]);fclose(prefs);return; }

		fuprefs_hdr.id=PREF_DEFS;
		fuprefs_hdr.len=sizeof(fuprefs_defs);
		if(!fwrite(&fuprefs_hdr,8,1,prefs)) { Message(mess[2]);fclose(prefs);return; }
		if(!fwrite(&fuprefs_defs,sizeof(fuprefs_defs),1,prefs)) { Message(mess[2]);fclose(prefs);return; }
		fclose(prefs);
	}
	else Message(mess[0]);
}

void LoadPrefs(char *fn)
{
	FILE *prefs;
	ULONG subtyp;
	LONG len;
	register UBYTE i;

	if((prefs=fopen(fn,"rb"))!=NULL)
	{
		if(!fread(&fuprefs_hdr,8,1,prefs)) { Message(mess[1]);fclose(prefs);return; }
		if(fuprefs_hdr.id!=PREF_FORM) { Message(mess[10]);fclose(prefs);return; }
		len=fuprefs_hdr.len-4L;
		if(!fread(&subtyp,4,1,prefs)) { Message(mess[1]);fclose(prefs);return; }
		if(subtyp!=PREF_PREF) { Message(mess[10]);fclose(prefs);return; }

		while(len>0)
		{
			if(!fread(&fuprefs_hdr,8,1,prefs)) { Message(mess[1]);fclose(prefs);return; }
			len-=8;
			switch(fuprefs_hdr.id)
			{
				case PREF_VERS:
					if(!fread(&fuprefs_ver,sizeof(fuprefs_ver),1,prefs)) { Message(mess[1]);fclose(prefs);return; }
					break;
				case PREF_PATH:
					if(!fread(&fuprefs_path,sizeof(fuprefs_path),1,prefs)) { Message(mess[1]);fclose(prefs);return; }
					break;
				case PREF_GUI_:
					if(!fread(&fuprefs_gui,sizeof(fuprefs_gui),1,prefs)) { Message(mess[1]);fclose(prefs);return; }
					break;
				case PREF_DEFS:
					if(!fread(&fuprefs_defs,sizeof(fuprefs_defs),1,prefs)) {Message(mess[1]);fclose(prefs);return; }
					break;
				default:
					fseek(prefs,fuprefs_hdr.len,1);
					break;
			}
			len-=fuprefs_hdr.len;
			if(fuprefs_hdr.len&1) { len--;fseek(prefs,1L,1); }
		}
		fclose(prefs);

		RunTime.fracfunc	=fuprefs_defs.fracfunc;
		RunTime.subfunc		=fuprefs_defs.subfunc;
//		GfxInfo.scrmode		=fuprefs_defs.screenmode;	/* ?? */
		GfxInfo.xres		=fuprefs_defs.xres;
		GfxInfo.yres		=fuprefs_defs.yres;
		GfxInfo.xdef		=fuprefs_defs.xdef;
		GfxInfo.ydef		=fuprefs_defs.ydef;
		GfxInfo.oscan		=fuprefs_defs.oscan;
		GfxInfo.depth		=fuprefs_defs.depth;
		GfxInfo.scrmode		=fuprefs_defs.scrmode;		/* ?? */
		GfxInfo.autoscroll	=fuprefs_defs.autoscroll;
		GfxInfo.revpal		=fuprefs_defs.revpal;
		GfxInfo.dither		=fuprefs_defs.dither;
		GfxInfo.ordscl		=fuprefs_defs.ordscl;
		GfxInfo.palscl		=fuprefs_defs.palscl;
		GfxInfo.palmap		=fuprefs_defs.palmap;
		GfxInfo.gfxtyp		=fuprefs_defs.gfxtyp;
		GfxInfo.palbits		=fuprefs_defs.palbits;
		GfxInfo.maxcol=GfxInfo.realcol=1L<<GfxInfo.depth;
		GfxInfo.absmaxcol=GfxInfo.maxcol-1;
		GfxInfo.aspect=(float)(GfxInfo.xres)/(float)(GfxInfo.yres);

		RenderInfo.outside		=fuprefs_defs.outside;
		RenderInfo.outpar1		=fuprefs_defs.outpar1;
		RenderInfo.outpar2		=fuprefs_defs.outpar2;
		RenderInfo.inside		=fuprefs_defs.inside;
		RenderInfo.inpar1		=fuprefs_defs.inpar1;
		RenderInfo.inpar2		=fuprefs_defs.inpar2;
		RenderInfo.rendermode	=fuprefs_defs.rendermode;
		RenderInfo.signal		=fuprefs_defs.signal;
		RenderInfo.obstep		=fuprefs_defs.obstep;
		RenderInfo.obsize		=fuprefs_defs.obsize;
		RenderInfo.obconnect	=fuprefs_defs.obconnect;

		RenderInfo.xb1=0;RenderInfo.xb2=GfxInfo.xres-1;
		RenderInfo.yb1=0;RenderInfo.yb2=GfxInfo.yres-1;

		cdata.rate			=fuprefs_defs.cyclerate;
		cdata.dir			=fuprefs_defs.cycledir;

		PalInfo				=fuprefs_defs.PalInfo;

		SetPaletteMode();
		for(i=0;i<10;i++)
		{
			GetPalShape(PalInfo.r[i].pst,rps[i]);
			GetPalShape(PalInfo.g[i].pst,gps[i]);
			GetPalShape(PalInfo.b[i].pst,bps[i]);
		}
		ChooseFracFunc(0);
		ChooseColorFunc();
		RenderInfo.xb1=0;RenderInfo.xb2=GfxInfo.xres-1;
		RenderInfo.yb1=0;RenderInfo.yb2=GfxInfo.yres-1;
		RenderInfo.z=51;
		RenderInfo.rot=0;
		RunTime.picavail=0;
		epointer=0;
		RunTime.aktpal=0;
	}
	else Message(mess[0]);
}

void Open_ABWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	struct Gadget *amGadgets[1];
	struct Gadget *amGList=0l;
	struct RastPort amrp;
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	int quit=0,tx;
	int i,j;
	char infostr[40];

	if(g=CreateContext(&amGList))
	{
		ng.ng_LeftEdge		=RunTime.scx[160];
		ng.ng_TopEdge		=RunTime.scy[120];
		ng.ng_Width			=RunTime.scx[80];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="_Okay";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=0;
		ng.ng_Flags			=PLACETEXT_IN;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		amGadgets[0]=g;

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[400])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[138])>>1;
			smwintags[2].ti_Data=RunTime.scx[400];
			smwintags[3].ti_Data=RunTime.scy[138];
			smwintags[4].ti_Data=BUTTONIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)amGList;
			smwintags[7].ti_Data=(ULONG)"About";
			if(abwin=OpenWindowTagList(0l,smwintags))
			{
				if(!RunTime.status) GT_SetGadgetAttrs(amGadgets[0],abwin,0l,GA_Disabled,TRUE,TAG_DONE);

				GT_RefreshWindow(abwin,0l);
				amrp=*abwin->RPort;

				DrawBox(amrp,RunTime.scx[10],RunTime.scy[15],RunTime.scx[380],RunTime.scy[30],"About");
				DrawBox(amrp,RunTime.scx[10],RunTime.scy[50],RunTime.scx[380],RunTime.scy[30],"Credits");
				DrawBox(amrp,RunTime.scx[10],RunTime.scy[85],RunTime.scx[380],RunTime.scy[30],"Registation");

				SetAPen(&amrp,1);
				Move(&amrp,RunTime.scx[123],RunTime.scy[28]);Text(&amrp,"Fractal-Universe  V1.6",22);
				Move(&amrp,RunTime.scx[123],RunTime.scy[36]);Text(&amrp,"by ENSONIC of TRINOMIC",22);

				/*
				if(RunTime.status) sprintf(infostr,"Regnr.: %s",Key.line0);
				else sprintf(infostr,"Regnr.: -DEMO-");
				Move(&amrp,RunTime.scx[100],RunTime.scy[98]);Text(&amrp,infostr,strlen(infostr));
				if(RunTime.status) sprintf(infostr,"Name  : %s %s",Key.line2,Key.line1);
				else sprintf(infostr,"Name  : ------ ------");
				Move(&amrp,RunTime.scx[100],RunTime.scy[106]);Text(&amrp,infostr,strlen(infostr));
				*/

				for(i=0;i<(thankanz-1);i++)
				{
					SetAPen(&amrp,1);
					tx=RunTime.scx[200]-(TextLength(&amrp,(STRPTR)thanks[i].author,strlen((unsigned char const *)thanks[i].author))>>1);
					Move(&amrp,tx,RunTime.scy[62]);Text(&amrp,(STRPTR)thanks[i].author,strlen((unsigned char const *)thanks[i].author));

					tx=RunTime.scx[200]-(TextLength(&amrp,(STRPTR)thanks[i].theme,strlen((unsigned char const *)thanks[i].theme))>>1);
					Move(&amrp,tx,RunTime.scy[70]);Text(&amrp,(STRPTR)thanks[i].theme,strlen((unsigned char const *)thanks[i].theme));

					for(j=0;j<60;j++)
					{
						Delay(2);
						while(imsg=GT_GetIMsg(abwin->UserPort))
						{
							iclass	=imsg->Class;
							iadr	=imsg->IAddress;
							icode	=imsg->Code;
							GT_ReplyIMsg(imsg);
							switch(iclass)
							{
								case IDCMP_GADGETUP:
									if((int)(((struct Gadget *)iadr)->GadgetID)==0) { quit=1;j=255;i=thankanz; }
									break;
								case IDCMP_VANILLAKEY:
									if(RunTime.status && (icode=='O' || icode=='o')) { quit=1;j=255;i=thankanz; }
									break;
								case IDCMP_RAWKEY:
									if(icode==0x5F)	Help("fu.guide","Project_About");
									break;
								case IDCMP_CLOSEWINDOW:
									if(RunTime.status)
									{
										quit=1;j=255;i=thankanz;
									}
									break;
							}
						}
					}
					SetAPen(&amrp,0);WaitTOF();
					RectFill(&amrp,RunTime.scx[13],RunTime.scy[54],RunTime.scx[387],RunTime.scy[77]);
				}
				if(!quit)
				{
					SetAPen(&amrp,1);
					tx=RunTime.scx[200]-(TextLength(&amrp,(STRPTR)thanks[i].author,strlen((unsigned char const *)thanks[i].author))>>1);
					Move(&amrp,tx,RunTime.scy[62]);Text(&amrp,(STRPTR)thanks[i].author,strlen((unsigned char const *)thanks[i].author));

					tx=RunTime.scx[200]-(TextLength(&amrp,(STRPTR)thanks[i].theme,strlen((unsigned char const *)thanks[i].theme))>>1);
					Move(&amrp,tx,RunTime.scy[70]);Text(&amrp,(STRPTR)thanks[i].theme,strlen((unsigned char const *)thanks[i].theme));

					if(!RunTime.status) GT_SetGadgetAttrs(amGadgets[0],abwin,0l,GA_Disabled,FALSE,TAG_DONE);

					while(!quit)
					{
						WaitPort(abwin->UserPort);
						while(imsg=GT_GetIMsg(abwin->UserPort))
						{
							iclass	=imsg->Class;
							iadr	=imsg->IAddress;
							icode	=imsg->Code;
							GT_ReplyIMsg(imsg);
							switch(iclass)
							{
								case IDCMP_GADGETUP:
									if((int)(((struct Gadget *)iadr)->GadgetID)==0) quit=1;
									break;
								case IDCMP_VANILLAKEY:
									if(icode=='O' || icode=='o') quit=1;
									break;
								case IDCMP_RAWKEY:
									if(icode==0x5F)	Help("fu.guide","Project_About");
									break;
								case IDCMP_CLOSEWINDOW:
									quit=1;
									break;
							}
						}
					}
				}
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
	if(abwin) CloseWindow(abwin);
	if(amGList) FreeGadgets(amGList);
}
