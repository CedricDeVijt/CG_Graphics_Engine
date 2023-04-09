#ifndef ENGINE_V2_LSYSTEM2D_H
#define ENGINE_V2_LSYSTEM2D_H


#include <vector>
#include "../easy_image.h"
#include "../l_parser.h"
#include "../objects/Line2D.h"


class LSystem2D {
public:
    // constructor
    LSystem2D(int size, std::vector<int> backgroundcolor, std::string inputfile, std::vector<double>& color);

    // getter
    img::EasyImage getImage() const;

private:
    Lines2D systemLines;
    img::EasyImage image;

    img::Color color;

    double x_max;
    double y_max;
    double x_min;
    double y_min;


    // getters
    static LParser::LSystem2D getLSystem2D(const std::string& inputfile);
    std::string getString(const LParser::LSystem2D& parseSystem);
    Lines2D get2DLines(const LParser::LSystem2D& parsedSystem, const std::string& systemString, const std::vector<double> &color);
    std::vector<int> getImageSize(int size);

    // other
    void transform2DLines();
    void draw2DLines(const img::Color& lineColor);

};


#endif //ENGINE_V2_LSYSTEM2D_H
