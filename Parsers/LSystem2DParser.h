#ifndef CG_GRAPICS_ENGINE_LSYSTEM2DPARSER_H
#define CG_GRAPICS_ENGINE_LSYSTEM2DPARSER_H


#include "../BaseFiles/ini_configuration.h"
#include "../BaseFiles/easy_image.h"
#include "../BaseFiles/l_parser.h"
#include "../Objects/Line2D.h"

class LSystem2DParser {
public:
    static img::EasyImage parse2DLSystem(const ini::Configuration &configuration);

private:
    // getters
    static LParser::LSystem2D getLSystem2D(const std::string& inputfile);
    static std::string getString(const LParser::LSystem2D& parseSystem);
    static Lines2D get2DLines(const LParser::LSystem2D& parsedSystem, const std::string& systemString, const img::Color &lineColor);
};


#endif //CG_GRAPICS_ENGINE_LSYSTEM2DPARSER_H
