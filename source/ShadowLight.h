#pragma once
#ifndef SHADOWLIGHT_H
#define SHADOWLIGHT_H

#include "vec\vec.h"
#include "vec\mat.h"


using namespace linalg;

class shadowLight_t
{
public:
	float vfov, aspect;
	float zNear, zFar;

	vec3f position;
	vec3f lookAt;
	mat4f rotation;

	shadowLight_t(
		float vfov,
		float aspect,
		float zNear,
		float zFar) :
		vfov(vfov), aspect(aspect), zNear(zNear), zFar(zFar)
	{

	}

	//583 i directx bok
	void moveTo(const vec3f v)
	{
		position += v;
	}

	void Dir(const vec3f lightDir)
	{
		vec4f temp = lightDir.xyz0();
		vec4f dir = get_ViewToWorldMatrix() *temp;
		position += dir.xyz();
	}

	void Rotation(const vec3f rotateAgains)
	{
		rotation = mat4f::rotation(rotateAgains.x, rotateAgains.y, rotateAgains.z,0);
	}

	/*mat4f get_ProjectionMatrix()
	{
		return mat4f::translation(-position);
	}*/

//	mat4f get_lightView()
//	{
//		
//		//return mat4f::translation(position) * rotation;
//	}
	mat4f get_ViewToWorldMatrix()
	{
		return mat4f::translation(position)* rotation;
	}

	mat4f get_lightView()
	{
		return transpose(rotation)* mat4f::translation(-position);
	}

	mat4f get_ProjectionMatrix()
	{
		return mat4f::projection(vfov, aspect, zNear, zFar);
	}

	//~shadowLight_t();

private:

};
//
//shadowLight_t::shadowLight_t()
//{
//}
//
//shadowLight_t::~shadowLight_t()
//{
//}

#endif
