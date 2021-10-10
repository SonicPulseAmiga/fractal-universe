/****h* FractalUniverse/FU-Proj1.c [1.68] *
*
*  NAME
*    FU-Proj1.c
*  COPYRIGHT
*    $VER: FU-Proj1.c 1.68 (25.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    23.Oct.2001
*  MODIFICATION HISTORY
*    25.Oct.2001	V 1.68	most recent version
*    23.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

//-- includes -----------------------------------------------------------------

#define FU_PROJ1_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void Open_COWin(void);
void Test_COWin(void);
void Refresh_COWin(void);
void Open_ZOWin(void);
void Test_ZOWin(void);
void Refresh_ZOWin(void);
void Open_OPWin(void);
void Test_OPWin(void);
void Refresh_OPWin(void);
void Open_FOWin(void);
void Test_FOWin(void);
void Refresh_FOWin(void);
void mm_screen(void);

void LoadPalette(char *fn);
void SavePalette(char *fn);
void RefreshPalShapes(struct RastPort rp,struct Gadget *Gadgets[]);

//-- globals ------------------------------------------------------------------

struct Gadget *cmGList=0l;
struct Gadget *cmGadgets[48];
struct RastPort cmrp;
UBYTE *cmShapeLabels[]={ "Triangle 1","Triangle 2","Triangle 3","Sine 1","Sine 2","Sine 3","Sine 1 Up","Sine 1 Down","Sine 2 Down","Sine 1 Up","Line","Ramp Up","Ramp Down","Roof 1.1","Roof 1.2","Roof 2.1","Roof 2.2","Roof 3.1","Roof 3.2","Ramp Up & Hold","Hold & Ramp Down","Hold & Ramp Up","Ramp Down & Hold",0l };
UBYTE *cmBufferLabels[]={ "PalBuffer.0","PalBuffer.1","PalBuffer.2","PalBuffer.3","PalBuffer.4","PalBuffer.5","PalBuffer.6","PalBuffer.7","PalBuffer.8","PalBuffer.9",0l };

struct Gadget *zmGList=0l;
struct Gadget *zmGadgets[22];
UBYTE zm_ztype=0,zm_zmode=0,zm_zsnap=0;
UWORD zm_x1,zm_x2,zm_y1,zm_y2;
UBYTE *zmGadget14Labels[]={ "Zoom In","Zoom Out","Window","Recalc.",0l };
UBYTE *zmGadget15Labels[]={ "Prop.","Unprop.",0l };
UBYTE *zmGadget16Labels[]={ "Centre","Corner",0l };
UBYTE *zmGadget22Labels[]={ "None","X-Axis","Y-Axis","Both",0l };

struct Gadget *omGList=0l;
struct Gadget *omGadgets[40];
struct RastPort omrp;
//UBYTE *omGadgetXXLabels[]={ "Auto","Integer","Float",0l };
UBYTE *omGadget02Labels[]={ "None","Small","Medium","Large","Order",0l };
UBYTE *omGadget04Labels[]={ "Solid","Square","Square+","Preview",0l };
UBYTE *omGadget05Labels[]={ "Turbo","System",0l };
UBYTE *omGadget09Labels[]={ "Linear","Rev. 1","Rev. 2",0l };
UBYTE *omGadget28Labels[]={ "None","X-Axis","Y-Axis","Both",0l };
UBYTE *omGadget39Labels[]={"0.5","0.375","0.25",0l};
UBYTE *omGadgetFuncLabels[]={ "Sin","Cos","Tan","SinH","CosH","TanH","Log","Exp","Abs","Real","Imag","Swap","Inv",0l };

struct Gadget *fmGList=0l;
struct Gadget *fmGadgets[3];

WORD OutsideDefs[osanz][2]={
	 -1, -1,	/*  0 BinDecomp */	
	  5, -1,	/*  1 BiomorAbs1 */	
	  5, -1,	/*  2 BiomorRel1 */	
	  5, -1,	/*  3 BiomorAbs2 */	
	  5, -1,	/*  4 BiomorRel2 */	
     50, -1,	/*  5 ContPot */		
	200, -1,	/*  6 Decomposition */
	 -1, -1,	/*  7 DiffIterImag */	
	 -1, -1,	/*  8 DiffIterReal */	
	 -1, -1,	/*  9 DiffIterReIm */	
	 10, -1,	/* 10 DiffParImag */	
	 10, -1,	/* 11 DiffParReal */	
	 10, -1,	/* 12 DiffParReIm */	
	 10, -1,	/* 13 Normal */		
	 -1, -1,	/* 14 Stripes */		
	 -1, -1,	/* 15 SummImagIt */	
	 -1, -1,	/* 16 SummRealIt */	
	 -1, -1		/* 17 SummReImIt */	
};
WORD InsideDefs[isanz][2]={
	200, -1,	/*  0 BoF60 */		
	 -1, -1,	/*  1 BoF61 */		
	100, -1,	/*  2 Decomposition */
	100, -1,	/*  3 DiffParImag */	
	100, -1,	/*  4 DiffParReal */	
	100, -1,	/*  5 DiffParReIm */	
	200, -1,	/*  6 MagnifyImag */	
	200, -1,	/*  7 MagnifyReal */	
	200, -1,	/*  8 MagnifyReIm */	
	  0, -1,	/*  9 Normal */		
	300,  1,	/* 10 Orbit  */	
	100,  1,	/* 11 OrbitLength  */	
	100,  1,	/* 12 OrbitReIm  */	
};

//-- definitions --------------------------------------------------------------

void Open_COWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	register UBYTE i;
	register UWORD x;
	UWORD gx,gy;

/* Free ID : 12,13 Free IDX : 0,1 */

	if(g=CreateContext(&cmGList))
	{
		ng.ng_LeftEdge		=RunTime.scx[32];
		ng.ng_TopEdge		=RunTime.scy[184];
		ng.ng_Width			=RunTime.scx[90];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="_Load";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=14;
		ng.ng_Flags			=PLACETEXT_IN;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		cmGadgets[2]=g;

		ng.ng_LeftEdge		=RunTime.scx[132];
		ng.ng_GadgetText	="_Save";
		ng.ng_GadgetID		=15;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		cmGadgets[3]=g;

		ng.ng_LeftEdge		=RunTime.scx[232];
		ng.ng_GadgetText	="_View";
		ng.ng_GadgetID		=16;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		cmGadgets[4]=g;

		ng.ng_LeftEdge		=RunTime.scx[332];
		ng.ng_Width			=RunTime.scx[120];
		ng.ng_GadgetText	=" ";
		ng.ng_GadgetID		=17;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,cmBufferLabels,GTCY_Active,RunTime.aktpal,TAG_DONE);
		cmGadgets[5]=g;

		ng.ng_LeftEdge		=RunTime.scx[46];		/* Red */
		ng.ng_TopEdge		=RunTime.scy[155];
		ng.ng_Width			=RunTime.scx[40];
		ng.ng_GadgetText	="ScX";
		ng.ng_GadgetID		=21;
		ng.ng_Flags			=PLACETEXT_LEFT;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,2,GTIN_Number,PalInfo.r[RunTime.aktpal].scx,TAG_DONE);
		cmGadgets[9]=g;

		ng.ng_LeftEdge		=RunTime.scx[125];
		ng.ng_GadgetText	="ScY";
		ng.ng_GadgetID		=23;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,2,GTIN_Number,PalInfo.r[RunTime.aktpal].scy,TAG_DONE);
		cmGadgets[11]=g;

		ng.ng_LeftEdge		=RunTime.scx[20];
		ng.ng_TopEdge		=RunTime.scy[142];
		ng.ng_Width			=RunTime.scx[145];
		ng.ng_GadgetText	="";
		ng.ng_GadgetID		=22;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,cmShapeLabels,GTCY_Active,PalInfo.r[RunTime.aktpal].pst,TAG_DONE);
		cmGadgets[10]=g;

		ng.ng_LeftEdge		=RunTime.scx[221];		/* Green */
		ng.ng_TopEdge		=RunTime.scy[155];
		ng.ng_Width			=RunTime.scx[40];
		ng.ng_GadgetText	="ScX";
		ng.ng_GadgetID		=24;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,2,GTIN_Number,PalInfo.g[RunTime.aktpal].scx,TAG_DONE);
		cmGadgets[12]=g;

		ng.ng_LeftEdge		=RunTime.scx[300];
		ng.ng_GadgetText	="ScY";
		ng.ng_GadgetID		=26;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,2,GTIN_Number,PalInfo.g[RunTime.aktpal].scy,TAG_DONE);
		cmGadgets[14]=g;

		ng.ng_LeftEdge		=RunTime.scx[195];
		ng.ng_TopEdge		=RunTime.scy[142];
		ng.ng_Width			=RunTime.scx[145];
		ng.ng_GadgetText	=" ";
		ng.ng_GadgetID		=25;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,cmShapeLabels,GTCY_Active,PalInfo.g[RunTime.aktpal].pst,TAG_DONE);
		cmGadgets[13]=g;

		ng.ng_LeftEdge		=RunTime.scx[396];		/* Blue */
		ng.ng_TopEdge		=RunTime.scy[155];
		ng.ng_Width			=RunTime.scx[40];
		ng.ng_GadgetText	="ScX";
		ng.ng_GadgetID		=27;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,2,GTIN_Number,PalInfo.b[RunTime.aktpal].scx,TAG_DONE);
		cmGadgets[15]=g;

		ng.ng_LeftEdge		=RunTime.scx[475];
		ng.ng_GadgetText	="Scy";
		ng.ng_GadgetID		=29;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,2,GTIN_Number,PalInfo.b[RunTime.aktpal].scy,TAG_DONE);
		cmGadgets[17]=g;

		ng.ng_LeftEdge		=RunTime.scx[370];
		ng.ng_TopEdge		=RunTime.scy[142];
		ng.ng_Width			=RunTime.scx[145];
		ng.ng_GadgetText	=" ";
		ng.ng_GadgetID		=28;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,cmShapeLabels,GTCY_Active,PalInfo.b[RunTime.aktpal].pst,TAG_DONE);
		cmGadgets[16]=g;

		ng.ng_LeftEdge		=RunTime.scx[18];		/* Red Up Down */
		ng.ng_TopEdge		=RunTime.scy[130];
		ng.ng_Width			=RunTime.scx[17];
		ng.ng_Height		=RunTime.scy[10];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="¨";
		ng.ng_GadgetID		=30;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[18]=g;

		ng.ng_TopEdge		=RunTime.scy[120];
		ng.ng_GadgetText	="¤";
		ng.ng_GadgetID		=31;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[19]=g;

		ng.ng_TopEdge		=RunTime.scy[109];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="R";
		ng.ng_GadgetID		=32;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[20]=g;

		ng.ng_TopEdge		=RunTime.scy[99];
		ng.ng_Height		=RunTime.scy[10];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="£";
		ng.ng_GadgetID		=33;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[21]=g;

		ng.ng_TopEdge		=RunTime.scy[89];
		ng.ng_GadgetText	="§";
		ng.ng_GadgetID		=34;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[22]=g;

		ng.ng_LeftEdge		=RunTime.scx[35];		/* Red Left Rigth */
		ng.ng_TopEdge		=RunTime.scy[79];
		ng.ng_Width			=RunTime.scx[25];
		ng.ng_GadgetText	="²";
		ng.ng_GadgetID		=35;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[23]=g;

		ng.ng_LeftEdge		=RunTime.scx[60];
		ng.ng_GadgetText	="«";
		ng.ng_GadgetID		=36;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[25]=g;

		ng.ng_LeftEdge		=RunTime.scx[85];
		ng.ng_Width			=RunTime.scx[29];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="R";
		ng.ng_GadgetID		=37;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[25]=g;

		ng.ng_LeftEdge		=RunTime.scx[114];
		ng.ng_Width			=RunTime.scx[25];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="»";
		ng.ng_GadgetID		=38;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[25]=g;

		ng.ng_LeftEdge		=RunTime.scx[139];
		ng.ng_GadgetText	="³";
		ng.ng_GadgetID		=39;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[27]=g;

		ng.ng_LeftEdge		=RunTime.scx[193];		/* Green Up Down */
		ng.ng_TopEdge		=RunTime.scy[130];
		ng.ng_Width			=RunTime.scx[17];
		ng.ng_GadgetText	="¨";
		ng.ng_GadgetID		=40;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[28]=g;

		ng.ng_TopEdge		=RunTime.scy[120];
		ng.ng_GadgetText	="¤";
		ng.ng_GadgetID		=41;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[29]=g;

		ng.ng_TopEdge		=RunTime.scy[109];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="R";
		ng.ng_GadgetID		=42;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[30]=g;

		ng.ng_TopEdge		=RunTime.scy[99];
		ng.ng_Height		=RunTime.scy[10];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="£";
		ng.ng_GadgetID		=43;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[31]=g;

		ng.ng_TopEdge		=RunTime.scy[89];
		ng.ng_GadgetText	="§";
		ng.ng_GadgetID		=44;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[32]=g;

		ng.ng_LeftEdge		=RunTime.scx[210];		/* Green Left Rigth */
		ng.ng_TopEdge		=RunTime.scy[79];
		ng.ng_Width			=RunTime.scx[25];
		ng.ng_GadgetText	="²";
		ng.ng_GadgetID		=45;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[33]=g;

		ng.ng_LeftEdge		=RunTime.scx[235];
		ng.ng_GadgetText	="«";
		ng.ng_GadgetID		=46;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[34]=g;

		ng.ng_LeftEdge		=RunTime.scx[260];
		ng.ng_Width			=RunTime.scx[29];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="R";
		ng.ng_GadgetID		=47;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[35]=g;

		ng.ng_LeftEdge		=RunTime.scx[289];
		ng.ng_Width			=RunTime.scx[25];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="»";
		ng.ng_GadgetID		=48;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[36]=g;

		ng.ng_LeftEdge		=RunTime.scx[314];
		ng.ng_GadgetText	="³";
		ng.ng_GadgetID		=49;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[37]=g;

		ng.ng_LeftEdge		=RunTime.scx[368];		/* Blue Up Down */
		ng.ng_TopEdge		=RunTime.scy[130];
		ng.ng_Width			=RunTime.scx[17];
		ng.ng_GadgetText	="¨";
		ng.ng_GadgetID		=50;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[38]=g;

		ng.ng_TopEdge		=RunTime.scy[120];
		ng.ng_GadgetText	="¤";
		ng.ng_GadgetID		=51;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[39]=g;

		ng.ng_TopEdge		=RunTime.scy[109];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="R";
		ng.ng_GadgetID		=52;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[40]=g;

		ng.ng_TopEdge		=RunTime.scy[99];
		ng.ng_Height		=RunTime.scy[10];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="£";
		ng.ng_GadgetID		=53;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[41]=g;

		ng.ng_TopEdge		=RunTime.scy[89];
		ng.ng_GadgetText	="§";
		ng.ng_GadgetID		=54;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[42]=g;

		ng.ng_LeftEdge		=RunTime.scx[385];		/* Blue Left Rigth */
		ng.ng_TopEdge		=RunTime.scy[79];
		ng.ng_Width			=RunTime.scx[25];
		ng.ng_GadgetText	="²";
		ng.ng_GadgetID		=55;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[43]=g;

		ng.ng_LeftEdge		=RunTime.scx[410];
		ng.ng_GadgetText	="«";
		ng.ng_GadgetID		=56;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[44]=g;

		ng.ng_LeftEdge		=RunTime.scx[435];
		ng.ng_Width			=RunTime.scx[29];
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetText	="R";
		ng.ng_GadgetID		=57;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[45]=g;

		ng.ng_LeftEdge		=RunTime.scx[464];
		ng.ng_Width			=RunTime.scx[25];
		ng.ng_TextAttr		=&SigFont;
		ng.ng_GadgetText	="»";
		ng.ng_GadgetID		=58;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[46]=g;

		ng.ng_LeftEdge		=RunTime.scx[489];
		ng.ng_GadgetText	="³";
		ng.ng_GadgetID		=59;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		cmGadgets[47]=g;

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[535])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[208])>>1;
			smwintags[2].ti_Data=RunTime.scx[535];
			smwintags[3].ti_Data=RunTime.scy[208];
			smwintags[4].ti_Data=BUTTONIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)cmGList;
			smwintags[7].ti_Data=(ULONG)"Colors";
			if(cowin=OpenWindowTagList(0l,smwintags))
			{
				GT_RefreshWindow(cowin,0l);
				cmrp=*cowin->RPort;
				x=27;
				gx=RunTime.scx[14];gy=RunTime.scy[4];
				for(i=0;i<32;i++)
				{
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[22],gx,gy,FALSE);
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[27],gx,gy,FALSE);
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[32],gx,gy,FALSE);
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[37],gx,gy,FALSE);
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[42],gx,gy,FALSE);
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[47],gx,gy,FALSE);
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[52],gx,gy,FALSE);
					DrawGad(cmrp,RunTime.scx[x],RunTime.scy[57],gx,gy,FALSE);
					x+=15;
				}
				SetColorRange(RunTime.aktpal);
				DrawColorRange(cmrp);
				DrawPalShape(cmrp,0,rps[RunTime.aktpal]);
				DrawPalShape(cmrp,1,gps[RunTime.aktpal]);
				DrawPalShape(cmrp,2,bps[RunTime.aktpal]);

				DrawBox(cmrp,RunTime.scx[ 10],RunTime.scy[ 15],RunTime.scx[515],RunTime.scy[ 52],"Palette");
				DrawBox(cmrp,RunTime.scx[ 10],RunTime.scy[ 72],RunTime.scx[165],RunTime.scy[100],"Red");
				DrawBox(cmrp,RunTime.scx[185],RunTime.scy[ 72],RunTime.scx[165],RunTime.scy[100],"Green");
				DrawBox(cmrp,RunTime.scx[360],RunTime.scy[ 72],RunTime.scx[165],RunTime.scy[100],"Blue");
				DrawBox(cmrp,RunTime.scx[ 10],RunTime.scy[177],RunTime.scx[515],RunTime.scy[ 24],"Control");

				RunTime.sig_in|=(1L<<cowin->UserPort->mp_SigBit);
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
}

void Test_COWin(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	UBYTE quit=0;
	char fn[200];

	while(imsg=GT_GetIMsg(cowin->UserPort))
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
					case 14:			/* Load */
						if(AslRequest(Col_FRequest,Col_Reqtags))
						{
							strmfp(fn,Col_FRequest->fr_Drawer,Col_FRequest->fr_File);
							strcpy(fuprefs_path.color_path,Col_FRequest->fr_Drawer);
							LoadPalette(fn);
							RefreshPalShapes(cmrp,cmGadgets);
						}
						SetColorRange(RunTime.aktpal);
						break;
					case 15:			/* Save */
						if(AslRequest(Col_FRequest,Col_Reqtags))
						{
							strmfp(fn,Col_FRequest->fr_Drawer,Col_FRequest->fr_File);
							strcpy(fuprefs_path.color_path,Col_FRequest->fr_Drawer);
							SavePalette(fn);
						}
						SetColorRange(RunTime.aktpal);
						break;
					case 16:			/* View */
						MakeColorPalettes();SetColorPalette();
						mm_view();ActivateWindow(cowin);
						break;
					case 17:			/* PalBuffer */
						RunTime.aktpal=(int)icode;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						break;
					case 21:			/* Scale X Red */
						PalInfo.r[RunTime.aktpal].scx=(UBYTE)CheckGad_int(cmGadgets[9],cowin,1,1,255);
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 22:			/* Shape Red */
						PalInfo.r[RunTime.aktpal].pst=(UBYTE)icode;
						GetPalShape(PalInfo.r[RunTime.aktpal].pst,rps[RunTime.aktpal]);
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 23:			/* Scale Y Red */
						PalInfo.r[RunTime.aktpal].scy=(UBYTE)CheckGad_int(cmGadgets[11],cowin,1,1,255);
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 24:			/* Scale X Green */
						PalInfo.g[RunTime.aktpal].scx=(UBYTE)CheckGad_int(cmGadgets[12],cowin,1,1,255);
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 25:			/* Shape Green */
						PalInfo.g[RunTime.aktpal].pst=(UBYTE)icode;
						GetPalShape(PalInfo.g[RunTime.aktpal].pst,gps[RunTime.aktpal]);
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 26:			/* Scale Y Green */
						PalInfo.g[RunTime.aktpal].scy=(UBYTE)CheckGad_int(cmGadgets[14],cowin,1,1,255);
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 27:			/* Scale Blue */
						PalInfo.b[RunTime.aktpal].scx=(UBYTE)CheckGad_int(cmGadgets[15],cowin,1,1,255);
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 28:			/* Shape Blue */
						PalInfo.b[RunTime.aktpal].pst=(UBYTE)icode;
						GetPalShape(PalInfo.b[RunTime.aktpal].pst,bps[RunTime.aktpal]);
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 29:			/* Scale Y Blue */
						PalInfo.b[RunTime.aktpal].scy=(UBYTE)CheckGad_int(cmGadgets[17],cowin,1,1,255);
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 30:				/* Red Slow Down */
						PalInfo.r[RunTime.aktpal].yoff=(PalInfo.r[RunTime.aktpal].yoff-1)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 31:				/* Red Fast Down */
						PalInfo.r[RunTime.aktpal].yoff=(PalInfo.r[RunTime.aktpal].yoff-10)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 32:				/* Red Reset vert. */
						PalInfo.r[RunTime.aktpal].yoff=0;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 33:				/* Red Fast Up */
						PalInfo.r[RunTime.aktpal].yoff=(PalInfo.r[RunTime.aktpal].yoff+10)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 34:				/* Red Slow Up */
						PalInfo.r[RunTime.aktpal].yoff=(PalInfo.r[RunTime.aktpal].yoff+1)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 35:				/* Red Slow Left */
						PalInfo.r[RunTime.aktpal].xoff=(PalInfo.r[RunTime.aktpal].xoff+1)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 36:				/* Red Fast Left */
						PalInfo.r[RunTime.aktpal].xoff=(PalInfo.r[RunTime.aktpal].xoff+10)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 37:				/* Red Reset horiz. */
						PalInfo.r[RunTime.aktpal].xoff=0;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 38:				/* Red Fast Right */
						PalInfo.r[RunTime.aktpal].xoff=(PalInfo.r[RunTime.aktpal].xoff-10)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 39:				/* Red Slow Right */
						PalInfo.r[RunTime.aktpal].xoff=(PalInfo.r[RunTime.aktpal].xoff-1)&255;
						DrawPalShape(cmrp,0,rps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 40:				/* Green Slow Down */
						PalInfo.g[RunTime.aktpal].yoff=(PalInfo.g[RunTime.aktpal].yoff-1)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 41:				/* Green Fast Down */
						PalInfo.g[RunTime.aktpal].yoff=(PalInfo.g[RunTime.aktpal].yoff-10)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 42:				/* Green Reset vert. */
						PalInfo.g[RunTime.aktpal].yoff=0;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 43:				/* Green Fast Up */
						PalInfo.g[RunTime.aktpal].yoff=(PalInfo.g[RunTime.aktpal].yoff+10)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 44:				/* Green Slow Up */
						PalInfo.g[RunTime.aktpal].yoff=(PalInfo.g[RunTime.aktpal].yoff+1)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 45:				/* Green Slow Left */
						PalInfo.g[RunTime.aktpal].xoff=(PalInfo.g[RunTime.aktpal].xoff+1)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 46:				/* Red Fast Left */
						PalInfo.g[RunTime.aktpal].xoff=(PalInfo.g[RunTime.aktpal].xoff+10)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 47:				/* Green Reset horiz. */
						PalInfo.g[RunTime.aktpal].xoff=0;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 48:				/* Red Fast Right */
						PalInfo.g[RunTime.aktpal].xoff=(PalInfo.g[RunTime.aktpal].xoff-10)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 49:				/* Green Slow Right */
						PalInfo.g[RunTime.aktpal].xoff=(PalInfo.g[RunTime.aktpal].xoff-1)&255;
						DrawPalShape(cmrp,1,gps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 50:				/* Blue Slow Down */
						PalInfo.b[RunTime.aktpal].yoff=(PalInfo.b[RunTime.aktpal].yoff-1)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 51:				/* Blue Fast Down */
						PalInfo.b[RunTime.aktpal].yoff=(PalInfo.b[RunTime.aktpal].yoff-10)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 52:				/* Blue Reset vert. */
						PalInfo.b[RunTime.aktpal].yoff=0;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 53:				/* Blue Fast Up */
						PalInfo.b[RunTime.aktpal].yoff=(PalInfo.b[RunTime.aktpal].yoff+10)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 54:				/* Blue Slow Up */
						PalInfo.b[RunTime.aktpal].yoff=(PalInfo.b[RunTime.aktpal].yoff+1)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 55:				/* Blue Slow Left */
						PalInfo.b[RunTime.aktpal].xoff=(PalInfo.b[RunTime.aktpal].xoff+1)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 56:				/* Blue Fast Left */
						PalInfo.b[RunTime.aktpal].xoff=(PalInfo.b[RunTime.aktpal].xoff+10)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 57:				/* Blue Reset horiz. */
						PalInfo.b[RunTime.aktpal].xoff=0;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 58:				/* Blue Fast Left */
						PalInfo.b[RunTime.aktpal].xoff=(PalInfo.b[RunTime.aktpal].xoff-10)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
					case 59:				/* Blue Slow Right */
						PalInfo.b[RunTime.aktpal].xoff=(PalInfo.b[RunTime.aktpal].xoff-1)&255;
						DrawPalShape(cmrp,2,bps[RunTime.aktpal]);SetColorRange(RunTime.aktpal);
						break;
				}
				break;
			case IDCMP_VANILLAKEY:
				switch(icode)
				{
					case 'L':
					case 'l':
						if(AslRequest(Col_FRequest,Col_Reqtags))
						{
							strmfp(fn,Col_FRequest->fr_Drawer,Col_FRequest->fr_File);
							strcpy(fuprefs_path.color_path,Col_FRequest->fr_Drawer);
							LoadPalette(fn);
							RefreshPalShapes(cmrp,cmGadgets);
						}
						SetColorRange(RunTime.aktpal);
						break;
					case 'S':
					case 's':
						if(AslRequest(Col_FRequest,Col_Reqtags))
						{
							strmfp(fn,Col_FRequest->fr_Drawer,Col_FRequest->fr_File);
							strcpy(fuprefs_path.color_path,Col_FRequest->fr_Drawer);
							SavePalette(fn);
						}
						SetColorRange(RunTime.aktpal);
						break;
					case 'V':
					case 'v':
						MakeColorPalettes();SetColorPalette();
						mm_view();ActivateWindow(cowin);
						break;
					case '1':				/* 1 */
						RunTime.aktpal=0;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '2':				/* 2 */
						RunTime.aktpal=1;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '3':				/* 3 */
						RunTime.aktpal=2;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '4':				/* 4 */
						RunTime.aktpal=3;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '5':				/* 5 */
						RunTime.aktpal=4;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '6':				/* 6 */
						RunTime.aktpal=5;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '7':				/* 7 */
						RunTime.aktpal=6;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '8':				/* 8 */
						RunTime.aktpal=7;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '9':				/* 9 */
						RunTime.aktpal=8;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
					case '0':				/* 0 */
						RunTime.aktpal=9;
						RefreshPalShapes(cmrp,cmGadgets);
						SetColorRange(RunTime.aktpal);
						GT_SetGadgetAttrs(cmGadgets[5],cowin,0l,GTCY_Active,RunTime.aktpal,TAG_DONE);
						break;
				}
				break;
			case IDCMP_RAWKEY:
				switch(icode)
				{
					case 0x5F:
						Help("fu.guide","Project_Colors");
						SetColorRange(RunTime.aktpal);
						break;
				}
				break;
			case IDCMP_CLOSEWINDOW:
				quit=1;break;
		}
	}
	MakeColorPalettes();SetColorPalette();
	if(quit)
	{
		RunTime.sig_in&=(~(1L<<cowin->UserPort->mp_SigBit));
		if(cowin) CloseWindow(cowin);
		if(cmGList) FreeGadgets(cmGList);
		cowin=0l;
		cmGList=0l;
	}
}

void Refresh_COWin(void)
{
	SetColorRange(RunTime.aktpal);
	DrawPalShape(cmrp,0,rps[RunTime.aktpal]);
	DrawPalShape(cmrp,1,gps[RunTime.aktpal]);
	DrawPalShape(cmrp,2,bps[RunTime.aktpal]);
}

void Open_ZOWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	struct RastPort zmrp;
	char buf[30];
	UBYTE ac;

// Free : [0,12],[19,31]

	if(g=CreateContext(&zmGList))
	{
/* Zoom */
		ng.ng_LeftEdge		=RunTime.scx[55];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[85];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="Type";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=13;
		ng.ng_Flags			=PLACETEXT_LEFT;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,zmGadget14Labels,GTCY_Active,zm_ztype,TAG_DONE);
		zmGadgets[1]=g;

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="Mode";
		ng.ng_GadgetID		=14;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,zmGadget15Labels,GTCY_Active,zm_zmode,TAG_DONE);
		zmGadgets[2]=g;

		ng.ng_TopEdge		=RunTime.scy[44];
		ng.ng_GadgetText	="Snap";
		ng.ng_GadgetID		=15;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,zmGadget16Labels,GTCY_Active,zm_zsnap,TAG_DONE);
		zmGadgets[3]=g;

		ng.ng_LeftEdge		=RunTime.scx[144];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[50];
		ng.ng_GadgetText	="_Zoom";
		ng.ng_GadgetID		=16;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,GT_Underscore,'_',TAG_DONE);
		zmGadgets[4]=g;

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="Use";
		ng.ng_GadgetID		=30;
		g=CreateGadget(BUTTON_KIND,g,&ng,GA_Disabled,TRUE,TAG_DONE);
		zmGadgets[18]=g;
/* Window */
		ng.ng_LeftEdge		=RunTime.scx[40];
		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_Width			=RunTime.scx[60];
		ng.ng_GadgetText	="X1";
		ng.ng_GadgetID		=26;
		ng.ng_Flags			=PLACETEXT_LEFT;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,4,GTIN_Number,RenderInfo.xb1,TAG_DONE);
		zmGadgets[14]=g;

		ng.ng_TopEdge		=RunTime.scy[84];
		ng.ng_GadgetText	="Y1";
		ng.ng_GadgetID		=27;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,4,GTIN_Number,RenderInfo.yb1,TAG_DONE);
		zmGadgets[15]=g;

		ng.ng_LeftEdge		=RunTime.scx[135];
		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_GadgetText	="X2";
		ng.ng_GadgetID		=28;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,4,GTIN_Number,RenderInfo.xb2,TAG_DONE);
		zmGadgets[16]=g;

		ng.ng_TopEdge		=RunTime.scy[84];
		ng.ng_GadgetText	="Y2";
		ng.ng_GadgetID		=29;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,4,GTIN_Number,RenderInfo.yb2,TAG_DONE);
		zmGadgets[17]=g;

		ng.ng_LeftEdge		=RunTime.scx[20];
		ng.ng_TopEdge		=RunTime.scy[97];
		ng.ng_Width			=RunTime.scx[85];
		ng.ng_GadgetText	="Reset Win";
		ng.ng_GadgetID		=19;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		zmGadgets[7]=g;

		ng.ng_LeftEdge		=RunTime.scx[110];
		ng.ng_GadgetText	="Centre Win";
		ng.ng_GadgetID		=33;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		zmGadgets[21]=g;
/* Range */
		ng.ng_LeftEdge		=RunTime.scx[300];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[105];
		ng.ng_GadgetText	="real min";
		ng.ng_GadgetID		=20;
		ng.ng_Flags			=PLACETEXT_LEFT;
		sprintf(buf,"%20.15lf",RenderInfo.x1);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		zmGadgets[8]=g;

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="imag min";
		ng.ng_GadgetID		=21;
		sprintf(buf,"%20.15lf",RenderInfo.y1);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		zmGadgets[9]=g;

		ng.ng_TopEdge		=RunTime.scy[44];
		ng.ng_GadgetText	="Rotation";
		ng.ng_GadgetID		=32;
		sprintf(buf,"%20.15lf",RenderInfo.rot);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		zmGadgets[20]=g;

		ng.ng_TopEdge		=RunTime.scy[57];
		ng.ng_GadgetText	="Mirrormode";
		ng.ng_GadgetID		=22;
		ac=0;
		if(RenderInfo.mirrorx && RenderInfo.mirrory) ac=3;
		if(!RenderInfo.mirrorx && RenderInfo.mirrory) ac=2;
		if(RenderInfo.mirrorx && !RenderInfo.mirrory) ac=1;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,zmGadget22Labels,GTCY_Active,ac,TAG_DONE );
		zmGadgets[10]=g;

		ng.ng_TopEdge		=RunTime.scy[68];
		ng.ng_GadgetText	="Aspect X";
		ng.ng_GadgetID		=17;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		zmGadgets[5]=g;

		ng.ng_LeftEdge		=RunTime.scx[444];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[105];
		ng.ng_GadgetText	="max";
		ng.ng_GadgetID		=23;
		ng.ng_Flags			=PLACETEXT_LEFT;
		sprintf(buf,"%20.15lf",RenderInfo.x2);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		zmGadgets[11]=g;

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="max";
		ng.ng_GadgetID		=24;
		sprintf(buf,"%20.15lf",RenderInfo.y2);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		zmGadgets[12]=g;

		ng.ng_TopEdge		=RunTime.scy[57];
		ng.ng_GadgetText	="Reset";
		ng.ng_GadgetID		=25;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE );
		zmGadgets[13]=g;

		ng.ng_TopEdge		=RunTime.scy[68];
		ng.ng_GadgetText	="Aspect Y";
		ng.ng_GadgetID		=18;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		zmGadgets[6]=g;

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[569])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[121])>>1;
			smwintags[2].ti_Data=RunTime.scx[569];
			smwintags[3].ti_Data=RunTime.scy[121];
			smwintags[4].ti_Data=BUTTONIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)zmGList;
			smwintags[7].ti_Data=(ULONG)"Zoom";
			if(zowin=OpenWindowTagList(0l,smwintags))
			{
				GT_RefreshWindow(zowin,0l);

				zmrp=*zowin->RPort;

				DrawBox(zmrp,RunTime.scx[ 10],RunTime.scy[15],RunTime.scx[194],RunTime.scy[46],"Zoom");
				DrawBox(zmrp,RunTime.scx[214],RunTime.scy[15],RunTime.scx[345],RunTime.scy[70],"Corners");
				DrawBox(zmrp,RunTime.scx[ 10],RunTime.scy[66],RunTime.scx[194],RunTime.scy[48],"Window");

				RunTime.sig_in|=(1L<<zowin->UserPort->mp_SigBit);
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
}

void Test_ZOWin(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	UBYTE quit=0,ac,erg=0;
	LONG sx,sy;
	double nxd,nyd;
	char buf[30];
	LONG tmpxb1,tmpxb2,tmpyb1,tmpyb2;
	double tmpx1,tmpx2,tmpy1,tmpy2;
	long rs,rf;
	LONG xdif,ydif,xmit,ymit;

	while(imsg=GT_GetIMsg(zowin->UserPort))
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
/* Zoom */
					case 13:				/* Type */
						zm_ztype=(UBYTE)icode;break;
					case 14:				/* Mode */
						zm_zmode=(UBYTE)icode;break;
					case 15:				/* Snap */
						zm_zsnap=(UBYTE)icode;break;
					case 16:				/* Zoom */
						Zoom(zm_ztype,zm_zmode,zm_zsnap,&zm_x1,&zm_y1,&zm_x2,&zm_y2);
						GT_SetGadgetAttrs(zmGadgets[18],zowin,0l,GA_Disabled,FALSE,TAG_DONE);
						break;
					case 30:				/* Use */
						switch(zm_ztype)
						{
							case 0:
								sx=RenderInfo.xb2-RenderInfo.xb1;
								sy=RenderInfo.yb2-RenderInfo.yb1;
								xd=(RenderInfo.x2-RenderInfo.x1)/(float)sx;
								yd=(RenderInfo.y2-RenderInfo.y1)/(float)sy;
								RenderInfo.x1+=(zm_x1-RenderInfo.xb1)*xd;
								RenderInfo.y1+=(zm_y1-RenderInfo.yb1)*yd;
								RenderInfo.x2+=(zm_x2-RenderInfo.xb2)*xd;
								RenderInfo.y2+=(zm_y2-RenderInfo.yb2)*yd;
								sprintf(buf,"%20.15lf",RenderInfo.x1);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[8],zowin,0l,GTST_String,buf,TAG_DONE);
								sprintf(buf,"%20.15lf",RenderInfo.x2);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[11],zowin,0l,GTST_String,buf,TAG_DONE);
								if(RenderInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2<=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2>=0.0)))
								{
									RenderInfo.mirrory=0;ac=0;
									if(RenderInfo.mirrorx) ac=1;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}
								if(!RenderInfo.mirrory && FractalInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2>=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2<=0.0)))
								{
									RenderInfo.mirrory=1;ac=2;
									if(RenderInfo.mirrorx) ac=3;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}

								sprintf(buf,"%20.15lf",RenderInfo.y1);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[9],zowin,0l,GTST_String,buf,TAG_DONE);
								sprintf(buf,"%20.15lf",RenderInfo.y2);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[12],zowin,0l,GTST_String,buf,TAG_DONE);
								if(RenderInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2<=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2>=0.0)))
								{
									RenderInfo.mirrorx=0;ac=0;
									if(RenderInfo.mirrory) ac=2;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}
								if(!RenderInfo.mirrorx && FractalInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2>=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2<=0.0)))
								{
									RenderInfo.mirrorx=1;ac=1;
									if(RenderInfo.mirrory) ac=3;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}
								break;
							case 1:
								sx=zm_x2-zm_x1;
								sy=zm_y2-zm_y1;
								xd=(RenderInfo.x2-RenderInfo.x1)/(float)sx;
								yd=(RenderInfo.y2-RenderInfo.y1)/(float)sy;
								RenderInfo.x1-=(zm_x1-RenderInfo.xb1)*xd;
								RenderInfo.y1-=(zm_y1-RenderInfo.yb1)*yd;
								RenderInfo.x2-=(zm_x2-RenderInfo.xb2)*xd;
								RenderInfo.y2-=(zm_y2-RenderInfo.yb2)*yd;
								sprintf(buf,"%20.15lf",RenderInfo.x1);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[8],zowin,0l,GTST_String,buf,TAG_DONE);
								sprintf(buf,"%20.15lf",RenderInfo.x2);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[11],zowin,0l,GTST_String,buf,TAG_DONE);
								if(RenderInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2<=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2>=0.0)))
								{
									RenderInfo.mirrory=0;ac=0;
									if(RenderInfo.mirrorx) ac=1;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}
								if(!RenderInfo.mirrory && FractalInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2>=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2<=0.0)))
								{
									RenderInfo.mirrory=1;ac=2;
									if(RenderInfo.mirrorx) ac=3;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}
									sprintf(buf,"%20.15lf",RenderInfo.y1);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[9],zowin,0l,GTST_String,buf,TAG_DONE);
								sprintf(buf,"%20.15lf",RenderInfo.y2);FilterString(buf);
								GT_SetGadgetAttrs(zmGadgets[12],zowin,0l,GTST_String,buf,TAG_DONE);
								if(RenderInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2<=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2>=0.0)))
								{
									RenderInfo.mirrorx=0;ac=0;
									if(RenderInfo.mirrory) ac=2;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}
								if(!RenderInfo.mirrorx && FractalInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2>=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2<=0.0)))
								{
									RenderInfo.mirrorx=1;ac=1;
									if(RenderInfo.mirrory) ac=3;
									GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
								}
								break;
							case 2:
								if(zm_x2-zm_x1<40) { zm_x2+=20;zm_x1-=20; }
								if(zm_y2-zm_y1<32) { zm_y2+=16;zm_y1-=16; }
								if(zm_x1<0) zm_x1=0;
								if(zm_x2>=GfxInfo.xres) zm_x2=GfxInfo.xres-1;
								if(zm_y1<0) zm_y1=0;
								if(zm_y2>=GfxInfo.yres) zm_y2=GfxInfo.yres-1;
								xmit=(GfxInfo.xres-1)/2.0;ymit=(GfxInfo.yres-1)/2.0;
								xdif=(zm_x2-zm_x1)/2.0;ydif=(zm_y2-zm_y1)/2.0;
								RenderInfo.xb1=xmit-xdif;RenderInfo.xb2=xmit+xdif;
								RenderInfo.yb1=ymit-ydif;RenderInfo.yb2=ymit+ydif;
								GT_SetGadgetAttrs(zmGadgets[14],zowin,0l,GTIN_Number,zm_x1,TAG_DONE);
								GT_SetGadgetAttrs(zmGadgets[15],zowin,0l,GTIN_Number,zm_y1,TAG_DONE);
								GT_SetGadgetAttrs(zmGadgets[16],zowin,0l,GTIN_Number,zm_x2,TAG_DONE);
								GT_SetGadgetAttrs(zmGadgets[17],zowin,0l,GTIN_Number,zm_y2,TAG_DONE);
								break;
							case 3:
								preprender();
								tmpxb1=RenderInfo.xb1;tmpxb2=RenderInfo.xb2;
								tmpyb1=RenderInfo.yb1;tmpyb2=RenderInfo.yb2;
								tmpx1=RenderInfo.x1;tmpx2=RenderInfo.x2;
								tmpy1=RenderInfo.y1;tmpy2=RenderInfo.y2;
								if(zm_x1<0) zm_x1=0;
								if(zm_x2>=GfxInfo.xres) zm_x2=GfxInfo.xres-1;
								if(zm_y1<0) zm_y1=0;
								if(zm_y2>=GfxInfo.yres) zm_y2=GfxInfo.yres-1;
								RenderInfo.xb1=zm_x1;
								RenderInfo.yb1=zm_y1;
								RenderInfo.xb2=zm_x2;
								RenderInfo.yb2=zm_y2;
								sx=tmpxb2-tmpxb1;
								sy=tmpyb2-tmpyb1;
								xd=(RenderInfo.x2-RenderInfo.x1)/(float)sx;
								yd=(RenderInfo.y2-RenderInfo.y1)/(float)sy;
								RenderInfo.x1+=(zm_x1-tmpxb1)*xd;
								RenderInfo.y1+=(zm_y1-tmpyb1)*yd;
								RenderInfo.x2+=(zm_x2-tmpxb2)*xd;
								RenderInfo.y2+=(zm_y2-tmpyb2)*yd;
								ScreenToFront(rscreen);
								RectFill(&rrp[0],zm_x1,zm_y1,zm_x2,zm_y2);
								ActivateWindow(rwindow);
								time(&rs);
								switch(RenderInfo.rendermode)
								{
									case 0: erg=RenderSolid();break;
									case 1: erg=RenderSquare();break;
									case 2: erg=RenderFastSquare();break;
									case 3: erg=RenderPreview();break;
								}
								time(&rf);
								rendertime+=difftime(rf,rs);
								if(!erg)
								{
									if(RenderInfo.signal) DisplayBeep(rscreen);
									mm_view();
								}
								else
								{
									ScreenToFront(mmscr);
								}
								ActivateWindow(zowin);
								RenderInfo.xb1=tmpxb1;RenderInfo.xb2=tmpxb2;
								RenderInfo.yb1=tmpyb1;RenderInfo.yb2=tmpyb2;
								RenderInfo.x1=tmpx1;RenderInfo.x2=tmpx2;
								RenderInfo.y1=tmpy1;RenderInfo.y2=tmpy2;
								break;
						}
						GT_SetGadgetAttrs(zmGadgets[18],zowin,0l,GA_Disabled,TRUE,TAG_DONE);
						break;
/* Range */
					case 17:				/* Restore Aspect X */
						xd=RenderInfo.x2-RenderInfo.x1;
						yd=RenderInfo.y2-RenderInfo.y1;
						nxd=(yd*GfxInfo.xres)/GfxInfo.yres;
						nxd=(nxd-xd)/2.0;
						RenderInfo.x1-=nxd;RenderInfo.x2+=nxd;
						sprintf(buf,"%20.15lf",RenderInfo.x1);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[8],zowin,0l,GTST_String,buf,TAG_DONE);
						sprintf(buf,"%20.15lf",RenderInfo.x2);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[11],zowin,0l,GTST_String,buf,TAG_DONE);
						if(RenderInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2<=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2>=0.0)))
						{
							RenderInfo.mirrory=0;ac=0;
							if(RenderInfo.mirrorx) ac=1;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						if(!RenderInfo.mirrory && FractalInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2>=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2<=0.0)))
						{
							RenderInfo.mirrory=1;ac=2;
							if(RenderInfo.mirrorx) ac=3;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						break;
					case 18:				/* Restore Aspect Y */
						xd=RenderInfo.x2-RenderInfo.x1;
						yd=RenderInfo.y2-RenderInfo.y1;
						nyd=(xd*GfxInfo.yres)/GfxInfo.xres;
						nyd=(nyd-yd)/2.0;
						RenderInfo.y1-=nyd;RenderInfo.y2+=nyd;
						sprintf(buf,"%20.15f",RenderInfo.y1);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[9],zowin,0l,GTST_String,buf,TAG_DONE);
						sprintf(buf,"%20.15f",RenderInfo.y2);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[12],zowin,0l,GTST_String,buf,TAG_DONE);
						if(RenderInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2<=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2>=0.0)))
						{
							RenderInfo.mirrorx=0;ac=0;
							if(RenderInfo.mirrory) ac=2;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						if(!RenderInfo.mirrorx && FractalInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2>=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2<=0.0)))
						{
							RenderInfo.mirrorx=1;ac=1;
							if(RenderInfo.mirrory) ac=3;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						break;
					case 20:				/* real min */
						RenderInfo.x1=CheckGad_dbl(zmGadgets[8],zowin,0,0.0,0.0);
						if(RenderInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2<=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2>=0.0)))
						{
							RenderInfo.mirrory=0;ac=0;
							if(RenderInfo.mirrorx) ac=1;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						if(!RenderInfo.mirrory && FractalInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2>=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2<=0.0)))
						{
							RenderInfo.mirrory=1;ac=2;
							if(RenderInfo.mirrorx) ac=3;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						ActivateGadget(zmGadgets[11],zowin,0L);
						break;
					case 21:				/* imag min */
						RenderInfo.y1=CheckGad_dbl(zmGadgets[9],zowin,0,0.0,0.0);
						if(RenderInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2<=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2>=0.0)))
						{
							RenderInfo.mirrorx=0;ac=0;
							if(RenderInfo.mirrory) ac=2;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						if(!RenderInfo.mirrorx && FractalInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2>=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2<=0.0)))
						{
							RenderInfo.mirrorx=1;ac=1;
							if(RenderInfo.mirrory) ac=3;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						ActivateGadget(zmGadgets[12],zowin,0L);
						break;
					case 22:				/* mirrormode */
						switch(icode)
						{
							case 0:
								RenderInfo.mirrorx=0;RenderInfo.mirrory=0;break;
							case 1:
								RenderInfo.mirrorx=1;RenderInfo.mirrory=0;break;
							case 2:
								RenderInfo.mirrorx=0;RenderInfo.mirrory=1;break;
							case 3:
								RenderInfo.mirrorx=1;RenderInfo.mirrory=1;break;
						}
						break;
					case 23:				/* real max */
						RenderInfo.x2=CheckGad_dbl(zmGadgets[11],zowin,0,0.0,0.0);
						if(RenderInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2<=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2>=0.0)))
						{
							RenderInfo.mirrory=0;ac=0;
							if(RenderInfo.mirrorx) ac=1;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						if(!RenderInfo.mirrory && FractalInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2>=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2<=0.0)))
						{
							RenderInfo.mirrory=1;ac=2;
							if(RenderInfo.mirrorx) ac=3;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						ActivateGadget(zmGadgets[9],zowin,0L);
						break;
					case 24:				/* imag max */
						RenderInfo.y2=CheckGad_dbl(zmGadgets[12],zowin,0,0.0,0.0);
						if(RenderInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2<=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2>=0.0)))
						{
							RenderInfo.mirrorx=0;ac=0;
							if(RenderInfo.mirrory) ac=2;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						if(!RenderInfo.mirrorx && FractalInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2>=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2<=0.0)))
						{
							RenderInfo.mirrorx=1;ac=1;
							if(RenderInfo.mirrory) ac=3;
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						}
						ActivateGadget(zmGadgets[8],zowin,0L);
						break;
					case 25:				/* reset */
						sprintf(buf,"%20.15lf",FractalInfo.x1);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[8],zowin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.x1=FractalInfo.x1;
						sprintf(buf,"%20.15lf",FractalInfo.y1);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[9],zowin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.y1=FractalInfo.y1;
						sprintf(buf,"%20.15lf",FractalInfo.x2);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[11],zowin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.x2=FractalInfo.x2;
						sprintf(buf,"%20.15lf",FractalInfo.y2);FilterString(buf);
						GT_SetGadgetAttrs(zmGadgets[12],zowin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.y2=FractalInfo.y2;
						ac=0;
						if(FractalInfo.mirrorx && FractalInfo.mirrory) ac=3;
						if(!FractalInfo.mirrorx && FractalInfo.mirrory) ac=2;
						if(FractalInfo.mirrorx && !FractalInfo.mirrory) ac=1;
						GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
						RenderInfo.mirrorx=FractalInfo.mirrorx;RenderInfo.mirrory=FractalInfo.mirrory;
						break;
					case 32:				/* Rotation */
						RenderInfo.rot=CheckGad_dbl(zmGadgets[20],zowin,0,0.0,0.0);
						if((int)RenderInfo.rot==0)
						{
							if(RenderInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2<=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2>=0.0)))
							{
								RenderInfo.mirrory=0;ac=0;
								if(RenderInfo.mirrorx) ac=1;
								GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
							}
							if(!RenderInfo.mirrory && FractalInfo.mirrory && ((RenderInfo.x1<=0.0 && RenderInfo.x2>=0.0)||(RenderInfo.x1>=0.0 && RenderInfo.x2<=0.0)))
							{
								RenderInfo.mirrory=1;ac=2;
								if(RenderInfo.mirrorx) ac=3;
								GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
							}
							if(RenderInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2<=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2>=0.0)))
							{
								RenderInfo.mirrorx=0;ac=0;
								if(RenderInfo.mirrory) ac=2;
								GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
							}
							if(!RenderInfo.mirrorx && FractalInfo.mirrorx && ((RenderInfo.y1<=0.0 && RenderInfo.y2>=0.0)||(RenderInfo.y1>=0.0 && RenderInfo.y2<=0.0)))
							{
								RenderInfo.mirrorx=1;ac=1;
								if(RenderInfo.mirrory) ac=3;
								GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
							}
						}
						else
						{
							GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,0,TAG_DONE);
							RenderInfo.mirrorx=0;RenderInfo.mirrory=0;
						}
						break;
/* Window */
					case 19:				/* Reset Render Area */
						RenderInfo.xb1=0;RenderInfo.xb2=GfxInfo.xres-1;
						RenderInfo.yb1=0;RenderInfo.yb2=GfxInfo.yres-1;
						GT_SetGadgetAttrs(zmGadgets[14],zowin,0l,GTIN_Number,RenderInfo.xb1,TAG_DONE);
						GT_SetGadgetAttrs(zmGadgets[15],zowin,0l,GTIN_Number,RenderInfo.yb1,TAG_DONE);
						GT_SetGadgetAttrs(zmGadgets[16],zowin,0l,GTIN_Number,RenderInfo.xb2,TAG_DONE);
						GT_SetGadgetAttrs(zmGadgets[17],zowin,0l,GTIN_Number,RenderInfo.yb2,TAG_DONE);
						break;
					case 33:				/* Centre Render Area */
						xmit=(GfxInfo.xres-1)/2.0;ymit=(GfxInfo.yres-1)/2.0;
						xdif=(RenderInfo.xb2-RenderInfo.xb1)/2.0;
						ydif=(RenderInfo.yb2-RenderInfo.yb1)/2.0;
						RenderInfo.xb1=xmit-xdif;RenderInfo.xb2=xmit+xdif;
						RenderInfo.yb1=ymit-ydif;RenderInfo.yb2=ymit+ydif;
						GT_SetGadgetAttrs(zmGadgets[14],zowin,0l,GTIN_Number,RenderInfo.xb1,TAG_DONE);
						GT_SetGadgetAttrs(zmGadgets[15],zowin,0l,GTIN_Number,RenderInfo.yb1,TAG_DONE);
						GT_SetGadgetAttrs(zmGadgets[16],zowin,0l,GTIN_Number,RenderInfo.xb2,TAG_DONE);
						GT_SetGadgetAttrs(zmGadgets[17],zowin,0l,GTIN_Number,RenderInfo.yb2,TAG_DONE);
						break;
					case 26:				/* X1 */
						RenderInfo.xb1=CheckGad_int(zmGadgets[14],zowin,1,0,GfxInfo.xres-1);
						if(RenderInfo.xb1>RenderInfo.xb2)
						{
							Swap_shr((short *)(&RenderInfo.xb1),(short *)(&RenderInfo.xb2));
							GT_SetGadgetAttrs(zmGadgets[14],zowin,0l,GTIN_Number,RenderInfo.xb1,TAG_DONE);
							GT_SetGadgetAttrs(zmGadgets[16],zowin,0l,GTIN_Number,RenderInfo.xb2,TAG_DONE);
						}
						ActivateGadget(zmGadgets[16],zowin,0L);
						break;
					case 27:				/* Y1 */
						RenderInfo.yb1=CheckGad_int(zmGadgets[15],zowin,1,0,GfxInfo.yres-1);
						if(RenderInfo.yb1>RenderInfo.yb2)
						{
							Swap_shr((short *)(&RenderInfo.yb1),(short *)(&RenderInfo.yb2));
							GT_SetGadgetAttrs(zmGadgets[15],zowin,0l,GTIN_Number,RenderInfo.yb1,TAG_DONE);
							GT_SetGadgetAttrs(zmGadgets[17],zowin,0l,GTIN_Number,RenderInfo.yb2,TAG_DONE);
						}
						ActivateGadget(zmGadgets[17],zowin,0L);
						break;
					case 28:				/* X2 */
						RenderInfo.xb2=CheckGad_int(zmGadgets[16],zowin,1,0,GfxInfo.xres-1);
						if(RenderInfo.xb2<RenderInfo.xb1)
						{
							Swap_shr((short *)(&RenderInfo.xb1),(short *)(&RenderInfo.xb2));
							GT_SetGadgetAttrs(zmGadgets[14],zowin,0l,GTIN_Number,RenderInfo.xb1,TAG_DONE);
							GT_SetGadgetAttrs(zmGadgets[16],zowin,0l,GTIN_Number,RenderInfo.xb2,TAG_DONE);
						}
						ActivateGadget(zmGadgets[15],zowin,0L);
						break;
					case 29:				/* Y2 */
						RenderInfo.yb2=CheckGad_int(zmGadgets[17],zowin,1,0,GfxInfo.yres-1);
						if(RenderInfo.yb2<RenderInfo.yb1)
						{
							Swap_shr((short *)(&RenderInfo.yb1),(short *)(&RenderInfo.yb2));
							GT_SetGadgetAttrs(zmGadgets[15],zowin,0l,GTIN_Number,RenderInfo.yb1,TAG_DONE);
							GT_SetGadgetAttrs(zmGadgets[17],zowin,0l,GTIN_Number,RenderInfo.yb2,TAG_DONE);
						}
						ActivateGadget(zmGadgets[14],zowin,0L);
						break;
				}
				break;
			case IDCMP_VANILLAKEY:
				switch(icode)
				{
					case 'Z':
					case 'z':
						Zoom(zm_ztype,zm_zmode,zm_zsnap,&zm_x1,&zm_y1,&zm_x2,&zm_y2);
						GT_SetGadgetAttrs(zmGadgets[18],zowin,0l,GA_Disabled,FALSE,TAG_DONE);
						break;
				}
				break;
			case IDCMP_RAWKEY:
				switch(icode)
				{
					case 0x5F:
						Help("fu.guide","Project_Zoom");
						break;
				}
				break;
			case IDCMP_CLOSEWINDOW:
				quit=1;break;
		}
	}
	if(quit)
	{
		RunTime.sig_in&=(~(1L<<zowin->UserPort->mp_SigBit));
		if(zowin) CloseWindow(zowin);
		if(zmGList) FreeGadgets(zmGList);
		zowin=0l;
		zmGList=0l;
	}
}

void Refresh_ZOWin(void)
{
	UBYTE ac;
	char buf[30];

	sprintf(buf,"%20.15lf",RenderInfo.x1);FilterString(buf);
	GT_SetGadgetAttrs(zmGadgets[8],zowin,0l,GTST_String,buf,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.x2);FilterString(buf);
	GT_SetGadgetAttrs(zmGadgets[11],zowin,0l,GTST_String,buf,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.y1);FilterString(buf);
	GT_SetGadgetAttrs(zmGadgets[9],zowin,0l,GTST_String,buf,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.y2);FilterString(buf);
	GT_SetGadgetAttrs(zmGadgets[12],zowin,0l,GTST_String,buf,TAG_DONE);
	ac=0;
	if(RenderInfo.mirrorx && RenderInfo.mirrory) ac=3;
	if(!RenderInfo.mirrorx && RenderInfo.mirrory) ac=2;
	if(RenderInfo.mirrorx && !RenderInfo.mirrory) ac=1;
	GT_SetGadgetAttrs(zmGadgets[10],zowin,0l,GTCY_Active,ac,TAG_DONE);
}

void Open_OPWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	char buf[30];

// Free : 0,1,7,28

	if(g=CreateContext(&omGList))
	{
/* Draw Options */

		ng.ng_LeftEdge		=RunTime.scx[69];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[90];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="Dither";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=2;
		ng.ng_Flags			=PLACETEXT_LEFT;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadget02Labels,GTCY_Active,GfxInfo.dither,TAG_DONE);
		omGadgets[2]=g;

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="OrdScl";
		ng.ng_GadgetID		=3;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,2,GTIN_Number,GfxInfo.ordscl,TAG_DONE);
		omGadgets[3]=g;

		ng.ng_LeftEdge		=RunTime.scx[218];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_GadgetText	="Render";
		ng.ng_GadgetID		=4;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadget04Labels,GTCY_Active,RenderInfo.rendermode,TAG_DONE);
		omGadgets[4]=g;

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_GadgetText	="GFX";
		ng.ng_GadgetID		=5;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadget05Labels,GTCY_Active,GfxInfo.gfxtyp,TAG_DONE);
		omGadgets[5]=g;

/* Misc */

		ng.ng_LeftEdge		=RunTime.scx[397];		/* 388 */
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[26];
		ng.ng_GadgetText	="Beep";
		ng.ng_GadgetID		=6;
		g=CreateGadget(CHECKBOX_KIND,g,&ng,GTCB_Checked,RenderInfo.signal,GTCB_Scaled,TRUE,TAG_DONE);
		omGadgets[6]=g;

// 7 frei für Prec.

/* Palette */

		ng.ng_LeftEdge		=RunTime.scx[483];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[30];
		ng.ng_GadgetText	="Scl";
		ng.ng_GadgetID		=8;
		ng.ng_Flags			=PLACETEXT_LEFT;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,4,GTIN_Number,GfxInfo.palscl,TAG_DONE);
		omGadgets[8]=g;

		ng.ng_TopEdge		=RunTime.scy[33];
		ng.ng_Width			=RunTime.scx[85];
		ng.ng_GadgetText	="Map";
		ng.ng_GadgetID		=9;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadget09Labels,GTCY_Active,GfxInfo.palmap,TAG_DONE);
		omGadgets[9]=g;

		ng.ng_LeftEdge		=RunTime.scx[558];
		ng.ng_TopEdge		=RunTime.scy[22];
		ng.ng_Width			=RunTime.scx[26];
		ng.ng_GadgetText	="Rev.";
		ng.ng_GadgetID		=10;
		g=CreateGadget(CHECKBOX_KIND,g,&ng,GTCB_Checked,GfxInfo.revpal,GTCB_Scaled,TRUE,TAG_DONE);
		omGadgets[10]=g;

/* Params */

		ng.ng_LeftEdge		=RunTime.scx[43];
		ng.ng_TopEdge		=RunTime.scy[62];
		ng.ng_Width			=RunTime.scx[70];
		ng.ng_GadgetText	="P1";
		ng.ng_GadgetID		=11;
		ng.ng_Flags			=PLACETEXT_LEFT;
		sprintf(buf,"%20.15lf",RenderInfo.par1.r);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[11]=g;

		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_GadgetText	="P2";
		ng.ng_GadgetID		=12;
		sprintf(buf,"%20.15lf",RenderInfo.par2.r);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[12]=g;

		ng.ng_TopEdge		=RunTime.scy[84];
		ng.ng_GadgetText	="P3";
		ng.ng_GadgetID		=13;
		sprintf(buf,"%20.15lf",RenderInfo.par3.r);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[13]=g;

		ng.ng_TopEdge		=RunTime.scy[95];
		ng.ng_GadgetText	="P4";
		ng.ng_GadgetID		=14;
		sprintf(buf,"%20.15lf",RenderInfo.par4.r);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[14]=g;

		ng.ng_LeftEdge		=RunTime.scx[120];
		ng.ng_TopEdge		=RunTime.scy[62];
		ng.ng_GadgetText	="";
		ng.ng_GadgetID		=15;
		sprintf(buf,"%20.15lf",RenderInfo.par1.i);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[15]=g;

		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_GadgetID		=16;
		sprintf(buf,"%20.15lf",RenderInfo.par2.i);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[16]=g;

		ng.ng_TopEdge		=RunTime.scy[84];
		ng.ng_GadgetID		=17;
		sprintf(buf,"%20.15lf",RenderInfo.par3.i);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[17]=g;

		ng.ng_TopEdge		=RunTime.scy[95];
		ng.ng_GadgetID		=18;
		sprintf(buf,"%20.15lf",RenderInfo.par4.i);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend2;
		omGadgets[18]=g;

		ng.ng_LeftEdge		=RunTime.scx[201];
		ng.ng_TopEdge		=RunTime.scy[62];
		ng.ng_Width			=RunTime.scx[18];
		ng.ng_GadgetText	="P";
		ng.ng_GadgetID		=19;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		omGadgets[19]=g;

		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_GadgetID		=20;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		omGadgets[20]=g;

		ng.ng_TopEdge		=RunTime.scy[84];
		ng.ng_GadgetID		=21;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		omGadgets[21]=g;

		ng.ng_TopEdge		=RunTime.scy[95];
		ng.ng_GadgetID		=22;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		omGadgets[22]=g;

		ng.ng_LeftEdge		=RunTime.scx[266];
		ng.ng_TopEdge		=RunTime.scy[62];
		ng.ng_Width			=RunTime.scx[60];
		ng.ng_GadgetText	="Fn1";
		ng.ng_GadgetID		=23;
		ng.ng_Flags			=PLACETEXT_LEFT;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadgetFuncLabels,GTCY_Active,RenderInfo.tpar1,TAG_DONE);
		omGadgets[23]=g;

		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_GadgetText	="Fn2";
		ng.ng_GadgetID		=24;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadgetFuncLabels,GTCY_Active,RenderInfo.tpar2,TAG_DONE);
		omGadgets[24]=g;

		ng.ng_TopEdge		=RunTime.scy[84];
		ng.ng_GadgetText	="Fn3";
		ng.ng_GadgetID		=25;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadgetFuncLabels,GTCY_Active,RenderInfo.tpar3,TAG_DONE);
		omGadgets[25]=g;

		ng.ng_TopEdge		=RunTime.scy[95];
		ng.ng_GadgetText	="Fn4";
		ng.ng_GadgetID		=26;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadgetFuncLabels,GTCY_Active,RenderInfo.tpar4,TAG_DONE);
		omGadgets[26]=g;

		ng.ng_LeftEdge		=RunTime.scx[101];
		ng.ng_TopEdge		=RunTime.scy[108];
		ng.ng_Width			=RunTime.scx[74];
		ng.ng_GadgetText	="Iter";
		ng.ng_GadgetID		=27;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,6,GTIN_Number,RenderInfo.z,TAG_DONE);
		omGadgets[27]=g;

		ng.ng_LeftEdge		=RunTime.scx[251];
		ng.ng_TopEdge		=RunTime.scy[108];
		ng.ng_GadgetText	="bailout";
		ng.ng_GadgetID		=29;
		sprintf(buf,"%20.15lf",RenderInfo.bailout);FilterString(buf);
		g=CreateGadget(STRING_KIND,g,&ng,GTST_MaxChars,20,GTST_String,buf,TAG_DONE);
		((struct StringInfo*)g->SpecialInfo)->Extension=&stringextend3;
		omGadgets[29]=g;

		ng.ng_TopEdge		=RunTime.scy[121];
		ng.ng_GadgetText	="Reset";
		ng.ng_GadgetID		=30;
		ng.ng_Flags			=PLACETEXT_IN;
		g=CreateGadget(BUTTON_KIND,g,&ng,TAG_DONE);
		omGadgets[30]=g;

/* Color Models */

		ng.ng_LeftEdge		=RunTime.scx[359];
		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_Width			=RunTime.scx[110];
		ng.ng_Height		=RunTime.scy[60];
		ng.ng_GadgetText	="InsideMode";
		ng.ng_GadgetID		=31;
		ng.ng_Flags			=PLACETEXT_ABOVE;
		g=CreateGadget(LISTVIEW_KIND,g,&ng,GTLV_Labels,&InsideGadgetList,GTLV_Selected,RenderInfo.inside,GTLV_Top,RenderInfo.inside,GTLV_ShowSelected,0l,TAG_DONE);
		omGadgets[31]=g;

		ng.ng_LeftEdge		=RunTime.scx[409];
		ng.ng_TopEdge		=RunTime.scy[131];
		ng.ng_Width			=RunTime.scx[60];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="Par1";
		ng.ng_GadgetID		=32;
		ng.ng_Flags			=PLACETEXT_LEFT;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,5,GTIN_Number,RenderInfo.inpar1,TAG_DONE);
		omGadgets[32]=g;

		ng.ng_TopEdge		=RunTime.scy[142];
		ng.ng_GadgetText	="Par2";
		ng.ng_GadgetID		=33;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,5,GTIN_Number,RenderInfo.inpar2,TAG_DONE);
		omGadgets[33]=g;

		ng.ng_LeftEdge		=RunTime.scx[479];
		ng.ng_TopEdge		=RunTime.scy[73];
		ng.ng_Width			=RunTime.scx[110];
		ng.ng_Height		=RunTime.scy[60];
		ng.ng_GadgetText	="OutsideMode";
		ng.ng_GadgetID		=34;
		ng.ng_Flags			=PLACETEXT_ABOVE;
		g=CreateGadget(LISTVIEW_KIND,g,&ng,GTLV_Labels,&OutsideGadgetList,GTLV_Selected,RenderInfo.outside,GTLV_Top,RenderInfo.outside,GTLV_ShowSelected,0l,TAG_DONE);
		omGadgets[34]=g;

		ng.ng_LeftEdge		=RunTime.scx[529];
		ng.ng_TopEdge		=RunTime.scy[131];
		ng.ng_Width			=RunTime.scx[60];
		ng.ng_Height		=RunTime.scy[11];
		ng.ng_GadgetText	="Par1";
		ng.ng_GadgetID		=35;
		ng.ng_Flags			=PLACETEXT_LEFT;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,5,GTIN_Number,RenderInfo.outpar1,TAG_DONE);
		omGadgets[35]=g;

		ng.ng_TopEdge		=RunTime.scy[142];
		ng.ng_GadgetText	="Par2";
		ng.ng_GadgetID		=36;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_MaxChars,5,GTIN_Number,RenderInfo.outpar2,TAG_DONE);
		omGadgets[36]=g;

/* Orbit Options */

		ng.ng_LeftEdge		=RunTime.scx[395];
		ng.ng_TopEdge		=RunTime.scy[173];
		ng.ng_Width			=RunTime.scx[70];
		ng.ng_GadgetText	="Step";
		ng.ng_GadgetID		=37;
		g=CreateGadget(INTEGER_KIND,g,&ng,GTIN_Number,RenderInfo.obstep,TAG_DONE);
		omGadgets[37]=g;

		ng.ng_LeftEdge		=RunTime.scx[545];
		ng.ng_Width			=RunTime.scx[26];
		ng.ng_GadgetText	="Connect";
		ng.ng_GadgetID		=38;
		g=CreateGadget(CHECKBOX_KIND,g,&ng,GTCB_Checked,RenderInfo.obconnect,GTCB_Scaled,TRUE,TAG_DONE);
		omGadgets[38]=g;

		ng.ng_LeftEdge		=RunTime.scx[395];
		ng.ng_TopEdge		=RunTime.scy[185];
		ng.ng_Width			=RunTime.scx[70];
		ng.ng_GadgetText	="Size";
		ng.ng_GadgetID		=39;
		g=CreateGadget(CYCLE_KIND,g,&ng,GTCY_Labels,omGadget39Labels,GTCY_Active,RenderInfo.obsize,TAG_DONE);
		omGadgets[39]=g;

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[608])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[208])>>1;
			smwintags[2].ti_Data=RunTime.scx[608];
			smwintags[3].ti_Data=RunTime.scy[208];
			smwintags[4].ti_Data=BUTTONIDCMP|LISTVIEWIDCMP|SLIDERIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)omGList;
			smwintags[7].ti_Data=(ULONG)"Options";
			if(opwin=OpenWindowTagList(0l,smwintags))
			{
				if(GfxInfo.palmap!=0)
				{
					GfxInfo.dither=0;
					GT_SetGadgetAttrs(omGadgets[2],opwin,0l,GTCY_Active,GfxInfo.dither,GA_Disabled,TRUE,TAG_DONE);
					GT_SetGadgetAttrs(omGadgets[3],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
				}

				if(InsideDefs[RenderInfo.inside][0]==-1)
				{
					RenderInfo.inpar1=0;
					GT_SetGadgetAttrs(omGadgets[32],opwin,0l,GTIN_Number,RenderInfo.inpar1,GA_Disabled,TRUE,TAG_DONE);
				}
				if(InsideDefs[RenderInfo.inside][1]==-1)
				{
					RenderInfo.inpar2=0;
					GT_SetGadgetAttrs(omGadgets[33],opwin,0l,GTIN_Number,RenderInfo.inpar2,GA_Disabled,TRUE,TAG_DONE);
				}
				if(OutsideDefs[RenderInfo.outside][0]==-1)
				{
					RenderInfo.outpar1=0;
					GT_SetGadgetAttrs(omGadgets[35],opwin,0l,GTIN_Number,RenderInfo.outpar1,GA_Disabled,TRUE,TAG_DONE);
				}
				if(OutsideDefs[RenderInfo.outside][1]==-1)
				{
					RenderInfo.outpar2=0;
					GT_SetGadgetAttrs(omGadgets[36],opwin,0l,GTIN_Number,RenderInfo.outpar2,GA_Disabled,TRUE,TAG_DONE);
				}
				if(GfxInfo.dither!=4) GT_SetGadgetAttrs(omGadgets[3],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
				GT_RefreshWindow(opwin,0l);

				omrp=*opwin->RPort;

				DrawBox(omrp,RunTime.scx[ 10],RunTime.scy[ 15],RunTime.scx[327],RunTime.scy[ 35],"DrawOpt.");
				DrawBox(omrp,RunTime.scx[348],RunTime.scy[ 15],RunTime.scx[ 86],RunTime.scy[ 35],"Misc.");
				DrawBox(omrp,RunTime.scx[444],RunTime.scy[ 15],RunTime.scx[154],RunTime.scy[ 35],"Palette");
				DrawBox(omrp,RunTime.scx[ 10],RunTime.scy[ 55],RunTime.scx[328],RunTime.scy[ 83],"Parameter");
				DrawBox(omrp,RunTime.scx[348],RunTime.scy[ 55],RunTime.scx[250],RunTime.scy[105],"ColorModels");
				DrawBox(omrp,RunTime.scx[ 10],RunTime.scy[143],RunTime.scx[328],RunTime.scy[ 45],"Description");
				DrawBox(omrp,RunTime.scx[348],RunTime.scy[165],RunTime.scx[250],RunTime.scy[ 36],"Orbit");

				Refresh_OPWin();

				RunTime.sig_in|=(1L<<opwin->UserPort->mp_SigBit);

			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
}

void Test_OPWin(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	UBYTE quit=0;
	char buf[30];

	while(imsg=GT_GetIMsg(opwin->UserPort))
	{
		iclass	=imsg->Class;
		iadr		=imsg->IAddress;
		icode	=imsg->Code;
		GT_ReplyIMsg(imsg);
		switch(iclass)
		{
			case IDCMP_GADGETUP:
				switch((int)(((struct Gadget *)iadr)->GadgetID))
				{
/* Draw Options */
					case 2:				/* Dither */
						GfxInfo.dither=(int)icode;
						if(GfxInfo.dither==4) GT_SetGadgetAttrs(omGadgets[3],opwin,0l,GA_Disabled,FALSE,TAG_DONE);
						else GT_SetGadgetAttrs(omGadgets[3],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
						break;
					case 3:				/* Orderdscale */
						GfxInfo.ordscl=atoi(((struct StringInfo *)(omGadgets[3]->SpecialInfo))->Buffer);
						if(GfxInfo.ordscl<2)
						{
							GfxInfo.ordscl=2;
							GT_SetGadgetAttrs(omGadgets[3],opwin,0l,GTIN_Number,GfxInfo.ordscl,TAG_DONE);
						}
						if(GfxInfo.ordscl>16)
						{
							GfxInfo.ordscl=16;
							GT_SetGadgetAttrs(omGadgets[3],opwin,0l,GTIN_Number,GfxInfo.ordscl,TAG_DONE);
						}
						break;
					case 4:				/* RenderMode */
						RenderInfo.rendermode=(int)icode;
						break;
					case 5:				/* GfxRoutines */
						GfxInfo.gfxtyp=(UBYTE)icode;
						MSG1("gfx-typ=%d",GfxInfo.gfxtyp);
						break;
/* Misc */
					case 6:				/* Signal */
						RenderInfo.signal=(omGadgets[6]->Flags&GFLG_SELECTED);
						break;
/* Palette */
					case 8:				/* PaletteScale */
						GfxInfo.palscl=atoi(((struct StringInfo *)(omGadgets[8]->SpecialInfo))->Buffer);
						if(GfxInfo.palscl==0)
						{
							GfxInfo.palscl=1;
							GT_SetGadgetAttrs(omGadgets[8],opwin,0l,GTIN_Number,GfxInfo.palscl,TAG_DONE);
						}
						break;
					case 9:				/* PaletteMapping */
						GfxInfo.palmap=(int)icode;
						if(GfxInfo.palmap==0)
						{
							GT_SetGadgetAttrs(omGadgets[2],opwin,0l,GA_Disabled,FALSE,TAG_DONE);
						}
						else
						{
							GfxInfo.dither=0;
							GT_SetGadgetAttrs(omGadgets[2],opwin,0l,GTCY_Active,GfxInfo.dither,GA_Disabled,TRUE,TAG_DONE);
							GT_SetGadgetAttrs(omGadgets[3],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
						}
						break;
					case 10:				/* RevPal */
						GfxInfo.revpal=(omGadgets[10]->Flags&GFLG_SELECTED);
						break;
/* Parameter */
					case 11:				/* par1.r */
						RenderInfo.par1.r=CheckGad_dbl(omGadgets[11],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[15],opwin,0L);
						break;
					case 12:				/* par2.r */
						RenderInfo.par2.r=CheckGad_dbl(omGadgets[12],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[16],opwin,0L);
						break;
					case 13:				/* par3.r */
						RenderInfo.par3.r=CheckGad_dbl(omGadgets[13],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[17],opwin,0L);
						break;
					case 14:				/* par4.r */
						RenderInfo.par4.r=CheckGad_dbl(omGadgets[14],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[18],opwin,0L);
						break;
					case 15:				/* par1.i */
						RenderInfo.par1.i=CheckGad_dbl(omGadgets[15],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[11],opwin,0L);
						break;
					case 16:				/* par2.i */
						RenderInfo.par2.i=CheckGad_dbl(omGadgets[16],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[12],opwin,0L);
						break;
					case 17:				/* par3.i */
						RenderInfo.par3.i=CheckGad_dbl(omGadgets[17],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[13],opwin,0L);
						break;
					case 18:				/* par4.i */
						RenderInfo.par4.i=CheckGad_dbl(omGadgets[18],opwin,0,0.0,0.0);
						ActivateGadget(omGadgets[24],opwin,0L);
						break;
					case 19:
						Pick(&RenderInfo.par1.r,&RenderInfo.par1.i);
						sprintf(buf,"%20.15lf",RenderInfo.par1.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[11],opwin,0l,GTST_String,buf,TAG_DONE);
						sprintf(buf,"%20.15lf",RenderInfo.par1.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[15],opwin,0l,GTST_String,buf,TAG_DONE);
						break;
					case 20:
						Pick(&RenderInfo.par2.r,&RenderInfo.par2.i);
						sprintf(buf,"%20.15lf",RenderInfo.par2.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[12],opwin,0l,GTST_String,buf,TAG_DONE);
						sprintf(buf,"%20.15lf",RenderInfo.par2.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[16],opwin,0l,GTST_String,buf,TAG_DONE);
						break;
					case 21:
						Pick(&RenderInfo.par3.r,&RenderInfo.par3.i);
						sprintf(buf,"%20.15lf",RenderInfo.par3.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[13],opwin,0l,GTST_String,buf,TAG_DONE);
						sprintf(buf,"%20.15lf",RenderInfo.par3.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[17],opwin,0l,GTST_String,buf,TAG_DONE);
						break;
					case 22:
						Pick(&RenderInfo.par4.r,&RenderInfo.par4.i);
						sprintf(buf,"%20.15lf",RenderInfo.par4.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[14],opwin,0l,GTST_String,buf,TAG_DONE);
						sprintf(buf,"%20.15lf",RenderInfo.par4.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[18],opwin,0l,GTST_String,buf,TAG_DONE);
						break;
					case 23:
						RenderInfo.tpar1=(UBYTE)icode;
						break;
					case 24:
						RenderInfo.tpar2=(UBYTE)icode;
						break;
					case 25:
						RenderInfo.tpar3=(UBYTE)icode;
						break;
					case 26:
						RenderInfo.tpar4=(UBYTE)icode;
						break;
					case 27:				/* Iterations */
						RenderInfo.z=CheckGad_int(omGadgets[27],opwin,1,1,65535);
						break;
					case 29:				/* bailout */
						RenderInfo.bailout=CheckGad_dbl(omGadgets[29],opwin,0,0.0,0.0);
						break;
					case 30:			/* Reset */
						sprintf(buf,"%20.15lf",FractalInfo.par1.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[11],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par1.r=FractalInfo.par1.r;
						sprintf(buf,"%20.15lf",FractalInfo.par2.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[12],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par2.r=FractalInfo.par2.r;
						sprintf(buf,"%20.15lf",FractalInfo.par3.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[13],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par3.r=FractalInfo.par3.r;
						sprintf(buf,"%20.15lf",FractalInfo.par4.r);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[14],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par4.r=FractalInfo.par4.r;

						sprintf(buf,"%20.15lf",FractalInfo.par1.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[15],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par1.i=FractalInfo.par1.i;
						sprintf(buf,"%20.15lf",FractalInfo.par2.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[16],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par2.i=FractalInfo.par2.i;
						sprintf(buf,"%20.15lf",FractalInfo.par3.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[17],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par3.i=FractalInfo.par3.i;
						sprintf(buf,"%20.15lf",FractalInfo.par4.i);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[18],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.par4.i=FractalInfo.par4.i;

						sprintf(buf,"%20.15lf",FractalInfo.bailout);FilterString(buf);
						GT_SetGadgetAttrs(omGadgets[29],opwin,0l,GTST_String,buf,TAG_DONE);
						RenderInfo.bailout=FractalInfo.bailout;

						GT_SetGadgetAttrs(omGadgets[23],opwin,0l,GTCY_Active,FractalInfo.tpar1,TAG_DONE);
						RenderInfo.tpar1=FractalInfo.tpar1;
						GT_SetGadgetAttrs(omGadgets[24],opwin,0l,GTCY_Active,FractalInfo.tpar2,TAG_DONE);
						RenderInfo.tpar2=FractalInfo.tpar2;
						GT_SetGadgetAttrs(omGadgets[25],opwin,0l,GTCY_Active,FractalInfo.tpar3,TAG_DONE);
						RenderInfo.tpar3=FractalInfo.tpar3;
						GT_SetGadgetAttrs(omGadgets[26],opwin,0l,GTCY_Active,FractalInfo.tpar4,TAG_DONE);
						RenderInfo.tpar4=FractalInfo.tpar4;
						break;
/* ColorModels */
					case 31:				/* InsideMode */
						RenderInfo.inside=insidelist[icode].nr;
						if(InsideDefs[RenderInfo.inside][0]==-1)
						{
							RenderInfo.inpar1=0;
							GT_SetGadgetAttrs(omGadgets[32],opwin,0l,GTIN_Number,RenderInfo.inpar1,GA_Disabled,TRUE,TAG_DONE);
						}
						else
						{
							RenderInfo.inpar1=InsideDefs[RenderInfo.inside][0];
							GT_SetGadgetAttrs(omGadgets[32],opwin,0l,GTIN_Number,RenderInfo.inpar1,GA_Disabled,FALSE,TAG_DONE);
						}
						if(InsideDefs[RenderInfo.inside][1]==-1)
						{
							RenderInfo.inpar2=0;
							GT_SetGadgetAttrs(omGadgets[33],opwin,0l,GTIN_Number,RenderInfo.inpar2,GA_Disabled,TRUE,TAG_DONE);
						}
						else
						{
							RenderInfo.inpar2=InsideDefs[RenderInfo.inside][1];
							GT_SetGadgetAttrs(omGadgets[33],opwin,0l,GTIN_Number,RenderInfo.inpar2,GA_Disabled,FALSE,TAG_DONE);
						}
						if(RenderInfo.inside==IDecomp)
						{
							RenderInfo.mirrorx=0;RenderInfo.mirrory=0;
							GT_SetGadgetAttrs(omGadgets[28],opwin,0l,GTCY_Active,0,TAG_DONE);
						}
						break;
					case 32:				/* InsidePar1 */
						RenderInfo.inpar1=CheckGad_int(omGadgets[32],opwin,0,0,0);
						break;
					case 33:				/* InsidePar2 */
						RenderInfo.inpar2=CheckGad_int(omGadgets[33],opwin,0,0,0);
						break;
					case 34:				/* OutsideMode */
						RenderInfo.outside=outsidelist[icode].nr;
						if(OutsideDefs[RenderInfo.outside][0]==-1)
						{
							RenderInfo.outpar1=0;
							GT_SetGadgetAttrs(omGadgets[35],opwin,0l,GTIN_Number,RenderInfo.outpar1,GA_Disabled,TRUE,TAG_DONE);
						}
						else
						{
							RenderInfo.outpar1=OutsideDefs[RenderInfo.outside][0];
							GT_SetGadgetAttrs(omGadgets[35],opwin,0l,GTIN_Number,RenderInfo.outpar1,GA_Disabled,FALSE,TAG_DONE);
						}
						if(OutsideDefs[RenderInfo.outside][1]==-1)
						{
							RenderInfo.outpar2=0;
							GT_SetGadgetAttrs(omGadgets[36],opwin,0l,GTIN_Number,RenderInfo.outpar2,GA_Disabled,TRUE,TAG_DONE);
						}
						else
						{
							RenderInfo.outpar2=OutsideDefs[RenderInfo.outside][1];
							GT_SetGadgetAttrs(omGadgets[36],opwin,0l,GTIN_Number,RenderInfo.outpar2,GA_Disabled,FALSE,TAG_DONE);
						}
						if(RenderInfo.outside==ODecomp)
						{
							RenderInfo.mirrorx=0;RenderInfo.mirrory=0;
							GT_SetGadgetAttrs(omGadgets[28],opwin,0l,GTCY_Active,0,TAG_DONE);
						}
						break;
					case 35:				/* OusidePar1 */
						RenderInfo.outpar1=CheckGad_int(omGadgets[35],opwin,0,0,0);
						break;
					case 36:				/* OusidePar2 */
						RenderInfo.outpar2=CheckGad_int(omGadgets[36],opwin,0,0,0);
						break;
/* Orbit Options */
					case 37:				/* ObStep */
						RenderInfo.obstep=CheckGad_int(omGadgets[37],opwin,0,0,0);
						break;
					case 38:				/* ObConnect */
						RenderInfo.obconnect=(omGadgets[38]->Flags&GFLG_SELECTED);
						break;
					case 39:				/* ObSize */
						RenderInfo.obsize=icode;
						break;
				}
				break;
			case IDCMP_RAWKEY:
				switch(icode)
				{
					case 0x5F:
						Help("fu.guide","Project_Options");
						break;
				}
				break;
			case IDCMP_CLOSEWINDOW:
				quit=1;break;
		}
	}
	ChooseColorFunc();
	SetPaletteMode();
	SetColorPalette();
//	MakeColorPalettes();SetColorPalette();
	if(quit)
	{
		RunTime.sig_in&=(~(1L<<opwin->UserPort->mp_SigBit));
		if(opwin) CloseWindow(opwin);
		if(omGList) FreeGadgets(omGList);
		opwin=0l;
		omGList=0l;
	}
}

void Refresh_OPWin(void)
{
	register UBYTE i;
	UWORD sl,tx;
	char buf[30];

	sprintf(buf,"%20.15lf",RenderInfo.par1.r);FilterString(buf);
	if(!(RenderInfo.parendi&  1)) GT_SetGadgetAttrs(omGadgets[11],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[11],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.par1.i);FilterString(buf);
	if(!(RenderInfo.parendi&  2)) GT_SetGadgetAttrs(omGadgets[15],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[15],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.par2.r);FilterString(buf);
	if(!(RenderInfo.parendi&  4)) GT_SetGadgetAttrs(omGadgets[12],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[12],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.par2.i);FilterString(buf);
	if(!(RenderInfo.parendi&  8)) GT_SetGadgetAttrs(omGadgets[16],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[16],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.par3.r);FilterString(buf);
	if(!(RenderInfo.parendi& 16)) GT_SetGadgetAttrs(omGadgets[13],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[13],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.par3.i);FilterString(buf);
	if(!(RenderInfo.parendi& 32)) GT_SetGadgetAttrs(omGadgets[17],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[17],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.par4.r);FilterString(buf);
	if(!(RenderInfo.parendi& 64)) GT_SetGadgetAttrs(omGadgets[14],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[14],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);
	sprintf(buf,"%20.15lf",RenderInfo.par4.i);FilterString(buf);
	if(!(RenderInfo.parendi&128)) GT_SetGadgetAttrs(omGadgets[18],opwin,0l,GTST_String,buf,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[18],opwin,0l,GTST_String,buf,GA_Disabled,FALSE,TAG_DONE);

	if(!(RenderInfo.pickendi&1) || !RunTime.picavail) GT_SetGadgetAttrs(omGadgets[19],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[19],opwin,0l,GA_Disabled,FALSE,TAG_DONE);
	if(!(RenderInfo.pickendi&2) || !RunTime.picavail) GT_SetGadgetAttrs(omGadgets[20],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[20],opwin,0l,GA_Disabled,FALSE,TAG_DONE);
	if(!(RenderInfo.pickendi&4) || !RunTime.picavail) GT_SetGadgetAttrs(omGadgets[21],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[21],opwin,0l,GA_Disabled,FALSE,TAG_DONE);
	if(!(RenderInfo.pickendi&8) || !RunTime.picavail) GT_SetGadgetAttrs(omGadgets[22],opwin,0l,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[22],opwin,0l,GA_Disabled,FALSE,TAG_DONE);

	if(!(RenderInfo.trigendi&1)) GT_SetGadgetAttrs(omGadgets[23],opwin,0l,GTCY_Active,RenderInfo.tpar1,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[23],opwin,0l,GTCY_Active,RenderInfo.tpar1,GA_Disabled,FALSE,TAG_DONE);
	if(!(RenderInfo.trigendi&2)) GT_SetGadgetAttrs(omGadgets[24],opwin,0l,GTCY_Active,RenderInfo.tpar2,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[24],opwin,0l,GTCY_Active,RenderInfo.tpar2,GA_Disabled,FALSE,TAG_DONE);
	if(!(RenderInfo.trigendi&4)) GT_SetGadgetAttrs(omGadgets[25],opwin,0l,GTCY_Active,RenderInfo.tpar3,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[25],opwin,0l,GTCY_Active,RenderInfo.tpar3,GA_Disabled,FALSE,TAG_DONE);
	if(!(RenderInfo.trigendi&8)) GT_SetGadgetAttrs(omGadgets[26],opwin,0l,GTCY_Active,RenderInfo.tpar4,GA_Disabled,TRUE,TAG_DONE);
	else GT_SetGadgetAttrs(omGadgets[26],opwin,0l,GTCY_Active,RenderInfo.tpar4,GA_Disabled,FALSE,TAG_DONE);

	sprintf(buf,"%20.15lf",RenderInfo.bailout);FilterString(buf);
	GT_SetGadgetAttrs(omGadgets[29],opwin,0l,GTST_String,buf,TAG_DONE);
	GT_SetGadgetAttrs(omGadgets[27],opwin,0l,GTIN_Number,RenderInfo.z,TAG_DONE);

	SetAPen(&omrp,0);RectFill(&omrp,RunTime.scx[13],RunTime.scy[148],RunTime.scx[332],RunTime.scy[182]);
	SetFont(&omrp,scrfont);SetAPen(&omrp,1);
	sl=strlen(fd[0]);tx=RunTime.scx[165]-(TextLength(&omrp,fd[0],sl)/2);
	Move(&omrp,RunTime.scx[11]+tx,RunTime.scy[155]);Text(&omrp,fd[0],sl);
	for(i=1;i<5;i++) { Move(&omrp,RunTime.scx[21],RunTime.scy[159+i*6]);Text(&omrp,fd[i],strlen(fd[i])); }
}

void Open_FOWin(void)
{
	struct NewGadget ng;
	struct Gadget *g;
	struct RastPort fmrp;

	if(g=CreateContext(&fmGList))
	{
		ng.ng_LeftEdge		=RunTime.scx[20];
		ng.ng_TopEdge		=RunTime.scy[30];
		ng.ng_Width			=RunTime.scx[140];
		ng.ng_Height		=RunTime.scy[100];
		ng.ng_GadgetText	="Group";
		ng.ng_TextAttr		=&ScrFont;
		ng.ng_GadgetID		=0;
		ng.ng_Flags			=PLACETEXT_ABOVE;
		ng.ng_VisualInfo	=VisualInfo;
		g=CreateGadget(LISTVIEW_KIND,g,&ng,GTLV_Labels,&FormulaGadgetList,GTLV_Selected,RunTime.fracfunc,GTLV_ShowSelected,0l,TAG_DONE);
		fmGadgets[0]=g;

		ng.ng_LeftEdge		=RunTime.scx[170];
		ng.ng_GadgetText	="Formula";
		ng.ng_GadgetID		=1;
		g=CreateGadget(LISTVIEW_KIND,g,&ng,GTLV_Labels,&FormulaGadgetList,GTLV_Selected,RunTime.subfunc,GTLV_ShowSelected,0l,TAG_DONE);
		fmGadgets[1]=g;

		if(g)
		{
			smwintags[0].ti_Data=(RunTime.xres-RunTime.scx[330])>>1;
			smwintags[1].ti_Data=(RunTime.yres-RunTime.scy[143])>>1;
			smwintags[2].ti_Data=RunTime.scx[330];
			smwintags[3].ti_Data=RunTime.scy[143];
			smwintags[4].ti_Data=BUTTONIDCMP|LISTVIEWIDCMP|SLIDERIDCMP|IDCMP_VANILLAKEY|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW|IDCMP_CLOSEWINDOW;
			smwintags[6].ti_Data=(ULONG)fmGList;
			smwintags[7].ti_Data=(ULONG)"Formula";
			if(fowin=OpenWindowTagList(0l,smwintags))
			{
				GT_SetGadgetAttrs(fmGadgets[0],fowin,0l,GTLV_Labels,&FormulaGadgetList,GTLV_Selected,match_nr2ix(RunTime.fracfunc,ffanz,fflist),TAG_DONE);
				switch(RunTime.fracfunc)
				{
					case 0:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvCircleList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf0anz,sf0list),TAG_DONE);
						break;
					case 1:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormCircleList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf1anz,sf1list),TAG_DONE);
						break;
					case 2:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&FormulaList,GTLV_Selected,RunTime.subfunc,TAG_DONE);
						break;
					case 3:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvNewtonList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf3anz,sf3list),TAG_DONE);
						break;
					case 4:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormNewtonList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf4anz,sf4list),TAG_DONE);
						break;
					case 5:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvFixPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf5anz,sf5list),TAG_DONE);
						break;
					case 6:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvVarPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf6anz,sf6list),TAG_DONE);
						break;
					case 7:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormFixPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf7anz,sf7list),TAG_DONE);
						break;
					case 8:
						GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormVarPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf8anz,sf8list),TAG_DONE);
						break;
				}
				GT_RefreshWindow(fowin,0l);
				fmrp=*fowin->RPort;

				DrawBox(fmrp,RunTime.scx[10],RunTime.scy[ 15],RunTime.scx[310],RunTime.scy[121],"Formula");

				RunTime.sig_in|=(1L<<fowin->UserPort->mp_SigBit);
			}
			else Message(mess[5]);
		}
		else Message(mess[6]);
	}
	else Message(mess[7]);
}

void Test_FOWin(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	APTR iadr;
	USHORT icode;
	UBYTE quit=0,ref=0;

	while(imsg=GT_GetIMsg(fowin->UserPort))
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
					case 0:		/* group */
						RunTime.fracfunc=fflist[icode].nr;
						switch(RunTime.fracfunc)
						{
							case 0:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvCircleList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf0anz,sf0list),TAG_DONE);
								break;
							case 1:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormCircleList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf1anz,sf1list),TAG_DONE);
								break;
							case 2:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&FormulaList,GTLV_Selected,RunTime.subfunc,TAG_DONE);
								break;
							case 3:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvNewtonList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf3anz,sf3list),TAG_DONE);
								break;
							case 4:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormNewtonList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf4anz,sf4list),TAG_DONE);
								break;
							case 5:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvFixPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf5anz,sf5list),TAG_DONE);
								break;
							case 6:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvVarPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf6anz,sf6list),TAG_DONE);
								break;
							case 7:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormFixPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf7anz,sf7list),TAG_DONE);
								break;
							case 8:
								GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormVarPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf8anz,sf8list),TAG_DONE);
								break;
						}
						ChooseFracFunc(0);ref=1;
						break;
					case 1:
						switch(RunTime.fracfunc)
						{
							case 0:				/* InvCircle ... */
								RunTime.subfunc=sf0list[icode].nr;break;
							case 1:				/* NormCircle ... */
								RunTime.subfunc=sf1list[icode].nr;break;
							case 2:				/* Formula */
								RunTime.subfunc=icode;break;
							case 3:				/* InvNewton */
								RunTime.subfunc=sf3list[icode].nr;break;
							case 4:				/* NormNewton */
								RunTime.subfunc=sf4list[icode].nr;break;
							case 5:				/* InvFixPlaneC */
								RunTime.subfunc=sf5list[icode].nr;break;
							case 6:				/* InvVarPlaneC */
								RunTime.subfunc=sf6list[icode].nr;break;
							case 7:			/* NormFixPlaneC */
								RunTime.subfunc=sf7list[icode].nr;break;
							case 8:			/* NormVarPlaneC */
								RunTime.subfunc=sf8list[icode].nr;break;
						}
						ChooseFracFunc(0);ref=1;
						break;
				}
				break;
			case IDCMP_VANILLAKEY:
				switch(icode)
				{
					case 'R':
					case 'r':
						if(RunTime.fracfunc==2)
						{
							ScanFormulas();
							GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&FormulaList,GTLV_Selected,RunTime.subfunc,TAG_DONE);
						}
						break;
				}
			case IDCMP_RAWKEY:
				switch(icode)
				{
					case 0x5F:
						Help("fu.guide","Project_Formula");
						break;
				}
				break;
			case IDCMP_CLOSEWINDOW:
				quit=1;break;
		}
	}
	if(ref)
	{
		if(opwin) Refresh_OPWin();
		if(zowin) Refresh_ZOWin();
	}
	if(quit)
	{
		RunTime.sig_in&=(~(1L<<fowin->UserPort->mp_SigBit));
		if(fowin) CloseWindow(fowin);
		if(fmGList) FreeGadgets(fmGList);
		fowin=0l;
		fmGList=0l;
	}
}

void Refresh_FOWin(void)
{
	GT_SetGadgetAttrs(fmGadgets[0],fowin,0l,GTLV_Labels,&FormulaGadgetList,GTLV_Selected,match_nr2ix(RunTime.fracfunc,ffanz,fflist),TAG_DONE);
	switch(RunTime.fracfunc)
	{
		case 0:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvCircleList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf0anz,sf0list),TAG_DONE);
			break;
		case 1:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormCircleList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf1anz,sf1list),TAG_DONE);
			break;
		case 2:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&FormulaList,GTLV_Selected,RunTime.subfunc,TAG_DONE);
			break;
		case 3:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvNewtonList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf3anz,sf3list),TAG_DONE);
			break;
		case 4:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormNewtonList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf4anz,sf4list),TAG_DONE);
			break;
		case 5:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvFixPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf5anz,sf5list),TAG_DONE);
			break;
		case 6:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&InvVarPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf6anz,sf6list),TAG_DONE);
			break;
		case 7:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormFixPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf7anz,sf7list),TAG_DONE);
			break;
		case 8:
			GT_SetGadgetAttrs(fmGadgets[1],fowin,0l,GTLV_Labels,&NormVarPlaneCList,GTLV_Selected,match_nr2ix(RunTime.subfunc,sf8anz,sf8list),TAG_DONE);
			break;
	}
}

void mm_screen(void)
{
	UWORD oxres,oyres;
	LONG xdif,ydif,xmit,ymit;
	double xsc,ysc;
	SelScr ScreenEntry;

	oxres=GfxInfo.xres;oyres=GfxInfo.yres;

	ScreenEntry.scrmdnr	=RunTime.rscreenmode;
	ScreenEntry.xres	=GfxInfo.xres;
	ScreenEntry.yres	=GfxInfo.yres;
	ScreenEntry.xdef	=GfxInfo.xdef;
	ScreenEntry.ydef	=GfxInfo.ydef;
	ScreenEntry.oscan	=GfxInfo.oscan;
	ScreenEntry.dep		=GfxInfo.depth;
	ScreenEntry.palbits	=GfxInfo.palbits;

	ScrMdReq(&ModeList,Modes,&ScreenEntry);

	GfxInfo.xres		=ScreenEntry.xres;
	GfxInfo.yres		=ScreenEntry.yres;
	GfxInfo.xdef		=ScreenEntry.xdef;
	GfxInfo.ydef		=ScreenEntry.ydef;
	GfxInfo.oscan		=ScreenEntry.oscan;
	GfxInfo.depth		=ScreenEntry.dep;
	GfxInfo.maxcol		=GfxInfo.realcol=1L<<GfxInfo.depth;
	GfxInfo.absmaxcol	=GfxInfo.maxcol-1;
	GfxInfo.scrmode		=ScreenEntry.scrmode;
	GfxInfo.aspect		=(float)(GfxInfo.xres)/(float)(GfxInfo.yres);
	GfxInfo.palbits		=ScreenEntry.palbits;
	RunTime.rscreenmode	=ScreenEntry.scrmdnr;
	ChangeScreen();
	SetPaletteMode();
	if(RenderInfo.xb1==0 && RenderInfo.yb1==0 && RenderInfo.xb2==oxres-1 && RenderInfo.yb2==oyres-1)
	{
		RenderInfo.xb2=GfxInfo.xres-1;RenderInfo.yb2=GfxInfo.yres-1;
	}
	else
	{
		xsc=2.0*((double)oxres/(double)GfxInfo.xres);
		ysc=2.0*((double)oyres/(double)GfxInfo.yres);
		xmit=(GfxInfo.xres-1)/2.0;
		ymit=(GfxInfo.yres-1)/2.0;
		xdif=(double)(RenderInfo.xb2-RenderInfo.xb1)/xsc;
		ydif=(double)(RenderInfo.yb2-RenderInfo.yb1)/ysc;
		RenderInfo.xb1=xmit-xdif;RenderInfo.xb2=xmit+xdif;
		RenderInfo.yb1=ymit-ydif;RenderInfo.yb2=ymit+ydif;
		if(RenderInfo.xb1<0)	/* nach links verschieben */
		{
			RenderInfo.xb2-=RenderInfo.xb1;
			RenderInfo.xb1=0;
		}
		if(RenderInfo.yb1<0)	/* nach unten verschieben */
		{
			RenderInfo.yb2-=RenderInfo.yb1;
			RenderInfo.yb1=0;
		}
		if(RenderInfo.xb2>GfxInfo.xres-1)	/* nach rechts verschieben */
		{
			RenderInfo.xb1-=(GfxInfo.xres-RenderInfo.xb2);
			RenderInfo.xb2=GfxInfo.xres-1;
		}
		if(RenderInfo.yb2>GfxInfo.yres-1)	/* nach oben verschieben */
		{
			RenderInfo.yb1-=(GfxInfo.yres-RenderInfo.yb2);
			RenderInfo.yb2=GfxInfo.yres-1;
		}
	}
}

void LoadPalette(char *fn)
{
	FILE *col;
	char header[10];

	if((col=fopen(fn,"rb"))!=NULL)
	{
		fread(header,9,1,col);header[9]=0;
		if(strcmp(header,"FU-COLORS")==0)
		{
			fread(&PalInfo.r[RunTime.aktpal],sizeof(PalInfo.r[RunTime.aktpal]),1,col);
			fread(&PalInfo.g[RunTime.aktpal],sizeof(PalInfo.g[RunTime.aktpal]),1,col);
			fread(&PalInfo.b[RunTime.aktpal],sizeof(PalInfo.b[RunTime.aktpal]),1,col);
			GetPalShape(PalInfo.r[RunTime.aktpal].pst,rps[RunTime.aktpal]);
			GetPalShape(PalInfo.g[RunTime.aktpal].pst,gps[RunTime.aktpal]);
			GetPalShape(PalInfo.b[RunTime.aktpal].pst,bps[RunTime.aktpal]);
			MakeColorPalettes();SetColorPalette();
		}
		else Message(mess[8]);
		fclose(col);
	}
	else Message(mess[0]);
}

void SavePalette(char *fn)
{
	FILE *col;

	if((col=fopen(fn,"rb"))!=NULL)
	{
		fclose(col);
		if(Question(ques[0]))
		{
			if((col=fopen(fn,"wb"))!=NULL)
			{
				fwrite(&"FU-COLORS",9,1,col);
				fwrite(&PalInfo.r[RunTime.aktpal],sizeof(PalInfo.r[RunTime.aktpal]),1,col);
				fwrite(&PalInfo.g[RunTime.aktpal],sizeof(PalInfo.g[RunTime.aktpal]),1,col);
				fwrite(&PalInfo.b[RunTime.aktpal],sizeof(PalInfo.b[RunTime.aktpal]),1,col);
				fclose(col);
			}
			else Message(mess[0]);
		}
	}
	else
	{
		if((col=fopen(fn,"wb"))!=NULL)
		{
			fwrite(&"FU-COLORS",9,1,col);
			fwrite(&PalInfo.r[RunTime.aktpal],sizeof(PalInfo.r[RunTime.aktpal]),1,col);
			fwrite(&PalInfo.g[RunTime.aktpal],sizeof(PalInfo.g[RunTime.aktpal]),1,col);
			fwrite(&PalInfo.b[RunTime.aktpal],sizeof(PalInfo.b[RunTime.aktpal]),1,col);
			fclose(col);
		}
		else Message(mess[0]);
	}
}

void RefreshPalShapes(struct RastPort rp,struct Gadget *Gadgets[])
{
	DrawPalShape(rp,0,rps[RunTime.aktpal]);
	DrawPalShape(rp,1,gps[RunTime.aktpal]);
	DrawPalShape(rp,2,bps[RunTime.aktpal]);
	GT_SetGadgetAttrs(Gadgets[10],cowin,0l,GTCY_Active,PalInfo.r[RunTime.aktpal].pst,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[13],cowin,0l,GTCY_Active,PalInfo.g[RunTime.aktpal].pst,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[16],cowin,0l,GTCY_Active,PalInfo.b[RunTime.aktpal].pst,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[ 9],cowin,0l,GTIN_Number,PalInfo.r[RunTime.aktpal].scx,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[11],cowin,0l,GTIN_Number,PalInfo.r[RunTime.aktpal].scy,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[12],cowin,0l,GTIN_Number,PalInfo.g[RunTime.aktpal].scx,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[14],cowin,0l,GTIN_Number,PalInfo.g[RunTime.aktpal].scy,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[15],cowin,0l,GTIN_Number,PalInfo.b[RunTime.aktpal].scx,TAG_DONE);
	GT_SetGadgetAttrs(Gadgets[17],cowin,0l,GTIN_Number,PalInfo.b[RunTime.aktpal].scy,TAG_DONE);
}
