/* $VER: FU ArexxAnim : JuliaParam
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : JuliaParam[31m[24m';say;

SetFormula 'NormFixPlaneC Julia'
if RC~=0 then call AppError('SetFormula',RC);

SetZoom '-1.625 -1.3 1.625 1.3';
if RC~=0 then call AppError('SetZoom',RC);

SetInside 'Normal 0 -1'
if RC~=0 then call AppError('SetInside',RC);

SetOutside 'Stripes -1 -1'
if RC~=0 then call AppError('SetInside',RC);

SetIter '100';
if RC~=0 then call AppError('SetIter',RC);

frames=100
par1rs=0.11031;
par1re=0.17281;
par1rst=(par1re-par1rs)/frames;
par1is=-0.67037;
par1ie=-0.60787;
par1ist=(par1ie-par1is)/frames;

do i=0 to frames
	name='swap:frames/juliaparam.'right(i,3,'0');
	say 'Working on : ' name;

	SetParam '1' par1rs par1is;
	if RC~=0 then call AppError('SetParam',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	par1rs=par1rs+par1rst;
	par1is=par1is+par1ist;
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
