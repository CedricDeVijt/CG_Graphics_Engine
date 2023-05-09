#ifndef CG_GRAPICS_ENGINE_DRAWLINES_H
#define CG_GRAPICS_ENGINE_DRAWLINES_H


#include <cmath>
#include "../Objects/Line2D.h"
#include "../Objects/ZBuffer.h"


class DrawLines {
public:
    static void draw2DLines(img::EasyImage &image, const Lines2D& lines);

    // Z-buffering
    static void drawZBuffer2DLines(img::EasyImage &image, const Lines2D &lines);
    static void draw_zbuf_line(ZBuffer &zbuffer, img::EasyImage &image, unsigned int x0, unsigned int y0, unsigned int z0, unsigned int x1,
                               unsigned int y1, unsigned int z1, img::Color color);
};


#endif //CG_GRAPICS_ENGINE_DRAWLINES_H
