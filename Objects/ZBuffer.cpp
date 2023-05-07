#include "ZBuffer.h"
#include <limits>

ZBuffer::ZBuffer(const int width, const int height) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            zBufferMatrix(i, j) = std::numeric_limits<double>::infinity();
        }
    }
}
