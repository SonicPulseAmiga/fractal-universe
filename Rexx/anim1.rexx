/* FU Arexxtester */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim1[31m[24m';say;

SetZoom '-1.625 -1.3 1.625 1.3';
if RC~=0 then call AppError('SetZoom',RC);

SetIter '100';
if RC~=0 then call AppError('SetIter',RC);

par1r=0.11031;	par1rs=0.0025;
par1i=-0.67037;	par1is=0.0025;

do i=0 to 10
	name='xh3:frames/tjulia.'right(i,3,'0');
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
