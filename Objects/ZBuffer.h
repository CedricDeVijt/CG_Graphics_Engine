#ifndef CG_GRAPICS_ENGINE_ZBUFFER_H
#define CG_GRAPICS_ENGINE_ZBUFFER_H


#include <vector>
#include "vector3d.h"

class ZBuffer : public std::vector<std::vector < double> >{
public:
    ZBuffer(const int width, const int height);

    Matrix zBufferMatrix;
};


#endif //CG_GRAPICS_ENGINE_ZBUFFER_H
