#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


class Camera
{
	void updateVectors();

public:
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	float yaw;
	float pitch;

	float sensitivity;		//Czu³oœæ myszy. Mo¿ecie zmieniaæ jak wam nie pasuje
	float zoom;
	float movementSpeed;

	//pocz¹tkowe po³o¿enie kamery
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~Camera();

	glm::mat4 GetViewMatrix();
	void Keyboard(Camera_Movement direction, float deltaTime);
	void MouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void MouseScroll(float yoffset);
};

