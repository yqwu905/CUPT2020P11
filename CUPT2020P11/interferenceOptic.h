#pragma once
#include <string>
#define random() rand()/double(RAND_MAX)
#define MAX_INTENSITY 5000
#define SEED 114514
#define SPEED 3000000

class ray;
using namespace std;

class wave
{
public:
	wave();
	wave(double freqa, double ampla, double phasea, double ya, double za);
	void calcDistributionOnPlane(double xa, float** plane, double planeya, double planeza, long solutionH, long solutionW);
	double freq, ampl, phase, y, z;
};

class speckle
{
public:
	~speckle();
	speckle(long waveNuma, double xa, double freqa, double waveYMAXa, double waveYMINa, double waveZMAXa, double waveZMINa, double planeya, double planeza, long solutionXa, long solutionYa, std::string fileNamea);
	void generateWaves();
	void generateImage();
private:
	std::string fileName;
	long waveNum, solutionW, solutionH;
	float** plane;
	double waveYMAX, waveYMIN, waveZMAX, waveZMIN, x, freq, planey, planez;
	wave* waves;
};