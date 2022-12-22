#!/bin/bash
if [ -d ./build/ ]; then
	rm -rf ./build/;
fi

if [ $? ]; then 
	cmake -Bbuild .;
	if [ $? ]; then
		cd build;
		cmake --build . --parallel 8;
		cd ..;
	fi
 else 
	echo "---------------------------error above-------------"
fi