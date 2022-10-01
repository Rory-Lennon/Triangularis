@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by TRIANGULARIS.HPJ. >"hlp\Triangularis.hm"
echo. >>"hlp\Triangularis.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Triangularis.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Triangularis.hm"
echo. >>"hlp\Triangularis.hm"
echo // Prompts (IDP_*) >>"hlp\Triangularis.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Triangularis.hm"
echo. >>"hlp\Triangularis.hm"
echo // Resources (IDR_*) >>"hlp\Triangularis.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Triangularis.hm"
echo. >>"hlp\Triangularis.hm"
echo // Dialogs (IDD_*) >>"hlp\Triangularis.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Triangularis.hm"
echo. >>"hlp\Triangularis.hm"
echo // Frame Controls (IDW_*) >>"hlp\Triangularis.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Triangularis.hm"
REM -- Make help for Project TRIANGULARIS


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Triangularis.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Triangularis.hlp" goto :Error
if not exist "hlp\Triangularis.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Triangularis.hlp" Debug
if exist Debug\nul copy "hlp\Triangularis.cnt" Debug
if exist Release\nul copy "hlp\Triangularis.hlp" Release
if exist Release\nul copy "hlp\Triangularis.cnt" Release
echo.
goto :done

:Error
echo hlp\Triangularis.hpj(1) : error: Problem encountered creating help file

:done
echo.
