#ifndef CG_GRAPICS_ENGINE_ZBUFFERPARSER_H
#define CG_GRAPICS_ENGINE_ZBUFFERPARSER_H


#include "../BaseFiles/ini_configuration.h"
#include "../BaseFiles/easy_image.h"

class ZBufferParser {
    static img::EasyImage parseZBuffer(const ini::Configuration &configuration);

};


#endif //CG_GRAPICS_ENGINE_ZBUFFERPARSER_H
