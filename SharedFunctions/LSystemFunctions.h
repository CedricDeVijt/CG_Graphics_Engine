#ifndef CG_GRAPICS_ENGINE_LSYSTEMFUNCTIONS_H
#define CG_GRAPICS_ENGINE_LSYSTEMFUNCTIONS_H


#include <string>
#include "../BaseFiles/l_parser.h"
#include "../Objects/Face3D.h"

class LSystemFunctions {
public:
    static LParser::LSystem3D parseLSystem3D(const std::string &inputfile);

    static std::string getLSystemString(const LParser::LSystem3D &l_system);

    static std::pair<std::vector<Face3D>, std::vector<Vector3D>> getFacesAndPoints(const LParser::LSystem3D &l_system, const std::string &figureString);

};


#endif //CG_GRAPICS_ENGINE_LSYSTEMFUNCTIONS_H
