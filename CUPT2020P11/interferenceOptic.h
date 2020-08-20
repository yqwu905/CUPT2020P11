#pragma once
#include <string>
#define random() rand()/double(RAND_MAX)
#define MAX_INTENSITY 5000
#define SEED 114514
#define SPEED 30000
#define DEFAULT_RADIUS 10

class ray;
using namespace std;

class wave
{
public:
	wave();
	wave(double freqa, double ampla, double phasea, double ya, double za);
	void calcDistributionOnPlane(double xa, float** plane, double planeYMAXa, double planeYMINa, double planeZMAXa, double planeZMINa, long solutionH, long solutionW);
	double freq, ampl, phase, y, z;
};

class speckle
{
public:
	~speckle();
	speckle(long waveNuma, double xa, double freqa, double waveYMAXa, double waveYMINa, double waveZMAXa, double waveZMINa, double planeYMAXa, double planeYMINa, double planeZMAXa, double planeZMINa, long solutionXa, long solutionYa, std::string fileNamea);
	void generateWaves();
	void generateImage();
private:
	std::string fileName;
	long waveNum, solutionW, solutionH;
	float** plane;
	double waveYMAX, waveYMIN, waveZMAX, waveZMIN, x, freq, planeYMAX, planeYMIN, planeZMAX, planeZMIN;
	wave* waves;
};