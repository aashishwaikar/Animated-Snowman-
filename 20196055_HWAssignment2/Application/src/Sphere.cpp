#include "Sphere.hpp"

Sphere::Sphere()
{
	r = 1.0f;
	div_phi = 20.0f;
	div_theta = 40.0f;
}


Sphere::~Sphere()
{
}

void Sphere::strip(Engine::Mesh* mesh, float phi)
{
	float value_div_theta = 6.28 / div_theta;
	float value_div_phi = 3.14 / div_phi;

	float cur_theta = 0;
	

	for (int i = 0; i < div_theta; i++)
	{
		glm::vec3 a;
		glm::vec3 b;
		glm::vec3 c;
		glm::vec3 d;

		a[0] = r * cos(phi) * cos(cur_theta);
		a[1] = r * cos(phi) * sin(cur_theta);
		a[2] = r * sin(phi);

		b[0] = r * cos(phi) * cos(cur_theta + value_div_theta);
		b[1] = r * cos(phi) * sin(cur_theta + value_div_theta);
		b[2] = r * sin(phi);

		c[0] = r * cos(phi + value_div_phi) * cos(cur_theta);
		c[1] = r * cos(phi + value_div_phi) * sin(cur_theta);
		c[2] = r * sin(phi + value_div_phi);

		d[0] = r * cos(phi + value_div_phi) * cos(cur_theta + value_div_theta);
		d[1] = r * cos(phi + value_div_phi) * sin(cur_theta + value_div_theta);
		d[2] = r * sin(phi + value_div_phi);

		mesh->AddVertexData(a);
		mesh->AddVertexData(1.0f);

		mesh->AddVertexData(b);
		mesh->AddVertexData(1.0f);

		mesh->AddVertexData(c);
		mesh->AddVertexData(1.0f);

		mesh->AddVertexData(d);
		mesh->AddVertexData(1.0f);

		mesh->AddVertexData(c);
		mesh->AddVertexData(1.0f);

		mesh->AddVertexData(b);
		mesh->AddVertexData(1.0f);

		cur_theta += value_div_theta;
	}

	return;
}

void Sphere::GenerateSphere(Engine::Mesh* mesh)
{
	mesh->AddAttribute(4);
	
	float cur_phi = -1.57;
	for (int i = 0; i < div_phi; i++)
	{
		strip(mesh, cur_phi);
		cur_phi += 3.14 / div_phi;
	}
	
	mesh->SetNumElements(4800);
	
	mesh->CreateMesh();
	return;
}