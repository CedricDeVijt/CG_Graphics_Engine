#ifndef ENGINE_V2_LINEDRAWING3D_H
#define ENGINE_V2_LINEDRAWING3D_H


#include "../ini_configuration.h"
#include "../easy_image.h"

class Linedrawing3D {
public:
    Linedrawing3D(const ini::Configuration &configuration);

    // getter
    const img::EasyImage &getImage() const;

private:
    img::EasyImage image;
};


#endif //ENGINE_V2_LINEDRAWING3D_H
