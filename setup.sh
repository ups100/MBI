#!/bin/sh
if [ ! -d ./build ] 
then 
	mkdir build
	mkdir build/lib
	mkdir build/bin 
fi

cd build
cmake -DQt5Core_DIR=/home/marcin/Qt5.2.0/5.2.0/gcc_64/lib/cmake/Qt5Core -DQt5Widgets_DIR=/home/marcin/Qt5.2.0/5.2.0/gcc_64/lib/cmake/Qt5Widgets  ../code
