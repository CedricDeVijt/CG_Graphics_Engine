#include <numeric>
#include <cmath>
#include "PlatonicFigure.h"
#include "../SharedFunctions/TriangulateFace.h"

Figure3D PlatonicFigure::createCube(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                    const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));
    points.emplace_back(Vector3D::point(1, 1, -1));
    points.emplace_back(Vector3D::point(-1, -1, -1));
    points.emplace_back(Vector3D::point(1, -1, 1));
    points.emplace_back(Vector3D::point(-1, 1, 1));

    // Faces
    faces.emplace_back(Face3D({0, 4, 2, 6}));
    faces.emplace_back(Face3D({4, 1, 7, 2}));
    faces.emplace_back(Face3D({1, 5, 3, 7}));
    faces.emplace_back(Face3D({5, 0, 6, 3}));
    faces.emplace_back(Face3D({6, 2, 7, 3}));
    faces.emplace_back(Face3D({0, 5, 1, 4}));

    return {faces, points, rotations, scale, center, color};;
}

Figure3D
PlatonicFigure::createTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                  const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));

    // Faces
    faces.emplace_back(Face3D({0, 1, 2}));
    faces.emplace_back(Face3D({1, 3, 2}));
    faces.emplace_back(Face3D({0, 3, 1}));
    faces.emplace_back(Face3D({0, 2, 3}));

    return {faces, points, rotations, scale, center, color};
}

Figure3D
PlatonicFigure::createOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                 const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(1, 0, 0));
    points.emplace_back(Vector3D::point(0, 1, 0));
    points.emplace_back(Vector3D::point(-1, 0, 0));
    points.emplace_back(Vector3D::point(0, -1, 0));
    points.emplace_back(Vector3D::point(0, 0, -1));
    points.emplace_back(Vector3D::point(0, 0, 1));

    // Faces
    faces.emplace_back(Face3D({0, 1, 5}));
    faces.emplace_back(Face3D({1, 2, 5}));
    faces.emplace_back(Face3D({2, 3, 5}));
    faces.emplace_back(Face3D({3, 0, 5}));
    faces.emplace_back(Face3D({1, 0, 4}));
    faces.emplace_back(Face3D({2, 1, 4}));
    faces.emplace_back(Face3D({3, 2, 4}));
    faces.emplace_back(Face3D({0, 3, 4}));


    return {faces, points, rotations, scale, center, color};
}

Figure3D
PlatonicFigure::createIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                  const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(0, 0, (sqrt(5)) / 2));
    for (int i = 1; i < 6; ++i) {
        points.emplace_back(Vector3D::point(cos((i - 2) * 2 * M_PI / 5), sin((i - 2) * 2 * M_PI / 5), 0.5));
    }
    for (int i = 6; i < 11; ++i) {
        points.emplace_back(
                Vector3D::point(cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5), sin(M_PI / 5 + (i - 7) * 2 * M_PI / 5), -0.5));
    }
    points.emplace_back(Vector3D::point(0, 0, -sqrt(5) / 2));

    // Faces
    faces.emplace_back(Face3D({0, 1, 2}));
    faces.emplace_back(Face3D({0, 2, 3}));
    faces.emplace_back(Face3D({0, 3, 4}));
    faces.emplace_back(Face3D({0, 4, 5}));
    faces.emplace_back(Face3D({0, 5, 1}));
    faces.emplace_back(Face3D({1, 6, 2}));
    faces.emplace_back(Face3D({2, 6, 7}));
    faces.emplace_back(Face3D({2, 7, 3}));
    faces.emplace_back(Face3D({3, 7, 8}));
    faces.emplace_back(Face3D({3, 8, 4}));
    faces.emplace_back(Face3D({4, 8, 9}));
    faces.emplace_back(Face3D({4, 9, 5}));
    faces.emplace_back(Face3D({5, 9, 10}));
    faces.emplace_back(Face3D({5, 10, 1}));
    faces.emplace_back(Face3D({1, 10, 6}));
    faces.emplace_back(Face3D({11, 7, 6}));
    faces.emplace_back(Face3D({11, 8, 7}));
    faces.emplace_back(Face3D({11, 9, 8}));
    faces.emplace_back(Face3D({11, 10, 9}));
    faces.emplace_back(Face3D({11, 6, 10}));


    return {faces, points, rotations, scale, center, color};
}

Figure3D
PlatonicFigure::createDodecahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    Figure3D icosahedron = createIcosahedron({0, 0, 0}, 1, Vector3D::vector(0, 0, 0), color);
    for (const Face3D &face: icosahedron.faces) {
        double x = (icosahedron.points[face.point_indexes[0]].x +
                    icosahedron.points[face.point_indexes[1]].x +
                    icosahedron.points[face.point_indexes[2]].x) / 3;

        double y = (icosahedron.points[face.point_indexes[0]].y +
                    icosahedron.points[face.point_indexes[1]].y +
                    icosahedron.points[face.point_indexes[2]].y) / 3;

        double z = (icosahedron.points[face.point_indexes[0]].z +
                    icosahedron.points[face.point_indexes[1]].z +
                    icosahedron.points[face.point_indexes[2]].z) / 3;

        points.push_back(Vector3D::point(x, y, z));
    }

    // Faces
    faces.emplace_back(Face3D({0, 1, 2, 3, 4}));
    faces.emplace_back(Face3D({0, 5, 6, 7, 1}));
    faces.emplace_back(Face3D({1, 7, 8, 9, 2}));
    faces.emplace_back(Face3D({2, 9, 10, 11, 3}));
    faces.emplace_back(Face3D({3, 11, 12, 13, 4}));
    faces.emplace_back(Face3D({4, 13, 14, 5, 0}));
    faces.emplace_back(Face3D({19, 18, 17, 16, 15}));
    faces.emplace_back(Face3D({19, 14, 13, 12, 18}));
    faces.emplace_back(Face3D({18, 12, 11, 10, 17}));
    faces.emplace_back(Face3D({17, 10, 9, 8, 16}));
    faces.emplace_back(Face3D({16, 8, 7, 6, 15}));
    faces.emplace_back(Face3D({15, 6, 5, 14, 19}));

    return {faces, points, rotations, scale, center, color};
}

Figure3D
PlatonicFigure::createCylinder(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                               const img::Color &color, const int &n, const double &height) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    for (int i = 0; i < n; ++i) {
        points.push_back(Vector3D::point(cos(2 * i * M_PI / n), sin(2 * i * M_PI / n), height));
        points.push_back(Vector3D::point(cos(2 * i * M_PI / n), sin(2 * i * M_PI / n), 0));
    }

    // Faces
    for (int i = 0; i < n; ++i) {
        faces.push_back(Face3D({2 * i, 2 * i + 1, (2 * i + 3) % (2 * n), (2 * i + 2) % (2 * n)}));
    }
    std::vector<int> topFace;
    std::vector<int> bottomFace;
    for (int i = 0; i < n; ++i) {
        topFace.push_back(2 * i);
        bottomFace.push_back(2 * i + 1);
    }
    faces.emplace_back(topFace);
    faces.emplace_back(bottomFace);

    return {faces, points, rotations, scale, center, color};
}

Figure3D PlatonicFigure::createCone(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                    const img::Color &color, const int &n, const double &height) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    for (int i = 0; i < n; ++i) {
        points.push_back(Vector3D::point(cos(2 * i * M_PI / n), sin(2 * i * M_PI / n), 0));
    }
    points.emplace_back(Vector3D::point(0, 0, height));

    // Faces
    for (int i = 0; i < n; ++i) {
        faces.emplace_back(Face3D({n, i % n, (i + 1) % n}));
    }
    std::vector<int> topFace;
    for (int i = 0; i < n; ++i) {
        topFace.push_back(i);
    }

    return {faces, points, rotations, scale, center, color};
}

Figure3D PlatonicFigure::createSphere(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                      const img::Color &color, const int &n) {
    if (n == 0) {
        return createIcosahedron(rotations, scale, center, color);
    } else {
        Figure3D icosahedron = createIcosahedron({0, 0, 0}, 1, Vector3D::vector(0, 0, 0), color);

        // Split icosahedron n-times
        std::pair<std::vector<Face3D>, std::vector<Vector3D>> splitFaces = TriangulateFace::splitFaces(
                icosahedron.faces, icosahedron.points, n);

        // Normalize points
        for (Vector3D &point: splitFaces.second) {
            point.normalise();
        }

        return {splitFaces.first, splitFaces.second, rotations, scale, center, color};
    }
}

Figure3D PlatonicFigure::createTorus(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                     const img::Color &color, const double &R, const double &r, const int &n,
                                     const int &m) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;
    // Split tube
    for (int i = 0; i < n; ++i) {
        double u = i * (2 * M_PI / n);
        // Split circle
        for (int j = 0; j < m; ++j) {
            double v = j * (2 * M_PI / m);

            points.emplace_back(Vector3D::point((R + r * cos(v)) * cos(u),
                                                (R + r * cos(v)) * sin(u),
                                                r * sin(v)));

            faces.emplace_back(
                    Face3D({
                                   calculateIndex(i, j, m),
                                   calculateIndex((i + 1) % n, j, m),
                                   calculateIndex((i + 1) % n, (j + 1) % m, m),
                                   calculateIndex(i, (j + 1) % m, m)})
            );
        }
    }

    return {faces, points, rotations, scale, center, color};
}

int PlatonicFigure::calculateIndex(const int &i, const int &j, const int &m) {
    return i * m + j;
}

Figure3D PlatonicFigure::createBuckyBall(const std::vector<double> &rotations, const double &scale, const Vector3D& center, img::Color color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Buckyball uses icosahedron as base, each face is split up in three triangles and one hexagon
    Figure3D icosahedron = createIcosahedron({0, 0, 0}, 1, Vector3D::vector(0, 0, 0), color);

    // Split all faces in three triangles and one hexagon
    for (int i = 0; i < icosahedron.faces.size(); ++i) {

    }

    // Return Figure3D
    return {faces, points, rotations, scale, center, color};
}

Figure3D PlatonicFigure::createMengerSponge(const std::vector<double> &rotations, const double &scale, Vector3D center,
                                            img::Color color) {
    return {};
}

