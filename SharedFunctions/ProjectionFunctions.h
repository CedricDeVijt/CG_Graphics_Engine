#ifndef CG_GRAPICS_ENGINE_PROJECTIONFUNCTIONS_H
#define CG_GRAPICS_ENGINE_PROJECTIONFUNCTIONS_H


#include "../objects/Figure3D.h"
#include "../objects/Line2D.h"

class ProjectionFunctions {
public:
    static Lines2D doProjection(const Figures3D &figures);
    static Point2D doProjection(const Vector3D &point, const double d);


};


#endif //CG_GRAPICS_ENGINE_PROJECTIONFUNCTIONS_H
