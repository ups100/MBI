::This script configure project.

if not exist build (
	mkdir build
	mkdir build\lib
	mkdir build\bin
)
cd build

::If paths to boost and GTest are NOT in PATH variable you should set it below
set BoostRoot=C:/Program Files/boost/boost_1_55_0
set GTestRoot=C:/gtest/gtest-1.7.0
set Qt5Core=C:/Qt/Qt5.2.1/5.2.1/msvc2012/lib/cmake/Qt5Core

:: NOTE If BoostRoot is not in PATH you should below options to cmake call
::-DBOOST_ROOT:PATH="%BoostRoot%" -DBoost_DIR:PATH="%BoostRoot%" -DBOOST_LIBRARYDIR:PATH="%BoostRoot%/stage/lib" -DBOOST_INCLUDEDIR:PATH="%BoostRoot%"

:: If you want to choose compiler which will be used to compile project you can add:
:: -G"Visual Studio 10"
:: To check which compiler can be use simply type cmake command in command line

cmake -DBoost_USE_STATIC_LIBS=ON -DQt5Core_DIR:PATH="%Qt5Core%" -DGTEST_ROOT="%GTestRoot%" -DGTEST_MSVC_SEARCH=MT -DGTEST_BOTH_LIBRARIES="%GTestRoot%/msvc/gtest/Debug" -DGTEST_INCLUDE_DIR="%GTestRoot%/include" ../code

cd ..

echo Force to copy all examples into build directory
cp example/* build/tests/