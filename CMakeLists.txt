cmake_minimum_required(VERSION 3.5)

project(CG_Grapics_Engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
	easy_image.cc
	engine.cc
	ini_configuration.cc
		l_parser.cc l_parser.h 2DLSystem/Line2D.cpp 2DLSystem/Line2D.h 2DLSystem/LineColor.h 2DLSystem/Point2D.cpp 2DLSystem/Point2D.h 2DLSystem/LSystem2D.cpp 2DLSystem/LSystem2D.h 3DLinedrawings/Face3D.h 3DLinedrawings/Face3D.cpp 3DLinedrawings/Figure3D.h 3DLinedrawings/Figure3D.cpp 3DLinedrawings/vector3d.h 3DLinedrawings/vector3d.cc 3DLinedrawings/Linedrawing3D.h 3DLinedrawings/Linedrawing3D.cpp)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
