#ifndef CG_GRAPICS_ENGINE_TRANSFORMATIONMATRIX_H
#define CG_GRAPICS_ENGINE_TRANSFORMATIONMATRIX_H

#include <cmath>
#include "vector3d.h"

class TransformationMatrix {
public:
    static Matrix scaleFigure(const double &scale);
    static Matrix translateFigure(const Vector3D &vector);

    static Matrix rotateX(const double &angle);
    static Matrix rotateY(const double &angle);
    static Matrix rotateZ(const double &angle);

    static Matrix eyePointTransformation(const Vector3D &eyepoint);

    static Matrix linedrawing3DTransformation(const double &scale, const double &angleX, const double &angleY, const double &angleZ, const Vector3D &center, const Vector3D& eye);
    static Matrix ZBufferTransformation(const double &scale, const double &angleX, const double &angleY, const double &angleZ, const Vector3D &center, Vector3D eye);
};


#endif //CG_GRAPICS_ENGINE_TRANSFORMATIONMATRIX_H
