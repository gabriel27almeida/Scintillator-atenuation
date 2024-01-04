#include "Simulator.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;

/////////////////////////
//////
Simulator::Simulator(double mu_, double r_, double L_){
	mu = mu_;
	r = r_,
	L = L_;
}

double Simulator::run(double x0, double y0, int N0, bool diffuse){
	int N = 0;

	for(int i=0; i<N0; i++){
		double x = x0;
		double y = y0;
		double theta = (double)rand()/RAND_MAX * 2.0*M_PI; // random (0,2pi)
		double dist=0;
		int n_r = 0;

		while(dist*mu < 5){
			update(x,y,theta,dist, diffuse);
			if (y==0) break;
			else n_r++;
		}
		double prob = exp(-mu*dist)*pow(r,n_r);
		double p = (double)rand()/RAND_MAX; // random (0,1)
		if (p < prob) N++;
	}

	return (double)N/N0;
}

void Simulator::update(double& x, double& y, double& theta, double& dist, bool diffuse){
	double x1, y1;
	if (cos(theta) > 0){
		y1 = y+(L-x)*tan(theta);
		if (y1 > L){
			x1=x + (L-y)/tan(theta);
			y1 = L;

			if (diffuse){
				theta =  - M_PI*(double)rand()/RAND_MAX;
			}
			else theta = -theta;
		}
		else if (y1 < 0){
			x1=x-y/tan(theta);
			y1=0;

			if (diffuse){
				theta =  M_PI*(double)rand()/RAND_MAX;
			}
			else theta = -theta;
		}
		else{
			x1=L;
			if (diffuse){
				theta =  0.5*M_PI+ M_PI*(double)rand()/RAND_MAX;
			}
			else theta = M_PI - theta;
		}
	}
	else{
		y1 = y - x*tan(theta);
		if (y1 > L){
			x1 = x + (L-y)/tan(theta);
			y1 = L;
			if (diffuse){
				theta =  - M_PI*(double)rand()/RAND_MAX;
			}
			else theta = -theta;
		}
		else if (y1 < 0){
			x1 = x-y/tan(theta);
			y1 = 0;

			if (diffuse){
				theta = M_PI*(double)rand()/RAND_MAX;
			}
			else theta = -theta;
		}
		else{
			x1=0;

			if (diffuse){
				theta =  -0.5*M_PI + M_PI*(double)rand()/RAND_MAX;
			}
			else theta = M_PI - theta;
		}
	}

	dist += sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
	x = x1;
	y = y1;
}