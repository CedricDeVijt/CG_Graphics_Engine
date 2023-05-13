#include "FigureFractaliser.h"
#include "../Objects/TransformationMatrix.h"

Figures3D FigureFractaliser::generateFractal(Figure3D &figure, int nrIterations, double fractalScale) {
    Figures3D resultingFigures = {figure};

    if (nrIterations == 0) {
        return resultingFigures;
    } else {
        for (int i = 0; i < nrIterations; ++i) {
            Figures3D newFigures;
            for (Figure3D figure: resultingFigures) {
                for (int j = 0; j < (int) (figure.points.size()); ++j) {
                    Figure3D newFigure = figure;
                    newFigure.applyTransformation(TransformationMatrix::scaleFigure(1 / fractalScale));

                    Vector3D A = figure.points[j];
                    Vector3D B = newFigure.points[j];

                    newFigure.applyTransformation(TransformationMatrix::translateFigure(A - B));
                    newFigures.push_back(newFigure);
                }
            }
            resultingFigures = newFigures;
        }
        return resultingFigures;
    }
}
