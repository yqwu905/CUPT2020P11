#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <pthread.h>

#define random() rand()/double(RAND_MAX)
#define MAX_INTENSITY 5000
#define SEED 114514
#define SPEED 30000
#define DEFAULT_RADIUS 10
#define NUM_THREADS 8

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

wave::wave(){}

wave::wave(double freqa, double ampla, double phasea, double ya, double za)
{
	freq = freqa;
	ampl = ampla;
	phase = phasea;
	y = ya;
	z = za;
}

void wave::calcDistributionOnPlane(double xa, float** plane, double planeYMAXa, double planeYMINa, double planeZMAXa, double planeZMINa, long solutionH, long solutionW)
{
	double yUnit = (planeYMAXa - planeYMINa) / double(solutionH), zUnit = (planeZMAXa - planeZMINa) / double(solutionW);
	for(long i = 0;i<solutionH;i++)
	{
		for (long j = 0; j < solutionW; j++)
		{
			double x1 = xa, y1 = planeYMINa + i * yUnit, z1 = planeZMINa + j * zUnit, r, t;
			r = sqrt(pow(x1, 2) + pow(y1 - y, 2) + pow(z1 - z, 2));
			t = r / SPEED;
			plane[i][j] += ampl * sin(6.283185306 * freq * t + phase) / pow((r / DEFAULT_RADIUS),2);
		}
	}
}

speckle::speckle(long waveNuma, double xa, double freqa, double waveYMAXa, double waveYMINa, double waveZMAXa, double waveZMINa, double planeYMAXa, double planeYMINa, double planeZMAXa, double planeZMINa, long solutionXa, long solutionYa, std::string fileNamea)
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
	planeYMAX = planeYMAXa;
	planeYMIN = planeYMINa;
	planeZMAX = planeZMAXa;
	planeZMIN = planeZMINa;
	waves = new wave[waveNum];
	plane = new float* [solutionH];
	for (long i = 0; i < solutionH; i++)
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
		w.calcDistributionOnPlane(x, plane, planeYMAX, planeYMIN, planeZMAX, planeZMIN, solutionH, solutionW);
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



void threadFunc(void* args)
{
    double* size = ((void**)args)[0];
    int* i = ((void**)args)[1];
    string fileName("Image");
    fileName += to_string(*i);
    fileName += ".csv"
    speckle s3(50000, 0.5, 44000, 0.05, -0.05, 0.05, -0.05, *size, -*size, *size, -*size, 800, 800, fileName);
    s3.generateWaves();
    s3.generateImage();
}


int main()
{
    double sizeList = [5, 10, 20, 50, 100, 200, 300, 500];
    pthread_t pids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++)
    {
        void* arg[2] = {&sizeList[i], &i};
        int ret = pthread_create(&pids[i], NULL, threadFunc, arg);
        if (ret != 0)
        {
            cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    return 0;
}