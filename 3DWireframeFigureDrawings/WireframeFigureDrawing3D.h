#ifndef CG_GRAPICS_ENGINE_WIREFRAMEFIGUREDRAWING3D_H
#define CG_GRAPICS_ENGINE_WIREFRAMEFIGUREDRAWING3D_H


#include <list>
#include "../ini_configuration.h"
#include "../easy_image.h"
#include "../objects/vector3d.h"
#include "../objects/Figure3D.h"

class WireframeFigureDrawing3D {
public:
    explicit WireframeFigureDrawing3D(const ini::Configuration &configuration);

    const img::EasyImage &getImage() const;

private:
    img::EasyImage image;

    double x_max;
    double y_max;
    double x_min;
    double y_min;

    std::list<Figure3D>getFigures(const ini::Configuration &configuration, Vector3D &eye, int nrFigures) const;
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEFIGUREDRAWING3D_H
