#ifndef COMPUTERGRAPICS_ENGINE_FACE_H
#define COMPUTERGRAPICS_ENGINE_FACE_H


#include <vector>
#include "vector3d.h"
#include "../2DLSystem/Point2D.h"

class Face3D {
public:
    // Constructor
    Face3D(const std::vector<int> &point_indexes);

    // Getters
    std::vector<Point2D> doProjection();

    std::vector<int> point_indexes;
};
#endif //COMPUTERGRAPICS_ENGINE_FACE_H
