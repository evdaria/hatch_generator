#include "hatch_generator.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{   
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " --angle <angle> --step <step>" << endl;
        return 1;
    }

    double angle, step;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "--angle") {
            angle = stod(argv[++i]);
        }
        else if (arg == "--step") {
            step = stod(argv[++i]);
        }
        else {
            cerr << "Unknown parameter: " << arg << endl;
            return 1;
        }
    }


    if ((angle < 0.0) || (angle > 180.0)) {
        cerr << "Error: angle must be 0-180" << endl;
        return 1;
    }

    if (step <= 0) {
        cerr << "Error: step must be positive" << endl;
        return 1;
    }

    vector<Point_2> contoursPoints = {
        { {0,0}, {20,0}, {20,10}, {0,10} }
    };

    HatchGenerator test(contoursPoints, angle, step);

    std::vector<Line_2> result;
    result = test.generateHatchLines();
    test.printHatchLines(result);
    test.saveToSVG(result, "test1.svg");

    return 0;
}
