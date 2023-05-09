#ifndef CG_GRAPICS_ENGINE_IMAGEDRAWER_H
#define CG_GRAPICS_ENGINE_IMAGEDRAWER_H


#include <cmath>
#include "../Objects/Line2D.h"
#include "../Objects/ZBuffer.h"
#include "../Objects/Figure3D.h"


class ImageDrawer {
public:
    static void draw2DLines(img::EasyImage &image, const Lines2D& lines);

    // Z-buffering with lines
    static void drawZBuffer2DLines(img::EasyImage &image, const Lines2D &lines);
    static void draw_zbuf_line(ZBuffer &zbuffer, img::EasyImage &image, unsigned int x0, unsigned int y0, unsigned int z0, unsigned int x1,
                               unsigned int y1, unsigned int z1, img::Color color);

    // Z-buffering with triangles
    static void drawTriangulatedFigures(Figures3D figures);
    static void draw_zbuf_triag(ZBuffer &zBuffer, img::EasyImage &image, Vector3D const& A, Vector3D const& B, Vector3D const& C, double d, double dx, double dy, img::Color color);
};


#endif //CG_GRAPICS_ENGINE_IMAGEDRAWER_H
