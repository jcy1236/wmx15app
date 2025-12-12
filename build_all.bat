@echo off
setlocal

set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
set PROJECT=broker\WMXBroker.vcxproj

echo ============================================
echo WMXBroker Multi-Version Build Script
echo ============================================
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
