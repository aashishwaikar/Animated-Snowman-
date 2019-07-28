// STL
#include <iostream>
#include <math.h>
#include <stdlib.h>

// include opengl extension and application library
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// include Engine
#include <Camera.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <RenderObject.hpp>

// include application headers
#include <Sphere.hpp>
#include <DefaultMaterial.hpp>
#include <PickingMaterial.hpp>
#include <LineMaterial.hpp>
#include <Geometry.hpp>
#include <Animation.hpp>
#include <picking.hpp>
#include <PickableObject.hpp>
#include <Snowman.hpp>

#define _USE_MATH_DEFINES

GLFWwindow* g_window;
float g_window_width = 1024.f;
float g_window_height = 768.f;
int g_framebuffer_width = 1024;
int g_framebuffer_height = 768;


bool head_spin = false;
bool body_spin = false;
bool wdir = false;
bool frown = false;
bool nod = false;
bool stand = false;
bool walk = false;

float buf = 0.0f;

void GenerateGradientRectangle(Engine::Mesh* mesh)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);
	//pos
	glm::vec3 a(-10.0f, -8.0f, -5.0f);
	glm::vec3 b(10.0f, -8.0f, -5.0f);
	glm::vec3 c(10.0f, 8.0f, -5.0f);
	glm::vec3 d(-10.0f, 8.0f, -5.0f);

	//glm::vec3 normal = glm::normalize(glm::cross(a-b, c-a));
	glm::vec4 n(0.0f, 0.0f, 1.0f, 0.0f);
	//col
	//glm::vec3 a1(0.0f, 1.0f, 1.0f);
	//glm::vec3 b1(0.0f, 1.0f, 1.0f);
	//glm::vec3 c1(1.0f, 0.0f, 1.0f);
	//glm::vec3 d1(1.0f, 0.0f, 1.0f);

	mesh->AddVertexData(a);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(n);
	
	mesh->AddVertexData(b);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(n);
	
	mesh->AddVertexData(c);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(n);
	
	mesh->AddVertexData(c);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(n);
	
	mesh->AddVertexData(d);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(n);
	
	mesh->AddVertexData(a);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(n);
	
	mesh->SetNumElements(6);
	mesh->CreateMesh();
	return;
	//return;
}

// TODO: Implement custom type mesh generator for background object
void GenerateBackgroundMeshType1(Engine::Mesh* mesh)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);

	glm::vec3 a(-9.5f, -4.5f, 0.0f);
	glm::vec3 b(1.5f, -4.5f, 0.0f);
	glm::vec3 c(-4.0f, 1.0f, 0.0f);

	glm::vec3 a1(0.0f, 1.0f, 1.0f);
	glm::vec3 b1(0.0f, 1.0f, 1.0f);
	glm::vec3 c1(0.0f, 0.8f, 0.4f);

	mesh->AddVertexData(a);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(a1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(b);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(b1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(c);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(c1);
	mesh->AddVertexData(1.0f);

	glm::vec3 g(-6.0f, -4.0f, 0.0f);
	glm::vec3 h(2.0f, -4.0f, 0.0f);
	glm::vec3 i(-2.0f, 0.0f, 0.0f);

	glm::vec3 g1(0.0f, 1.0f, 1.0f);
	glm::vec3 h1(0.0f, 1.0f, 1.0f);
	glm::vec3 i1(0.2f, 1.0f, 0.6f);

	mesh->AddVertexData(g);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(g1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(h);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(h1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(i);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(i1);
	mesh->AddVertexData(1.0f);

	glm::vec3 j(-3.4f, -4.0f, 0.0f);
	glm::vec3 k(3.6f, -4.0f, 0.0f);
	glm::vec3 l(0.1f, -0.5f, 0.0f);

	glm::vec3 j1(0.0f, 1.0f, 1.0f);
	glm::vec3 k1(0.0f, 1.0f, 1.0f);
	glm::vec3 l1(0.4f, 1.0f, 0.75f);

	mesh->AddVertexData(j);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(j1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(k);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(k1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(l);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(l1);
	mesh->AddVertexData(1.0f);

	glm::vec3 d(0.25f, -4.5f, 0.1f);
	glm::vec3 e(9.75f, -4.5f, 0.1f);
	glm::vec3 f(5.0f, 0.5f, 0.1f);

	glm::vec3 d1(0.0f, 1.0f, 1.0f);
	glm::vec3 e1(0.0f, 1.0f, 1.0f);
	glm::vec3 f1(0.0f, 0.8f, 0.4f);

	mesh->AddVertexData(d);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(d1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(e);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(e1);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(f);
	mesh->AddVertexData(1.0f);
	mesh->AddVertexData(f1);
	mesh->AddVertexData(1.0f);
	mesh->SetNumElements(12);
	mesh->CreateMesh();
	return;
}

// TODO: Fill up GLFW mouse button callback function
static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods)
{
    //example code for get x position and y position of mouse click
    if (a_button == GLFW_MOUSE_BUTTON_LEFT && a_action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(a_window, &xpos, &ypos);
        xpos = xpos / ((double)g_window_width) * ((double)g_framebuffer_width);
        ypos = ypos / ((double)g_window_height) * ((double)g_framebuffer_height);
        int target = pick((int)xpos, (int)ypos, g_framebuffer_width, g_framebuffer_height);
        std::cout << "Picked object index: " << target << std::endl;

		if (target == 1)
		{
			head_spin = !head_spin;
		}
		if (target == 2)
		{
			body_spin = !body_spin;
		}
    }
}





// TODO: Fill up GLFW cursor position callback function
static void CursorPosCallback(GLFWwindow* a_window, double a_xpos, double a_ypos)
{

}

static void KeyboardCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
{
    if (a_action == GLFW_PRESS)
    {
        switch (a_key)
        {
        case GLFW_KEY_H:
            std::cout << "CS380 Homework 2" << std::endl;
            std::cout << "keymaps:" << std::endl;
            std::cout << "h\t\t Help command" << std::endl;
            break;
		case GLFW_KEY_R:
			std::cout << "Presses R" << std::endl;
			body_spin = !body_spin;
			break;

		case GLFW_KEY_F:
			std::cout << "Presses F" << std::endl;
			frown = !frown;
			break;

		case GLFW_KEY_N:
			std::cout << "Presses N" << std::endl;
			nod = !nod;
			break;

		case GLFW_KEY_S:
			std::cout << "Presses S" << std::endl;
			stand = !stand;
			break;

		case GLFW_KEY_W:
			std::cout << "Presses W" << std::endl;
			walk = !walk;
			break;
        default:
            break;
        }
    }
}
/*
void nod(float del_t)
{
	->SetOrientation(glm::rotate(body->GetOrientation(), glm::radians(del_t*20.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
}
*/

int main(int argc, char** argv)
{
    // Initialize GLFW library
    if (!glfwInit())
    {
        return -1;
    }

    // Create window and OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    g_window = glfwCreateWindow(g_window_width, g_window_height, "HW2 - Do you want to build a snowman?", NULL, NULL);
    if (!g_window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(g_window);

    // Initialize GLEW library
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK)
    {
        std::cout << "GLEW Error: " << glewGetErrorString(glew_error) << std::endl;
        exit(1);
    }


    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

    glfwSetInputMode(g_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(g_window, MouseButtonCallback);
    glfwSetCursorPosCallback(g_window, CursorPosCallback);
    glfwSetKeyCallback(g_window, KeyboardCallback);

    // Initialize framebuffer object and picking textures
    pickingInitialize(g_framebuffer_width, g_framebuffer_width);

    Engine::Camera* main_camera = new Engine::Camera();
    main_camera->SetPosition(glm::vec3(0.0f, 0.0f, 7.5f));

	Engine::Mesh* bmesh = new Engine::Mesh();
	//geomGenerateTriangleMesh(bmesh);
	
	//Engine::RenderObject brenderObject = Engine::RenderObject(bmesh, bmaterial);
    // TODO: Create mesh and material (in main.cpp) Slide No. 10 (Define cube mesh, material), No. 18 (Define pickable object)
	//Sphere sph = Sphere();
	Geometry geometry = Geometry();
	GenerateGradientRectangle(bmesh);
	DefaultMaterial* bmaterial = new DefaultMaterial();
	bmaterial->CreateMaterial();
	bmaterial->UpdateColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	DefaultMaterial* s1material = new DefaultMaterial();
	DefaultMaterial* s2material = new DefaultMaterial();
	DefaultMaterial* s3material = new DefaultMaterial();
	DefaultMaterial* s4material = new DefaultMaterial();
	DefaultMaterial* s5material = new DefaultMaterial();
	DefaultMaterial* s6material = new DefaultMaterial();
	DefaultMaterial* s7material = new DefaultMaterial();
	DefaultMaterial* s8material = new DefaultMaterial();

	DefaultMaterial* s9material = new DefaultMaterial();
	DefaultMaterial* s10material = new DefaultMaterial();
	DefaultMaterial* s11material = new DefaultMaterial();
	DefaultMaterial* s12material = new DefaultMaterial();
	DefaultMaterial* s13material = new DefaultMaterial();
	DefaultMaterial* s14material = new DefaultMaterial();
	DefaultMaterial* s15material = new DefaultMaterial();
	DefaultMaterial* s16material = new DefaultMaterial();

	s1material->CreateMaterial();
	s1material->UpdateColor(glm::vec4(0.5f, 0.5f, 0.5f,1.0f));
	s2material->CreateMaterial();
	s2material->UpdateColor(glm::vec4(0.0f, 0.5f, 0.5f,1.0f));
	s3material->CreateMaterial();
	s3material->UpdateColor(glm::vec4(1.0f, 0.5f, 0.0f,1.0f));
	s4material->CreateMaterial();
	s4material->UpdateColor(glm::vec4(1.0f, 0.2f, 1.0f,1.0f));
	s5material->CreateMaterial();
	s5material->UpdateColor(glm::vec4(0.75f, 0.4f, 1.0f,1.0f));
	s6material->CreateMaterial();
	s6material->UpdateColor(glm::vec4(1.0f, 0.0f, 0.0f,1.0f));
	s7material->CreateMaterial();
	s7material->UpdateColor(glm::vec4(0.4f, 1.0f, 0.75f,1.0f));
	s8material->CreateMaterial();
	s8material->UpdateColor(glm::vec4(0.6f, 0.0f, 0.0f,1.0f));
	s9material->CreateMaterial();
	s9material->UpdateColor(glm::vec4(0.4f, 0.2f, 0.0f,1.0f));
	s10material->CreateMaterial();
	s10material->UpdateColor(glm::vec4(0.0f, 0.4f, 0.8f,1.0f));
	s11material->CreateMaterial();
	s11material->UpdateColor(glm::vec4(0.2f, 0.0f, 0.1f,1.0f));
	s12material->CreateMaterial();
	s12material->UpdateColor(glm::vec4(0.4f, 0.4f, 1.0f,1.0f));
	s13material->CreateMaterial();
	s13material->UpdateColor(glm::vec4(0.5f, 0.7f, 0.9f,1.0f));
	s14material->CreateMaterial();
	s14material->UpdateColor(glm::vec4(0.7f, 0.9f, 0.5f,1.0f));
	s15material->CreateMaterial();
	s15material->UpdateColor(glm::vec4(0.9f, 0.5f, 0.7f,1.0f));
	s16material->CreateMaterial();
	s16material->UpdateColor(glm::vec4(0.6f, 0.0f, 0.0f,1.0f));


	Engine::Mesh* mesh = new Engine::Mesh();
	//float r = 0.05f;
	//float h = 1.5f;
	geometry.GenerateSnowflake(mesh);

	Engine::Mesh* cy_mesh = new Engine::Mesh();
	float r = 0.05f;
	float h = 1.5f;
	geometry.GenerateCylinder(cy_mesh, h,r);

	Engine::Mesh* cy_mesh2 = new Engine::Mesh();
	float rcy = 0.05f;
	float hcy = 0.5f;
	geometry.GenerateCylinder(cy_mesh2, hcy, rcy);

	Engine::Mesh* cy_mesh1 = new Engine::Mesh();
	float rn = 0.16f;
	float hn = 0.5f;
	geometry.GenerateCylinder(cy_mesh1, hn, rn);

	Engine::Mesh* cone_mesh = new Engine::Mesh();
	float r3 = 0.2f;
	float h3 = 1.0f;
	geometry.GenerateCone(cone_mesh, h3, r3);

	

	Engine::Mesh* tree_mesh = new Engine::Mesh();
	//float rt = 4.0f;
	//float ht = 2.5f;
	geometry.GenerateTriangleMesh(tree_mesh);

	Engine::Mesh* eye_mesh = new Engine::Mesh();
	float re = 0.08f;
	float he = 0.3f;
	geometry.GenerateCone(eye_mesh, he, re);

	Engine::Mesh* cap_mesh = new Engine::Mesh();
	float rc = 0.4f;
	float hc = 1.0f;
	geometry.GenerateCone(cap_mesh, hc, rc);

    Engine::Mesh* sph_mesh = new Engine::Mesh();
	float r2 = 1.0f;
    geometry.GenerateSphere(sph_mesh,r2);

	Engine::Mesh* sph_mesh1 = new Engine::Mesh();
	float r1 = 0.68f;
	geometry.GenerateSphere(sph_mesh1, r1);

	Engine::Mesh* sph_mesh2 = new Engine::Mesh();
	float rs2 = 0.1f;
	geometry.GenerateSphere(sph_mesh2, rs2);

	Engine::Mesh* sph_mesh3 = new Engine::Mesh();
	float rs3 = 0.2f;
	geometry.GenerateSphere(sph_mesh3, rs3);

	Engine::Mesh* sph_mesh4 = new Engine::Mesh();
	float rs4 = 0.06f;
	geometry.GenerateSphere(sph_mesh4, rs4);

	Animation* animation = new Animation();

	Engine::Mesh* star_mesh = new Engine::Mesh();
	geometry.GenerateStar(star_mesh);
	Engine::RenderObject brenderObject = Engine::RenderObject(bmesh, bmaterial);
    DefaultMaterial* material = new DefaultMaterial();
    material->CreateMaterial();

	Snowflake exampleSnowflake = Snowflake(mesh, s1material);
	Snowflake exampleSnowflake2 = Snowflake(mesh, s2material);
	Snowflake exampleSnowflake3 = Snowflake(mesh, s3material);
	Snowflake exampleSnowflake4 = Snowflake(mesh, s4material);
	Snowflake exampleSnowflake5 = Snowflake(mesh, s5material);
	Snowflake exampleSnowflake6 = Snowflake(mesh, s6material);
	Snowflake exampleSnowflake7 = Snowflake(mesh, s7material);
	Snowflake exampleSnowflake8 = Snowflake(mesh, s8material);
	Snowflake exampleSnowflake9 = Snowflake(mesh, s9material);
	Snowflake exampleSnowflake10 = Snowflake(mesh, s10material);
	Snowflake exampleSnowflake11 = Snowflake(mesh, s11material);
	Snowflake exampleSnowflake12 = Snowflake(mesh, s12material);
	Snowflake exampleSnowflake13 = Snowflake(mesh, s13material);
	Snowflake exampleSnowflake14 = Snowflake(mesh, s14material);
	Snowflake exampleSnowflake15 = Snowflake(mesh, s15material);
	Snowflake exampleSnowflake16 = Snowflake(mesh, s16material);

	exampleSnowflake2.SetPosition(glm::vec3(1.0f, 3.0f, 0.0f));
	exampleSnowflake2.xmean = 1.0f;
	exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake3.SetPosition(glm::vec3(3.0f, 4.0f, 0.0f));
	exampleSnowflake3.xmean = 3.0f;
	//exampleSnowflake3.rotspeed = 1.4f;

	exampleSnowflake4.SetPosition(glm::vec3(5.0f, 4.0f, 0.0f));
	exampleSnowflake4.xmean = 5.0f;
	//exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake5.SetPosition(glm::vec3(-2.0f, 3.0f, 0.0f));
	exampleSnowflake5.xmean = -2.0f;
	//exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake6.SetPosition(glm::vec3(-3.0f, 2.0f, 0.0f));
	exampleSnowflake6.xmean = -3.0f;
	exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake7.SetPosition(glm::vec3(-4.0f, 3.0f, 0.0f));
	exampleSnowflake7.xmean = -4.0f;
	//exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake8.SetPosition(glm::vec3(-5.0f, 2.0f, 0.0f));
	exampleSnowflake8.xmean = -5.0f;
	//exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake9.SetPosition(glm::vec3(1.0f, 5.0f, 0.0f));
	exampleSnowflake9.xmean = 1.0f;
	exampleSnowflake9.rotspeed = 1.4f;

	exampleSnowflake10.SetPosition(glm::vec3(3.0f, 7.4f, 0.0f));
	exampleSnowflake10.xmean = 3.0f;
	//exampleSnowflake3.rotspeed = 1.4f;

	exampleSnowflake11.SetPosition(glm::vec3(5.0f, 6.0f, 0.0f));
	exampleSnowflake11.xmean = 5.0f;
	exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake12.SetPosition(glm::vec3(-2.0f, 7.0f, 0.0f));
	exampleSnowflake12.xmean = -2.0f;
	//exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake13.SetPosition(glm::vec3(-3.0f, 5.0f, 0.0f));
	exampleSnowflake13.xmean = -3.0f;
	exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake14.SetPosition(glm::vec3(-4.0f, 5.0f, 0.0f));
	exampleSnowflake14.xmean = -4.0f;
	//exampleSnowflake2.rotspeed = 1.4f;

	exampleSnowflake15.SetPosition(glm::vec3(-5.0f, 6.1f, 0.0f));
	exampleSnowflake15.xmean = -5.0f;
	//exampleSnowflake2.rotspeed = 1.4f;

	animation->AddSnowflake(&exampleSnowflake);
	animation->AddSnowflake(&exampleSnowflake2);
	animation->AddSnowflake(&exampleSnowflake3);
	animation->AddSnowflake(&exampleSnowflake4);
	animation->AddSnowflake(&exampleSnowflake5);
	animation->AddSnowflake(&exampleSnowflake6);
	animation->AddSnowflake(&exampleSnowflake7);
	animation->AddSnowflake(&exampleSnowflake8);
	animation->AddSnowflake(&exampleSnowflake9);
	animation->AddSnowflake(&exampleSnowflake10);
	animation->AddSnowflake(&exampleSnowflake11);
	animation->AddSnowflake(&exampleSnowflake12);
	animation->AddSnowflake(&exampleSnowflake13);
	animation->AddSnowflake(&exampleSnowflake14);
	animation->AddSnowflake(&exampleSnowflake15);

    PickingMaterial* picking_material = new PickingMaterial();
    picking_material->CreateMaterial();

	//material->UpdateColor(glm::vec4(1.0f, 0.0f, 1.0f,0.0f));
    PickableObject cube1 = PickableObject(sph_mesh1, material);
    cube1.SetPickingMat(picking_material);
    cube1.SetPosition(glm::vec3(0.0f, 1.2f, 0.0f));
	//cube1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
    cube1.SetIndex(1);

	Engine::RenderObject leaf = Engine::RenderObject(tree_mesh, material);
	leaf.SetPosition(glm::vec3(3.5, -4.5, -2.1));

	Engine::RenderObject leaf1 = Engine::RenderObject(tree_mesh, material);
	leaf1.SetPosition(glm::vec3(-3.4, -3.5, -2.1));
	//leaf1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

	//Engine::RenderObject igloo = Engine::RenderObject(igloo_mesh, material);
	//igloo.SetOrientation(glm::rotate(igloo.GetOrientation(), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	//igloo.SetPosition

	PickableObject nose =PickableObject(cone_mesh, material);
	//nose.SetPickingMat(picking_material);
	nose.SetPosition(glm::vec3(0.0f, 0.1f, 0.2f));
	nose.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	nose.SetIndex(3);

	PickableObject cap = PickableObject(cap_mesh, material);
	//nose.SetPickingMat(picking_material);
	cap.SetPosition(glm::vec3(0.0f, 0.48f, -0.3f));
	cap.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	cap.SetIndex(10);

	PickableObject arm1 = PickableObject(cy_mesh, material);
	//nose.SetPickingMat(picking_material);
	arm1.SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	arm1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	arm1.SetIndex(4);

	PickableObject hand1 = PickableObject(cy_mesh2, material);
	//nose.SetPickingMat(picking_material);
	hand1.SetPosition(glm::vec3(0.0f, 1.46f, 0.0f));
	hand1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.5f, 0.0f, 1.0f)));
	hand1.SetIndex(15);

	PickableObject finger1 = PickableObject(sph_mesh4, material);
	//nose.SetPickingMat(picking_material);
	finger1.SetPosition(glm::vec3(0.0f, 0.50f, 0.0f));
	//finger1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.5f, 0.0f, 0.0f)));
	finger1.SetIndex(17);

	PickableObject arm2 = PickableObject(cy_mesh, material);
	//nose.SetPickingMat(picking_material);
	arm2.SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	arm2.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(-50.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	arm2.SetIndex(5);

	PickableObject hand2 = PickableObject(cy_mesh2, material);
	//nose.SetPickingMat(picking_material);
	hand2.SetPosition(glm::vec3(0.0f, 1.46f, 0.0f));
	hand2.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.5f, 0.0f, -1.0f)));
	hand2.SetIndex(16);

	PickableObject finger2 = PickableObject(sph_mesh4, material);
	//nose.SetPickingMat(picking_material);
	finger2.SetPosition(glm::vec3(0.0f, 0.5f, 0.0f));
	//finger1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.5f, 0.0f, 0.0f)));
	finger2.SetIndex(18);

	PickableObject leg1 = PickableObject(cy_mesh1, material);
	//nose.SetPickingMat(picking_material);
	leg1.SetPosition(glm::vec3(0.3f, -0.75f, 0.0f));
	leg1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	leg1.SetIndex(6);

	PickableObject leg11 = PickableObject(sph_mesh3, material);
	//nose.SetPickingMat(picking_material);
	//leg11.SetPosition(glm::vec3(0.5f, -1.1f, 0.6f));
	leg11.SetPosition(glm::vec3(0.0f, 0.45f, 0.0f));
	//leg1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, -0.3f)));
	leg11.SetIndex(11);
	PickableObject leg12 = PickableObject(sph_mesh3, material);
	//nose.SetPickingMat(picking_material);
	//leg11.SetPosition(glm::vec3(0.5f, -1.1f, 0.6f));
	leg12.SetPosition(glm::vec3(0.0f, -0.15f, 0.0f));
	//leg1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, -0.3f)));
	leg12.SetIndex(13);

	PickableObject leg2 = PickableObject(cy_mesh1, material);
	//nose.SetPickingMat(picking_material);
	leg2.SetPosition(glm::vec3(-0.3f, -0.75f, 0.0f));
	leg2.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	leg2.SetIndex(7);

	PickableObject leg21 = PickableObject(sph_mesh3, material);
	//nose.SetPickingMat(picking_material);
	//leg21.SetPosition(glm::vec3(-0.5f, -1.1f, 0.6f));
	leg21.SetPosition(glm::vec3(0.0f, 0.45f, 0.0f));
	//leg1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, -0.3f)));
	leg21.SetIndex(12);

	PickableObject leg22 = PickableObject(sph_mesh3, material);
	//nose.SetPickingMat(picking_material);
	//leg21.SetPosition(glm::vec3(-0.5f, -1.1f, 0.6f));
	leg22.SetPosition(glm::vec3(0.0f, -0.15f, 0.0f));
	//leg1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, -0.3f)));
	leg22.SetIndex(14);

	PickableObject eyes = PickableObject(sph_mesh2, material);
	//cube1.SetPickingMat(picking_material);
	//eyes.SetPosition(glm::vec3(0.3f, 0.45f, 0.5f));
	eyes.SetPosition(glm::vec3(0.2f, 0.45f, 0.43f));
	//eyes.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	eyes.SetIndex(8);

	PickableObject eyes1 = PickableObject(sph_mesh2, material);
	//cube1.SetPickingMat(picking_material);
	eyes1.SetPosition(glm::vec3(-0.2f, 0.45f, 0.43f));
	//cube1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	eyes1.SetIndex(9);
	/*
	PickableObject arm2 = PickableObject(cy_mesh, material);
	//nose.SetPickingMat(picking_material);
	arm2.SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	arm2.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(-50.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	arm2.SetIndex(5);
	*/
	//material->UpdateColor(glm::vec4(1.0f, 0.5f, 1.0f, 0.0f));
    PickableObject cube2 = PickableObject(sph_mesh, material);
    cube2.SetPickingMat(picking_material);
    cube2.SetPosition(glm::vec3(0.0f, -1.5f, 0.0f));
	//cube2.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    cube2.SetIndex(2);
    // TODO: Add parent (cube2) to cube1 (Slide No. 14)
    cube1.AddParent(&cube2);
	nose.AddParent(&cube1);
	arm1.AddParent(&cube2);
	hand1.AddParent(&arm1);
	finger1.AddParent(&hand1);
	arm2.AddParent(&cube2);
	hand2.AddParent(&arm2);
	finger2.AddParent(&hand2);
	leg1.AddParent(&cube2);
	leg11.AddParent(&leg1);
	leg12.AddParent(&leg1);
	leg2.AddParent(&cube2);
	leg21.AddParent(&leg2);
	leg22.AddParent(&leg2);
	eyes.AddParent(&cube1);
	eyes1.AddParent(&cube1);
	cap.AddParent(&cube1);
	Snowman snowman = Snowman();
	snowman.head = &cube1;
	snowman.body = &cube2;
	

	// Create star objects
	/*
	for (int i = 0; i < 20; i++)
	{
		Engine::RenderObject* star = new Engine::RenderObject(star_mesh, bmaterial);
		star->SetPosition(glm::vec3(-5.0f + 10.0f * ((rand() % 255) / 255.0f), 5.0f * ((rand() % 255) / 255.0f), 0.0f));
		star->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
		animation->AddObject(star);
	}
	*/
    float prev_time = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(g_window) && glfwGetKey(g_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float total_time = (float)glfwGetTime();
        float elapsed_time = total_time - prev_time;
        prev_time = total_time;
		
		if (head_spin)
		{
			snowman.rotate_head(elapsed_time);
		}
		if (body_spin)
		{
			snowman.rotate_body(elapsed_time);
		}

		if (walk)
		{
			snowman.walking(elapsed_time);
		}
        // First Pass: Object Selection (Slide No. 20)
        // this is for picking the object using mouse interaction
        // binding framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, picking_fbo);
        // Background: RGB = 0x000000 => objectID: 0
        glClearColor((GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render your objects that you want to select using mouse interaction here
        cube1.RenderPicking(main_camera);
        cube2.RenderPicking(main_camera);
        
        // Second Pass: Object Rendering (Slide No. 11)
        // Drawing object again
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor((GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Todo: Render object with main camera in the loop
		if(frown) eyes.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

		if (stand)
		{
			leg1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
			leg2.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		}
		if (walk)
		{
			if (!wdir)
			{
				cube1.SetOrientation(glm::rotate(cube1.GetOrientation(), glm::radians(-14.0f * elapsed_time), glm::vec3(0.0f, 1.0f, 0.0f)));
				leg1.SetOrientation(glm::rotate(leg1.GetOrientation(), glm::radians(40.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				arm1.SetOrientation(glm::rotate(arm1.GetOrientation(), glm::radians(-20.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				arm2.SetOrientation(glm::rotate(arm2.GetOrientation(), glm::radians(20.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				leg2.SetOrientation(glm::rotate(leg2.GetOrientation(), glm::radians(-40.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				if(buf>=0.0f) cube2.SetOrientation(glm::rotate(cube2.GetOrientation(), glm::radians(4.5f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				else cube2.SetOrientation(glm::rotate(cube2.GetOrientation(), glm::radians(-4.5f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				buf += 40.0f*elapsed_time;
				if (buf >= 25.0f)
				{
					wdir = !wdir;
					//buf = 0.0f;
				}
			}
			else
			{
				cube1.SetOrientation(glm::rotate(cube1.GetOrientation(), glm::radians(14.0f * elapsed_time), glm::vec3(0.0f, 1.0f, 0.0f)));
				leg1.SetOrientation(glm::rotate(leg1.GetOrientation(), glm::radians(-40.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				arm1.SetOrientation(glm::rotate(arm1.GetOrientation(), glm::radians(+20.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				arm2.SetOrientation(glm::rotate(arm2.GetOrientation(), glm::radians(-20.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				leg2.SetOrientation(glm::rotate(leg2.GetOrientation(), glm::radians(40.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				if(buf>=0.0f) cube2.SetOrientation(glm::rotate(cube2.GetOrientation(), glm::radians(-4.5f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				else cube2.SetOrientation(glm::rotate(cube2.GetOrientation(), glm::radians(4.5f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
				buf -= 40.0f*elapsed_time;
				if (buf <= -25.0f) 
				{
					wdir = !wdir;
					//buf = 0.0f;
				}
			}
		}
		//if(jump)

		bmaterial->UpdateColor(glm::vec4(1.0f, 0.6f, 0.4f, 1.0f));
		brenderObject.Render(main_camera);
		
		material->UpdateColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		eyes.Render(main_camera);
		eyes1.Render(main_camera);
		material->UpdateColor(glm::vec4(1.0f, 0.3f, 0.0f, 1.0f));
		nose.Render(main_camera);
		material->UpdateColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		cap.Render(main_camera);
        material->UpdateColor(glm::vec4(0.6f, 0.26f, 0.0f, 1.0f));
		leg1.Render(main_camera);
		leg2.Render(main_camera);
		//material->UpdateColor(glm::vec4(0.8f, 0.0f, 0.0f, 1.0f));
		leg11.Render(main_camera);
		leg12.Render(main_camera);
		leg21.Render(main_camera);
		leg22.Render(main_camera);
		material->UpdateColor(glm::vec4(0.4f, 0.2f, 0.0f, 1.0f));
		arm1.Render(main_camera);
		hand1.Render(main_camera);
		finger1.Render(main_camera);
		arm2.Render(main_camera);
		hand2.Render(main_camera);
		finger2.Render(main_camera);
		material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        cube1.Render(main_camera);
        material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        cube2.Render(main_camera);
		material->UpdateColor(glm::vec4(0.0f, 1.0f, 0.01f, 1.0f));
		leaf.Render(main_camera);
		material->UpdateColor(glm::vec4(0.005f, 1.0f, 0.0f, 1.0f));
		leaf1.Render(main_camera);

		material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		
			//arm1.SetOrientation(glm::rotate(arm1.GetOrientation(), glm::radians(+20.0f * elapsed_time), glm::vec3(1.0f, 0.0f, 0.0f)));
		//igloo.Render(main_camera);
		/*
		material->UpdateColor(glm::vec4(1.0f, 215.0f/ 256.0f, 1.0f,1.0f));
		*/
		animation->Animate(1.0f);
		
        /* Swap front and back buffers */
        glfwSwapBuffers(g_window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Delete resources
    delete main_camera;

    glfwTerminate();
    return 0;

}