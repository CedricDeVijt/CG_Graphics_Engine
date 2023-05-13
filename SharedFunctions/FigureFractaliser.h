#ifndef CG_GRAPICS_ENGINE_FIGUREFRACTALISER_H
#define CG_GRAPICS_ENGINE_FIGUREFRACTALISER_H


#include "../Objects/Figure3D.h"

class FigureFractaliser {
public:
    static Figures3D generateFractal(Figure3D &figure, int nrIterations, double fractalScale);

};


#endif //CG_GRAPICS_ENGINE_FIGUREFRACTALISER_H
