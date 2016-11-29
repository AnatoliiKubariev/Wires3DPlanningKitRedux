cmake_minimum_required(VERSION 3.0)
project( Wires3DPlanningKit )

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
)

add_executable(Wires3DPlanningKit ${HEADERS} ${SOURCE})

INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES( Wires3DPlanningKit ${Qt5Widgets_LIBRARIES} )
