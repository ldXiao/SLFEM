cmake_minimum_required(VERSION 3.1)
project(slfem)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

message(${CMAKE_CURRENT_SOURCE_DIR})



######################################################################
# libigl
#######################################################################
option(LIBIGL_USE_STATIC_LIBRARY "Use libigl as static library" OFF)
option(LIBIGL_WITH_ANTTWEAKBAR       "Use AntTweakBar"    OFF)
option(LIBIGL_WITH_CGAL              "Use CGAL"           OFF)
option(LIBIGL_WITH_COMISO            "Use CoMiso"         OFF)
option(LIBIGL_WITH_CORK              "Use Cork"           OFF)
option(LIBIGL_WITH_EMBREE            "Use Embree"         OFF)
option(LIBIGL_WITH_LIM               "Use LIM"            OFF)
option(LIBIGL_WITH_MATLAB            "Use Matlab"         OFF)
option(LIBIGL_WITH_MOSEK             "Use MOSEK"          OFF)
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGui"          ON)
option(LIBIGL_WITH_PNG               "Use PNG"            OFF)
option(LIBIGL_WITH_PYTHON            "Use Python"         OFF)
option(LIBIGL_WITH_TETGEN            "Use Tetgen"         ON)
option(LIBIGL_WITH_TRIANGLE          "Use Triangle"       ON)
option(LIBIGL_WITH_VIEWER            "Use OpenGL viewer"  ON)
option(LIBIGL_WITH_XML               "Use XML"            OFF)

find_package(LIBIGL REQUIRED QUIET)

######################################################################
# polyfem
######################################################################

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/polyfem polyfem)
file(GLOB SRCFILES src/main.cpp)
add_executable(${PROJECT_NAME}_bin ${SRCFILES}
        src/SturmLiouville.cpp
        src/SturmLiouville.hpp
        src/UIState.cpp
        src/UIMenu.cpp
        src/UIState.cpp
        src/CustomAssemblerUtils.cpp src/CustomAssemblerUtils.hpp src/CustomState.cpp src/CustomState.hpp)



target_link_libraries(${PROJECT_NAME}_bin  igl::core igl::opengl_glfw igl::opengl_glfw_imgui polyfem)
#target_link_libraries(${PROJECT_NAME}_bin  polyfem)

add_executable(${PROJECT_NAME}_test
        src/test.cpp
        src/SturmLiouville.cpp
        src/SturmLiouville.hpp
        )
target_link_libraries(${PROJECT_NAME}_test igl::core igl::opengl_glfw igl::opengl_glfw_imgui polyfem)
