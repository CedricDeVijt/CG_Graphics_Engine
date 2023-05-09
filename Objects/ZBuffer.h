#ifndef CG_GRAPICS_ENGINE_ZBUFFER_H
#define CG_GRAPICS_ENGINE_ZBUFFER_H


#include <vector>
#include "vector3d.h"

class ZBuffer : public std::vector<std::vector<double> > {
public:
    ZBuffer(int width, int height);

    bool isCloser(unsigned int x0, unsigned int y0, unsigned int z0, unsigned int x1, unsigned int y1, unsigned int z1,
             unsigned int xi, unsigned int yi);

private:
    double interpolate(double z0, double z1, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int xi, unsigned int yi);
//    double getZInterpolationValue();

    std::vector<std::vector<double>> zBuffer;
};


#endif //CG_GRAPICS_ENGINE_ZBUFFER_H
