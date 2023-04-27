#ifndef CG_GRAPICS_ENGINE_SCALELINES_H
#define CG_GRAPICS_ENGINE_SCALELINES_H


#include <vector>
#include "../Objects/Line2D.h"

class ScaleLines {
public:
    static void scale2DLines(Lines2D &lines, std::vector<int> imageSize, const double &x_min, const double &x_max, const double &y_min, const double &y_max);

};


#endif //CG_GRAPICS_ENGINE_SCALELINES_H
