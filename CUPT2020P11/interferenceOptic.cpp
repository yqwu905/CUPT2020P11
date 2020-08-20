#include "interferenceOptic.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

wave::wave(){}

wave::wave(double freqa, double ampla, double phasea, double ya, double za)
{
	freq = freqa;
	ampl = ampla;
	phase = phasea;
	y = ya;
	z = za;
}

void wave::calcDistributionOnPlane(double xa, float** plane, double planeya, double planeza, long solutionH, long solutionW)
{
	double yUnit = planeya / double(solutionH), zUnit = planeza / double(solutionW);
	for(long i = 0;i<solutionH;i++)
	{
		for (long j = 0; j < solutionW; j++)
		{
			double x1 = xa, y1 = i * yUnit, z1 = j * zUnit, r, t;
			r = sqrt(pow(x1, 2) + pow(y1 - y, 2) + pow(z1 - z, 2));
			t = r / SPEED;
			plane[i][j] += ampl * sin(freq * t + phase);
		}
	}
}

speckle::speckle(long waveNuma, double xa, double freqa, double waveYMAXa, double waveYMINa, double waveZMAXa, double waveZMINa, double planeya, double planeza, long solutionXa, long solutionYa, std::string fileNamea)
{
	waveNum = waveNuma;
	freq = freqa;
	waveYMAX = waveYMAXa;
	waveYMIN = waveYMINa;
	waveZMAX = waveZMAXa;
	waveZMIN = waveZMINa;
	solutionW = solutionXa;
	solutionH = solutionYa;
	x = xa;
	fileName = fileNamea;
	planey = planeya;
	planez = planeza;
	waves = new wave[waveNum];
	plane = new float* [solutionH];
	for (long i = 0; i < waveNum; i++)
		plane[i] = new float[solutionW];
	for (long i = 0; i < solutionH; i++)
		for (long j = 0; j < solutionW; j++)
			plane[i][j] = 0;
}

speckle::~speckle()
{
	delete[] waves;
	delete[] plane;
}


void speckle::generateWaves()
{
	srand(SEED);
	cout << rand();
	//srand((long)time(0));
	for(long i = 0; i < waveNum; i++)
	{
		wave w;
		w.freq = freq;
		w.ampl = rand() % MAX_INTENSITY;
		w.y = waveYMIN + random() * (waveYMAX - waveYMIN);
		w.z = waveZMIN + random() * (waveZMAX - waveZMIN);
		w.phase = random() * 6.283185306;
		waves[i] = w;
	}
}

void speckle::generateImage()
{
	long unit = waveNum / 100, percentage = 0;
	for (long i = 0; i < waveNum; i++)
	{
		wave w = waves[i];
		w.calcDistributionOnPlane(x, plane, planey, planez, solutionH, solutionW);
		if (i%unit == 0)
		{
			percentage++;
			cout << percentage << "/100" << endl;
		}
	}
	ofstream fp(fileName, ios::out);
	for (long i = 0; i < solutionH; i++)
	{
		string s("");
		s += to_string(plane[i][0]);
		for (long j = 1; j < solutionW; j++)
		{
			s += ",";
			s += to_string(plane[i][j]);
		}
		fp << s << endl;
		//cout << i << "/" << solutionH << endl;
	}
	fp.close();
}

