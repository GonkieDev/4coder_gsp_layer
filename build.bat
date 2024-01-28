@echo off

REM NOTE(Gonk): cd %~dp0 so you can call this from anywhere
cd %~dp0

call ..\bin\buildsuper_x64-win.bat .\4coder_gsp.cpp release
copy .\custom_4coder.dll ..\..\custom_4coder.dll
copy .\custom_4coder.pdb ..\..\custom_4coder.pdb