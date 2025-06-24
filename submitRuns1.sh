#!/bin/bash

for i in 2 3 4 5 6 7;
do
	cd rand$i
	make run
	cd ../
done
