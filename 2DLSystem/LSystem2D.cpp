#include <fstream>
#include <cmath>
#include "LSystem2D.h"

LSystem2D::LSystem2D(int size, std::vector<int> backgroundcolor, std::string inputfile, std::vector<double>& color){
    img::Color lineColor(color[0]*255,color[1]*255,color[2]*255);

    // get LSystem2D from .2DL file
    LParser::LSystem2D parsedSystem = getLSystem2D(inputfile);

    // get string of system for lines
    std::string systemString = getString(parsedSystem);

    // get all lines for system
    systemLines = get2DLines(parsedSystem, systemString, color);

    // get size for image
    std::vector<int> imageSize = getImageSize(size);

    // make new image
    image = img::EasyImage(imageSize[0], imageSize[1], img::Color(backgroundcolor[0]*255,
                                                                  backgroundcolor[1]*255,
                                                                  backgroundcolor[2]*255));

    // scale and move all lines so they fit on image
    transform2DLines();

    // draw all lines on image
    draw2DLines(lineColor);
}

img::EasyImage LSystem2D::getImage() const{
    return image;
}

LParser::LSystem2D LSystem2D::getLSystem2D(const std::string& inputfile){
    LParser::LSystem2D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    return l_system;
}

std::string LSystem2D::getString(const LParser::LSystem2D& parseSystem) {
    std::string oldString = parseSystem.get_initiator();
    std::string newString;

    if (parseSystem.get_nr_iterations() == 0){
        return oldString;
    }

    for (int i = 0; i < parseSystem.get_nr_iterations(); ++i) {
        newString = "";
        for (char c: oldString) {
            if (parseSystem.get_alphabet().find(c) != parseSystem.get_alphabet().end()){
                newString += parseSystem.get_replacement(c);
            } else {
                newString += c;
            }
        }
        oldString = newString;
    }
    return newString;
}

Lines2D LSystem2D::get2DLines(const LParser::LSystem2D& parsedSystem, const std::string& systemString, const std::vector<double> &color) {
    // create list of lines
    Lines2D lines;

    // create stack for brackets
    std::vector<std::vector<double>> bracket_stack = {};

    // get current angle in degrees
    double current_angle = parsedSystem.get_starting_angle() * M_PI /180;
    double angle_component = parsedSystem.get_angle() * M_PI /180;

    // set initial position to (0,0)
    Point2D current_position(0,0);
    Point2D previous_position(0,0);

    // loop over every char in string
    for (char c : systemString){
        if (c == '+'){
            // if + -> increase angle
            current_angle += angle_component;
            continue;
        } else if (c == '-'){
            // if - -> decrease angle
            current_angle -= angle_component;
            continue;
        } else if (c == '('){
            // if [ -> save current location to stack
            bracket_stack.push_back({current_position.x, current_position.y, current_angle});
            continue;
        } else if (c == ')'){
            // if ] -> set current location to last stack value
            current_position = Point2D(bracket_stack.back()[0], bracket_stack.back()[1]);
            current_angle = bracket_stack.back()[2];
            bracket_stack.pop_back();
            continue;
        } else {
            // else (letter form alphabet)
            // set previous position to current location
            previous_position = current_position;
            // calculate new position
            current_position.move_with_offset(cos(current_angle), sin(current_angle));

            // check if char means to draw a line
            if (parsedSystem.draw(c)){
                // Add line from old position to new position to list
                Line2D newLine(previous_position, current_position, LineColor(color[0]*255, color[1]*255,color[2]*255));
                lines.push_back(newLine);
            }

        }
    }


    return lines;
}

std::vector<int> LSystem2D::getImageSize(int size) {
    // Find min and max of x and y
    x_max = systemLines.begin()->pointA.x;
    y_max = systemLines.begin()->pointA.y;
    x_min = systemLines.begin()->pointA.x;
    y_min = systemLines.begin()->pointA.y;

    for (Line2D line : systemLines){
        // x_max
        x_max = std::max(line.pointA.x, x_max);
        x_max = std::max(line.pointB.x, x_max);

        // x_min
        x_min = std::min(line.pointA.x, x_min);
        x_min = std::min(line.pointB.x, x_min);

        // y_max
        y_max = std::max(line.pointA.y, y_max);
        y_max = std::max(line.pointB.y, y_max);


        // y_min
        y_min = std::min(line.pointA.y, y_min);
        y_min = std::min(line.pointB.y, y_min);
    }

    // calculate range for x en y
    double range_x = x_max - x_min;
    double range_y = y_max - y_min;

    // calculate max range
    double max_range = std::max(range_x, range_y);

    // calculate size of image
    double image_x = size*(range_x/max_range);
    double image_y = size*(range_y/max_range);

    return {int(image_x), int(image_y)};
}

void LSystem2D::transform2DLines(){
    double size_x = image.get_width();
    double size_y = image.get_height();

    // scale all lines
    double scalingFactor = 0.95 * (size_x / (x_max-x_min));
    for (Line2D& line : systemLines){
        line.scaleLine(scalingFactor);
    }

    // move all lines
    double DCx = (scalingFactor * (x_min + x_max)) / 2;
    double DCy = (scalingFactor * (y_min + y_max)) / 2;

    double dx = (size_x / 2) - DCx;
    double dy = (size_y / 2) - DCy;

    for (Line2D &line2D : systemLines){
        line2D.moveLine(dx, dy);
    }
}

void LSystem2D::draw2DLines(img::Color lineColor) {
    // draw all lines in line list
    for (Line2D const& line : systemLines){
        image.draw_line(lround(line.pointA.x), lround(line.pointA.y), lround(line.pointB.x), lround(line.pointB.y), lineColor);
//        std::cout << "A:"<< line.pointA.x << ", " << line.pointA.y << "       B:"<< line.pointB.x << ", " << line.pointB.y << std::endl;
    }

}

