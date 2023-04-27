#ifndef CG_GRAPICS_ENGINE_PROJECTIONFUNCTIONS_H
#define CG_GRAPICS_ENGINE_PROJECTIONFUNCTIONS_H


#include "../Objects/Figure3D.h"
#include "../Objects/Line2D.h"

class ProjectionFunctions {
public:
    static Lines2D doProjection(const Figures3D &figures);
    static Point2D doProjection(const Vector3D &point, double d);


};


#endif //CG_GRAPICS_ENGINE_PROJECTIONFUNCTIONS_H
