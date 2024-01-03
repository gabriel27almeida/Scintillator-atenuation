#ifndef __SIMULATOR__
#define __SIMULATOR__

class Simulator{
	public:
		Simulator() = default;
		Simulator(double mu, double reflectivity, double L=1);

		double run(double x, double y, int N0, bool diffuse=false);
		void update(double& x, double& y, double& theta, double& dist, bool diffuse);


	private:
		double mu, r, L;


};


#endif