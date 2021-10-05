#pragma once
#include "vectormath.h"
#include <random>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class DSAttractors
{
private:
	Event event;
	Clock clock;
	View view;

	double inputTimer = 0;
	double timeStep;

	float screenWidth = 1920;
	float screenHeight = 1080;

	bool isFullscreen = true;
	bool endSubProgram = false;

	// Camera values
	Vector3f camPosition = {0, 0, -50};
	vector<float> camAngle = {0, 0, 0};
	Vector3f displayPosition = {0, 0, 100};

	vector<Vector3f> point;
	Vector2f projectedPoint;

	// Attractor parameters
	unsigned attractorIndex = 0;
	vector<vector<float>> attractorConfig;

	// Rotation Matrices
	Matrix3<float> rotMatrixX;
	Matrix3<float> rotMatrixY;
	Matrix3<float> rotMatrixZ;

	// Visual assets
	vector<vector<Vector3f>> trail; // Contains "numPoints" many "trailLength" previous coordinates
	vector<unsigned> j;					  // Indices of the last position drawn (algorithm for drawing trails without reallocating memory)
	VertexArray line;						  // Line object to be drawn
	vector<CircleShape> circle;
	vector<Color> colours;
	vector<vector<float>> trailColoursParams;

	// Visual parameters
	unsigned numPoints = 300;
	unsigned trailLength = 5;
	float speed = 2.0f;

	// Constants
	float PI = 3.141f;

	// Names per attractor
	Text text;
	Font font;
	vector<string> attractorNames = {
		"Lorenz Attractor",
		"3-Cells CNN Attractor",
		"Aizawa Attractor",
		"Bouali Attractor",
		"Chen-Lee Attractor",
		"Halvorsen Attractor",
		"Finance Attractor",
		"Newton-Leipnik Attractor",
		"Nose-Hoover Attractor",
		"Thomas Attractor"
	};

	void setupText();
	void createBalls();
	void initiateCamera();

public:
	DSAttractors();

	static unsigned char clamp(float x) {
		if (x <= 0) return 0;
		else if (x >= 255) return 255;
		else return static_cast<unsigned char>(x);
	}

	static float getRandomNumber(float min, float max) {
		random_device device;
		mt19937 generator(device());
		uniform_real_distribution<float> distribution(min, max);
		return distribution(generator);
	}

	void input(RenderWindow &window);
	void update();
	void draw(RenderWindow &window);
	void run(RenderWindow &window);
	~DSAttractors();

    void setupText() const;

    void createBalls() const;

    void initiateCamera();
};

