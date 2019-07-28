#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PickableObject.hpp>

class Snowman
{
private:
	float deg;
	bool dir;
	bool dir1;
public:
    Snowman();
    ~Snowman();
	PickableObject* body;
	PickableObject* head;
	void rotate_head(float del_t);
	void rotate_body(float del_t);
	void walking(float del_t);
};