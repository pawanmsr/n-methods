@REM compile and run on Windows
@ECHO OFF

@REM use prefix for idenfication
SET prefix=
SET binary_name=
SET file_extension=.cpp
SET binary_extension=.exe

@REM increase stack size to 64MBs
SET /A stack_size= 64 * 1024 * 1024
@REM FIXME: not working on 32 bit compiler
@REM prefer 64 bit compiler, always

@REM store checksums of played programs
SET sum_extension=.log

SET sum=MD5
SET compiler=g++
SET flags=-g -Wl,--stack,%stack_size% -std=c++2a -DLOCAL -pedantic -Wall -Wextra -Wshadow -Wconversion

SET clean=again

IF [%~1] == [] (
    ECHO Problem name / number not provided.
    CALL :usage

    IF [%prefix%] == [] (
        ECHO Filename is empty.
        ECHO:
        EXIT \B 1
    )
)

IF [%~1] == [%clean%] (
    ECHO Clean-up to play again.
    ECHO Using %PROCESSOR_ARCHITECTURE% system.
    ECHO:

    DEL /F /Q *%sum_extension%
    DEL /F /Q *%binary_extension%

    EXIT /B 0
)

WHERE %compiler% >NUL 2>NUL
IF %ERRORLEVEL% NEQ 0 (
    ECHO Compiler %compiler% not found.
    ECHO:
    EXIT \B %ERRORLEVEL%
)

SET filename=%prefix%%1%file_extension%
IF [%binary_name%] == [] (
    SET binary=%prefix%%1%binary_extension%
) ELSE SET binary=%binary_name%%binary_extension%

SET sumfile=%prefix%%sum_extension%
SETLOCAL ENABLEDELAYEDEXPANSION
SET sums=absent
IF EXIST %sumfile% (
    @REM filename checksum
    FOR /F "tokens=1,2 delims= " %%a IN (%sumfile%) DO (
        IF [%%a] EQU [%filename%] IF [%%b] NEQ [] SET sums=%%b
    )
)
ENDLOCAL & SET sums=%sums%

SETLOCAL ENABLEDELAYEDEXPANSION
IF EXIST %filename% (
    @REM ^ before special characters in backquotes
    FOR /F "usebackq skip=1 delims=" %%h IN (
        `2^>NUL CertUtil -hashfile %filename% %sum%`
    ) DO IF NOT DEFINED csum SET csum=%%h
)
ENDLOCAL & SET csum=%csum%

IF EXIST %filename% (
    IF [%sums%] NEQ [%csum%] (
        ECHO %compiler% is compiling %filename%
        %compiler% %flags% %filename% -I . -o %binary%

        IF [%csum%] NEQ [] ECHO %filename% %csum% >> %sumfile%
    )
    
    IF EXIST %binary% (
        %binary%
    ) ELSE ECHO %binary% absent. Play again.
    EXIT \B 0
) ELSE (
    ECHO %filename% is not present in %CD%
    ECHO:
    
    CALL :usage
    EXIT \B 3
)

:usage
ECHO Usage: play.bat [problem | %clean%]
ECHO Problem may be a, b, . . .
ECHO:
EXIT /B %ERRORLEVEL%
