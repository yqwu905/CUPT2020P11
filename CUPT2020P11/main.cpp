
#include "geoOptic.h"
#include "interferenceOptic.h"

using namespace std;

void main(void)
{
	/*
	spot s1(200000, 0.5, 0.5, -0.5, 0.5, -0.5, 800, 800, "Image1.csv");
	spot s2(200000, 1, 0.5, -0.5, 0.5, -0.5, 800, 800, "Image2.csv");
	s1.genreateRay();
	s1.generateImage();
	s2.genreateRay();
	s2.generateImage();
	*/
	speckle s3(2000, 0.5, 44000, 0.05, -0.05, 0.05, -0.05, 3, -3, 3, -3, 800, 800, "Image4.csv");
	s3.generateWaves();
	s3.generateImage();
}