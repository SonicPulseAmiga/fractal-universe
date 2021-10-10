/****h* FractalUniverse/FU-ErrMsg.c [1.68] *
*
*  NAME
*    FU-ErrMsg.c
*  COPYRIGHT
*    $VER: FU-ErrMsg.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    Fehlerbehandlung
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

#define FU_ERRMSG_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void Message(char *mess);
long Question(char *mess);

//-- globals ------------------------------------------------------------------

char *mess[]={
	"Can`t open file !",						/*  0 */
	"Can`t read data !",						/*  1 */
	"Can`t write data !",						/*  2 */
	"Can`t acces file !",						/*  3 */
	"Can`t allocate memory !",					/*  4 */
	"Can`t open window !",						/*  5 */
	"Can`t create gadgets !",					/*  6 */
	"Can`t create context !",					/*  7 */
	"Not a FU-COLORS-File !",					/*  8 */
	"Not a FU-PREFS-File !",					/*  9 */
	"False FRUN-Chunkversion !",				/* 10 */
	"Not an IFF-File!",							/* 11 */
	"Not an IFF-ILBM-File!",					/* 12 */
	"No FRUN-Chunk found !",					/* 13 */
	"Can`t open screen !", 						/* 14 */
	"This is an unregistered version of FractalUniverse !\nSaving of your work is disabled !\nSee guide for further informations !",			/* 15 */
	"You have used an unregistered version of FractalUniverse !",				/* 16 */
	"If`ve already told you -\nYOU CAN`T SAVE YOUR PICTURES IN THE DEMO !",		/* 17 */
	"This function is not ready implemented !"									/* 18 */
	"Take your fingers away from the keyfile !!!",								/* 19 */
};

char *ques[]={
	"File allready exists !\nShould I continue ?",							/*  0 */
	"Do you really want to quit !",											/*  1 */
	"FU is already running !\nShould I start it again ?",					/*  2 */
	"Screenmode isn`t available !\nShould I load the fractal-picturedata ?"	/*  3 */
};

//-- definitions --------------------------------------------------------------

void Message(char *mess)
{
	struct EasyStruct es;

	if(mmwin)
	{
		es.es_Title="FractalUniverse-Request";
		es.es_TextFormat=mess;
		es.es_GadgetFormat="Okay";
		EasyRequestArgs(mmwin,&es,0,0);
	}
}

long Question(char *mess)
{
	struct EasyStruct es;

	if(mmwin)
	{
		es.es_Title="FractalUniverse-Request";
		es.es_TextFormat=mess;
		es.es_GadgetFormat="Okay|Cancel";
		return(EasyRequestArgs(mmwin,&es,0,0));
	}
	else return(0);
}
