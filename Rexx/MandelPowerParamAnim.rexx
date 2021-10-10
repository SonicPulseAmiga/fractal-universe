/* $VER: FU ArexxAnim : MandelPowerParam
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : MandelPowerParam[31m[24m';say;

SetZoom '-0.7 -0.7 0.7 0.7';
if RC~=0 then call AppError('SetZoom',RC);

SetIter '100';
if RC~=0 then call AppError('SetIter',RC);

par2r=1.0;par2rs=0.02;
par2i=0.0;

do i=0 to 50
	name='swap:frames/mandelpower.'right(i,3,'0');
	say 'Working on : ' name;

	SetParam '2' par2r par2i;
	if RC~=0 then call AppError('SetParam',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	par2r=par2r+par2rs;
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
