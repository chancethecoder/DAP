#!/bin/bash
TARGET_NAMES=("cpu_integer_exe" "cpu_float_exe")
GPROF_OUTPUT="gmon.out"
LOG_DIR="logs"

# Make directory if not exists
mkdir $LOG_DIR 2> /dev/null

# Read parameters
echo "choose testcase's number (default: 1)" 
echo -n "1.cpu-integer 2.cpu-float 3.gpu-integer 4.gpu-float: "
read TARGET_NUMBER
TARGET_NUMBER=${TARGET_NUMBER:-1}
TEST_CASE=${TARGET_NAMES[$TARGET_NUMBER-1]}

echo -n "choose size of matrix (default: 500): " 
read SIZE
SIZE=${SIZE:-500}

echo -n "choose amout of increment of size (defalut: 500): "
read INCREMENT
INCREMENT=${INCREMENT:-500}

echo "testcase: ${TEST_CASE}, initial size: ${SIZE}, increment size: ${INCREMENT}"

while true;
do
    LOGFILE="$LOG_DIR/$SIZE.txt"
    echo "start benchmark with N: $SIZE"
    ./$TEST_CASE $SIZE
    SIZE=$[$SIZE+$INCREMENT]

    # Check if process killed and stop loop.
    if [[ "$?" != "0" ]]; then
        echo "Memory failed. stop benchmark."
        break;
    fi
    gprof -b $TEST_CASE $GPROF_OUTPUT > $LOGFILE
done
