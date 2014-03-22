cmake_minimum_required (VERSION 2.8.9) 

#project name
project (MBI)

# Eliminate a warning when building in Windows that relates
# to static linking of Qt executables to qtmain.lib.
# This policy was introduced in CMake version 2.8.11.
# CMake version 2.8.11.2 warns when the policy is not set
# and uses OLD behavior.
if(POLICY CMP0020)
	cmake_policy(SET CMP0020 NEW)
endif()

#look for boost library (required for this project)
FIND_PACKAGE( Boost COMPONENTS thread random REQUIRED )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#look for libGL.so (necessary for QtWidgets)
	FIND_PACKAGE(OpenGL REQUIRED)
endif()
#look for qt library (required for this project)
find_package(Qt5Core REQUIRED )
find_package(Qt5Widgets REQUIRED )

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
add_subdirectory(view)

add_executable(mbi ${MBI_SRC})

qt5_use_modules(mbi Core Widgets)



