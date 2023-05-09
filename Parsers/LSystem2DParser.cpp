#include "LSystem2DParser.h"
#include "../SharedFunctions/ImageSize.h"
#include "../SharedFunctions/ScaleLines.h"
#include "../SharedFunctions/DrawLines.h"
#include <fstream>
#include <cmath>

img::EasyImage LSystem2DParser::parse2DLSystem(const ini::Configuration &configuration) {
    // Get data from ini file
    std::string type = configuration["General"]["type"].as_string_or_die();
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    std::vector<double> color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    img::Color lineColor(color[0] * 255, color[1] * 255, color[2] * 255);

    // get LSystem2D from .2DL file
    LParser::LSystem2D parsedSystem = getLSystem2D(inputfile);

    // get string of system for lines
    std::string systemString = getString(parsedSystem);

    // get all lines for system
    Lines2D lines = get2DLines(parsedSystem, systemString, lineColor);

    // Calculate size image
    double x_max, y_max, x_min, y_min;
    std::vector<int> imageSize = ImageSize::getImageSize(lines, size, x_min, x_max, y_min, y_max);

    // make new image
    img::EasyImage image = img::EasyImage(imageSize[0], imageSize[1], img::Color(backgroundcolor[0] * 255,
                                                                                 backgroundcolor[1] * 255,
                                                                                 backgroundcolor[2] * 255));

    // scale and move all lines so they fit on image
    ScaleLines::scale2DLines(lines, imageSize, x_min, x_max, y_min, y_max);

    // draw all lines on image
    DrawLines::draw2DLines(image, lines);

    return image;
}

LParser::LSystem2D LSystem2DParser::getLSystem2D(const std::string &inputfile) {
    LParser::LSystem2D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    return l_system;
}

std::string LSystem2DParser::getString(const LParser::LSystem2D &parseSystem) {
    std::string oldString = parseSystem.get_initiator();
    std::string newString;

    if (parseSystem.get_nr_iterations() == 0) {
        return oldString;
    }

    for (int i = 0; i < parseSystem.get_nr_iterations(); ++i) {
        newString = "";
        for (char c: oldString) {
            if (parseSystem.get_alphabet().find(c) != parseSystem.get_alphabet().end()) {
                newString += parseSystem.get_replacement(c);
            } else {
                newString += c;
            }
        }
        oldString = newString;
    }
    return newString;
}

Lines2D LSystem2DParser::get2DLines(const LParser::LSystem2D &parsedSystem, const std::string &systemString,
                                    const img::Color &lineColor) {
    // create list of lines
    Lines2D lines;

    // create stack for brackets
    std::vector<std::vector<double>> bracket_stack = {};

    // get current angle in degrees
    double current_angle = parsedSystem.get_starting_angle() * M_PI / 180;
    double angle_component = parsedSystem.get_angle() * M_PI / 180;

    // set initial position to (0,0)
    Point2D current_position(0, 0);
    Point2D previous_position(0, 0);

    // loop over every char in string
    for (char c: systemString) {
        if (c == '+') {
            // if + -> increase angle
            current_angle += angle_component;
            continue;
        } else if (c == '-') {
            // if - -> decrease angle
            current_angle -= angle_component;
            continue;
        } else if (c == '(') {
            // if [ -> save current location to stack
            bracket_stack.push_back({current_position.x, current_position.y, current_angle});
            continue;
        } else if (c == ')') {
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
            if (parsedSystem.draw(c)) {
                // Add line from old position to new position to list
                Line2D newLine(previous_position, current_position, lineColor);
                lines.push_back(newLine);
            }
        }
    }


    return lines;
}
