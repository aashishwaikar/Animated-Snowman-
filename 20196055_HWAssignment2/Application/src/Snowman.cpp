#include <Snowman.hpp>
Snowman::Snowman()
{
	deg = 0.0;
	dir = 0;
	dir1 = 0;
}

Snowman::~Snowman()
{

}


void Snowman::rotate_body(float del_t)
{
	body->SetOrientation(glm::rotate(body->GetOrientation(), glm::radians(del_t*20.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Snowman::rotate_head(float del_t)
{
	float deg1 = 0;
	if(!dir)  deg1 = deg - 20.0f * del_t;
	else  deg1 = deg + 20.0f * del_t;

	if (deg1 < -8.0f) dir = 1;
	if (deg1 > 8.0f) dir = 0;
	if (!dir)
	{
		head->SetOrientation(glm::rotate(head->GetOrientation(), glm::radians(-10.0f * del_t), glm::vec3(1.0f, 0.0f, 0.0f)));
		deg -= 10.0f * del_t;
	}
	else
	{
		head->SetOrientation(glm::rotate(head->GetOrientation(), glm::radians(10.0f * del_t), glm::vec3(1.0f, 0.0f, 0.0f)));
		deg += 10.0f * del_t;
	}
}

void Snowman::walking(float del_t)
{
		//body->SetPosition(body->GetPosition()+glm::vec3(0.0f,0.0f,10*del_t));
	
}