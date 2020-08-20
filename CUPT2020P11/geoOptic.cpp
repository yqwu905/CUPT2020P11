#include "geoOptic.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

ray::ray(){}

ray::ray(double ya, double za, double longensitya, double directionya, double directionza)
{
	y = ya;
	z = za;
	intensity = longensitya; 
	directiony = directionya;
	directionz = directionza;
}

float* ray::clacImageOnPlane(double xa)
{
	float* result = new float[3];
	result[0] = y + xa * directiony;
	result[1] = z + xa * directionz;
	result[2] = intensity / (pow(result[0] - y, 2) + pow(result[1] - z, 2));
	return result;
}

spot::spot(long rayNuma, double xa, double rayYMAXa, double rayYMINa, double rayZMAXa, double rayZMINa, long solutionXa, long solutionYa, string fileNamea)
{
	rayNum = rayNuma;
	rayYMAX = rayYMAXa;
	rayYMIN = rayYMINa;
	rayZMAX = rayZMAXa;
	rayZMIN = rayZMINa;
	std::cout << rayYMINa << rayYMIN;
	solutionW = solutionXa;
	solutionH = solutionYa;
	x = xa;
	fileName = fileNamea;
	rays = new ray[rayNum];
	plane = new float* [rayNum];
	for (long i = 0; i < rayNum; i++)
		plane[i] = new float[solutionW];
}

spot::~spot()
{
	delete[] plane;
	delete[] rays;
}


void spot::genreateRay()
{
	srand(SEED);
	cout << rand();
	//srand((long)time(0));
	for(long i = 0; i < rayNum; i++)
	{
		ray r;
		r.y = rayYMIN + random() * (rayYMAX - rayYMIN);
		r.z = rayZMIN + random() * (rayZMAX - rayZMIN);
		r.intensity = rand() % MAX_INTENSITY;
		r.directiony = random() > 0.5 ? random() : -1 * random();
		r.directionz = random() > 0.5 ? random() : -1 * random();
		rays[i] = r;
	}
}


void spot::generateImage()
{
	for(long i = 0; i < rayNum; i++)
	{
		ray r = rays[i];
		float *res = r.clacImageOnPlane(x);
		plane[i][0] = res[0];
		plane[i][1] = res[1];
		plane[i][2] = res[2];
	}
	float ymax = - INFINITY, ymin = INFINITY, zmax = - INFINITY, zmin = INFINITY;
	for(long i = 0; i < rayNum; i++)
	{
		if (plane[i][0] > ymax)
			ymax = plane[i][0];
		if (plane[i][0] < ymin)
			ymin = plane[i][0];
		if (plane[i][1] > zmax)
			zmax = plane[i][1];
		if (plane[i][1] < zmin)
			zmin = plane[i][1];
	}
	float yUnit = (ymax - ymin) / (solutionW - 1), zUnit = (zmax - zmin) / (solutionH - 1);
	float** img = new float* [solutionH];
	for (long i = 0; i < solutionH; i++)
		img[i] = new float[solutionW];
	for (long i = 0; i < solutionH; i++)
		for (long j = 0; j < solutionW; j++)
			img[i][j] = 0;
	for(long i = 0; i < rayNum; i++)
	{
		long yi = long((plane[i][0] - ymin) / yUnit), zi = long((plane[i][1] - zmin) / zUnit);
		img[yi][zi] += plane[i][2];
	}
	ofstream fp(fileName, ios::out);
	for(long i = 0; i < solutionH; i++)
	{
		string s("");
		s += to_string(img[i][0]);
		for(long j = 1; j < solutionW; j++)
		{
			s += ",";
			s += to_string(img[i][j]);
		}
		fp << s << endl;
		//cout << i << "/" << solutionH << endl;
	}
	fp.close();

}




