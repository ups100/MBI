MESSAGE( "Building view target." )

# Eliminate a warning when building in Windows that relates
# to static linking of Qt executables to qtmain.lib.
# This policy was introduced in CMake version 2.8.11.
# CMake version 2.8.11.2 warns when the policy is not set
# and uses OLD behavior.
if(POLICY CMP0020)
	cmake_policy(SET CMP0020 NEW)
endif()

#look for qt library (required for this project)
find_package(Qt5Core REQUIRED )
find_package(Qt5Widgets REQUIRED )

# compile Qt resource file (images in this project)
qt5_add_resources(UI_RESOURCES AppResources.qrc)
# compile GUI from QtDesigner .ui files
qt5_wrap_ui(	UI_HEADERS 
				${MBI_SOURCE_DIR}/view/ui/infoview.ui
				${MBI_SOURCE_DIR}/view/ui/mainwindow.ui
				${MBI_SOURCE_DIR}/view/ui/resultwindow.ui
				${MBI_SOURCE_DIR}/view/ui/seqinputview.ui
				${MBI_SOURCE_DIR}/view/ui/tableview.ui
)

# preparing only path from filepath to UI headers list (orginally contains also file names)
list(GET UI_HEADERS 0 UI_HEADERS_FIRST) #get one list element (first is good)
get_filename_component( UI_HEADERS_PATH ${UI_HEADERS_FIRST} PATH) #extract only path - remove file name

#subdirectories
INCLUDE_DIRECTORIES(	${QT_INCLUDES}
						${UI_HEADERS} #list of UI headers files
						${UI_HEADERS_PATH} #path to UI headers directory
						${MBI_SOURCE_DIR}/algorithm/include 
						${MBI_SOURCE_DIR}/view/include
)

SET( VIEW_SRC
		${MBI_SOURCE_DIR}/view/src/main.cpp
		${MBI_SOURCE_DIR}/view/src/infoview.cpp
		${MBI_SOURCE_DIR}/view/src/mainwindow.cpp
		${MBI_SOURCE_DIR}/view/src/resultwindow.cpp
		${MBI_SOURCE_DIR}/view/src/seqinputview.cpp
		${MBI_SOURCE_DIR}/view/src/tableabstract.cpp
		${MBI_SOURCE_DIR}/view/src/tableplainview.cpp
		${MBI_SOURCE_DIR}/view/src/tableview.cpp
		${MBI_SOURCE_DIR}/view/include/infoview.h
		${MBI_SOURCE_DIR}/view/include/mainwindow.h
		${MBI_SOURCE_DIR}/view/include/resultwindow.h
		${MBI_SOURCE_DIR}/view/include/seqinputview.h
		${MBI_SOURCE_DIR}/view/include/tableabstract.h
		${MBI_SOURCE_DIR}/view/include/tableplainview.h
		${MBI_SOURCE_DIR}/view/include/tableview.h
)

# This variable is used on Visual Studio to hide console when application is running.
SET( WIN_NO_CONSOLE "")
IF (WIN32)
	SET( WIN_NO_CONSOLE WIN32 )
ENDIF (WIN32)

add_executable( view ${WIN_NO_CONSOLE} ${VIEW_SRC} ${UI_RESOURCES} ${UI_HEADERS} )

#here add some additional qt modules
TARGET_LINK_LIBRARIES( view
        ${QT_LIBRARIES}
)

qt5_use_modules(view Core Widgets)
