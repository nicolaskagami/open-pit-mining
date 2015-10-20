#!/bin/bash

TESTS="./Tests"
EXEC="./OPM/myOPM"
RESULTS="./Results"

for file in ${TESTS}/*.ins;
do
    TEST="${RESULTS}/$(basename ${file} .ins)"
    ${EXEC} < ${file} > ${TEST}.sol
    ./OPM/OPM --ins $file --sol ${TEST}.sol --pbm ${TEST}.pbm
done
