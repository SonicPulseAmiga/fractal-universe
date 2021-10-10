/******************************************************************************
** FU-ARRANGELIST.h                                                          **
**---------------------------------------------------------------------------**
** Zuweisungslisten                                                          **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

ArrangeList fflist[ffanz]=
{
	"InvCircle",		0,
	"NormCircle",		1,
	"Formula",			2,
	"InvNewton",		3,
	"NormNewton",		4,
	"InvFixPlaneC",		5,
	"InvVarPlaneC",		6,
	"NormFixPlaneC",	7,
	"NormVarPlaneC",	8, 
};

ArrangeList sf0list[sf0anz]=
{
	"Circle 0",			0,
	"Circle 1",			1,
	"Circle 2",			2,
	"Circle 3",			3,
	"Circle 4",			4,
	"Circle 5",			5,
	"Circle 6",			6,
	"Circle 7",			7,
};

ArrangeList sf1list[sf1anz]=
{
	"Circle 0",			0,
	"Circle 1",			1,
	"Circle 2",			2,
	"Circle 3",			3,
	"Circle 4",			4,
	"Circle 5",			5,
	"Circle 6",			6,
	"Circle 7",			7,
};

ArrangeList sf3list[sf3anz]=
{
	"Newton 0.0",		0,
	"Newton 1.0",		1,
	"Newton 1.1",		2,
	"Newton 2.0",		3,
	"Newton 3.0",		4,
};

ArrangeList sf4list[sf4anz]=
{
	"Newton 0.0",		0,
	"Newton 1.0",		1,
	"Newton 1.1",		2,
	"Newton 2.0",		3,
	"Newton 3.0",		4,
};

ArrangeList sf5list[sf5anz]=
{
	"Julia",			0,
	"JuliaFn",			1,
	"JuliaPower",		2,
	"JuliaWar",			3,
	"Magnet1",			4,
	"SqrFn",			5,
	"JuliaMan",			6,
	"Trinomic",			7,
	"Julia^3",			8,
	"Julia^4",			9,
};

ArrangeList sf6list[sf6anz]=
{
	"Mandel",			0,
	"MandelFn",			1,
	"MandelPower",		2,
	"MandelWar",		3,
	"Magnet1z",			4,
	"SqrFn",			5,
	"MandelMan",		6,
	"Trinomic",			7,
	"Mandel^3",			8,
	"Mandel^4",			9,
	"Magnet1p",			10,
};

ArrangeList sf7list[sf7anz]=
{
	"Julia",			0,
	"JuliaFn",			1,
	"JuliaPower",		2,
	"JuliaWar",			3,
	"Magnet1",			4,
	"SqrFn",			5,
	"JuliaMan",			6,
	"Trinomic",			7,
	"Julia^3",			8,
	"Julia^4",			9,
};

ArrangeList sf8list[sf8anz]=
{
	"Mandel",			0,
	"MandelFn",			1,
	"MandelPower",		2,
	"MandelWar",		3,
	"Magnet1z",			4,
	"SqrFn",			5,
	"MandelMan",		6,
	"Trinomic",			7,
	"Mandel^3",			8,
	"Mandel^4",			9,
	"Magnet1p",			10,
};
									/* Für Inside-/Outsidemodelle */
ArrangeList insidelist[isanz]=
{
	"BoF60",			0,
	"BoF61",			1,
	"Decomposition",	2,
	"DiffParImag",		3,
	"DiffParReal",		4,
	"DiffParReIm",		5,
	"MagnifyImag",		6,
	"MagnifyReal",		7,
	"MagnifyReIm",		8,
	"Normal",			9,
	"Orbit",			10,
	"OrbitLength",		11,
	"OrbitSumReIm",		12,
};

ArrangeList outsidelist[osanz]=
{
	"BinDecomp",		0,
	"BiomorphAbs1",		1,
	"BiomorphRel1",		2,
	"BiomorphAbs2",		3,
	"BiomorphRel2",		4,
	"ContPot",			5,
	"Decomposition",	6,
	"DiffIterImag",		7,
	"DiffIterReal",		8,
	"DiffIterReIm",		9,
	"DiffParImag",		10,
	"DiffParReal",		11,
	"DiffParReIm",		12,
	"Normal",			13,
	"Stripes",			14,
	"SummImagIt",		15,
	"SummRealIt",		16,
	"SummReImIt",		17,
};
