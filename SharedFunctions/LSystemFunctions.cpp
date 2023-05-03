#include <fstream>
#include <stack>
#include "LSystemFunctions.h"

LParser::LSystem3D LSystemFunctions::parseLSystem3D(const std::string &inputfile) {
    LParser::LSystem3D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    return l_system;
}

std::string LSystemFunctions::getLSystemString(const LParser::LSystem3D &l_system) {
    if (l_system.get_nr_iterations() == 0){
        return l_system.get_initiator();
    } else {
        std::string oldString = l_system.get_initiator();
        std::string figureString;
        // Iterate x times over the string
        for (int i = 0; i < l_system.get_nr_iterations(); ++i) {
            figureString = "";
            for (char c: oldString) {
                if (l_system.get_alphabet().find(c) != l_system.get_alphabet().end()){
                    figureString += l_system.get_replacement(c);
                } else {
                    figureString += c;
                }
            }
            oldString = figureString;
        }
        return figureString;
    }
}

std::pair<std::vector<Face3D>, std::vector<Vector3D>>
LSystemFunctions::getFacesAndPoints(const LParser::LSystem3D &l_system, const std::string &figureString) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    double angle = l_system.get_angle()*M_PI/180;
    Vector3D vectorH = Vector3D::vector(1,0,0);
    Vector3D vectorL = Vector3D::vector(0,1,0);
    Vector3D vectorU = Vector3D::vector(0,0,1);

    std::stack<std::vector<Vector3D>> bracketStack = {};
    Vector3D previousPosition = Vector3D::point(0, 0, 0);
    Vector3D currentPosition = Vector3D::point(0, 0, 0);

    for (char c : figureString){
        if (c == '+'){
            Vector3D newVectorH = vectorH*cos(angle) + vectorL * sin(angle);
            Vector3D newVectorL = -vectorH * sin(angle) + vectorL*cos(angle);
            vectorH = newVectorH;
            vectorL = newVectorL;
            continue;
        } else if (c == '-'){
            Vector3D newVectorH = vectorH*cos(-angle) + vectorL * sin(-angle);
            Vector3D newVectorL = -vectorH * sin(-angle) + vectorL*cos(-angle);
            vectorH = newVectorH;
            vectorL = newVectorL;
            continue;
        } else if (c == '^'){
            Vector3D newVectorH = vectorH*cos(angle) + vectorU * sin(angle);
            Vector3D newVectorU = -vectorH * sin(angle) + vectorU*cos(angle);
            vectorH = newVectorH;
            vectorU = newVectorU;
            continue;
        } else if (c == '&'){
            Vector3D newVectorH = vectorH*cos(-angle) + vectorU * sin(-angle);
            Vector3D newVectorU = -vectorH * sin(-angle) + vectorU*cos(-angle);
            vectorH = newVectorH;
            vectorU = newVectorU;
            continue;
        } else if (c == '\\'){
            Vector3D newVectorL = vectorL*cos(angle) - vectorU * sin(angle);
            Vector3D newVectorU = vectorL * sin(angle) + vectorU*cos(angle);
            vectorL = newVectorL;
            vectorU = newVectorU;
            continue;
        } else if (c == '/'){
            Vector3D newVectorL = vectorL*cos(-angle) - vectorU * sin(-angle);
            Vector3D newVectorU = vectorL * sin(-angle) + vectorU*cos(-angle);
            vectorL = newVectorL;
            vectorU = newVectorU;
            continue;
        } else if (c == '|'){
            vectorH *= -1;
            vectorL *= -1;
            continue;
        } else if (c == '('){
            bracketStack.push({currentPosition, vectorH, vectorL, vectorU});
            continue;
        } else if (c == ')'){
            std::vector<Vector3D> oldPosition = bracketStack.top();
            bracketStack.pop();

            currentPosition = oldPosition[0];
            vectorH = oldPosition[1];
            vectorL = oldPosition[2];
            vectorU = oldPosition[3];
            continue;
        } else {
            previousPosition = currentPosition;
            currentPosition += vectorH;
            if (l_system.draw(c)){
                points.push_back(previousPosition);
                points.push_back(currentPosition);
                faces.push_back(Face3D({static_cast<int>(points.size() - 2), static_cast<int>(points.size() - 1)}));
            }
        }
    }
    return {faces, points};
}
