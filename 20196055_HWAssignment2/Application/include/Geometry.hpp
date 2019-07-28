#pragma once

#include <vector>
#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Mesh.hpp>

class Geometry
{
private:

protected:
	Geometry *parent;
	std::vector<Geometry *> children;
public:
	//float r;
	int div_phi;
	int div_theta;
	Geometry();
	~Geometry();
	void GenerateCube(Engine::Mesh* mesh);
	void Quad(Engine::Mesh* mesh, int a_a, int a_b, int a_c, int a_d);
	glm::vec3 ComputeNormal(glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c);
	void GenerateTriangleMesh(Engine::Mesh* mesh);
	void GenerateLine(Engine::Mesh* mesh);
	void GenerateStar(Engine::Mesh* mesh);
	void strip(Engine::Mesh* mesh, float phi, float r);
	void strip1(Engine::Mesh* mesh, float phi, float r);
	void GenerateSphere(Engine::Mesh* mesh, float r);
	void GenerateIgloo(Engine::Mesh* mesh, float r);
	void GenerateCylinder(Engine::Mesh* mesh, float h, float r);
	void GenerateCone(Engine::Mesh* mesh, float h, float r);
	void GenerateSnowflake(Engine::Mesh* mesh);
	void side(glm::vec3 a, glm::vec3 b, int iter, Engine::Mesh* mesh);
	//void GenerateCone(Engine::Mesh* mesh);
	void AddChild(Geometry *geometry);
};

