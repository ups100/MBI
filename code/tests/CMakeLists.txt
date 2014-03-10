MESSAGE( "Building gtest target." )

# Locate GTest
find_package(GTest REQUIRED)

#directories with headers for this target
INCLUDE_DIRECTORIES(    ${QT_INCLUDES}
                        ${MBI_SOURCE_DIR}/algorithm/include
                        ${MBI_SOURCE_DIR}/tests/include
                        ${GTEST_INCLUDE_DIRS}
)
SET( GTEST_SRC
       ${MBI_SOURCE_DIR}/tests/src/main.cpp
       ${MBI_SOURCE_DIR}/tests/src/BLOSUMAlgorithmTest.cpp
)

add_executable( test ${GTEST_SRC} )

#here add some additional qt modules
TARGET_LINK_LIBRARIES( test
        ${QT_LIBRARIES}
        ${GTEST_LIBRARIES}
	pthread
)

qt5_use_modules(test Core)
