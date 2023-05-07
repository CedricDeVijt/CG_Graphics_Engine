#ifndef ENGINE_POINT2D_H
#define ENGINE_POINT2D_H

class Point2D{
public:
    double x;
    double y;

    double z1;
    double z2;

    Point2D() = default;

    Point2D(double x, double y){
        this->x = x;
        this->y = y;
    }
    ~Point2D() = default;

    void move_with_offset(const double offset_x, const double offset_y);

};
#endif //ENGINE_POINT2D_H
