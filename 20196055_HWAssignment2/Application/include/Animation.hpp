#pragma once

#include <vector>
//#include <GLFW/glfw3.h>
#include <Snowflake.hpp>
#include<cmath>

/*
 * Animation class supports continuous animation by changing RenderObject's transform with elasped time in seconds
 */

class Animation
{
private:
    std::vector<Snowflake*> _snowflakes;
	double previous_t;
	double current_t;
	bool dir;
public:
    Animation();
    ~Animation();
    void AddSnowflake(Snowflake* snowflake);
    void Animate(float deltaTime);
};