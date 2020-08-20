#include <iostream>
#include "calc.h"

using namespace std;

void main(void)
{
	speckle s(200000, 0.5, 0.5, -0.5, 0.5, -0.5, 800, 800);
	s.genreateRay();
	s.generateImage();
}