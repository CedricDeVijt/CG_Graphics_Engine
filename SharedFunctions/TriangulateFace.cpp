#include "TriangulateFace.h"

std::pair<std::vector<Face3D>, std::vector<Vector3D>> TriangulateFace::splitFaces(const std::vector<Face3D> &faces, const std::vector<Vector3D> &points, const int &splitAmount) {
    std::vector<Face3D> splitFaces = faces;
    std::vector<Vector3D> splitPoints = points;

    for (int i = 0; i < splitAmount; ++i) {
        std::vector<Face3D> newFaces;

        // Split each face
        for (int j = 0; j < splitFaces.size(); ++j) {
            Face3D face = splitFaces[j];

            // Current point of triangle
            const Vector3D& A = splitPoints[face.point_indexes[0]];
            const Vector3D& B = splitPoints[face.point_indexes[1]];
            const Vector3D& C = splitPoints[face.point_indexes[2]];

            // New split points of triangle
            Vector3D D = Vector3D::point((A.x + B.x)/2,
                                         (A.y + B.y)/2,
                                         (A.z + B.z)/2);
            Vector3D E = Vector3D::point((A.x + C.x)/2,
                                         (A.y + C.y)/2,
                                         (A.z + C.z)/2);
            Vector3D F = Vector3D::point((B.x + C.x)/2,
                                         (B.y + C.y)/2,
                                         (B.z + C.z)/2);

            splitPoints.push_back(D);
            splitPoints.push_back(E);
            splitPoints.push_back(F);

            int Ai = face.point_indexes[0];
            int Bi = face.point_indexes[1];
            int Ci = face.point_indexes[2];
            int Di = splitPoints.size()-3;
            int Ei = splitPoints.size()-2;
            int Fi = splitPoints.size()-1;

            newFaces.push_back(Face3D({Ai, Di, Ei}));
            newFaces.push_back(Face3D({Bi, Fi, Di}));
            newFaces.push_back(Face3D({Ci, Ei, Fi}));
            newFaces.push_back(Face3D({Di, Fi, Ei}));
        }

        splitFaces = newFaces;
    }
    return {splitFaces, splitPoints};
}

void TriangulateFace::triangulateFigures(Figures3D &figures) {
    for (auto &figure : figures){
        std::vector<Face3D> newFaces;
        for (Face3D face : figure.faces){
            if (face.point_indexes.size() <= 3){
                newFaces.push_back(face);
                continue;
            }
            for (int i = 0; i < face.point_indexes.size()-2; ++i) {
                newFaces.push_back(Face3D({face.point_indexes[0], face.point_indexes[i+1], face.point_indexes[i+2]}));
            }
        }
        figure.faces = newFaces;
    }
}
