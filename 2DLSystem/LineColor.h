#ifndef ENGINE_LINECOLOR_H
#define ENGINE_LINECOLOR_H
class LineColor{
public:
    double red;
    double green;
    double blue;

    LineColor() = default;

    LineColor(double red, double green, double blue){
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

};
#endif //ENGINE_LINECOLOR_H
