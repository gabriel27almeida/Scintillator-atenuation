#ifndef __SIMULATOR__
#define __SIMULATOR__

class Simulator{
	public:
		Simulator() = default;
		Simulator(double mu, double reflecitivty, double L=1);

		double run(double x, double y, int N0);
		void update(double& x, double& y, double& theta, double& dist);


	private:
		double mu, r, L;


};


#endif