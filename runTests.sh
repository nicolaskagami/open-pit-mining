#!/bin/bash

GENERATION="./Generation"
BENCHMARKS="./Benchmarks"
RESULTFILE="Bench.dat"
TESTS="./Tests"
EXECDIR="./MaxFlow"
VERIF="./Verification/Verif"


for EXEC in EdmondsKarp FordFulkerson;
do
    for file in ${TESTS}/*.gr;
    do
        BENCHFILE=$(basename $file .gr | cut -d '_' -f1)
        if [ ! -f "${BENCHMARKS}/${BENCHFILE}" ]
        then
            echo "Alg Verts Edges Expanded_Verts Paths" > ${BENCHMARKS}/${BENCHFILE}
        fi
        RESULT=$(${EXECDIR}/${EXEC} < ${file} 2>> ${BENCHMARKS}/${BENCHFILE})
        ANSWER=$($VERIF < ${file})
        if [ "$RESULT" = "$ANSWER" ]
        then
            echo "OK $EXEC: $file"
        else
            echo "Different: $EXEC: $file = $RESULT != $ANSWER"
        fi
    done
done
