@REM compile and run on Windows
@ECHO OFF

@REM use prefix for idenfication
SET prefix=
SET binary_name=
SET file_extension=.cpp
@REM SET file_extension=.rs
SET binary_extension=.exe

@REM increase stack size to 64MBs
SET /A stack_size= 64 * 1024 * 1024
@REM FIXME: not working on 32 bit compiler
@REM prefer 64 bit compiler, always

@REM store checksums of played programs
SET sum_extension=.log
@REM limit the number of records in checksum log
SET /A sum_limit=100

SET sum=MD5
SET compiler=g++
@REM SET compiler=rustc
SET pre_flags=-g -Wl,--stack,%stack_size% -std=c++2a -DLOCAL -pedantic -Wall -Wextra -Wshadow -Wconversion
@REM SET pre_flags=--cfg LOCAL
SET post_flags=-I .

@REM supply as first argument to clean
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
SET /A sumlines=0
@REM stored checksum
SET ssum=absent
IF EXIST %sumfile% (
    @REM filename checksum
    FOR /F "tokens=1,2 delims= " %%a IN (%sumfile%) DO (
        SET /A sumlines+=1
        IF [%%a] EQU [%filename%] IF [%%b] NEQ [] SET ssum=%%b
    )
)
ENDLOCAL & (
    SET ssum=%ssum%
    SET sumlines=%sumlines%
)

SETLOCAL ENABLEDELAYEDEXPANSION
IF EXIST %filename% (
    @REM ^ before special characters in backquotes
    FOR /F "usebackq skip=1 delims=" %%h IN (
        `2^>NUL CertUtil -hashfile %filename% %sum%`
    ) DO IF NOT DEFINED csum SET csum=%%h
)
ENDLOCAL & SET csum=%csum%

IF EXIST %filename% (
    IF [%ssum%] NEQ [%csum%] CALL :compile
    IF NOT EXIST %binary% CALL :compile
    
    IF EXIST %binary% (
        %binary%
    ) ELSE ECHO %binary% absent. Play again.
    @REM else block is for when durability fails
    EXIT \B 0
) ELSE (
    ECHO %filename% is not present in %CD%
    ECHO:
    
    CALL :usage
    EXIT \B 3
)

:compile
    ECHO %compiler% is compiling %filename%
    %compiler% %pre_flags% %filename% %post_flags% -o %binary%

    IF %sumlines% GEQ %sum_limit% (
        @REM FIXME: date time is not universal
        REN %sumfile% %DATE:~6,4%-%DATE:~3,2%-%DATE:~0,2%-%TIME:~0,2%-%TIME:~3,2%-%TIME:~6,2%%sum_extension%
    )

    IF [%csum%] NEQ [] ECHO %filename% %csum% >> %sumfile%
    EXIT /B %ERRORLEVEL%

:usage
    ECHO Usage: play.bat [problem ^| %clean%]
    ECHO Problem may be a, b, . . .
    ECHO:
    EXIT /B %ERRORLEVEL%
