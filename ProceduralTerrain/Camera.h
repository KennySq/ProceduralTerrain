#pragma once
class Camera
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	float FOV = 0.0f;
	float AspectRatio = 0.0f;
	float Near = 0.0f;
	float Far = 0.0f;

public:

	XMMATRIX& GetView() { return View; }
	XMMATRIX& GetProjection() { return Projection; }

	Camera(float FOV_, float AR_, float Near_, float Far_);
	static Camera* MakePerspectiveCamera(float FOV_, float AR_, float Near_, float Far_);
};