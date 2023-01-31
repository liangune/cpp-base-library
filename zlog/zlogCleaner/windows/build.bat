@echo off
set filepath=..\zlog_cleaner.go ..\log_cleaner.go
set dllpath=zlog_cleaner.dll

@echo %filepath% 
@echo %dllpath%

:make
@echo build %filepath%  -^> %dllpath%
call go build -ldflags "-s -w" -buildmode=c-shared -o %dllpath% %filepath% 
call "C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64\lib.exe" /def:zlog_cleaner.def /machine:x64 /out:zlog_cleaner.lib
@echo "build success!"

:end
pause
