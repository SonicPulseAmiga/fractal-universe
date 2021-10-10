/* $VER: FU ArexxAnim : Orbit
 * display one orit in each frame
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : Orbit[31m[24m';say;

SetFormula 'NormVarPlaneC Mandel'
if RC~=0 then call AppError('SetFormula',RC);

SetOutside 'Stripes -1 -1'
if RC~=0 then call AppError('SetInside',RC);

SetIter '150';
if RC~=0 then call AppError('SetIter',RC);

orbit=1

do i=0 to 100
	name='swap:frames/orbit.'right(i,3,'0');
	say 'Working on : ' name;

	SetInside 'Orbit 150' orbit
	if RC~=0 then call AppError('SetInside',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	orbit=orbit+1;
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
