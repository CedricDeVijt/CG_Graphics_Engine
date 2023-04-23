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
		l_parser.cc
		l_parser.h

		objects/Line2D.cpp
		objects/Line2D.h
		objects/LineColor.h
		objects/Point2D.cpp
		objects/Point2D.h
		objects/Face3D.h
		objects/Face3D.cpp
		objects/Figure3D.h
		objects/Figure3D.cpp
		objects/vector3d.h
		objects/vector3d.cc
		objects/TransformationMatrix.cpp
		objects/TransformationMatrix.h

		2DLSystem/LSystem2D.cpp
		2DLSystem/LSystem2D.h

		3DLinedrawings/Linedrawing3D.h
		3DLinedrawings/Linedrawing3D.cpp
		3DLinedrawings/Linedrawing3DFigureParser.cpp
		3DLinedrawings/Linedrawing3DFigureParser.h

		3DWireframeFigureDrawings/WireframeFigureDrawing3D.cpp
		3DWireframeFigureDrawings/WireframeFigureDrawing3D.h
		3DWireframeFigureDrawings/WireframeFigureDrawing3DParser.cpp
		3DWireframeFigureDrawings/WireframeFigureDrawing3DParser.h
        SharedFunctions/ProjectionFunctions.cpp SharedFunctions/ProjectionFunctions.h SharedFunctions/ImageSize.cpp SharedFunctions/ImageSize.h SharedFunctions/ScaleLines.cpp SharedFunctions/ScaleLines.h SharedFunctions/DrawLines.cpp SharedFunctions/DrawLines.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
