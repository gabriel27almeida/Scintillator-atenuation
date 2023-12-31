# Simulations of scintillator atenuation

This repository contains **simulations of the atenuation in scintillating materials**. 

We consider a square scintillator with size $L$ and atenuation coefficient $\mu$. In a typical experiment, we can shine an electron beam at position $(x,y)$ and an optical fiber, 
at the bottom of the scintilator, will collect the scintillation light. ALso, the scintillator is covered with a reflecting material with reflectivity $r$.

Our goal is to study the atenuation profile and relate it with $\mu$ and $r$.

## Our model

We use a simple model where we generate a large amout of photons in the point $(x,y)$ and measure the fraction that arrives to the optical fiber without being absorved 
(either by the scintillator or the reflecting envelope). To calculate this fraction we use a Monte Carlo method, for each photon:
* Assign a random initial direction to the photon
* Trace the trajetory to the optical fiber (assuming either specular or diffused reflections)
* Compute the distance traveled by the photon, $d$, and the number of reflections, $n$.
* Accept the photon with probability $r^n e^{-\mu d}$.

We intend to compare this computations with experimental atenuation profiles and study the impact of the parameters $\mu$ and $r$. 

## What can you find here?

The code we wrote is organized as follows:
* `src` folder contains the class `Simulator` that handles the simulation
* `main` folder contains the main functions used to
  * generate an atenuation profile (`run.cpp`)
  * fit the model to experimental data (`fit.cpp`)
* `plot.ipynb` is a Python notebook to plot the atenuation profile produced by `run.cpp`
* `plot-fit.ipynb` is a Python notebook to plot the $\chi^2$ map generated by `fit.cpp`

## How to use the code?

To use this code, first compile the C++ programs:

```g++ main/run.cpp src/Simulator.cpp -o bin/run.exe -std=c++11 -I src && g++ main/fit.cpp src/Simulator.cpp -o bin/fit.exe -std=c++11 -I src```

To execute, use `./bin/run.exe` or `./bin/fit.exe`.

The `run` program reads the `CONFIG` file, while the `fit` program reads the files `CONFIG-FIT` and `DATA-FIT`. The CONFIG files contain the relevant parameters of the simulation/fit, while the data file contains the experimental data. Distances should come in $\mathrm{cm}$ and the atenuation coefficient in $\mathrm{cm}^{-1}$.

