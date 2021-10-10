/* $VER: FU ArexxAnim : JuliaParam2
 */

options results

ADDRESS REXX_FU

CALL ADDLIB('rexxmathlib.library',0,-30,0)

say '[4m[32mFU-ArexxAnim : JuliaParam2[31m[24m';say;

SetFormula 'NormFixPlaneC Julia'
if RC~=0 then call AppError('SetFormula',RC);

SetZoom '-1.625 -1.3 1.625 1.3';
if RC~=0 then call AppError('SetZoom',RC);

SetInside 'Normal 0 -1'
if RC~=0 then call AppError('SetInside',RC);

SetOutside 'BiomorphRel2 3 -1'
if RC~=0 then call AppError('SetInside',RC);

SetIter '100';
if RC~=0 then call AppError('SetIter',RC);

frames=200
angle=0
anglest=360.0/frames

do i=1 to frames
	rangle=angle*PI(0)/180.0
	par1r=(1.1*COS(rangle))-0.7;
	par1i=(0.9*SIN(rangle));

	name='swap:frames/pic.'right(i,3,'0');
	say 'Working on : ' name;
	say 'Par1       : ' par1r par1i;

	SetParam '1' par1r par1i;
	if RC~=0 then call AppError('SetParam',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	angle=i*anglest;
end

ActivateFU;
if RC~=0 then call AppError('ActivateFU',RC);

ExitFU;
if RC~=0 then call AppError('ExitFU',RC);

exit

AppError:procedure
	cmd=arg(1);
	ret=arg(2);
	say '[4m[33mApplication Error[31m[24m';say;
	say 'Command 'cmd' failed with Returncode 'ret;
	select
		when ret='1' then say '	=> unknown command';
		when ret='2' then say '	=> unknown parameter';
		otherwise say '	=> unknown returncode';
	end
	say;
return
