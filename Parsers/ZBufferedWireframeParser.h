#ifndef CG_GRAPICS_ENGINE_ZBUFFEREDWIREFRAMEPARSER_H
#define CG_GRAPICS_ENGINE_ZBUFFEREDWIREFRAMEPARSER_H


#include "../BaseFiles/easy_image.h"
#include "../BaseFiles/ini_configuration.h"
#include "../Objects/Figure3D.h"

class ZBufferedWireframeParser {

public:
    static img::EasyImage parseZBufferedWireframe(const ini::Configuration &configuration);
};


#endif //CG_GRAPICS_ENGINE_ZBUFFEREDWIREFRAMEPARSER_H
