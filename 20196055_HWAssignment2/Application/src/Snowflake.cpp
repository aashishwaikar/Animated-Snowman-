#include <Snowflake.hpp>

/*
 * TODO: Inherit RenderObject class to implement animation
 */
Snowflake::Snowflake(Engine::Mesh* mesh, Engine::Material* material) : Engine::RenderObject(mesh, material)
{
	//Engine::RenderObject renderObject = Engine::RenderObject(mesh, material);
	xmean = 0.0f;
	rotspeed = 1.0f;
	delx = 1.2f;
	tmelt = 3.0f;
}

/*
void Snowflake::SetPosition(glm::vec3 pos) {
	this->SetPosition(pos);
}

void Snowflake::SetOrientation(glm::mat4 mat) {
	this->SetOrientation(mat);
}
*/

// Add more functions