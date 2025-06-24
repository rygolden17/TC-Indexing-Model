#!/bin/bash

echo "The script starts now."

echo "rand2"
cd rand2

for num in 3 4 5 6 7; do
    cd .. 
    echo "copy rand$num"
    mkdir rand$num
    cp -r  rand2/* rand$num/
    cd rand$num
    rm mindcurrent
    cat currents.h |sed s/'#define time2(a) (2)'/'#define time2(a) (RANDNUM)'/ >currents_temp.h
    cat currents_temp.h |sed s/RANDNUM/${num}/ >currents.h 

    cat constructTrainedWeightFile.py |sed s/"num=2"/"num=RANDNUM"/ >constructTrainedWeightFile_tmp.py
    cat constructTrainedWeightFile_tmp.py |sed s/RANDNUM/${num}/ >constructTrainedWeightFile.py
    rm constructTrainedWeightFile_tmp.py

    make
done

echo "The script ends now."


