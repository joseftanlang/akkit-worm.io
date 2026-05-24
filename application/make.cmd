@echo off
setlocal

set "MAKE_EXE="
for %%I in (mingw32-make.exe make.exe) do (
    if not defined MAKE_EXE if exist "%%~$PATH:I" set "MAKE_EXE=%%~$PATH:I"
)

if defined MAKE_EXE (
    "%MAKE_EXE%" -f Makefile %*
    exit /b %ERRORLEVEL%
)

if /I "%~1"=="clean" (
    if exist build_worm-game rmdir /s /q build_worm-game
    exit /b 0
)

echo GNU make is not installed. Install GNU Make or use Git Bash/MSYS2 for full build targets.
exit /b 1