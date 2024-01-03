#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <string>

using namespace std;

int main() {
	map<string, double> variables;

    // Open the input and output file
    ifstream file("CONFIG");
    ofstream outFile("OUTPUT");


    // Check if the files are open
    if (!file.is_open()) {
        cerr << "Error opening file!" << std::endl;
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing!" << std::endl;
        return 1;
    }

    // Read the file line by line
    string line;
    while (std::getline(file, line)) {
        // Skip lines starting with '#'
        outFile << line << endl;

        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Parse variable name and its value
        istringstream iss(line);
        string variableName;
        double variableValue;

        if (iss >> variableName >> variableValue) {
            // Store the variable name and its value in the map
            variables[variableName] = variableValue;
        } else {
            cerr << "Error parsing line: " << line << std::endl;
        }
    }

    outFile << "\nx y intensity\n\n";

    

	Simulator s(variables["mu"], variables["r"], variables["L"]);
	for (double x=variables["xmin"]; x<= variables["xmax"]; x+= variables["xstep"]){
		for(double y=variables["ymin"]; y<=variables["ymax"]; y+= variables["ystep"]){
			double ratio = s.run(x,y, (int)variables["N0"],(bool)variables["diffusion"]);
			outFile << x << " " << y << " " << ratio << endl;
		}
	}

    // Close the files
    file.close();
	outFile.close();


    return 0;
}
