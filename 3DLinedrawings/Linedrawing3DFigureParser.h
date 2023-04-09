#ifndef CG_GRAPICS_ENGINE_LINEDRAWING3DFIGUREPARSER_H
#define CG_GRAPICS_ENGINE_LINEDRAWING3DFIGUREPARSER_H


#include "../objects/Figure3D.h"

class Linedrawing3DFigureParser {
public:
    static Figure3D parseLinedrawing3D(const ini::Section& figure);
};


#endif //CG_GRAPICS_ENGINE_LINEDRAWING3DFIGUREPARSER_H
