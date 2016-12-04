cmake_minimum_required(VERSION 3.0)
project( Wires3DPlanningKit )


set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
set(OGRE_SAMPLES_INCLUDEPATH $ENV{OGRE_HOME}/Samples/include)

set(Boost_USE_STATIC_LIBS TRUE)

find_package(Boost REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(HEADERS 
AddSocket2DState.h
AddSocketCommand.h
AddWall2DState.h
AddWallCommand.h
Controller.h
GraphicsCommand.h 
GraphicsScene.h 
Model.h 
ModelSocket.h
ModelWall.h 
QGraphicsItemSocket.h
QGraphicsItemWall.h 
SecondView2D.h
UndoRedoStack.h 
Updatable.h 
View2D.h 
View2DState.h
View3D.h 
Wires3DPlanningKit.h 
View3DCamera.h
)

SET(SOURCE 
AddSocket2DState.cpp
AddSocketCommand.cpp
AddWall2DState.cpp
AddWallCommand.cpp
Controller.cpp
GraphicsCommand.cpp 
GraphicsScene.cpp 
Model.cpp 
ModelSocket.cpp
ModelWall.cpp 
QGraphicsItemSocket.cpp
QGraphicsItemWall.cpp 
SecondView2D.cpp
UndoRedoStack.cpp 
Utility.cpp
Utility.h
View2D.cpp
View2DState.cpp 
View3D.cpp 
Wires3DPlanningKit.cpp 
main.cpp 
View3DCamera.cpp
)

add_executable(Wires3DPlanningKit ${HEADERS} ${SOURCE})

include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${OIS_INCLUDE_DIRS}
	                 ${OGRE_INCLUDE_DIRS}
					 ${OGRE_SAMPLES_INCLUDEPATH})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES( Wires3DPlanningKit ${Boost_LIBRARIES} )
target_link_libraries( Wires3DPlanningKit ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
TARGET_LINK_LIBRARIES( Wires3DPlanningKit ${Qt5Widgets_LIBRARIES} )

#add_custom_command( TARGET Wires3DPlanningKit POST_BUILD
#                    COMMAND xcopy
#					\"$ENV{OGRE_HOME}/bin/Debug/OgreMain_d.dll\"
#					\"D:/Wires3DPlanningKitRedux_build/Wires3DPlanningKit/Debug/OgreMain_d.dll\" /Y)