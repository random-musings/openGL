#pragma once


class Dust
{
public:
	Point origin;
    Point velocity;
    bool enabled;
	Color color;
	GLfloat size
	Dust::Dust();
	Dust::Dust(Point newOrigin,
				Point newVelocity,
				GLfloat newSize,
				bool isEnabled,
				Color newColor);

	void advance();
	void degradeVelocity(Point speedDegrade);
	void display();

};


class Smoke
{
	GLint maxParticles;
	vector<Dust> smokeTrail;

public:
	Smoke(GLint newMaxParticles);
	~Smoke(void);
	void display();
};
