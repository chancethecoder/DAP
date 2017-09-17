#!/bin/bash
TARGET_CPU_EXAMPLE="cpu_practice_exe"
TIMEOUT_FLAGS="--signal=SIGKILL"
TIMEOUT_TIME="3"
GPROF_OUTPUT="gmon.out"
GPROF_LOG="log.txt"

function timeout() { perl -e 'alarm shift; exec @ARGV' "$@"; }

for N in {500..2000..250}
do
    echo "start program with N: $N"
    SIG=`timeout $TIMEOUT_TIME ./$TARGET_CPU_EXAMPLE $N || echo "0"`
    echo "$SIG"
    if [ "$SIG" -ne "0" ] ; then
        echo "비정상 종료"
    fi
    gprof -b $TARGET_CPU_EXAMPLE $GPROF_OUTPUT >> $GPROF_LOG
    echo "\n\n\n==========================\n\n\n" >> $GPROF_LOG
done
