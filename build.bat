@echo off
rem Builds the game with Visual Studio's compiler (cl.exe) into build\dungeon.exe.
rem Works from any terminal: it finds Visual Studio and loads its environment first.

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -property installationPath`) do set "VSPATH=%%i"

if not defined VSPATH (
    echo Could not find Visual Studio. Install "Desktop development with C++".
    exit /b 1
)

call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1

if not exist build mkdir build
cl /nologo /std:c++17 /EHsc /W4 /Zi src\*.cpp /Fe:build\dungeon.exe /Fo:build\ /Fd:build\
