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
    Figure3D(ini::Section figure);

private:
    std::string type;
    int rotateX;
    int rotateY;
    int rotateZ;
    int scale;

    std::vector<int> center;

    std::vector<Vector3D> points;
    std::vector<Face3D> faces;
    img::Color color;
};

typedef std::list<Figure3D> Figures3D;

#endif //ENGINE_V2_FIGURE3D_H
