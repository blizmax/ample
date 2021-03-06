cmake_minimum_required(VERSION 3.3)

project(ample-gui)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17 -fPIC -lstdc++fs")

set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_INCLUDE_DIRS /usr/include/SDL2/)

set(GLEW_LIBRARY /usr/lib/x86_64-linux-gnu/libGLEW.so.2.0.0)

include_directories(include)
include_directories(../extern/imgui/)
include_directories(../extern/imgui-filebrowser/)
include_directories(../extern/rapidjson/include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(../core/include)
include_directories(../extern/imnodes/)

set(IMGUI_SOURCES
    ../extern/imgui/imgui.cpp
    ../extern/imgui/imgui_draw.cpp
    ../extern/imgui/imgui_demo.cpp
    ../extern/imgui/imgui_widgets.cpp
    ../extern/imgui_sdl/imgui_sdl.cpp
    ../extern/imgui/examples/imgui_impl_opengl3.cpp
    ../extern/imgui/examples/imgui_impl_sdl.cpp
    ../extern/imnodes/imnodes.cpp
   )

set(SOURCES
    src/main.cpp
    src/ImguiActivity.cpp
    src/AmpleGui.cpp
    src/Observer.cpp
    src/InterfaceUnit.cpp
    src/Editor.cpp
    src/Browser.cpp
    src/TextureManager.cpp
    src/StateMachineEditor.cpp
    src/LevelEditor.cpp
    src/ObjectConstructor.cpp
    src/LevelBrowser.cpp
    src/ObjectStorageGui.cpp
    src/StateMachineBrowser.cpp
    src/Utils.cpp

    src/objects/GraphicalEdgeGui.cpp
    src/objects/GraphicalPolygonGui.cpp
    src/objects/GraphicalObjectGui.cpp
    src/objects/GraphicalObject2dGui.cpp
    src/objects/LevelGui.cpp
    src/objects/SliceGui.cpp
    src/objects/ObjectGui.cpp
    src/objects/StateMachineGui.cpp
    src/objects/WorldObjectGui.cpp
    src/objects/TextureGui.cpp
    src/objects/TimerTransitionGui.cpp
    src/objects/CollisionTransitionGui.cpp
    src/objects/KeyboardTransitionGui.cpp
    src/objects/StateGui.cpp
    src/objects/ActionGui.cpp
    src/objects/TransitionGui.cpp
    src/objects/GraphicalRotateActionGui.cpp
    src/objects/PhysicalApplyForceActionGui.cpp
    src/objects/FollowObjectActionGui.cpp
    src/objects/CameraTranslateActionGui.cpp
    )

add_executable(ample-gui ${SOURCES} ${IMGUI_SOURCES})

target_link_libraries(ample-gui ${SDL2_LIBRARY})
target_link_libraries(ample-gui ${GLEW_LIBRARY})
target_link_libraries(ample-gui ample)
