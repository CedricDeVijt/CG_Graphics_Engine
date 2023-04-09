#ifndef ENGINE_V2_LINEDRAWING3D_H
#define ENGINE_V2_LINEDRAWING3D_H


#include "../ini_configuration.h"
#include "../easy_image.h"
#include "../objects/vector3d.h"
#include "../objects/Figure3D.h"
#include "../objects/TransformationMatrix.h"
#include "../objects/Line2D.h"

class Linedrawing3D {
public:
    Linedrawing3D(const ini::Configuration &configuration);

    // getter
    const img::EasyImage &getImage() const;

private:
    img::EasyImage image;

    double x_max;
    double y_max;
    double x_min;
    double y_min;

    static Lines2D doProjection(const Figures3D &figure);
    static Point2D doProjection(const Vector3D &point, const double d);


    std::vector<int> getImageSize(Lines2D lines, int size);

    void draw2DLines(Lines2D lines);

    void scale2DLines(Lines2D &lines, const std::vector<int> imageSize) const;

    Lines2D doProjection(const Figure3D &figure);
};


#endif //ENGINE_V2_LINEDRAWING3D_H
