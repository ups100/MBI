MESSAGE( "Building gtest target." )

# Locate GTest
find_package(GTest REQUIRED)

# On Windows
#	If GTest was build into static libraries (by default)
#	then there is GTEST_MSVC_SEARCH cmake option defined to different value then MD
#	so VS project properties should be set to Multithread Static library (MT)
if (MSVC AND NOT ${GTEST_MSVC_SEARCH} STREQUAL "MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

# VisualStudio 12 has problems with building GTest 1.7.0 (release 18 Sep 2013)
# There is official bugfix on GTest trunk - revision r675 (date: 13 Jan 2014)
#   but this bugfix waits for new GTest release
# For the time being to build GTest on VS2012 we must define macro 
#   the same macro must be defined in the project
if (MSVC12 OR MSVC11)
	add_definitions(-D_VARIADIC_MAX=10)
endif()

#directories with headers for this target
INCLUDE_DIRECTORIES(    ${QT_INCLUDES}
                        ${MBI_SOURCE_DIR}/algorithm/include
                        ${MBI_SOURCE_DIR}/tests/include
                        ${GTEST_INCLUDE_DIRS}
)
SET( GTEST_SRC
       ${MBI_SOURCE_DIR}/tests/src/main.cpp
       ${MBI_SOURCE_DIR}/tests/src/BLOSUMAlgorithmTest.cpp
       ${MBI_SOURCE_DIR}/tests/src/TestCaseRepresentation.cpp
)

add_executable( test ${GTEST_SRC} )

#here add some additional qt modules
TARGET_LINK_LIBRARIES( test
        ${QT_LIBRARIES}
        ${GTEST_LIBRARIES}
	#pthread
)

# Link pthread.lib only if it isn't WINDOWS system
if (NOT WIN32)
	TARGET_LINK_LIBRARIES( test
		pthread )
endif()

qt5_use_modules(test Core Widgets)
