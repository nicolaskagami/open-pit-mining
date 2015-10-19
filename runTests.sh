#!/bin/bash

TESTS="./Tests"
EXEC="./OPM/myOPM"
RESULTS="./Results"

for file in ${TESTS}/*.ins;
do
    SOLUTION="${RESULTS}/$(basename ${file} .ins).sol"
    ${EXEC} < ${file} > ${SOLUTION}
done
