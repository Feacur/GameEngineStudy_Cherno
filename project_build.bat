@echo off

chcp 1252
rem code page 1250: Windows Central Europe
rem code page 1251: Windows Cyrillic
rem code page 1252: Windows Western

rem read batch file arguments
set architecture=%1
set configuration=%2

pushd "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build"
call "vcvarsall.bat" %architecture%
popd

echo ---- BUILD ---- %time%
msbuild -p:Configuration=%configuration%
echo ---- DONE ---- %time%
