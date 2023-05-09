#include "ZBuffer.h"
#include <limits>

ZBuffer::ZBuffer(const int width, const int height) {
    zBuffer = std::vector<std::vector<double>>(width, std::vector<double>(height, std::numeric_limits<double>::infinity()));
}

bool ZBuffer::isCloser(unsigned int x0, unsigned int y0, unsigned int z0, unsigned int x1, unsigned int y1, unsigned int z1,
                  unsigned int xi, unsigned int yi) {
    double inv_z = 1.0 / interpolate(z0, z1, x0, y0, x1, y1, xi, yi); // Calculate the 1/z value of the current point
    if (inv_z < zBuffer[xi][yi]) { // Check if the current point is closer to the origin than the value in the z-buffer
        zBuffer[xi][yi] = inv_z; // Update the z-buffer with the closer 1/z value
        return true;
    } else {
        return false;
    }
//    double zBufferValue = zBuffer[xi][yi];
//    double zValue = round(((xi-x0)/(x1-x0)*(z1-z0) +z0));
//
//    if (zValue < zBufferValue){
//        zBufferValue = zValue;
//        return true;
//    } else {
//        return false;
//    }
}

double ZBuffer::interpolate(double z0, double z1, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int xi, unsigned int yi) {
    double dx = x1 - x0;
    double dy = y1 - y0;
    double dz = z1 - z0;
    double delta_x = xi - x0;
    double delta_y = yi - y0;
    double dist = std::sqrt(dx*dx + dy*dy);
    double interp_z = z0 + (delta_x*dx + delta_y*dy) / dist * dz;
    return interp_z;
}
