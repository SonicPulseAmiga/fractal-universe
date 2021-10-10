/****h* FractalUniverse/FU-IORx.c [1.68] *
*
*  NAME
*    FU-IORx.c
*  COPYRIGHT
*    $VER: FU-IORx.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    ARexx event handling
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

#define FU_IORX_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void DoIO_Rexx(void);

//-- definitions --------------------------------------------------------------

void DoIO_Rexx(void)
{
	struct RexxMsg		*rmsg;
	char rxstr[MaxCmdLen],params[MaxParLen*MaxParAnz];
	UBYTE cf,nr;
	ULONG sl;
	register int i;
	LONG temp;
	UBYTE off;

	while(rmsg=(struct RexxMsg *)GetMsg(arexxport))
	{
		sl=strlen(rmsg->rm_Args[0]);
		if(sl>0 && sl<MaxCmdLen)
		{
			strcpy(rxstr,rmsg->rm_Args[0]);
			GetRexxStr(rxstr,params);
			rmsg->rm_Result1=rmsg->rm_Result2=0;
			cf=0;
/* Simple Functions */
			if(!cf && !stricmp(&params[0],"ExitFU"))
			{
				cf=1;RunTime.quitfu=1;
			}
			if(!cf && !stricmp(&params[0],"ActivateFU"))
			{
				cf=1;ScreenToFront(mmscr);
			}
/* Set-Functions */
			if(!cf && !stricmp(&params[0],"SetZoom"))
			{
				cf=1;
				if(params[MaxParLen<<2]!=0)
				{
					RenderInfo.x1=atof(&params[MaxParLen]);
					RenderInfo.y1=atof(&params[2*MaxParLen]);
					RenderInfo.x2=atof(&params[3*MaxParLen]);
					RenderInfo.y2=atof(&params[4*MaxParLen]);
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"SetParam"))
			{
				cf=1;
				if(params[MaxParLen*3]!=0)
				{
					nr=atoi(&params[MaxParLen]);
					switch(nr)
					{
						case 1:
							RenderInfo.par1.r=atof(&params[2*MaxParLen]);
							RenderInfo.par1.i=atof(&params[3*MaxParLen]);
							break;
						case 2:
							RenderInfo.par2.r=atof(&params[2*MaxParLen]);
							RenderInfo.par2.i=atof(&params[3*MaxParLen]);
							break;
						case 3:
							RenderInfo.par3.r=atof(&params[2*MaxParLen]);
							RenderInfo.par3.i=atof(&params[3*MaxParLen]);
							break;
						case 4:
							RenderInfo.par4.r=atof(&params[2*MaxParLen]);
							RenderInfo.par4.i=atof(&params[3*MaxParLen]);
							break;
					}
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"SetFn"))
			{
				cf=1;
				if(params[MaxParLen<<1]!=0)
				{
					nr=atoi(&params[MaxParLen]);
					switch(nr)
					{
						case 1:
							RenderInfo.tpar1=atoi(&params[2*MaxParLen]);
							break;
						case 2:
							RenderInfo.tpar2=atoi(&params[2*MaxParLen]);
							break;
						case 3:
							RenderInfo.tpar3=atoi(&params[2*MaxParLen]);
							break;
						case 4:
							RenderInfo.tpar4=atoi(&params[2*MaxParLen]);
							break;
					}
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"SetIter"))
			{
				cf=1;
				if(params[MaxParLen]!=0)
				{
					RenderInfo.z=atoi(&params[MaxParLen]);
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"SetBailout"))
			{
				cf=1;
				if(params[MaxParLen]!=0)
				{
					RenderInfo.bailout=atof(&params[MaxParLen]);
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"SetInside"))
			{
				cf=1;
				if(params[MaxParLen*3]!=0)
				{
					nr=0;
					for(i=0;i<isanz;i++) if(!strcmp(&params[MaxParLen],insidelist[i].name)) { RenderInfo.inside=i;i=isanz;nr=1; }
					if(nr)
					{
						temp=atoi(&params[2*MaxParLen]);
						if(temp>-1) RenderInfo.inpar1=temp;
						else RenderInfo.inpar1=0;
						temp=atoi(&params[3*MaxParLen]);
						if(temp>-1) RenderInfo.inpar2=temp;
						else RenderInfo.inpar2=0;
						ChooseColorFunc();
					}
					else rmsg->rm_Result1=2;
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"SetOutside"))
			{
				cf=1;
				if(params[MaxParLen*3]!=0)
				{
					nr=0;
					for(i=0;i<osanz;i++) if(!strcmp(&params[MaxParLen],outsidelist[i].name)) { RenderInfo.outside=i;i=osanz;nr=1; }
					if(nr)
					{
						temp=atoi(&params[2*MaxParLen]);
						if(temp>-1) RenderInfo.outpar1=temp;
						else RenderInfo.outpar1=0;
						temp=atoi(&params[3*MaxParLen]);
						if(temp>-1) RenderInfo.outpar2=temp;
						else RenderInfo.outpar2=0;
						ChooseColorFunc();
					}
					else rmsg->rm_Result1=2;
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"SetFormula"))
			{
				cf=1;
				if(params[MaxParLen*2]!=0)
				{
					off=RunTime.fracfunc;
					nr=0;
					for(i=0;i<ffanz;i++) if(!strcmp(&params[MaxParLen],fflist[i].name)) { RunTime.fracfunc=fflist[i].nr;i=ffanz;nr=1; }
					if(nr)
					{
						nr=0;
						switch(RunTime.fracfunc)
						{
							case 0:
								for(i=0;i<sf0anz;i++) if(!strcmp(&params[MaxParLen<<1],sf0list[i].name)) { RunTime.subfunc=sf0list[i].nr;i=sf0anz;nr=1; }
								break;
							case 1:
								for(i=0;i<sf1anz;i++) if(!strcmp(&params[MaxParLen<<1],sf1list[i].name)) { RunTime.subfunc=sf1list[i].nr;i=sf1anz;nr=1; }
								break;
							case 2:
								for(i=0;i<sf2anz;i++) if(!strcmp(&params[MaxParLen<<1],Formulas[i])) { RunTime.subfunc=i;i=sf2anz;nr=1; }
								break;
							case 3:
								for(i=0;i<sf3anz;i++) if(!strcmp(&params[MaxParLen<<1],sf3list[i].name)) { RunTime.subfunc=sf3list[i].nr;i=sf3anz;nr=1; }
								break;
							case 4:
								for(i=0;i<sf4anz;i++) if(!strcmp(&params[MaxParLen<<1],sf4list[i].name)) { RunTime.subfunc=sf4list[i].nr;i=sf4anz;nr=1; }
								break;
							case 5:
								for(i=0;i<sf5anz;i++) if(!strcmp(&params[MaxParLen<<1],sf5list[i].name)) { RunTime.subfunc=sf5list[i].nr;i=sf5anz;nr=1; }
								break;
							case 6:
								for(i=0;i<sf6anz;i++) if(!strcmp(&params[MaxParLen<<1],sf6list[i].name)) { RunTime.subfunc=sf6list[i].nr;i=sf6anz;nr=1; }
								break;
							case 7:
								for(i=0;i<sf7anz;i++) if(!strcmp(&params[MaxParLen<<1],sf7list[i].name)) { RunTime.subfunc=sf7list[i].nr;i=sf7anz;nr=1; }
								break;
							case 8:
								for(i=0;i<sf8anz;i++) if(!strcmp(&params[MaxParLen<<1],sf8list[i].name)) { RunTime.subfunc=sf8list[i].nr;i=sf8anz;nr=1; }
								break;
						}
						if(nr) ChooseFracFunc(0);
						else {
							MSG1("unknown formula : [%s]",&params[MaxParLen<<1]);
							RunTime.fracfunc=off;rmsg->rm_Result1=2;
						}
					}
					else {
						MSG1("unknown formula group : [%s]",&params[MaxParLen]);
						rmsg->rm_Result1=2;
					}
				}
				else rmsg->rm_Result1=2;
			}
/* Action-Commands */
			if(!cf && !stricmp(&params[0],"SavePicture"))
			{
				cf=1;
				if(params[MaxParLen<<1]!=0)
				{
					SaveImage(&params[MaxParLen],atoi(&params[2*MaxParLen]));
				}
				else rmsg->rm_Result1=2;
			}
			if(!cf && !stricmp(&params[0],"RenderPicture"))
			{
				cf=1;RunTime.rexxactive=1;mm_render();RunTime.rexxactive=0;
			}
			if(!cf) rmsg->rm_Result1=1;
		}
		else rmsg->rm_Result1=1;
		ReplyMsg(rmsg);
	}
}
