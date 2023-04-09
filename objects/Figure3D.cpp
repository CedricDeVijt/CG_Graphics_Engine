#include "Figure3D.h"
#include "TransformationMatrix.h"


Figure3D::Figure3D(const std::vector<Face3D> &faces, const std::vector<Vector3D> &points, std::vector<int> rotations,
                   double scale, Vector3D center, img::Color color) : faces(faces), points(points), center(center), scale(scale), color(color){
    rotateX = rotations[0];
    rotateY = rotations[1];
    rotateZ = rotations[2];
}

const img::Color &Figure3D::getColor() const {
    return color;
}

void Figure3D::applyTransformation(const Matrix& transformationMatrix) {
    for (auto &point : points){
        point = point * transformationMatrix;
    }
}

int Figure3D::getRotateX() const {
    return rotateX;
}

int Figure3D::getRotateY() const {
    return rotateY;
}

int Figure3D::getRotateZ() const {
    return rotateZ;
}

double Figure3D::getScale() const {
    return scale;
}

const Vector3D &Figure3D::getCenter() const {
    return center;
}
