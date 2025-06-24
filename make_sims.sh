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

    make mindcurrent
done

echo "The script ends now."


