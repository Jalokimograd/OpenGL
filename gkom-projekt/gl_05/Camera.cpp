#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->movementSpeed = 5.0f;
	this->sensitivity = 0.2f;
	this->zoom = 45.0f;
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	updateVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->movementSpeed = 2.0f;
	this->sensitivity = 0.2f;
	this->zoom = 45.0f;
	this->position = glm::vec3(posX, posY, posZ);
	this->worldUp = glm::vec3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	updateVectors();
}


Camera::~Camera()
{

}

void Camera::updateVectors()
{
	//Obliczanie nowego wektora kierunku
	glm::vec3 f;
	f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	f.y = sin(glm::radians(pitch));
	f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(f);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Keyboard(Camera_Movement direction, float deltaTime)
{
	//float movementSpeed = 0.1;
/*
	Tutaj mo¿na by by³o zastosowaæ powy¿sze rozwi¹zanie (zakomentowane) ze sta³¹ szybkoœci¹ kamery,
	ale to by oznacza³o poruszanie siê o sta³¹ odleg³oœæ za ka¿dym obiegiem pêtli. Wiemy dobrze, ¿e
	im lepsza karta graficzna tym szybciej komputer sobie z tym poradzi wiêc dla dobrych kart sta³a
	ustalona prêdkoœæ by³aba zbyt szybka i analogicznie dla s³abszych kart - wolna.
	Poni¿sze rozwi¹zanie bazuje na czasie systemowym wiêc niezale¿nie od szybkoœci g³ównej pêtli,
	poruszamy siê proporcjonalnie do czasu który up³yn¹³
*/

	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

//zmiana k¹ta widzenia scrolem
void Camera::MouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateVectors();
}

void Camera::MouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}
