cmake_minimum_required (VERSION 2.8.9) 

#project name
project (MBI) 

#look for boost library (required for this project)
FIND_PACKAGE( Boost COMPONENTS thread random REQUIRED )

#look for qt library (required for this project)
find_package(Qt5Core REQUIRED )

#look for doxygen to make documentation
find_package(Doxygen REQUIRED)

SET(QT_DONT_USE_QTGUI TRUE)

#turn on automoc
SET(CMAKE_AUTOMOC ON)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

#subdirectories

INCLUDE_DIRECTORIES( ${MBI_SOURCE_DIR}/algorithm/include )


SET( MBI_SRC
		${MBI_SOURCE_DIR}/main.cpp
)

#subdirectory with tests
add_subdirectory(tests)

add_executable(mbi ${MBI_SRC})

qt5_use_modules(mbi Core)



