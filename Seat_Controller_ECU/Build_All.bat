@echo off
REM ========================================================================
REM STM32F401 Project Build Script
REM Project Path: C:\Users\Moata\OneDrive\Desktop\New folder (3)
REM ========================================================================

set PROJECT_PATH=C:\Users\Moata\OneDrive\Desktop\New folder (3)
set PROJECT=STM32_MASTER
set LINKER=%PROJECT_PATH%\STM32F401RCTX_FLASH.ld

REM Toolchain Configuration
set TOOLCHAIN_PATH=D:\STM32CubeIDE_1.19.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.13.3.rel1.win32_1.0.0.202411081344\tools\bin
set CC="%TOOLCHAIN_PATH%\arm-none-eabi-gcc.exe"
set OBJCOPY="%TOOLCHAIN_PATH%\arm-none-eabi-objcopy.exe"
set SIZE="%TOOLCHAIN_PATH%\arm-none-eabi-size.exe"

REM Compiler Flags for STM32F401
set MCPU=-mcpu=cortex-m4
set MTHUMB=-mthumb  
set MFPU=-mfpu=fpv4-sp-d16
set MFLOAT_ABI=-mfloat-abi=hard
set DEFINES=-DUSE_HAL_DRIVER -DSTM32F401xC
set CFLAGS=%MCPU% %MTHUMB% %MFPU% %MFLOAT_ABI% %DEFINES% -Wall -fdata-sections -ffunction-sections -g -O0

REM Include Directories
set INC_DIRS=-I"%PROJECT_PATH%\Core\Inc" ^
-I"%PROJECT_PATH%\Drivers\STM32F4xx_HAL_Driver\Inc" ^
-I"%PROJECT_PATH%\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy" ^
-I"%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\include" ^
-I"%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2" ^
-I"%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F" ^
-I"%PROJECT_PATH%\Drivers\CMSIS\Device\ST\STM32F4xx\Include" ^
-I"%PROJECT_PATH%\Drivers\CMSIS\Include"

REM Linker Flags
set LDFLAGS=%MCPU% %MTHUMB% %MFPU% %MFLOAT_ABI% -specs=nano.specs -T"%LINKER%" -lc -lm -Wl,-Map=%PROJECT%.map,--cref -Wl,--gc-sections

REM Clean old build files
echo Cleaning previous build...
del *.o *.elf *.bin *.hex *.map 2>nul

echo.
echo ========================================================================
echo Building %PROJECT% from %PROJECT_PATH%
echo ========================================================================

REM Compile Core Sources
echo Compiling Core sources...
for %%f in ("%PROJECT_PATH%\Core\Src\*.c") do (
    echo   Compiling %%~nxf
    %CC% %CFLAGS% %INC_DIRS% -c "%%f" -o "%%~nf.o"
    if errorlevel 1 (
        echo Error compiling %%f
        exit /b 1
    )
)

REM Compile HAL Driver Sources
echo Compiling HAL Driver sources...
for %%f in ("%PROJECT_PATH%\Drivers\STM32F4xx_HAL_Driver\Src\*.c") do (
    echo   Compiling %%~nxf
    %CC% %CFLAGS% %INC_DIRS% -c "%%f" -o "%%~nf.o"
    if errorlevel 1 (
        echo Error compiling %%f
        exit /b 1
    )
)

REM Compile FreeRTOS Sources (if exists)
if exist "%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\*.c" (
    echo Compiling FreeRTOS sources...
    for %%f in ("%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\*.c") do (
        echo   Compiling %%~nxf
        %CC% %CFLAGS% %INC_DIRS% -c "%%f" -o "%%~nf.o"
        if errorlevel 1 (
            echo Error compiling %%f
            exit /b 1
        )
    )
    
    for %%f in ("%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2\*.c") do (
        echo   Compiling %%~nxf
        %CC% %CFLAGS% %INC_DIRS% -c "%%f" -o "%%~nf.o"
        if errorlevel 1 (
            echo Error compiling %%f
            exit /b 1
        )
    )
    
    for %%f in ("%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F\*.c") do (
        echo   Compiling %%~nxf
        %CC% %CFLAGS% %INC_DIRS% -c "%%f" -o "%%~nf.o"
        if errorlevel 1 (
            echo Error compiling %%f
            exit /b 1
        )
    )
    
    for %%f in ("%PROJECT_PATH%\Middlewares\Third_Party\FreeRTOS\Source\portable\MemMang\*.c") do (
        echo   Compiling %%~nxf
        %CC% %CFLAGS% %INC_DIRS% -c "%%f" -o "%%~nf.o"
        if errorlevel 1 (
            echo Error compiling %%f
            exit /b 1
        )
    )
)

REM Compile Startup File
echo Compiling startup file...
for %%f in ("%PROJECT_PATH%\Core\Startup\*.s") do (
    echo   Compiling %%~nxf
    %CC% %CFLAGS% -c "%%f" -o "startup.o"
    if errorlevel 1 (
        echo Error compiling %%f
        exit /b 1
    )
)

REM Collect all object files
echo Collecting object files...
set OBJ_FILES=
for %%f in (*.o) do call set OBJ_FILES=%%OBJ_FILES%% %%f

echo Linking...
%CC% %LDFLAGS% %OBJ_FILES% -o %PROJECT%.elf
if errorlevel 1 (
    echo Error linking
    exit /b 1
)

echo Generating binary...
%OBJCOPY% -O binary %PROJECT%.elf %PROJECT%.bin
if errorlevel 1 (
    echo Error generating binary
    exit /b 1
)

echo Generating hex file...
%OBJCOPY% -O ihex %PROJECT%.elf %PROJECT%.hex
if errorlevel 1 (
    echo Error generating hex file
    exit /b 1
)

echo.
echo Size Information:
%SIZE% %PROJECT%.elf

echo.
echo ========================================================================
echo Build Complete!
echo ========================================================================
echo Generated files:
echo   - %PROJECT%.elf  (Executable with debug info)
echo   - %PROJECT%.bin  (Raw binary for flashing)
echo   - %PROJECT%.hex  (Intel HEX format)
echo   - %PROJECT%.map  (Memory map)
echo ========================================================================