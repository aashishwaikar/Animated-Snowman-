#include <Animation.hpp>

Animation::Animation()
{
    _snowflakes = std::vector<Snowflake*>();
	previous_t = 0;
	current_t = 0;
	dir = 1;
}

Animation::~Animation()
{
    _snowflakes.clear();
}

void Animation::AddSnowflake(Snowflake* snowflake)
{
    _snowflakes.push_back(snowflake);
}

void Animation::Animate(float deltaTime)
{	
	Engine::Camera* aCam = new Engine::Camera();
	current_t = glfwGetTime();
	std::vector<Snowflake*> ::iterator it;

	aCam->SetPosition(glm::vec3(0.0f, 0.0f, 7.5f));

	double t_gap = current_t - previous_t;
	//(_snowflakes[1])->SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));

	for(it = _snowflakes.begin(); it != _snowflakes.end(); it++)
	{
		glm::vec3 p = (*it)->GetPosition();
		glm::mat4 o = (*it)->GetOrientation();

		//glm::vec3 del;
		if (dir==1)
		{
			if (p[0] < 0.6f + (*it)->xmean)
			{
				p[0] += 0.4f * t_gap / deltaTime;
			}
			else
			{
				p[0] -= 0.4f * t_gap / deltaTime;
				dir = 0;
			}
			
		}
		else
		{
			if (p[0] > 0.0f + (*it)->xmean)
			{
				p[0] -= 0.4f * t_gap / deltaTime;
			}
			else
			{
				p[0] += 0.4f * t_gap / deltaTime;
				dir = 1;
			}

		}

		if (p[1] < -6.0f)
		{
			//p[0] += 0.4f * t_gap / deltaTime;
			//(*it)->SetMaterial
			
			//if ((*it)->tmelt < 0.0f)
			//{
			//	(*it)->tmelt = 3.0f;
				p[1] = 7.0f;
			//p[1] -= 0.5f * t_gap / deltaTime;
			//}
			//else
			//{
				//p[1] = -40f;
				//(*it)->tmelt = (*it)->tmelt - 1.0f;
			//}
			
		}
		else if (p[1] < -4.0f)
		{
			//p[1] = 7.0f;
			p[1] -= 0.4f * t_gap / deltaTime;
		}
		else
		{
			p[1] -= 1.0f * t_gap / deltaTime;
			//dir = 0;
		}

		float c = cos(((*it)->rotspeed)*3.0f*t_gap / deltaTime);
		float s = sin(((*it)->rotspeed)*3.0f*t_gap / deltaTime);
		/*
		float rvec[16] = {
			c, -1.0f * s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		*/
		glm::mat4 rot;// = glm::make_mat4(rvec);
		rot[0][0] = c;
		rot[0][1] = -1.0f * s;
		rot[0][2] = 0;
		rot[0][3] = 0;
		rot[1][0] = s;
		rot[1][1] = c;
		rot[1][2] = 0;
		rot[1][3] = 0;
		rot[2][0] = 0;
		rot[2][1] = 0;
		rot[2][2] = 1;
		rot[2][3] = 0;
		rot[3][0] = 0;
		rot[3][1] = 0;
		rot[3][2] = 0;
		rot[3][3] = 1;

		(*it)->SetPosition(p);
		(*it)->SetOrientation(o*rot);

		(*it)->Render(aCam);
	}
	
	previous_t = current_t;
	delete aCam;
	return;
}