#include "Figure3D.h"
#include "TransformationMatrix.h"


Figure3D::Figure3D(const std::vector<Face3D> &faces, const std::vector<Vector3D> &points, std::vector<int> rotations,
                   double scale, Vector3D center, img::Color color) : faces(faces), points(points), center(center), scale(scale), color(color){
    rotateX = rotations[0];
    rotateY = rotations[1];
    rotateZ = rotations[2];
}

void Figure3D::applyTransformation(Vector3D eye) {
    Matrix combinedMatrix = TransformationMatrix::linedrawing3DTransformation(scale, rotateX, rotateY, rotateZ, center, eye);

    for (auto &point : points){
        point = point * combinedMatrix;
    }
}

const img::Color &Figure3D::getColor() const {
    return color;
}
