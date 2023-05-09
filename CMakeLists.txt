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
		engine.cc

		BaseFiles/easy_image.cc
		BaseFiles/ini_configuration.cc
		BaseFiles/l_parser.cc
		BaseFiles/l_parser.h

		Objects/Line2D.cpp
		Objects/Line2D.h
        Objects/Point2D.cpp
		Objects/Point2D.h
		Objects/Face3D.h
		Objects/Face3D.cpp
		Objects/Figure3D.h
		Objects/Figure3D.cpp
		Objects/vector3d.h
		Objects/vector3d.cc
		Objects/TransformationMatrix.cpp
		Objects/TransformationMatrix.h
		Objects/ZBuffer.cpp
		Objects/ZBuffer.h

        Parsers/LSystem2DParser.cpp
        Parsers/LSystem2DParser.h
		Parsers/ZBufferedWireframeParser.cpp
		Parsers/ZBufferedWireframeParser.h
		Parsers/WireframeParser.cpp
		Parsers/WireframeParser.h
		Parsers/WireframeFigureParser.cpp
		Parsers/WireframeFigureParser.h
		Parsers/WireframeFigureParser.cpp
		Parsers/WireframeFigureParser.h

        SharedFunctions/ProjectionFunctions.cpp
		SharedFunctions/ProjectionFunctions.h
		SharedFunctions/ImageSize.cpp
		SharedFunctions/ImageSize.h
		SharedFunctions/ScaleLines.cpp
		SharedFunctions/ScaleLines.h
		SharedFunctions/DrawLines.cpp
		SharedFunctions/DrawLines.h
		SharedFunctions/LSystemFunctions.cpp
		SharedFunctions/LSystemFunctions.h
		SharedFunctions/SplitTriangleFaces.cpp
		SharedFunctions/SplitTriangleFaces.h
        Parsers/ZBufferParser.cpp Parsers/ZBufferParser.h Objects/PlatonicFigure.cpp Objects/PlatonicFigure.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
