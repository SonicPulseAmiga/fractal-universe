/****h* FractalUniverse/FU-Inter.c [1.68] *
*
*  NAME
*    FU-Inter.c
*  COPYRIGHT
*    $VER: FU-Inter.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    Formula Interpreter
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

#define FU_INTER_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

int interpret(void);

int ReadLine(char *buf);
void ConvertLine(char *buf);
void SplitEqu(char *buf,char *svar,char *salgo);
int GetVarIX(char *svar1);

//-- globals ------------------------------------------------------------------

FILE *frm;
UBYTE fn1bi[20],fn1pi;
UBYTE fn2bi[20],fn2pi;
UBYTE fn3bi[20],fn3pi;
UBYTE fn4bi[20],fn4pi;
UBYTE fn1bs[20],fn1ps;
UBYTE fn2bs[20],fn2ps;
UBYTE fn3bs[20],fn3ps;
UBYTE fn4bs[20],fn4ps;
int fline;						/* current line */

//-- definitions --------------------------------------------------------------

int interpret(void)
{
	char line[81],hv1[20],hv2[20];
	int quit,ix;
	char svar[10],svar1[10],svar2[10],sop,salgo[70];
	register int i,j;
	char fn[50],fname[20];
	char mess[100];
	UBYTE fufo;

	fline=0;
	fn1pi=fn2pi=fn3pi=fn4pi=fn1ps=fn2ps=fn3ps=fn4ps=0;
	luv=lhv=lmopi=lmops=0;
	strcpy(uv[0].vname,"PIXEL");
	strcpy(uv[1].vname,"PAR1");
	strcpy(uv[2].vname,"PAR2");
	strcpy(uv[3].vname,"PAR3");
	strcpy(uv[4].vname,"PAR4");
	strcpy(uv[5].vname,"BAILOUT");
	luv=6;

	strcpy(fname,Formulas[RunTime.subfunc]);
	sprintf(fn,"formulas/%s.form",Formulas[RunTime.subfunc]);
	if((frm=fopen(fn,"rt"))!=NULL)
	{
		quit=0;						/* Searching Formulaname */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(!stricmp(line,fname)) quit=1;
				else quit=3;
			}
		}
		switch(quit)
		{
			case 2:
				sprintf(mess,"Formula : ERROR in pass 1 line %3d !\nEOF reached !",fline);Message(mess);
				fclose(frm);return(-1);
				break;
			case 3:
				sprintf(mess,"Formula : ERROR in pass 1 line %3d !\n'%s'!='%s' !",fline,line,fname);Message(mess);
				fclose(frm);return(-1);
				break;
		}

		quit=0;						/* Searching 1. { */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='{') quit=1;
			}
		}
		if(quit==2)
		{
			sprintf(mess,"Formula : ERROR in pass 2 line %3d !\nMainblock not opened !",fline);Message(mess);
			fclose(frm);return(-1);
		}

		quit=0;						/* Searching 2. { */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='{') quit=1;
			}
		}
		if(quit==2)
		{
			sprintf(mess,"Formula : ERROR in pass 3 line %3d !\nBlock 1 not opened !",fline);Message(mess);
			fclose(frm);return(-1);
		}

		quit=0;						/* Default settings */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='}') quit=1;
				else
				{
					fufo=0;
					if(!strncmp(line,"MIRRORX",7)) { FractalInfo.mirrorx=1;fufo=1; }
					if(!strncmp(line,"MIRRORY",7)) { FractalInfo.mirrory=1;fufo=1; }
					if(!strncmp(line,"MIRRORXY",8) || !strncmp(line,"MIRRORYX",8)) { FractalInfo.mirrorx=FractalInfo.mirrory=1;fufo=1; }
					if(!strncmp(line,"PICKENDI=",9)) { FractalInfo.pickendi=(UBYTE)(atoi(line+9));fufo=1; }
					if(!strncmp(line,"X1=",3)) { FractalInfo.x1=atof(line+3);fufo=1; }
					if(!strncmp(line,"X2=",3)) { FractalInfo.x2=atof(line+3);fufo=1; }
					if(!strncmp(line,"Y1=",3)) { FractalInfo.y1=atof(line+3);fufo=1; }
					if(!strncmp(line,"Y2=",3)) { FractalInfo.y2=atof(line+3);fufo=1; }
					if(!strncmp(line,"PAR1.R=",7)) { uv[1].z.r=FractalInfo.par1.r=atof(line+7);FractalInfo.parendi|=  1;fufo=1; }
					if(!strncmp(line,"PAR1.I=",7)) { uv[1].z.i=FractalInfo.par1.i=atof(line+7);FractalInfo.parendi|=  2;fufo=1; }
					if(!strncmp(line,"PAR2.R=",7)) { uv[2].z.r=FractalInfo.par2.r=atof(line+7);FractalInfo.parendi|=  4;fufo=1; }
					if(!strncmp(line,"PAR2.I=",7)) { uv[2].z.i=FractalInfo.par2.i=atof(line+7);FractalInfo.parendi|=  8;fufo=1; }
					if(!strncmp(line,"PAR3.R=",7)) { uv[3].z.r=FractalInfo.par3.r=atof(line+7);FractalInfo.parendi|= 16;fufo=1; }
					if(!strncmp(line,"PAR3.I=",7)) { uv[3].z.i=FractalInfo.par3.i=atof(line+7);FractalInfo.parendi|= 32;fufo=1; }
					if(!strncmp(line,"PAR4.R=",7)) { uv[4].z.r=FractalInfo.par4.r=atof(line+7);FractalInfo.parendi|= 64;fufo=1; }
					if(!strncmp(line,"PAR4.I=",7)) { uv[4].z.i=FractalInfo.par4.i=atof(line+7);FractalInfo.parendi|=128;fufo=1; }
					if(!strncmp(line,"BAILOUT=",8)) { uv[5].z.r=FractalInfo.bailout=atof(line+8);fufo=1; }
					if(!strncmp(line,"FN1=",4))
					{
						FractalInfo.trigendi|=1;fufo=1;
						if(!strcmp(line+4, "0") || !strcmp(line+4,"SIN" )) FractalInfo.tpar1= 0;
						if(!strcmp(line+4, "1") || !strcmp(line+4,"COS" )) FractalInfo.tpar1= 1;
						if(!strcmp(line+4, "2") || !strcmp(line+4,"TAN" )) FractalInfo.tpar1= 2;
						if(!strcmp(line+4, "3") || !strcmp(line+4,"SINH")) FractalInfo.tpar1= 3;
						if(!strcmp(line+4, "4") || !strcmp(line+4,"COSH")) FractalInfo.tpar1= 4;
						if(!strcmp(line+4, "5") || !strcmp(line+4,"TANH")) FractalInfo.tpar1= 5;
						if(!strcmp(line+4, "6") || !strcmp(line+4,"LOG" )) FractalInfo.tpar1= 6;
						if(!strcmp(line+4, "7") || !strcmp(line+4,"EXP" )) FractalInfo.tpar1= 7;
						if(!strcmp(line+4, "8") || !strcmp(line+4,"ABS" )) FractalInfo.tpar1= 8;
						if(!strcmp(line+4, "9") || !strcmp(line+4,"IMAG")) FractalInfo.tpar1= 9;
						if(!strcmp(line+4,"10") || !strcmp(line+4,"REAL")) FractalInfo.tpar1=10;
						if(!strcmp(line+4,"11") || !strcmp(line+4,"SWAP")) FractalInfo.tpar1=11;
						if(!strcmp(line+4,"12") || !strcmp(line+4,"INV" )) FractalInfo.tpar1=12;
					}
					if(!strncmp(line,"FN2=",4))
					{
						FractalInfo.trigendi|=2;fufo=1;
						if(!strcmp(line+4, "0") || !strcmp(line+4,"SIN" )) FractalInfo.tpar2= 0;
						if(!strcmp(line+4, "1") || !strcmp(line+4,"COS" )) FractalInfo.tpar2= 1;
						if(!strcmp(line+4, "2") || !strcmp(line+4,"TAN" )) FractalInfo.tpar2= 2;
						if(!strcmp(line+4, "3") || !strcmp(line+4,"SINH")) FractalInfo.tpar2= 3;
						if(!strcmp(line+4, "4") || !strcmp(line+4,"COSH")) FractalInfo.tpar2= 4;
						if(!strcmp(line+4, "5") || !strcmp(line+4,"TANH")) FractalInfo.tpar2= 5;
						if(!strcmp(line+4, "6") || !strcmp(line+4,"LOG" )) FractalInfo.tpar2= 6;
						if(!strcmp(line+4, "7") || !strcmp(line+4,"EXP" )) FractalInfo.tpar2= 7;
						if(!strcmp(line+4, "8") || !strcmp(line+4,"ABS" )) FractalInfo.tpar2= 8;
						if(!strcmp(line+4, "9") || !strcmp(line+4,"IMAG")) FractalInfo.tpar2= 9;
						if(!strcmp(line+4,"10") || !strcmp(line+4,"REAL")) FractalInfo.tpar2=10;
						if(!strcmp(line+4,"11") || !strcmp(line+4,"SWAP")) FractalInfo.tpar2=11;
						if(!strcmp(line+4,"12") || !strcmp(line+4,"INV" )) FractalInfo.tpar2=12;
					}
					if(!strncmp(line,"FN3=",4))
					{
						FractalInfo.trigendi|=4;fufo=1;
						if(!strcmp(line+4, "0") || !strcmp(line+4,"SIN" )) FractalInfo.tpar3= 0;
						if(!strcmp(line+4, "1") || !strcmp(line+4,"COS" )) FractalInfo.tpar3= 1;
						if(!strcmp(line+4, "2") || !strcmp(line+4,"TAN" )) FractalInfo.tpar3= 2;
						if(!strcmp(line+4, "3") || !strcmp(line+4,"SINH")) FractalInfo.tpar3= 3;
						if(!strcmp(line+4, "4") || !strcmp(line+4,"COSH")) FractalInfo.tpar3= 4;
						if(!strcmp(line+4, "5") || !strcmp(line+4,"TANH")) FractalInfo.tpar3= 5;
						if(!strcmp(line+4, "6") || !strcmp(line+4,"LOG" )) FractalInfo.tpar3= 6;
						if(!strcmp(line+4, "7") || !strcmp(line+4,"EXP" )) FractalInfo.tpar3= 7;
						if(!strcmp(line+4, "8") || !strcmp(line+4,"ABS" )) FractalInfo.tpar3= 8;
						if(!strcmp(line+4, "9") || !strcmp(line+4,"IMAG")) FractalInfo.tpar3= 9;
						if(!strcmp(line+4,"10") || !strcmp(line+4,"REAL")) FractalInfo.tpar3=10;
						if(!strcmp(line+4,"11") || !strcmp(line+4,"SWAP")) FractalInfo.tpar3=11;
						if(!strcmp(line+4,"12") || !strcmp(line+4,"INV" )) FractalInfo.tpar3=12;
					}
					if(!strncmp(line,"FN4=",4))
					{
						FractalInfo.trigendi|=8;fufo=1;
						if(!strcmp(line+4, "0") || !strcmp(line+4,"SIN" )) FractalInfo.tpar4= 0;
						if(!strcmp(line+4, "1") || !strcmp(line+4,"COS" )) FractalInfo.tpar4= 1;
						if(!strcmp(line+4, "2") || !strcmp(line+4,"TAN" )) FractalInfo.tpar4= 2;
						if(!strcmp(line+4, "3") || !strcmp(line+4,"SINH")) FractalInfo.tpar4= 3;
						if(!strcmp(line+4, "4") || !strcmp(line+4,"COSH")) FractalInfo.tpar4= 4;
						if(!strcmp(line+4, "5") || !strcmp(line+4,"TANH")) FractalInfo.tpar4= 5;
						if(!strcmp(line+4, "6") || !strcmp(line+4,"LOG" )) FractalInfo.tpar4= 6;
						if(!strcmp(line+4, "7") || !strcmp(line+4,"EXP" )) FractalInfo.tpar4= 7;
						if(!strcmp(line+4, "8") || !strcmp(line+4,"ABS" )) FractalInfo.tpar4= 8;
						if(!strcmp(line+4, "9") || !strcmp(line+4,"IMAG")) FractalInfo.tpar4= 9;
						if(!strcmp(line+4,"10") || !strcmp(line+4,"REAL")) FractalInfo.tpar4=10;
						if(!strcmp(line+4,"11") || !strcmp(line+4,"SWAP")) FractalInfo.tpar4=11;
						if(!strcmp(line+4,"12") || !strcmp(line+4,"INV" )) FractalInfo.tpar4=12;
					}
					if(!fufo) quit=3;
				}
			}
		}
		switch(quit)
		{
			case 2:
				sprintf(mess,"Formula : ERROR in pass 4 line %3d !\nBlock 1 not closed !",fline);Message(mess);
				fclose(frm);return(-1);
				break;
			case 3:
				sprintf(mess,"Formula : ERROR in pass 4 line %3d !\nLine %s contains an illegal Token !",fline,line);Message(mess);
				fclose(frm);return(-1);
				break;
		}

		quit=0;						/* Searching 2. { */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='{') quit=1;
			}
		}
		if(quit==2)
		{
			sprintf(mess,"Formula : ERROR in pass 5 line %3d !\nBlock 2 not opened !",fline);Message(mess);
			fclose(frm);return(-1);
		}

		quit=0;						/* Initblock for every call */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='}') quit=1;
				else
				{
					SplitEqu(line,svar,salgo);
					if(GetVarIX(svar)==-1)				/* wenn Ziel nicht existiert, neues bilden */
					{
						strcpy(uv[luv].vname,svar);luv++;
					}
					if(strchr(salgo,'[') && strchr(salgo,']'))
					{
						i=0;
						while(salgo[i]!='[') i++;		/* Searching 1. [ */
						i++;j=0;
						while(salgo[i]!=',')			/* Getting 1. value */
						{
							hv1[j]=salgo[i];i++;j++;
						}
						hv1[j]=0;i++;j=0;
						while(salgo[i]!=']')			/* Getting 2. value */
						{
							hv2[j]=salgo[i];i++;j++;
						}
						hv2[j]=0;//i=0;
						sprintf(uv[luv].vname,"FRA%03d",lhv);	/* Neue Hilfsvar */
						uv[luv].z.r=atof(hv1);
						uv[luv].z.i=atof(hv2);
						ix=luv;
						luv++;
						lhv++;
						i=0;						/* Name einkopieren */
						while(salgo[i]!='[') i++;
						for(j=0;j<6;j++)
						{
							salgo[i]=uv[ix].vname[j];i++;
						}
						while(salgo[i]!=']')		/* Rest ranziehen */
						{
							j=i;
							while(salgo[j]!=0)
							{
								salgo[j]=salgo[j+1];j++;
							}
						}
						j=i;
						while(salgo[j]!=0)
						{
							salgo[j]=salgo[j+1];j++;
						}
					}
					if(strchr(salgo,'*') || strchr(salgo,'/') || strchr(salgo,'+') || strchr(salgo,'-')  || strchr(salgo,'^'))
					{
						i=0;
						while(salgo[i]!='*' && salgo[i]!='/' && salgo[i]!='+' && salgo[i]!='-'  && salgo[i]!='^')
						{
							svar1[i]=salgo[i];i++;
						}
						svar1[i]=0;
						sop=salgo[i];
						i++;j=0;
						while(salgo[i]!=0)
						{
							svar2[j]=salgo[i];i++;j++;
						}
						svar2[j]=0;
						switch(sop)
						{
							case '*': mabus[lmops].MathFunc=cplx_mul;break;
							case '/': mabus[lmops].MathFunc=cplx_div;break;
							case '+': mabus[lmops].MathFunc=cplx_add;break;
							case '-': mabus[lmops].MathFunc=cplx_sub;break;
							case '^': mabus[lmops].MathFunc=cplx_pow;break;
						}
						if((ix=GetVarIX(svar1))==-1) quit=4;
						mabus[lmops].p1=&uv[ix].z;
						if((ix=GetVarIX(svar2))==-1) quit=5;
						mabus[lmops].p2=&uv[ix].z;
						ix=GetVarIX(svar);
						mabus[lmops].e=&uv[ix].z;
						lmops++;
					}
					else
					{
						if(strchr(salgo,'(') || strchr(salgo,')'))
						{
							fufo=0;i=0;
							while(salgo[i]!='(') i++;
							i++;j=0;
							while(salgo[i]!=')')
							{
								svar1[j]=salgo[i];i++;j++;
							}
							svar1[j]=0;
							if(!strncmp(salgo,"SIN",3))
							{
								mabus[lmops].MathFunc=cplx_sin;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"COS",3))
							{
								mabus[lmops].MathFunc=cplx_cos;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"TAN",3))
							{
								mabus[lmops].MathFunc=cplx_tan;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"SINH",4))
							{
								mabus[lmops].MathFunc=cplx_sinh;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"COSH",4))
							{
								mabus[lmops].MathFunc=cplx_cosh;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"TANH",4))
							{
								mabus[lmops].MathFunc=cplx_tanh;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"LOG",3))
							{
								mabus[lmops].MathFunc=cplx_log;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"EXP",3))
							{
								mabus[lmops].MathFunc=cplx_exp;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"ABS",3))
							{
								mabus[lmops].MathFunc=cplx_abs;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"REAL",4))
							{
								mabus[lmops].MathFunc=cplx_real;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"IMAG",4))
							{
								mabus[lmops].MathFunc=cplx_imag;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"SWAP",4))
							{
								mabus[lmops].MathFunc=cplx_swap;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"INV",3))
							{
								mabus[lmops].MathFunc=cplx_inv;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"FN1",3))
							{
								fn1bs[fn1ps]=lmops;fn1ps++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"FN2",3))
							{
								fn2bs[fn2ps]=lmops;fn2ps++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"FN3",3))
							{
								fn3bs[fn3ps]=lmops;fn3ps++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"FN4",3))
							{
								fn4bs[fn4ps]=lmops;fn4ps++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(!strncmp(salgo,"POW",3))
							{
								mabus[lmops].MathFunc=cplx_pow;
								i=0;
								while(svar1[i]!=',') i++;
								svar1[i]=0;i++;j=0;
								while(svar1[i]!=0)
								{
									svar2[j]=svar1[i];i++;j++;
								}
								svar2[j]=0;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabus[lmops].p1=&uv[ix].z;
								if((ix=GetVarIX(svar2))==-1) quit=5;
								mabus[lmops].p2=&uv[ix].z;
								ix=GetVarIX(svar);
								mabus[lmops].e=&uv[ix].z;
								lmops++;fufo=1;
							}
							if(fufo==0) quit=3;
						}
						else
						{
							mabus[lmops].MathFunc=cplx_erg;
							i=0;
							while(salgo[i]!=0)
							{
								svar1[i]=salgo[i];i++;
							}
							svar1[i]=0;
							if((ix=GetVarIX(svar1))==-1) quit=4;
							mabus[lmops].p1=&uv[ix].z;
							ix=GetVarIX(svar);
							mabus[lmops].e=&uv[ix].z;
							lmops++;
						}
					}
				}
			}
		}
		switch(quit)
		{
			case 2:
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nBlock 2 not closed !",fline);Message(mess);
				fclose(frm);return(-1);
				break;
			case 3:
				i=0;
				while(salgo[i]!='(') i++;salgo[i]=0;
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nFunction '%s' not exists !",fline,salgo);Message(mess);
				fclose(frm);return(-1);
				break;
			case 4:
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nVariable '%s' isn`t created !",fline,svar1);Message(mess);
				fclose(frm);return(-1);
				break;
			case 5:
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nVariable '%s' isn`t created !",fline,svar2);Message(mess);
				fclose(frm);return(-1);
				break;
		}

		quit=0;						/* Searching for 2. { */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='{') quit=1;
			}
		}
		if(quit==2)
		{
			sprintf(mess,"Formula : ERROR in pass 7 line %3d !\nBlock 3 not opened !",fline);Message(mess);
			fclose(frm);return(-1);
		}

		quit=0;						/* Renderblock */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='}') quit=1;
				else
				{
					SplitEqu(line,svar,salgo);
					if(GetVarIX(svar)==-1)				/* wenn Ziel nicht existiert, neues bilden */
					{
						strcpy(uv[luv].vname,svar);luv++;
					}
					if(strchr(salgo,'[') && strchr(salgo,']'))
					{
						i=0;
						while(salgo[i]!='[') i++;		/* Searching 1. [ */
						i++;j=0;
						while(salgo[i]!=',')			/* Getting 1. value */
						{
							hv1[j]=salgo[i];i++;j++;
						}
						hv1[j]=0;i++;j=0;
						while(salgo[i]!=']')			/* Getting 2. value */
						{
							hv2[j]=salgo[i];i++;j++;
						}
						hv2[j]=0;//i=0;
						sprintf(uv[luv].vname,"FRA%03d",lhv);
						uv[luv].z.r=atof(hv1);
						uv[luv].z.i=atof(hv2);
						ix=luv;
						luv++;
						lhv++;
						i=0;						/* Name einkopieren */
						while(salgo[i]!='[') i++;
						for(j=0;j<6;j++)
						{
							salgo[i]=uv[ix].vname[j];i++;
						}
						while(salgo[i]!=']')		/* Rest ranziehen */
						{
							j=i;
							while(salgo[j]!=0)
							{
								salgo[j]=salgo[j+1];j++;
							}
						}
						j=i;
						while(salgo[j]!=0)
						{
							salgo[j]=salgo[j+1];j++;
						}
					}
					if(strchr(salgo,'*') || strchr(salgo,'/') || strchr(salgo,'+') || strchr(salgo,'-') || strchr(salgo,'^'))
					{
						i=0;
						while(salgo[i]!='*' && salgo[i]!='/' && salgo[i]!='+' && salgo[i]!='-' && salgo[i]!='^')
						{
							svar1[i]=salgo[i];i++;
						}
						svar1[i]=0;
						sop=salgo[i];
						i++;j=0;
						while(salgo[i]!=0)
						{
							svar2[j]=salgo[i];i++;j++;
						}
						svar2[j]=0;
						switch(sop)
						{
							case '*': mabui[lmopi].MathFunc=cplx_mul;break;
							case '/': mabui[lmopi].MathFunc=cplx_div;break;
							case '+': mabui[lmopi].MathFunc=cplx_add;break;
							case '-': mabui[lmopi].MathFunc=cplx_sub;break;
							case '^': mabus[lmops].MathFunc=cplx_pow;break;
						}
						if((ix=GetVarIX(svar1))==-1) quit=4;
						mabui[lmopi].p1=&uv[ix].z;
						if((ix=GetVarIX(svar2))==-1) quit=5;
						mabui[lmopi].p2=&uv[ix].z;
						ix=GetVarIX(svar);
						mabui[lmopi].e=&uv[ix].z;
						lmopi++;
					}
					else
					{
						if(strchr(salgo,'(') || strchr(salgo,')'))
						{
							fufo=0;i=0;
							while(salgo[i]!='(') i++;
							i++;j=0;
							while(salgo[i]!=')')
							{
								svar1[j]=salgo[i];i++;j++;
							}
							svar1[j]=0;
							if(!strncmp(salgo,"SIN",3))
							{
								mabui[lmopi].MathFunc=cplx_sin;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"COS",3))
							{
								mabui[lmopi].MathFunc=cplx_cos;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"TAN",3))
							{
								mabui[lmopi].MathFunc=cplx_tan;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"SINH",4))
							{
								mabui[lmopi].MathFunc=cplx_sinh;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"COSH",4))
							{
								mabui[lmopi].MathFunc=cplx_cosh;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"TANH",4))
							{
								mabui[lmopi].MathFunc=cplx_tanh;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"LOG",3))
							{
								mabui[lmopi].MathFunc=cplx_log;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"EXP",3))
							{
								mabui[lmopi].MathFunc=cplx_exp;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"ABS",3))
							{
								mabui[lmopi].MathFunc=cplx_abs;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"REAL",4))
							{
								mabui[lmopi].MathFunc=cplx_real;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"IMAG",4))
							{
								mabui[lmopi].MathFunc=cplx_imag;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"SWAP",4))
							{
								mabui[lmopi].MathFunc=cplx_swap;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"INV",3))
							{
								mabui[lmopi].MathFunc=cplx_inv;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"FN1",3))
							{
								fn1bi[fn1pi]=lmopi;fn1pi++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"FN2",3))
							{
								fn2bi[fn2pi]=lmopi;fn2pi++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"FN3",3))
							{
								fn3bi[fn3pi]=lmopi;fn3pi++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"FN4",3))
							{
								fn4bi[fn4pi]=lmopi;fn4pi++;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(!strncmp(salgo,"POW",3))
							{
								mabui[lmopi].MathFunc=cplx_pow;
								i=0;
								while(svar1[i]!=',') i++;
								svar1[i]=0;i++;j=0;
								while(svar1[i]!=0)
								{
									svar2[j]=svar1[i];i++;j++;
								}
								svar2[j]=0;
								if((ix=GetVarIX(svar1))==-1) quit=4;
								mabui[lmopi].p1=&uv[ix].z;
								if((ix=GetVarIX(svar2))==-1) quit=5;
								mabui[lmopi].p2=&uv[ix].z;
								ix=GetVarIX(svar);
								mabui[lmopi].e=&uv[ix].z;
								lmopi++;fufo=1;
							}
							if(fufo==0) quit=3;
						}
						else
						{
							mabui[lmopi].MathFunc=cplx_erg;
							i=0;
							while(salgo[i]!=0)
							{
								svar1[i]=salgo[i];i++;
							}
							svar1[i]=0;
							if((ix=GetVarIX(svar1))==-1) quit=4;
							mabui[lmopi].p1=&uv[ix].z;
							ix=GetVarIX(svar);
							mabui[lmopi].e=&uv[ix].z;
							lmopi++;
						}
					}
				}
			}
		}
		switch(quit)
		{
			case 2:
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nBlock 3 not closed !",fline);Message(mess);
				fclose(frm);return(-1);
				break;
			case 3:
				i=0;
				while(salgo[i]!='(') i++;salgo[i]=0;
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nFunction '%s' not exists !",fline,salgo);Message(mess);
				fclose(frm);return(-1);
				break;
			case 4:
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nVariable '%s' isn`t created !",fline,svar1);Message(mess);
				fclose(frm);return(-1);
				break;
			case 5:
				sprintf(mess,"Formula : ERROR in pass 6 line %3d !\nVariable '%s' isn`t created !",fline,svar2);Message(mess);
				fclose(frm);return(-1);
				break;
		}

		quit=0;						/* Searching for 2. { */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='{') quit=1;
			}
		}
		if(quit==2)
		{
			sprintf(mess,"Formula : ERROR in pass 9 line %3d !\nBlock 4 not opened !");Message(mess);
			fclose(frm);return(-1);
		}

		quit=0;						/* Bailoutblock */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='}') quit=1;
				else
				{
					bailt=0;
					if(strstr(line,"<") && !strstr(line,"="))
					{
						j=(int)strstr(line,"<")-(int)line;
						for(i=0;i<j;i++) svar[i]=line[i];
						svar[i]=0;
						j++;i=0;
						while(line[j]!=0)
						{
							svar1[i]=line[j];i++;j++;
						}
						svar1[i]=0;
						baill=GetVarIX(svar);
						bailr=GetVarIX(svar1);
						bailt=1;
					}
					if(strstr(line,"<="))
					{
						j=(int)strstr(line,"<=")-(int)line;
						for(i=0;i<j;i++) svar[i]=line[i];
						svar[i]=0;
						j+=2;i=0;
						while(line[j]!=0)
						{
							svar1[i]=line[j];i++;j++;
						}
						svar1[i]=0;
						baill=GetVarIX(svar);
						bailr=GetVarIX(svar1);
						bailt=2;
					}
					if(strstr(line,"=") && !strstr(line,"<") && !strstr(line,">"))
					{
						j=(int)strstr(line,"=")-(int)line;
						for(i=0;i<j;i++) svar[i]=line[i];
						svar[i]=0;
						j++;i=0;
						while(line[j]!=0)
						{
							svar1[i]=line[j];i++;j++;
						}
						svar1[i]=0;
						baill=GetVarIX(svar);
						bailr=GetVarIX(svar1);
						bailt=3;
					}
					if(strstr(line,">="))
					{
						j=(int)strstr(line,">=")-(int)line;
						for(i=0;i<j;i++) svar[i]=line[i];
						svar[i]=0;
						j+=2;i=0;
						while(line[j]!=0)
						{
							svar1[i]=line[j];i++;j++;
						}
						svar1[i]=0;
						baill=GetVarIX(svar);
						bailr=GetVarIX(svar1);
						bailt=4;
					}
					if(strstr(line,">") && !strstr(line,"="))
					{
						j=(int)strstr(line,">")-(int)line;
						for(i=0;i<j;i++) svar[i]=line[i];
						svar[i]=0;
						j++;i=0;
						while(line[j]!=0)
						{
							svar1[i]=line[j];i++;j++;
						}
						svar1[i]=0;
						baill=GetVarIX(svar);
						bailr=GetVarIX(svar1);
						bailt=5;
					}
					if(strstr(line,"<>")!=0)
					{
						j=(int)strstr(line,"<>")-(int)line;
						for(i=0;i<j;i++) svar[i]=line[i];
						svar[i]=0;
						j+=2;i=0;
						while(line[j]!=0)
						{
							svar1[i]=line[j];i++;j++;
						}
						svar1[i]=0;
						baill=GetVarIX(svar);
						bailr=GetVarIX(svar1);
						bailt=6;
					}
				}
			}
		}
		switch(quit)
		{
			case 2:
				sprintf(mess,"Formula : ERROR in pass 10 line %3d !\nBlock 4 not closed !",fline);Message(mess);
				fclose(frm);return(-1);
				break;
		}

		quit=0;						/* Searching 2. { */
		while(!quit)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				ConvertLine(line);
				if(line[0]=='{') quit=1;
			}
		}
		if(quit==2)
		{
			sprintf(mess,"Formula : ERROR in pass 11 line %3d !\nBlock 5 not opened !",fline);Message(mess);
			fclose(frm);return(-1);
		}

		quit=0;i=1;						/* Searching 2. } */
		while(!quit && i<5)
		{
			if(ReadLine(line)==NULL) quit=2;
			else
			{
				strcpy(salgo,line);
				ConvertLine(line);
				if(line[0]=='}') quit=1;
				else
				{
					salgo[41]=0;
					strcpy(fd[i],&salgo[2]);fd[i][strlen(&salgo[2])-1]=0;
					i++;
				}
			}
		}
		if(quit==2)
		{
			sprintf(mess,"Formula : ERROR in pass 12 line %3d !\nBlock 5 not closed !",fline);Message(mess);
			fclose(frm);return(-1);
		}
		fclose(frm);
	}
	else
	{
		sprintf(mess,"Formula : ERROR can`t open file %s !",fname);Message(mess);
		return(-1);
	}
	return(0);
}

int ReadLine(char *buf)
{
	char *status=0l;

	fline++;				/* Zeilenzähler erhöhen */
	buf[0]=';';
	while(buf[0]==';')
	{
		status=fgets(buf,80,frm);
		if(!status) buf[0]=64;
	}
	return(status!=0);
}

void ConvertLine(char *buf)
{
	register int i=0,j,quit=0;

	while(!quit)
	{
		if(buf[i]>=97 && buf[i]<=122) buf[i]-=32;		/* to upper case */
		if(buf[i]=='\n') buf[i]=0;						/* end of line */
		if(buf[i]==';')
		{
			while(buf[i-1]==32 || buf[i-1]==9) i--;
			buf[i]=0;
		}
		if(buf[i]==32 || buf[i]==9)						/* white space */
		{
			j=i;
			while(buf[j]!=0)
			{
				buf[j]=buf[j+1];
				j++;
			}
			i--;
		}
		if(i>=0 && buf[i]==0) quit=1;
		i++;
	}
}

void SplitEqu(char *buf,char *svar,char *salgo)
{
	register int i=0,j=0;

	while(buf[i]!='=')
	{
		svar[i]=buf[i];
		i++;
	}
	svar[i]=0;i++;
	while(buf[i-1]!=0)
	{
		salgo[j]=buf[i];
		i++;j++;
	}
	salgo[i]=0;
}

int GetVarIX(char *svar)
{
	register int i;

	for(i=0;i<luv;i++)
	{
		if(strcmp(uv[i].vname,svar)==0) return(i);
	}
	return(-1);
}
