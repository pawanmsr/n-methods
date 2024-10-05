#! /usr/bin/bash

set -e

PREFIX=
BINARY_NAME=
FILE_EXTENSION=".cpp"
BINARY_EXTENSION=".out"

COMPILER="g++"
FLAGS="-g -std=c++2a -DLOCAL -pedantic -Wall -Wextra -Wshadow -Wconversion"

usage() {
    echo "Usage: bash play.sh [problem]"
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

if [[ -e $FILENAME ]] ; then
    DEFAULT_STACK_SIZE=$(ulimit -s)
    # remove limits on stack
    STACK_SIZE="unlimited"
    ulimit -s $STACK_SIZE # (use sparingly)
    
    time $COMPILER $FLAGS $FILENAME -I . -o $BINARY
    if [[ -e $BINARY ]] ; then
        time ./$BINARY
    fi

    ulimit -s $DEFAULT_STACK_SIZE
    exit 0;
else
    echo "${FILENAME} is not present in ${PWD}"
    echo

    usage;
    exit 2;
fi
