#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <RenderObject.hpp>
#include <Mesh.hpp>
#include <Material.hpp>

/*
 * TODO: Inherit RenderObject class to implement animation
 */
class Snowflake: public Engine::RenderObject
{
private:
	
public:
	float xmean;
	float delx;
	float rotspeed;
	float tmelt;
    Snowflake(Engine::Mesh* mesh, Engine::Material* material);

	/*
	void SetPosition(glm::vec3 pos);
	void SetOrientation(glm::mat4 mat);
	*/
    // Add more functions
};