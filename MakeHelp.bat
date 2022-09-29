@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by JIKI.HPJ. >"hlp\Jiki.hm"
echo. >>"hlp\Jiki.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Jiki.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Jiki.hm"
echo. >>"hlp\Jiki.hm"
echo // Prompts (IDP_*) >>"hlp\Jiki.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Jiki.hm"
echo. >>"hlp\Jiki.hm"
echo // Resources (IDR_*) >>"hlp\Jiki.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Jiki.hm"
echo. >>"hlp\Jiki.hm"
echo // Dialogs (IDD_*) >>"hlp\Jiki.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Jiki.hm"
echo. >>"hlp\Jiki.hm"
echo // Frame Controls (IDW_*) >>"hlp\Jiki.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Jiki.hm"
REM -- Make help for Project JIKI


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Jiki.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Jiki.hlp" goto :Error
if not exist "hlp\Jiki.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Jiki.hlp" Debug
if exist Debug\nul copy "hlp\Jiki.cnt" Debug
if exist Release\nul copy "hlp\Jiki.hlp" Release
if exist Release\nul copy "hlp\Jiki.cnt" Release
echo.
goto :done

:Error
echo hlp\Jiki.hpj(1) : error: Problem encountered creating help file

:done
echo.
