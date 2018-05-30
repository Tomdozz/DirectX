//
//  Camera.h
//
//	Basic camera class
//

#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

class camera_t
{
public:

	float vfov, aspect;	// Aperture attributes
	float zNear, zFar;	// Clip planes
						// zNear should be >0
						// zFar should depend on the size of the scene
	vec3f position;
	vec3f lookAt; //Use later to see where camera is lookning
	mat4f rotation;
	
	float yaww, pitchh;

	camera_t(
		float vfov,
		float aspect,
		float zNear,
		float zFar) :
		vfov(vfov), aspect(aspect), zNear(zNear), zFar(zFar)
	{

	}

	// Move to an absolute position
	//
	void moveTo(const vec3f& p)
	{
		position = p;
	}

	// Move relatively
	// old move
	void move(const vec3f& v)
	{
		//vec4f temp = get_WorldToViewMatrix() * vec4f(0, 0, -1, 0);
		position += v;// *temp.xyz();
	}
	void MoveT(const vec3f& v)
	{
		vec4f temp = v.xyz0();
		vec4f dir = get_ViewToWorldMatrix() *temp;
		position += dir.xyz();// *temp.xyz();
	}	
	
	//call in update wit mousePos
	void Rotation(float pitch, float yaw)
	{
		//roterar kameran, på y och z axeln
		rotation = mat4f::rotation(0, yaw*0.5f, pitch*0.5f);	
	}
	
	// Return World-to-View matrix for this camera
	//
	mat4f get_WorldToViewMatrix()
	{
		// Assuming a camera's position and rotation is defined by matrices T(p) and R,
		// the View-to-World transform is T(p)*R (for a first-person style camera)
		// World-to-View then is the inverse of T*R;
		//	inverse(T(p)*R) = inverse(R)*inverse(T(p)) = transpose(R)*T(-p)
		// Since now there is no rotation, this matrix is simply T(-p)

				//rotation(theta(rotationsmatrisen), positionen den roterar runt)
	/*	return transpose(rotation)* mat4f::translation(-position);*/
		return  mat4f::translation(-position)*transpose(rotation);

		//return mat4f::translation(-position);
	}

	mat4f get_ViewToWorldMatrix()
	{
		//return rotation* mat4f::translation(position);
		return mat4f::translation(position)* rotation;
			//mat4f::rotation(0, yaww, pitchh);
	}

	// Matrix transforming from View space to Clip space
	// In a performance sensitive situation this matrix can be precomputed, as long as
	// all parameters are constant (which typically is the case)
	//
	mat4f get_ProjectionMatrix()
	{
		return mat4f::projection(vfov, aspect, zNear, zFar);
	}
};

#endif