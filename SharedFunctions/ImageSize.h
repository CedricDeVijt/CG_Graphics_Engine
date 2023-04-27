#ifndef CG_GRAPICS_ENGINE_IMAGESIZE_H
#define CG_GRAPICS_ENGINE_IMAGESIZE_H


#include "../Objects/Line2D.h"

class ImageSize {
public:
    static std::vector<int> getImageSize(Lines2D lines, int size, double &x_min, double &x_max, double &y_min, double &y_max);
};


#endif //CG_GRAPICS_ENGINE_IMAGESIZE_H
