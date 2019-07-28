#include <Geometry.hpp>
#include <stdlib.h>

Geometry::Geometry()
{
	//r = 1.0f;
	div_phi = 20;
	div_theta = 40;
}


Geometry::~Geometry()
{
}

glm::vec4 vertices[8] = {
    glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),
    glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
    glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),
    glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),
    glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),
    glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),
    glm::vec4(1.0f, -1.0f, -1.0f, 1.0f)
};

glm::vec3 Geometry::ComputeNormal(glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c)
{
    glm::vec3 normal = glm::normalize(glm::cross(a_b.xyz() - a_a.xyz(), a_c.xyz() - a_a.xyz()));
    return normal;
}

// TODO: Fill up Geometry::Quad (Slide No. 9)
void Geometry::Quad(Engine::Mesh* mesh, int a_a, int a_b, int a_c, int a_d)
{
    /* a -- d
     * |    |
     * b -- c
     */
    // Compute normal for quad
    glm::vec4 n = glm::vec4(ComputeNormal(vertices[a_a], vertices[a_b], vertices[a_c]), 0.0f);
    // Triangle 1, Vertex a
    mesh->AddVertexData(vertices[a_a]);
    mesh->AddVertexData(n);
    // Triangle 1, Vertex b
    mesh->AddVertexData(vertices[a_b]);
    mesh->AddVertexData(n);
    // Triangle 1, Vertex c
    mesh->AddVertexData(vertices[a_c]);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex a
    mesh->AddVertexData(vertices[a_a]);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex c
    mesh->AddVertexData(vertices[a_c]);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex d
    mesh->AddVertexData(vertices[a_d]);
    mesh->AddVertexData(n);
}

// TODO: Fill up Geometry::GenerateCube (Slide No. 8)
void Geometry::GenerateCube(Engine::Mesh* mesh)
{
    /*   5 -- 6
     *  /|   /|
     * 1(4)-2 7
     * |    |/
     * 0 -- 3
     */
    mesh->AddAttribute(4); // for position
    mesh->AddAttribute(4); // for normal

    // Add four quad for generating a cube
    Quad(mesh, 1, 0, 3, 2);
    Quad(mesh, 2, 3, 7, 6);
    Quad(mesh, 3, 0, 4, 7);
    Quad(mesh, 6, 5, 1, 2);
    Quad(mesh, 4, 5, 6, 7);
    Quad(mesh, 5, 4, 0, 1);

    mesh->SetNumElements(36);
    mesh->CreateMesh();
    return;
}

void Geometry::GenerateTriangleMesh(Engine::Mesh* mesh)
{
    mesh->AddAttribute(4);
	mesh->AddAttribute(4);

    glm::vec3 position_data[] = {
        glm::vec3(-8.0f, -3.0f, 0.0f),
        glm::vec3(7.0f, -2.0f, 0.0f),
        glm::vec3(0.0f,6.0f, 0.0f)
    };

    for (int i = 0; i < 3; i++)
    {
        mesh->AddVertexData(position_data[i]);
        mesh->AddVertexData(1.0f);
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

    }
    mesh->SetNumElements(3);
    mesh->CreateMesh();
    return;
}

void Geometry::GenerateLine(Engine::Mesh* mesh)
{
    mesh->SetDrawMode(GL_LINES);
    mesh->AddAttribute(4);
    mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mesh->AddVertexData(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    mesh->SetNumElements(2);
    mesh->CreateMesh();
    return;
}

void Geometry::strip(Engine::Mesh* mesh, float phi, float r)
{
	float value_div_theta = glm::radians(360.0f) / div_theta;
	float value_div_phi = glm::radians(180.0f) / div_phi;

	float cur_theta = 0;

	for (int i = 0; i < div_theta; i++)
	{
		double new_theta = cur_theta + value_div_theta;
		//if (new_theta == 6.28) new_theta = 0.0;

		double new_phi = phi + value_div_phi;
		//if (new_phi == 3.14) new_phi = 0.0;

		glm::vec3 a;
		glm::vec3 b;
		glm::vec3 c;
		glm::vec3 d;

		a[0] = r * cos(phi) * cos(cur_theta);
		a[1] = r * cos(phi) * sin(cur_theta);
		a[2] = r * sin(phi);

		b[0] = r * cos(phi) * cos(new_theta);
		b[1] = r * cos(phi) * sin(new_theta);
		b[2] = r * sin(phi);

		c[0] = r * cos(new_phi) * cos(cur_theta);
		c[1] = r * cos(new_phi) * sin(cur_theta);
		c[2] = r * sin(new_phi);

		d[0] = r * cos(new_phi) * cos(new_theta);
		d[1] = r * cos(new_phi) * sin(new_theta);
		d[2] = r * sin(new_phi);

		//glm::vec4 n = glm::vec4(ComputeNormal(glm::vec4(a,1.0f), glm::vec4(b, 1.0f), glm::vec4(d, 1.0f)), 0.0f);

		mesh->AddVertexData(a);
		mesh->AddVertexData(1.0f);
		mesh->AddVertexData(glm::vec4(a/r,0.0f));

		mesh->AddVertexData(b);
		mesh->AddVertexData(1.0f);
		mesh->AddVertexData(glm::vec4(b/r, 0.0f));

		mesh->AddVertexData(c);
		mesh->AddVertexData(1.0f);
		mesh->AddVertexData(glm::vec4(c/r, 0.0f));

		mesh->AddVertexData(d);
		mesh->AddVertexData(1.0f);
		mesh->AddVertexData(glm::vec4(d/r, 0.0f));

		mesh->AddVertexData(c);
		mesh->AddVertexData(1.0f);
		mesh->AddVertexData(glm::vec4(c/r, 0.0f));

		mesh->AddVertexData(b);
		mesh->AddVertexData(1.0f);
		mesh->AddVertexData(glm::vec4(b/r, 0.0f));

		cur_theta += value_div_theta;
	}

	return;
}


void Geometry::GenerateSphere(Engine::Mesh* mesh,float r)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);

	float cur_phi = -glm::radians(180.0f)/2;
	for (int i = 0; i < div_phi; i++)
	{
		strip(mesh, cur_phi, r);
		cur_phi += glm::radians(180.0f) / div_phi;
	}

	mesh->SetNumElements(4800);

	mesh->CreateMesh();
	return;
}


/*

void Geometry::GenerateHand(Engine::Mesh* mesh, float len)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);

	glm::vec3 a;
	a[0] = 0.0f;
	a[1] = 0.0f;
	a[2] = 0.0f;

	glm::vec3 b;
	b[0] = 0.1f;
	b[1] = 0.0f;
	b[2] = 0.0f;

	glm::vec3 c;
	c[0] = 0.0f;
	c[1] = len;
	c[2] = 0.0f;

	glm::vec3 d;
	d[0] = 0.1f;
	d[1] = len;
	d[2] = 0.0f;
	mesh->AddVertexData(a);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f,0.0f,1.0f, 0.0f));

	mesh->AddVertexData(b);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	mesh->AddVertexData(c);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	mesh->AddVertexData(d);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	
	mesh->SetNumElements(4);
	mesh->CreateMesh();
	return;
}
*/
void Geometry::GenerateCylinder(Engine::Mesh* mesh, float h,float r)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);
	int no_div_theta = 20;
	float div_theta = 6.28/no_div_theta;
	float theta = 0;

	for (int i = 0; i < no_div_theta; i++)
	{
		float new_theta = theta + div_theta;
		glm::vec4 a;
		a[0] = r*cos(theta);
		a[1] = 0.0f;
		a[2] = -r*sin(theta);
		a[3] = 1.0f;

		glm::vec4 b;
		b[0] = r*cos(new_theta);
		b[1] = 0.0f;
		b[2] = -r*sin(new_theta);
		b[3] = 1.0f;

		glm::vec4 b1;
		b1[0] = r * cos(new_theta);
		b1[1] = h;
		b1[2] = -r * sin(new_theta);
		b1[3] = 1.0f;

		glm::vec4 a1;
		a1[0] = r * cos(theta);
		a1[1] = h;
		a1[2] = -r * sin(theta);
		a1[3] = 1.0f;

		mesh->AddVertexData(a);
		mesh->AddVertexData(glm::vec4(cos(theta), 0.0f, -sin(theta), 0.0f));

		mesh->AddVertexData(b);
		mesh->AddVertexData(glm::vec4(cos(new_theta), 0.0f, -sin(new_theta), 0.0f));

		mesh->AddVertexData(b1);
		mesh->AddVertexData(glm::vec4(cos(new_theta), 0.0f, -sin(new_theta), 0.0f));

		mesh->AddVertexData(b1);
		mesh->AddVertexData(glm::vec4(cos(new_theta), 0.0f, -sin(new_theta), 0.0f));

		mesh->AddVertexData(a1);
		mesh->AddVertexData(glm::vec4(cos(theta), 0.0f, -sin(theta), 0.0f));

		mesh->AddVertexData(a);
		mesh->AddVertexData(glm::vec4(cos(theta), 0.0f, -sin(theta), 0.0f));

		theta = new_theta;
	}

	mesh->SetNumElements(120);

	mesh->CreateMesh();
	return;
}

void Geometry::GenerateCone(Engine::Mesh* mesh, float h, float r)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);
	int no_div_theta = 20;
	float div_theta = glm::radians(360.0f) / no_div_theta;
	float theta = 0;

	for (int i = 0; i < no_div_theta; i++)
	{
		float new_theta = theta + div_theta;
		glm::vec4 a;
		a[0] = r * cos(theta);
		a[1] = 0.0f;
		a[2] = -r * sin(theta);
		a[3] = 1.0f;

		glm::vec4 b;
		b[0] = r * cos(new_theta);
		b[1] = 0.0f;
		b[2] = -r * sin(new_theta);
		b[3] = 1.0f;

		glm::vec4 c;
		c[0] = 0;
		c[1] = h;
		c[2] = 0;
		c[3] = 1.0f;


		mesh->AddVertexData(a);
		glm::vec3 normal_a = cross((a - c).xyz(), glm::vec3(sin(theta), 0.0f, cos(theta)).xyz());
		mesh->AddVertexData(glm::vec4(-normal_a,0.0f));

		mesh->AddVertexData(b);
		glm::vec3 normal_b = cross((b - c).xyz(), glm::vec3(sin(new_theta), 0.0f, cos(new_theta)).xyz());
		mesh->AddVertexData(glm::vec4(-normal_b, 0.0f));

		mesh->AddVertexData(c);
		glm::vec3 normal_c = cross((a/2.0f+b/2.0f - c).xyz(), glm::vec3(sin((theta+new_theta)/2.0), 0.0f, cos((theta+new_theta)/2.0)).xyz());
		mesh->AddVertexData(glm::vec4(-normal_c, 0.0f));

		theta = new_theta;
	}

	mesh->SetNumElements(60);

	mesh->CreateMesh();
	return;
}

void Geometry::GenerateStar(Engine::Mesh* mesh)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);

	glm::vec4 position_data[] = {
		glm::vec4(1.0f * 2.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(-0.5f * 2.0f, sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(-0.5f * 2.0f, -sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(-1.0f * 2.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.5f * 2.0f, -sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(0.5f * 2.0f, sqrt(0.75f) * 2.0f, 0.0f, 1.0f)
	};
	glm::vec4 n = glm::vec4(ComputeNormal(position_data[0], position_data[1], position_data[2]), 0.0f);
	for (int i = 0; i < 6; i++)
	{
		mesh->AddVertexData(position_data[i]);
		mesh->AddVertexData(n);
	}

	mesh->SetNumElements(6);
	mesh->CreateMesh();

	return;
}


void Geometry::side(glm::vec3 a, glm::vec3 b, int iter, Engine::Mesh* mesh)
{
	glm::vec3 b2a = b - a;

	glm::vec3 comp;
	comp[0] = a[1] - b[1];
	comp[1] = b[0] - a[0];
	comp[2] = 0.0f;

	glm::vec3 p = a + b2a / 3.0f;
	glm::vec3 q = a + b2a / 2.0f - comp * sqrt(3.0f) / 6.0f;
	glm::vec3 r = a + b2a * 2.0f / 3.0f;

	mesh->AddVertexData(p);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	mesh->AddVertexData(q);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	mesh->AddVertexData(r);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	if (iter < 3)
	{
		side(a, p, iter + 1, mesh);

		side(p, q, iter + 1, mesh);

		side(q, r, iter + 1, mesh);

		side(r, b, iter + 1, mesh);
	}
	return;
}

/*
 * TODO: Implement koch snowflake mesh generator
 */
void Geometry::GenerateSnowflake(Engine::Mesh* mesh)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);
	glm::vec3 a(-0.5f, -0.5f, -2.0f);
	glm::vec3 b(0.5f, -0.5f, -2.0f);
	glm::vec3 c(0.0f, 0.5f, -2.0f);

	mesh->AddVertexData(a);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f,0.0f,1.0f,0.0f));
	mesh->AddVertexData(b);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	mesh->AddVertexData(c);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	glm::vec3 b2a = b - a;
	b2a[2] = 0.2f;

	glm::vec3 comp;
	comp[0] = a[1] - b[1];
	comp[1] = b[0] - a[0];
	comp[2] = 0.2f;

	side(a, b, 0, mesh);
	side(b, c, 0, mesh);
	side(c, a, 0, mesh);

	mesh->SetNumElements(768);
	mesh->CreateMesh();
	return;

}