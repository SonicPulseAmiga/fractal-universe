/****h* FractalUniverse/FU-Tools.c [1.68] *
*
*  NAME
*    FU-Tools.c
*  COPYRIGHT
*    $VER: FU-Tools.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

//-- includes -----------------------------------------------------------------

#define FU_TOOLS_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void DrawGad(struct RastPort rp,UWORD x,UWORD y,UWORD w,UWORD h,UBYTE akt);
void DrawBox(struct RastPort rp,UWORD x,UWORD y,UWORD w,UWORD h,char *text);
char *StringCopy(char *src);
void FilterString(char *strbuf);
void StripString(char *strbuf);
void Help(char *guidename,char *nodename);
void GetRexxStr(char *rstr,char *params);
void ChangeScreen(void);
void BytesPerRow(void);
UWORD CheckSum1(UWORD chk);
int CheckGad_int(struct Gadget *Gadget,struct Window *win,UBYTE chkrng,int minv,int maxv);
double CheckGad_dbl(struct Gadget *Gadget,struct Window *win,UBYTE chkrng,double minv,double maxv);
void Swap_int(int *val1,int *val2);
void Swap_shr(short *val1,short *val2);
void Swap_dbl(double *val1,double *val2);
int GetScrModes(struct List *ModeList,struct Node *ModeNodes,ScrMd *Modes,int maxanz,int minx,int miny,int mind);
void ScrMdReq(struct List *ModeList,ScrMd *Modes,SelScr *ScreenEntry);
long DepthToColors(struct Gadget *gad,WORD level);
UBYTE match_nr2ix(UBYTE nr,UBYTE anz,ArrangeList *alist);
UBYTE match_name2ix(UBYTE *name,UBYTE anz,ArrangeList *alist);
void SortAList(UBYTE anz,ArrangeList *alist);
void BuildList(struct Node *Nodes,struct List *List,UBYTE anz,ArrangeList *alist);
void ScanFormulas(void);

//-- globals ------------------------------------------------------------------

void DrawGad(struct RastPort rp,UWORD x,UWORD y,UWORD w,UWORD h,UBYTE akt)
{
	if(akt==TRUE)
	{
		SetAPen(&rp,1);
		Move(&rp,x,y+h);
		Draw(&rp,x,y);Draw(&rp,x+w,y);
		SetAPen(&rp,2);
		Draw(&rp,x+w,y+h);Draw(&rp,x,y+h);
	}
	else
	{
		SetAPen(&rp,2);
		Move(&rp,x,y+h);
		Draw(&rp,x,y);Draw(&rp,x+w,y);
		SetAPen(&rp,1);
		Draw(&rp,x+w,y+h);Draw(&rp,x,y+h);
	}
}

void DrawBox(struct RastPort rp,UWORD x,UWORD y,UWORD w,UWORD h,char *text)
{
	UWORD sl,gsl,tx,th;

	th=3;
	SetFont(&rp,scrfont);

	sl=strlen(text);
	gsl=TextLength(&rp,text,sl);
	if(gsl+11>w) w=gsl+17;
	tx=(w>>1)-(gsl>>1);

	SetDrMd(&rp,JAM1);
	SetAPen(&rp,1);Move(&rp,x+tx+1,y+th);Text(&rp,text,sl);
	SetAPen(&rp,2);Move(&rp,x+tx,y+(th-1));Text(&rp,text,sl);
	SetDrMd(&rp,JAM2);

	SetAPen(&rp,1);
	Move(&rp,x+tx-6,y);
	Draw(&rp,x,y);Draw(&rp,x,y+h-1);Draw(&rp,x+w-1,y+h-1);
	Draw(&rp,x+w-1,y);Draw(&rp,x+w-(tx-5),y);
	SetAPen(&rp,2);
	Move(&rp,x+tx-6,y+1);
	Draw(&rp,x+1,y+1);Draw(&rp,x+1,y+h);Draw(&rp,x+w,y+h);
	Draw(&rp,x+w,y+1);Draw(&rp,x+w-(tx-5),y+1);
}

/*****************************************************************************************************************/

char *StringCopy(char *src)
{
	register UWORD i;
	char *dst,ch;
	UWORD sl;

	sl=strlen(src)+1;
	if(sl&1) sl++;
	if(dst=AllocMem(sl,MEMF_ANY))
	{
		for(i=0;i<sl-1;i++)
		{
			ch=src[i];
			if(ch==0) ch=32;
			dst[i]=ch;
		}
		dst[sl-1]=0;
	}
	return(dst);
}

void FilterString(char *strbuf)
{
	char buf[20];
	char *allowed="0123456789+-.";
	register UWORD i,j;

	i=j=0;
	while(strbuf[i]!=0 && i!=19)
	{
		if(strchr(allowed,strbuf[i]))
		{
			buf[j]=strbuf[i];j++;
		}
		i++;
	}
	buf[j]=0;j++;
	for(i=0;i!=j;i++) strbuf[i]=buf[i];
}

void StripString(char *strbuf)
{
	char buf[20];
	register UBYTE i,j;

	i=j=0;
	while(strbuf[i]!=0 && i!=19)
	{
		if(strbuf[i]!=32)
		{
			buf[j]=strbuf[i];j++;
		}
		i++;
	}
	buf[j]=0;j++;
	for(i=0;i!=j;i++) strbuf[i]=buf[i];
}

void Help(char *guidename,char *nodename)
{
	struct NewAmigaGuide naguide={0L};
	AMIGAGUIDECONTEXT AGHandle;
	BPTR ndir,odir;

	if(ndir=Lock("progdir:guides/",ACCESS_READ))
	{
		naguide.nag_Lock	=0L;
		naguide.nag_Name	=guidename;
		naguide.nag_Screen	=mmscr;
		naguide.nag_BaseName="FractalUniverse";
		naguide.nag_Node	=nodename;
		naguide.nag_Line	=0L;

		odir=CurrentDir(ndir);

		if(AGHandle=OpenAmigaGuide(&naguide,NULL)) CloseAmigaGuide(AGHandle);
		else Message(mess[0]);

		ndir=CurrentDir(odir);
		UnLock(ndir);
	}
}

void GetRexxStr(char *rstr,char *params)			/* nimmt Rexx-parameter auseinander */
{
	ULONG i=0,pos1=0,pos2=0,sl=strlen(rstr);

	while(pos1<sl && i<MaxParAnz)					/* Trennzeichen = Sapce */
	{
		while(rstr[pos1]!=32 && rstr[pos1]!=0 && pos2<((i+1)*MaxParLen-1))
		{
			params[pos2]=rstr[pos1];
			pos1++;pos2++;
		}
		params[pos2]=0;
		i++;pos1++;pos2=i*MaxParLen;
	}
	for(i=pos2;i<MaxParAnz*MaxParLen;i++) params[i]=0;
}

void ChangeScreen(void)
{
	register UWORD i;
	UBYTE autoscroll;

	if(rwindow)
	{
		CloseWindow(rwindow);rwindow=0;
	}
	if(rscreen)
	{
		CloseScreen(rscreen);rscreen=0;
	}
	autoscroll=FALSE;
	if(!GfxInfo.xdef && GfxInfo.xres>Modes[RunTime.rscreenmode].OScans[1].MaxX) autoscroll=TRUE;
	if(!GfxInfo.ydef && GfxInfo.yres>Modes[RunTime.rscreenmode].OScans[1].MaxY) autoscroll=TRUE;

	if(GfxInfo.xdef) GfxInfo.xres=Modes[RunTime.rscreenmode].OScans[GfxInfo.oscan].MaxX;
	if(GfxInfo.ydef) GfxInfo.yres=Modes[RunTime.rscreenmode].OScans[GfxInfo.oscan].MaxY;

	RScreenTags[2].ti_Data=GfxInfo.xres;
	RScreenTags[3].ti_Data=GfxInfo.yres;
	RScreenTags[4].ti_Data=GfxInfo.depth;
	RScreenTags[8].ti_Data=GfxInfo.scrmode;
	if(autoscroll)
	{
		RScreenTags[10].ti_Data=OSCAN_MAX;
		RScreenTags[9].ti_Data=TRUE;
	}
	else RScreenTags[10].ti_Data=GfxInfo.oscan;

	if(RunTime.kickstart>2 && GfxInfo.depth>5)
	{
		RScreenTags[12].ti_Tag=SA_ColorMapEntries;
		RScreenTags[12].ti_Data=(ULONG)(1L<<GfxInfo.depth);
	}
	else
	{
		RScreenTags[12].ti_Tag=TAG_IGNORE;
		RScreenTags[12].ti_Data=0;		
	}
	if(rscreen=OpenScreenTagList(NULL,RScreenTags))
	{
		rvp=&rscreen->ViewPort;
		RWindowTags[2].ti_Data=RWindowTags[ 9].ti_Data=RWindowTags[11].ti_Data=GfxInfo.xres;
		RWindowTags[3].ti_Data=RWindowTags[10].ti_Data=RWindowTags[12].ti_Data=GfxInfo.yres;
		RWindowTags[8].ti_Data=OWindowTags[8].ti_Data=IWindowTags[8].ti_Data=(ULONG)rscreen;
		if(rwindow=OpenWindowTagList(NULL,RWindowTags))
		{
			for(i=0;i<max(GfxInfo.realcol,256);i++)
			{
				rrp[i]=*rwindow->RPort;
				SetAPen(&rrp[i],i);
			}
			SetRast(&rrp[0],0);
			for(i=0;i<GfxInfo.depth;i++) planes[i]=rscreen->RastPort.BitMap->Planes[i];
			BytesPerRow();
			MakeColorPalettes();
			SetColorPalette();
		}
		else Message(mess[5]);
	}
	else Message(mess[14]);
	if(mmscr && mmwin)
	{
		ScreenToFront(mmscr);
		ActivateWindow(mmwin);
	}
}

void BytesPerRow(void)
{
//	BPR=rscreen->RastPort.BitMap->BytesPerRow;
	BPR=GfxInfo.xres>>3;
	if((BPR<<3)<GfxInfo.xres) BPR++;
}

/*****************************************************************************************************************/

UWORD CheckSum1(UWORD chk)
{
	return((UWORD)((chk&0xFFFF+chk&0xFFF+chk&0xFF+chk&0xF)&0xFFFF));
}

/*****************************************************************************************************************/

int CheckGad_int(struct Gadget *Gadget,struct Window *win,UBYTE chkrng,int minv,int maxv)
{
	int val;

	val=atoi(((struct StringInfo *)(Gadget->SpecialInfo))->Buffer);
	if(chkrng)
	{
		if(val>maxv) { val=maxv;GT_SetGadgetAttrs(Gadget,win,0l,GTIN_Number,val,TAG_DONE); }
		if(val<minv) { val=minv;GT_SetGadgetAttrs(Gadget,win,0l,GTIN_Number,val,TAG_DONE); }
	}
	return(val);
}

double CheckGad_dbl(struct Gadget *Gadget,struct Window *win,UBYTE chkrng,double minv,double maxv)
{
	double val;
	char str[20];

	val=atof(((struct StringInfo *)(Gadget->SpecialInfo))->Buffer);
	if(chkrng)
	{
		if(val>maxv)
		{
			val=maxv;sprintf(str,"%20.15lf",val);
			GT_SetGadgetAttrs(Gadget,win,0l,GTST_String,str,TAG_DONE);
		}
		if(val<minv)
		{
			val=minv;sprintf(str,"%20.15lf",val);
			GT_SetGadgetAttrs(Gadget,win,0l,GTST_String,str,TAG_DONE);
		}
	}
	return(val);
}

void Swap_int(int *val1,int *val2)
{
	int tmp=*val1;

	*val1=*val2;
	*val2=tmp;
}

void Swap_shr(short *val1,short *val2)
{
	short tmp=*val1;

	*val1=*val2;
	*val2=tmp;
}

void Swap_dbl(double *val1,double *val2)
{
	double tmp=*val1;

	*val1=*val2;
	*val2=tmp;
}

int GetScrModes(struct List *ModeList,struct Node *ModeNodes,ScrMd *Modes,int maxanz,int minx,int miny,int mind)
{
	register int i,j,k;
	UBYTE alex,usual;
	struct NameInfo NameInfo;
	struct DisplayInfo DispInfo;
	struct DimensionInfo DimsInfo;
	ULONG ID=0l,nextID;

	NewList(ModeList);
	i=0;										/* Screenmodes holen */
	do
	{
		nextID=NextDisplayInfo(ID);
		if(j=GetDisplayInfoData(0,(UBYTE *)&DispInfo,sizeof(DispInfo),DTAG_DISP,ID))
		{
			if(j=GetDisplayInfoData(0,(UBYTE *)&NameInfo,sizeof(NameInfo),DTAG_NAME,ID))
			{
				if(j=GetDisplayInfoData(0,(UBYTE *)&DimsInfo,sizeof(DimsInfo),DTAG_DIMS,ID))
				{
					if(!DispInfo.NotAvailable && i<50)
					{
						alex=0;usual=1;
						for(k=0;k<i;k++)
						{
							if(!strcmp(Modes[k].name,NameInfo.Name))
							{
								k=i;alex=1;
							}
						}
						if(!alex)
						{
							if((int)DimsInfo.MaxDepth<mind) usual=0;
							if((int)DimsInfo.Nominal.MaxX+1<minx) usual=0;
							if((int)DimsInfo.Nominal.MaxX+1<miny) usual=0;
							if(usual)
							{
								strcpy(Modes[i].name,NameInfo.Name);
								Modes[i].scrmode=ID;
								Modes[i].dep=(int)DimsInfo.MaxDepth;

								if(RunTime.kickstart<3 && Modes[i].dep>6) Modes[i].dep=6;
								if(RunTime.kickstart>2)								/* AGA oder Grafikkarte */
								{
									Modes[i].palbits=max(DispInfo.RedBits,max(DispInfo.GreenBits,DispInfo.BlueBits));
									if(Modes[i].palbits>8) Modes[i].palbits=8;
								}
								else										/* Normal | ECS | oder sonstwas (vielleicht auch `ne GFXKarte) */
								{
									k=DispInfo.PaletteRange;
									Modes[i].palbits=((int)((log10((double)k)/log10(2.0))+0.5))/3;
									if(Modes[i].palbits>4) Modes[i].palbits=4;
								}

								Modes[i].OScans[0].MinX=(int)DimsInfo.Nominal.MinX;
								Modes[i].OScans[0].MinY=(int)DimsInfo.Nominal.MinY;
								Modes[i].OScans[0].MaxX=(int)DimsInfo.Nominal.MaxX+1;
								Modes[i].OScans[0].MaxY=(int)DimsInfo.Nominal.MaxY+1;

								Modes[i].OScans[1].MinX=(int)DimsInfo.MaxOScan.MinX;
								Modes[i].OScans[1].MinY=(int)DimsInfo.MaxOScan.MinY;
								Modes[i].OScans[1].MaxX=(int)DimsInfo.MaxOScan.MaxX+1;
								Modes[i].OScans[1].MaxY=(int)DimsInfo.MaxOScan.MaxY+1;

								Modes[i].OScans[2].MinX=(int)DimsInfo.VideoOScan.MinX;
								Modes[i].OScans[2].MinY=(int)DimsInfo.VideoOScan.MinY;
								Modes[i].OScans[2].MaxX=(int)DimsInfo.VideoOScan.MaxX+1;
								Modes[i].OScans[2].MaxY=(int)DimsInfo.VideoOScan.MaxY+1;

								Modes[i].OScans[3].MinX=(int)DimsInfo.TxtOScan.MinX;
								Modes[i].OScans[3].MinY=(int)DimsInfo.TxtOScan.MinY;
								Modes[i].OScans[3].MaxX=(int)DimsInfo.TxtOScan.MaxX+1;
								Modes[i].OScans[3].MaxY=(int)DimsInfo.TxtOScan.MaxY+1;

								Modes[i].OScans[4].MinX=(int)DimsInfo.StdOScan.MinX;
								Modes[i].OScans[4].MinY=(int)DimsInfo.StdOScan.MinY;
								Modes[i].OScans[4].MaxX=(int)DimsInfo.StdOScan.MaxX+1;
								Modes[i].OScans[4].MaxY=(int)DimsInfo.StdOScan.MaxY+1;

								ModeNodes[i].ln_Name=Modes[i].name;
								AddTail(ModeList,&ModeNodes[i]);
								i++;
							}
						}
					}
				}
			}
	 	}
		ID=nextID;
	} while(nextID!=INVALID_ID);
	return(i);
}

void ScrMdReq(struct List *ModeList,ScrMd *Modes,SelScr *ScreenEntry)
{
	register int i;
	struct NewGadget ng;
	struct Gadget *g;
	struct Gadget *smGList=0l;
	struct Gadget *smGadgets[6];
	struct Window *scwin;
	struct RastPort smrp;
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	int quit=0;

	UBYTE *OscanLabels[]={ "Nominal","MaxOScan","VideoOScan","TxtOScan","StdOScan",0l };

	if(g=CreateContext(&smGList))
	{
		ng.ng_LeftEdge		=RunTime.scx[177];
		ng.ng_TopEdge		=RunTime.scy[97];
		ng.ng_Width			=RunTime.scx[90];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="_Okay";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=0;
		ng.ng_Flags			=PLACETEXT_IN;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);

		ng.ng_LeftEdge		=RunTime.scx[20];
		ng.ng_TopEdge		=RunTime.scy[15];
		ng.ng_Width			=RunTime.scx[200];
		ng.ng_Height		=RunTime.scy[80];
		ng.ng_GadgetText	="";
		ng.ng_GadgetID		=2;
		ng.ng_Flags			=PLACETEXT_LEFT;
		g=CreateGadget(LISTVIEW_KIND,g,&ng,GTLV_Labels,ModeList,GTLV_ShowSelected,0l,GTLV_Selected,ScreenEntry->scrmdnr,GTLV_Top,ScreenEntry->scrmdnr,TAG_DONE);

		ng.ng_LeftEdge		=RunTime.scx[295];
		ng.ng_TopEdge		=RunTime.scy[15];
		ng.ng_Width			=RunTime.scx[100];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="OScan";
		ng.ng_GadgetID		=4;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,OscanLabels,GTCY_Active,ScreenEntry->oscan,TAG_DONE);

		ng.ng_TopEdge		=RunTime.scy[26];
		ng.ng_Width			=RunTime.scx[60];
		ng.ng_GadgetText	="XRes";
		ng.ng_GadgetID		=5;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,5,GTIN_Number,ScreenEntry->xres,TAG_DONE);
		smGadgets[5]=g;

		ng.ng_LeftEdge		=RunTime.scx[390];
		ng.ng_Width			=RunTime.scx[26];
		ng.ng_GadgetText	="Def";
		ng.ng_GadgetID		=7;
		g=CreateGadget(CHECKBOX_KIND,g,&ng,GTCB_Checked,ScreenEntry->xdef,GTCB_Scaled,TRUE,TAG_DONE);
		smGadgets[2]=g;

		ng.ng_LeftEdge		=RunTime.scx[295];
		ng.ng_TopEdge		=RunTime.scy[37];
		ng.ng_Width			=RunTime.scx[60];
		ng.ng_GadgetText	="YRes";
		ng.ng_GadgetID		=6;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,5,GTIN_Number,ScreenEntry->yres,TAG_DONE);
		smGadgets[4]=g;

		ng.ng_LeftEdge		=RunTime.scx[390];
		ng.ng_Width			=RunTime.scx[26];
		ng.ng_GadgetText	="Def";
		ng.ng_GadgetID		=8;
		g=CreateGadget(CHECKBOX_KIND,g,&ng,GTCB_Checked,ScreenEntry->ydef,GTCB_Scaled,TRUE,TAG_DONE);
		smGadgets[0]=g;

		ng.ng_LeftEdge		=RunTime.scx[295];
		ng.ng_TopEdge		=RunTime.scy[48];
		ng.ng_Width			=RunTime.scx[80];
		ng.ng_GadgetText	="Col";
		ng.ng_GadgetID		=3;
		g=CreateGadget(SLIDER_KIND,g,&ng,GTSL_Min,1,GTSL_Max,ScreenEntry->dep,GTSL_Level,ScreenEntry->dep,GTSL_MaxLevelLen,4,GTSL_LevelFormat," %3ld ",GTSL_LevelPlace,PLACETEXT_RIGHT,GTSL_DispFunc,DepthToColors,PGA_Freedom,LORIENT_HORIZ,GA_RelVerify,TRUE,TAG_DONE);
		smGadgets[3]=g;

		ng.ng_TopEdge		=RunTime.scy[59];
		ng.ng_Width			=RunTime.scx[50];
		ng.ng_GadgetText	="PalBits";
		ng.ng_GadgetID		=1;
		g=CreateGadget(NUMBER_KIND,g,&ng,GTNM_Border,TRUE,GTNM_Number,ScreenEntry->palbits,TAG_DONE);
		smGadgets[1]=g;

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[440])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[112])>>1;
			smwintags[2].ti_Data=RunTime.scx[440];
			smwintags[3].ti_Data=RunTime.scy[112];
			smwintags[4].ti_Data=BUTTONIDCMP|LISTVIEWIDCMP|SLIDERIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)smGList;
			smwintags[7].ti_Data=(ULONG)"Screenmode";
			if(scwin=OpenWindowTagList(0l,smwintags))
			{
				GT_RefreshWindow(scwin,0l);
				smrp=*scwin->RPort;

//				DrawBox(smrp,RunTime.scx[ 10],RunTime.scy[15],RunTime.scx[220],RunTime.scy[113],"Modes");
//				DrawBox(smrp,RunTime.scx[240],RunTime.scy[15],RunTime.scx[190],RunTime.scy[113],"Settings");

				i=ScreenEntry->scrmdnr;
				ScreenEntry->scrmode=Modes[i].scrmode;
				if(ScreenEntry->xdef) GT_SetGadgetAttrs(smGadgets[5],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxX,GA_Disabled,TRUE,TAG_DONE);
				else GT_SetGadgetAttrs(smGadgets[5],scwin,0l,GTIN_Number,ScreenEntry->xres,GA_Disabled,FALSE,TAG_DONE);
				if(ScreenEntry->ydef) GT_SetGadgetAttrs(smGadgets[4],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxY,GA_Disabled,TRUE,TAG_DONE);
				else GT_SetGadgetAttrs(smGadgets[4],scwin,0l,GTIN_Number,ScreenEntry->yres,GA_Disabled,FALSE,TAG_DONE);
				if(ScreenEntry->dep>Modes[i].dep) ScreenEntry->dep=Modes[i].dep;
				GT_SetGadgetAttrs(smGadgets[3],scwin,0l,GTSL_Max,Modes[i].dep,GTSL_Level,ScreenEntry->dep,TAG_DONE);
				ScreenEntry->palbits=Modes[i].palbits;
				GT_SetGadgetAttrs(smGadgets[1],scwin,0l,GTNM_Number,ScreenEntry->palbits,TAG_DONE);

				while(!quit)
				{
					WaitPort(scwin->UserPort);
					while(imsg=GT_GetIMsg(scwin->UserPort))
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
									case 0:				/* Okay */
										ScreenEntry->change=1;quit=1;
										break;
									case 2:			/* ScrMode */
										i=(int)icode;
										ScreenEntry->scrmdnr=i;
										ScreenEntry->xres=		Modes[i].OScans[ScreenEntry->oscan].MaxX;
										ScreenEntry->yres=		Modes[i].OScans[ScreenEntry->oscan].MaxY;
										ScreenEntry->dep=		Modes[i].dep;
										ScreenEntry->scrmode=	Modes[i].scrmode;
										ScreenEntry->palbits=	Modes[i].palbits;
										GT_SetGadgetAttrs(smGadgets[5],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxX,TAG_DONE);
										GT_SetGadgetAttrs(smGadgets[4],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxY,TAG_DONE);
										GT_SetGadgetAttrs(smGadgets[3],scwin,0l,GTSL_Max,Modes[i].dep,GTSL_Level,ScreenEntry->dep,TAG_DONE);
										GT_SetGadgetAttrs(smGadgets[1],scwin,0l,GTNM_Number,ScreenEntry->palbits,TAG_DONE);
										break;
									case 3:			/* Depth b.z.w. Colors */
										ScreenEntry->dep=(int)icode;
										break;
									case 4:			/* Oscan */
										ScreenEntry->oscan=(int)icode;
										if(ScreenEntry->xdef) GT_SetGadgetAttrs(smGadgets[5],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxX,GA_Disabled,TRUE,TAG_DONE);
										else GT_SetGadgetAttrs(smGadgets[5],scwin,0l,GTIN_Number,ScreenEntry->xres,GA_Disabled,FALSE,TAG_DONE);
										if(ScreenEntry->ydef) GT_SetGadgetAttrs(smGadgets[4],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxY,GA_Disabled,TRUE,TAG_DONE);
										else GT_SetGadgetAttrs(smGadgets[4],scwin,0l,GTIN_Number,ScreenEntry->yres,GA_Disabled,FALSE,TAG_DONE);
										break;
									case 5:			/* Width */
										ScreenEntry->xres=CheckGad_int(smGadgets[5],scwin,0,0,0);
										ActivateGadget(smGadgets[4],scwin,0L);
										break;
									case 6:			/* Height */
										ScreenEntry->yres=CheckGad_int(smGadgets[4],scwin,0,0,0);
										ActivateGadget(smGadgets[5],scwin,0L);
										break;
									case 7:			/* XDef */
										ScreenEntry->xdef=smGadgets[2]->Flags&GFLG_SELECTED;
										if(ScreenEntry->xdef) GT_SetGadgetAttrs(smGadgets[5],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxX,GA_Disabled,TRUE,TAG_DONE);
										else GT_SetGadgetAttrs(smGadgets[5],scwin,0l,GTIN_Number,ScreenEntry->xres,GA_Disabled,FALSE,TAG_DONE);
										break;
									case 8:			/* YDef */
										ScreenEntry->ydef=smGadgets[0]->Flags&GFLG_SELECTED;
										if(ScreenEntry->ydef) GT_SetGadgetAttrs(smGadgets[4],scwin,0l,GTIN_Number,Modes[i].OScans[ScreenEntry->oscan].MaxY,GA_Disabled,TRUE,TAG_DONE);
										else GT_SetGadgetAttrs(smGadgets[4],scwin,0l,GTIN_Number,ScreenEntry->yres,GA_Disabled,FALSE,TAG_DONE);
										break;
								}
								break;
							case IDCMP_VANILLAKEY:
								switch(icode)
								{
									case 'O':
									case 'o':
										ScreenEntry->change=1;quit=1;
										break;
								}
								break;
							case IDCMP_RAWKEY:
								switch(icode)
								{
									case 0x5F:
										Help("fu.guide","Project_Screen");
										break;
								}
								break;
							case IDCMP_CLOSEWINDOW:
								ScreenEntry->change=0;quit=1;
								break;
						}
					}
				}
				CloseWindow(scwin);
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
		FreeGadgets(smGList);
	}
	else Message(mess[7]);
}

long DepthToColors(struct Gadget *gad,WORD level)
{
	return((WORD)1L<<level);
}

// Arrangelisthandling

UBYTE match_nr2ix(UBYTE nr,UBYTE anz,ArrangeList *alist)
{
	register UBYTE i,ix=0;

	for(i=0;i<anz;i++)
		if(alist[i].nr==nr) { ix=i;i=anz; }
	return(ix);
}

UBYTE match_name2ix(UBYTE *name,UBYTE anz,ArrangeList *alist)
{
	register UBYTE i,ix=0;

	for(i=0;i<anz;i++)
		if(!strcmp(alist[i].name,name)) { ix=alist[i].nr;i=anz; }
	return(ix);
}

void SortAList(UBYTE anz,ArrangeList *alist)
{
	register UWORD j,k;
	char tempstr[50];
	WORD tmpi;

	for(j=0;j<anz-1;j++)
		for(k=0;k<anz-1;k++)
			if(stricmp(alist[k].name,alist[k+1].name)>0)
			{
				strcpy(tempstr,alist[k].name);strcpy(alist[k].name,alist[k+1].name);strcpy(alist[k+1].name,tempstr);
				tmpi=alist[k].nr;alist[k].nr=alist[k+1].nr;alist[k+1].nr=tmpi;
			}
}

void BuildList(struct Node *Nodes,struct List *List,UBYTE anz,ArrangeList *alist)
{
	register UWORD j;

	for(j=0;j<anz;j++)
	{
		Nodes[j].ln_Succ=&Nodes[j+1];
		if(j>0) Nodes[j-1].ln_Pred=&Nodes[j];
		else Nodes[0].ln_Pred=(struct Node *)&List->lh_Head;
		Nodes[j].ln_Name=alist[j].name;
	}
	Nodes[anz-1].ln_Succ=(struct Node *)&List->lh_Tail;
	List->lh_Head=Nodes;
	List->lh_Tail=0l;
	List->lh_TailPred=&Nodes[anz-1];
}

void ScanFormulas(void)
{
	register int j,k;
	struct FileLock *dirlock;
	struct FileInfoBlock *InfoBlock;
	int sl;
	char tempstr[40];
	UBYTE i;

	i=0;											/* FormulaFractalList */
	if(InfoBlock=(struct FileInfoBlock *)AllocMem(sizeof(struct FileInfoBlock),MEMF_PUBLIC|MEMF_CLEAR))
	{
		if(dirlock=(struct FileLock *)Lock((STRPTR)"formulas",SHARED_LOCK))
		{
			if(j=Examine((BPTR)dirlock,InfoBlock))
			{
				if(InfoBlock->fib_DirEntryType>0 && InfoBlock->fib_DirEntryType!=3)
				{
					while(j=ExNext((BPTR)dirlock,InfoBlock))
					{
						sl=strlen(InfoBlock->fib_FileName);
						if(sl>5 && !stricmp(&InfoBlock->fib_FileName[sl-5],".FORM"))
						{
							strcpy(Formulas[i],InfoBlock->fib_FileName);Formulas[i][sl-5]=0;i++;
						}
					}
					i--;
					for(j=0;j<i;j++)			/* Formeln sortieren */
						for(k=0;k<i;k++)
							if(stricmp(Formulas[k],Formulas[k+1])>0)
							{
								strcpy(tempstr,Formulas[k]);strcpy(Formulas[k],Formulas[k+1]);strcpy(Formulas[k+1],tempstr);
							}
					for(j=0;j<=i;j++)			/* Liste bauen */
					{
						FormulaNodes[j].ln_Succ=&FormulaNodes[j+1];
						if(j>0) FormulaNodes[j-1].ln_Pred=&FormulaNodes[j];
						else FormulaNodes[j].ln_Pred=(struct Node *)&FormulaList.lh_Head;
						FormulaNodes[j].ln_Name=Formulas[j];
					}
					FormulaNodes[i].ln_Succ=(struct Node *)&FormulaList.lh_Tail;
					FormulaList.lh_Head=&FormulaNodes[0];
					FormulaList.lh_Tail=(struct Node *)0l;
					FormulaList.lh_TailPred=&FormulaNodes[i];
				}
			}
			UnLock((BPTR)dirlock);
		}
		FreeMem(InfoBlock,sizeof(struct FileInfoBlock));
	}
}
