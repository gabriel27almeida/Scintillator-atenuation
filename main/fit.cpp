#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    srand(7);
	map<string, double> variables;

    // Open the input and output file
    ifstream file("CONFIG-FIT");
    ofstream outFile("OUTPUT-FIT");
    ifstream datafile("DATA-FIT");


    // Check if the files are open
    if (!file.is_open()) {
        cerr << "Error opening file!" << std::endl;
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing!" << std::endl;
        return 1;
    }
    if (!datafile.is_open()) {
        cerr << "Error opening file with data!" << std::endl;
        return 1;
    }

    // Read the file line by line
    string line;
    while (std::getline(file, line)) {
        // Copy to beginning of output file
        outFile << line << endl;

        // Skip lines starting with '#'
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

    // Read experimental data
    vector<double> x_exp;
    vector<double> y_exp;
    vector<double> intensity_exp;

    // Read the file line by line
    while (std::getline(datafile, line)) {
        // Skip lines starting with '#'
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Parse variable name and its value
        istringstream iss(line);
        double x_,y_,intensity_;

        if (iss >> x_ >> y_ >> intensity_) {
            x_exp.push_back(x_);
            y_exp.push_back(y_);
            intensity_exp.push_back(intensity_);
            
        } else {
            cerr << "Error parsing line: " << line << std::endl;
        }
    }

    // normalization
    double factor = intensity_exp[0];
    for (auto& val: intensity_exp){
        val = val/factor;
    }


    outFile << "\nmu r chi^2\n\n";

    auto start = chrono::steady_clock::now();

    for (double mu=variables["mu_min"]; mu<= variables["mu_max"]; mu+= variables["mu_step"]){
        for(double r=variables["r_min"]; r<=variables["r_max"]; r+= variables["r_step"]){
            Simulator s(mu, r, variables["L"]);
            double chi2 = 0;

            double factor;
            for (int i=0; i<x_exp.size(); i++){
                double ratio = s.run(x_exp[i], y_exp[i], (int)variables["N0"],(bool)variables["diffusion"]);
                if (i==0) factor = ratio;

                //outFile << x_exp[i] << " " << y_exp[i] << " " << ratio << endl;
                
                chi2 += (ratio/factor - intensity_exp[i])*(ratio/factor - intensity_exp[i]);
            }
        
            outFile << mu << " " << r << " " << chi2 << endl;
        }
    }

    //  Insert the code that will be timed

    auto end = chrono::steady_clock::now();

    // Store the time difference between start and end
    auto diff = end - start;

    cout << 0.001 * chrono::duration <double, milli> (diff).count() << " s" << endl;

    // Close the files
    file.close();
	outFile.close();
    datafile.close();


    return 0;
}
