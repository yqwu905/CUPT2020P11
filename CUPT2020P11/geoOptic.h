#pragma once
#include <string>
#define random() rand()/double(RAND_MAX)
#define MAX_INTENSITY 5000
#define SEED 114514
class ray
{
public:
	ray();
	ray(double ya, double za, double longensitya, double directionya, double directionza);
	float* clacImageOnPlane(double xa);
	double y, z, intensity, directiony, directionz;
};

class spot
{
public:
	spot(long rayNuma, double xa, double rayYMAXa, double rayYMINa, double rayZMAXa, double rayZMINa, long solutionXa, long solutionYa, std::string fileNamea);
	~spot();
	void genreateRay();
	void generateImage();
	
private:
	std::string fileName;
	long rayNum, solutionW, solutionH;
	float** plane;
	double rayYMAX, rayYMIN, rayZMAX, rayZMIN, x;
	ray* rays;
	
};