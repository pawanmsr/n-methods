#! /usr/bin/bash

set -e

PREFIX=
BINARY_NAME=
FILE_EXTENSION=".cpp"
BINARY_EXTENSION=".out"
STACK_SIZE="unlimited" # 64 * 1024 # for 64 MBs
SUM_EXTENSION=".log" # store checksums of played programs

SUM="md5sum"
COMPILER="g++"
FLAGS="-g -std=c++2a -DLOCAL -pedantic -Wall -Wextra -Wshadow -Wconversion"

CLEAN="again" # supply as first argument to clean

usage() {
    echo "Usage: bash play.sh [problem | $CLEAN]"
    echo "Problem may be a, b, . . ."
    echo
}

if [[ -z $1 ]] ; then
    echo "Problem name / number not provided."
    usage;

    if [[ -z $PREFIX ]] ; then
        echo "Filename is empty."
        echo
        exit 1;
    fi
elif [[ $1 == $CLEAN ]] ; then
    echo "Clean-up to play again."
    echo "Using $(uname -m) system."
    echo
    
    find . -name "*$SUM_EXTENSION" -type f -delete 
    find . -name "*$BINARY_EXTENSION" -type f -delete

    exit 0;
fi

if ! command -v $COMPILER &>/dev/null ; then
    echo "Compiler $COMPILER not found."
    echo
    exit $?;
fi

FILENAME="${PREFIX}${1}${FILE_EXTENSION}"
if [[ -z $BINARY_NAME ]] ; then
    BINARY="${PREFIX}${1}${BINARY_EXTENSION}"
else
    BINARY="${BINARY_NAME}${BINARY_EXTENSION}"
fi

declare -A SUMS
SUMFILE="${PREFIX}${SUM_EXTENSION}"
if [[ -e $SUMFILE ]] ; then
    while IFS=' ' read -r KEY VALUE ; do
        SUMS[$KEY]=$VALUE
    done < $SUMFILE
    
    # # using external tools
    # SUMS[$FILENAME]=$(grep "$FILENAME " $SUMFILE | 
    #     sed -e "s/^$FILENAME //" | tail -n 1)
fi

if [[ -e $FILENAME ]] ; then
    DEFAULT_STACK_SIZE=$(ulimit -s)
    # adjust limits on stack
    ulimit -s $STACK_SIZE # use sparingly
    
    CSUM=
    if command -v $SUM &>/dev/null ; then
        CSUM=($($SUM $FILENAME))
        CSUM=${CSUM[0]}
    fi
    
    if [[ ! -v SUMS[$FILENAME] ]] || [[ ${SUMS[$FILENAME]} != $CSUM ]] ; then
        echo "$COMPILER is compiling $FILENAME."
        time $COMPILER $FLAGS $FILENAME -I . -o $BINARY
        
        if [[ ! -z $CSUM ]] ; then
            echo "$FILENAME $CSUM" >> $SUMFILE
        fi
    fi
    
    if [[ -e $BINARY ]] ; then
        time ./$BINARY
    else
        echo "$BINARY is absent. Play again."
    fi
    
    ulimit -s $DEFAULT_STACK_SIZE
    
    exit 0;
else
    echo "${FILENAME} is not present in ${PWD}"
    echo

    usage;
    exit 2;
fi

# TODO: POSIX system compatibility (or not)?
