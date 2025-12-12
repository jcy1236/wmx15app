@echo off
setlocal enabledelayedexpansion

:: Find MSBuild using vswhere (works with VS 2017+)
set VSWHERE="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist %VSWHERE% (
    echo [ERROR] vswhere.exe not found. Please install Visual Studio 2017 or later.
    exit /b 1
)

for /f "usebackq tokens=*" %%i in (`%VSWHERE% -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
    set MSBUILD="%%i"
)

if not defined MSBUILD (
    echo [ERROR] MSBuild not found. Please install Visual Studio with C++ build tools.
    exit /b 1
)

set PROJECT=broker\WMXBroker.vcxproj

echo ============================================
echo WMXBroker Multi-Version Build Script
echo ============================================
echo.
echo Using MSBuild: %MSBUILD%
echo.

:: Check if SDK folders have content
if not exist "sdk\WMX34u4_Win\Lib\WMX3Api.lib" (
    echo [WARNING] SDK files not found in sdk\WMX34u4_Win\
    echo           Please copy SDK files first. See sdk\README.md
    echo.
)

:: Build WMX3.4u4 Windows
echo [1/4] Building WMX3.4u4 Windows...
%MSBUILD% %PROJECT% /p:Configuration=Release /p:Platform=x64 /p:WMXVersion=WMX34u4_Win /t:Rebuild /v:minimal
if errorlevel 1 (
    echo [ERROR] WMX3.4u4 Windows build failed!
    goto :error
)
echo [OK] WMX3.4u4 Windows build completed.
echo.

:: Build WMX3.4u4 RTX
echo [2/4] Building WMX3.4u4 RTX...
%MSBUILD% %PROJECT% /p:Configuration=Release /p:Platform=x64 /p:WMXVersion=WMX34u4_RTX /t:Rebuild /v:minimal
if errorlevel 1 (
    echo [ERROR] WMX3.4u4 RTX build failed!
    goto :error
)
echo [OK] WMX3.4u4 RTX build completed.
echo.

:: Build WMX3.6u1 Windows
echo [3/4] Building WMX3.6u1 Windows...
%MSBUILD% %PROJECT% /p:Configuration=Release /p:Platform=x64 /p:WMXVersion=WMX36u1_Win /t:Rebuild /v:minimal
if errorlevel 1 (
    echo [ERROR] WMX3.6u1 Windows build failed!
    goto :error
)
echo [OK] WMX3.6u1 Windows build completed.
echo.

:: Build WMX3.6u1 RTX
echo [4/4] Building WMX3.6u1 RTX...
%MSBUILD% %PROJECT% /p:Configuration=Release /p:Platform=x64 /p:WMXVersion=WMX36u1_RTX /t:Rebuild /v:minimal
if errorlevel 1 (
    echo [ERROR] WMX3.6u1 RTX build failed!
    goto :error
)
echo [OK] WMX3.6u1 RTX build completed.
echo.

echo ============================================
echo All builds completed successfully!
echo ============================================
echo.
echo Output locations:
echo   x64\Release_WMX34u4_Win\WMXBroker.dll
echo   x64\Release_WMX34u4_RTX\WMXBroker.dll
echo   x64\Release_WMX36u1_Win\WMXBroker.dll
echo   x64\Release_WMX36u1_RTX\WMXBroker.dll
echo.
goto :end

:error
echo.
echo Build failed with errors.
exit /b 1

:end
endlocal
