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
    explicit Figure3D(const ini::Section& figure);

    const img::Color &getColor() const;

    // Setters
    void applyTransformation(Vector3D eye);

    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

private:

    std::string type;
    int rotateX;
    int rotateY;
    int rotateZ;
    double scale;
    Vector3D center;

    int nrPoints{};

    int nrLines{};

    img::Color color;

    // Getters
    void getSection(const ini::Section &figure);
    void getPoints(const ini::Section &figure);
    void getFaces(const ini::Section &figure);

};

typedef std::list<Figure3D> Figures3D;

#endif //ENGINE_V2_FIGURE3D_H
