#ifndef CG_GRAPICS_ENGINE_DRAWLINES_H
#define CG_GRAPICS_ENGINE_DRAWLINES_H


#include <cmath>
#include "../Objects/Line2D.h"


class DrawLines {
public:
    static void draw2DLines(img::EasyImage &image, const Lines2D& lines);
};


#endif //CG_GRAPICS_ENGINE_DRAWLINES_H
