#pragma once
#define random() rand()/double(RAND_MAX)
#define MAX_INTENSITY 5000
class ray
{
public:
	ray();
	ray(double ya, double za, double longensitya, double directionya, double directionza);
	float* clacImageOnPlane(double xa);
	double y, z, intensity, directiony, directionz;
};

class speckle
{
public:
	speckle(long rayNuma, double xa, double rayYMAXa, double rayYMINa, double rayZMAXa, double rayZMINa, long solutionXa, long solutionYa);
	~speckle();
	void genreateRay();
	void generateImage();
private:
	long rayNum, solutionW, solutionH;
	float** plane;
	double rayYMAX, rayYMIN, rayZMAX, rayZMIN, x;
	ray* rays;
	
};