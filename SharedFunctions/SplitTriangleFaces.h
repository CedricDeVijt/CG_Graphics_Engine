#ifndef CG_GRAPICS_ENGINE_SPLITTRIANGLEFACES_H
#define CG_GRAPICS_ENGINE_SPLITTRIANGLEFACES_H


#include <utility>
#include "../Objects/Face3D.h"

class SplitTriangleFaces {
public:
    static std::pair<std::vector<Face3D>, std::vector<Vector3D>> splitFaces(const std::vector<Face3D> &faces, const std::vector<Vector3D> &points, const int &splitAmount);
};


#endif //CG_GRAPICS_ENGINE_SPLITTRIANGLEFACES_H
