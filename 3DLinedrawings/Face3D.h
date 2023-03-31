#ifndef COMPUTERGRAPICS_ENGINE_FACE_H
#define COMPUTERGRAPICS_ENGINE_FACE_H


#include <vector>

class Face3D {
public:
    Face3D(const std::vector<int> &point_indexes);
    std::vector<int> point_indexes;
};
#endif //COMPUTERGRAPICS_ENGINE_FACE_H
