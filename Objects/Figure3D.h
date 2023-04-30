#ifndef ENGINE_V2_FIGURE3D_H
#define ENGINE_V2_FIGURE3D_H


#include <vector>
#include <list>
#include "vector3d.h"
#include "Face3D.h"
#include "../easy_image.h"
#include "../ini_configuration.h"

class Figure3D {
public:
    // Constructor
    Figure3D();
    Figure3D(const std::vector<Face3D> &faces, const std::vector<Vector3D> &points, const std::vector<double> &rotations,
             double scale, Vector3D center, img::Color color);

    // Getters
    const img::Color &getColor() const;
    int getRotateX() const;
    int getRotateY() const;
    int getRotateZ() const;
    double getScale() const;
    const Vector3D &getCenter() const;

    // Setters
    void applyTransformation(const Matrix& transformationMatrix);

    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

private:

    std::string type;
    double rotateX;
    double rotateY;
    double rotateZ;
    double scale;
    Vector3D center;

    img::Color color;

};

typedef std::list<Figure3D> Figures3D;

#endif //ENGINE_V2_FIGURE3D_H
