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
GraphicsCommand.h 
GraphicsScene.h 
Model.h 
ModelWall.h 
QGraphicsItemWall.h 
UndoRedoStack.h 
Updatable.h 
View2D.h 
View2DState.h
View3D.h 
Wires3DPlanningKit.h 
ModelSocket.h
QGraphicsItemSocket.h
SecondView2D.h
Controller.h
)

SET(SOURCE 
AddSocket2DState.cpp
AddSocketCommand.cpp
AddWall2DState.cpp
AddWallCommand.cpp
GraphicsCommand.cpp 
GraphicsScene.cpp 
Model.cpp 
ModelWall.cpp 
QGraphicsItemWall.cpp 
UndoRedoStack.cpp 
View2D.cpp
View2DState.cpp 
View3D.cpp 
Wires3DPlanningKit.cpp 
ModelSocket.cpp
SecondView2D.cpp
QGraphicsItemSocket.cpp
Controller.cpp
main.cpp 
)

add_executable(Wires3DPlanningKit ${HEADERS} ${SOURCE})

INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES( Wires3DPlanningKit ${Qt5Widgets_LIBRARIES} )
