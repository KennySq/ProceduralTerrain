#include "stdafx.h"
#include "Camera.h"

Camera::Camera(float FOV_, float AR_, float Near_, float Far_)
{
	FOV = FOV_;
	AspectRatio = AR_;
	Near = Near_;
	Far = Far_;

	View = XMMatrixLookAtLH(XMVectorSet(50.0,50.0f,50.0f, 1.0f), 
					 XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
					 XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));

	Projection = XMMatrixPerspectiveFovLH(FOV_, AR_, Near_, Far_);

}

Camera* Camera::MakePerspectiveCamera(float FOV_, float AR_, float Near_, float Far_)
{
	
	return new Camera(FOV_, AR_, Near_, Far_);
}
