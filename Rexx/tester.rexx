/* FU Arexxtester */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxTester[31m[24m';say;

SetFormula 'NormFixPlaneC Julia'
if RC~=0 then call AppError('SetFormula',RC);

SetZoom '-3.0 -2.4 3.0 2.4';
if RC~=0 then call AppError('SetZoom',RC);

SetIter '30';
if RC~=0 then call AppError('SetIter',RC);

SetInside 'Normal 15 -1'
if RC~=0 then call AppError('SetInside',RC);

SetOutside 'BiomorphRel1 5 -1'
if RC~=0 then call AppError('SetOutside',RC);

par1r=0.11031;	par1rs=0.01;
par1i=-0.67037;	par1is=0.01;

do i=0 to 0
	name='xh3:frames/julia.'right(i,3,'0');
	say 'Working on : ' name;

	SetParam '1' par1r par1i;
	if RC~=0 then call AppError('SetParam',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	par1r=par1r+par1rs;
	par1i=par1i+par1is;
end

ActivateFU;
if RC~=0 then call AppError('ActivateFU',RC);

pull

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
