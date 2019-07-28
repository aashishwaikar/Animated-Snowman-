#pragma once

#include <vector>
#include<cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Mesh.hpp>
class Sphere
{
public:
	float r;
	float div_phi;
	float div_theta;
	Sphere();
	~Sphere();
	void strip(Engine::Mesh* mesh, float phi);
	void GenerateSphere(Engine::Mesh* mesh);
};

