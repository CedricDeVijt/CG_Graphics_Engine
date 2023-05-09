#ifndef CG_GRAPICS_ENGINE_TRIANGULATEFACE_H
#define CG_GRAPICS_ENGINE_TRIANGULATEFACE_H


#include <utility>
#include "../Objects/Face3D.h"
#include "../Objects/Figure3D.h"

class TriangulateFace {
public:
    static std::pair<std::vector<Face3D>, std::vector<Vector3D>> splitFaces(const std::vector<Face3D> &faces, const std::vector<Vector3D> &points, const int &splitAmount);

    static void triangulateFigures(Figures3D &figures);
    static Figure3D triangulateFigure(const Figure3D &figure);

};


#endif //CG_GRAPICS_ENGINE_TRIANGULATEFACE_H
