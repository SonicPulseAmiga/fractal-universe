/* $VER: FU ArexxAnim : Iter
 * Formula : Magnet
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : Iter[31m[24m';say;

zyklen=3
SetIter zyklen;
if RC~=0 then call AppError('SetIter',RC);

x1=1.8934;y1=-1.7549;x2=2.1944;y2=-1.5196
SetZoom x1 y1 x2 y2;
if RC~=0 then call AppError('SetZoom',RC);

frames=50

do i=0 to frames
	name='swap:frames/Iter.'right(i,3,'0');
	say 'Working on : ' name;

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	zyklen=zyklen+1;
	SetIter zyklen;
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
