@echo off

set GBDK_PATH=c:\gbdk\bin
set BGB_PATH=c:\gb\bgb
set SOURCE_PATH=src
set OUTPUT_PATH=out

mkdir %OUTPUT_PATH% 2>nul

for /r %SOURCE_PATH% %%i in (*.c) do (
    %GBDK_PATH%\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o %OUTPUT_PATH%\%%~ni.o "%%i"
)

%GBDK_PATH%\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o %OUTPUT_PATH%\main.gb %OUTPUT_PATH%\*.o


echo "start game..."
%BGB_PATH%\bgb.exe ./out/main.gb