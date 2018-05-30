#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "stdafx.h"
#include <vector>
#include "vec\vec.h"
#include "vec\mat.h"
#include "ShaderBuffers.h"
#include "drawcall.h"
#include "mesh.h"

using namespace linalg;

class light_t
{
protected:
	vec3f position;
	float4 lightColor;
	
	ID3D11Device* const			dxdevice;
	ID3D11DeviceContext* const	dxdevice_context;

	ID3D11Buffer* light_buffer = nullptr;

public:

	light_t(ID3D11Device* dxdevice,
		ID3D11DeviceContext* dxdevice_context)
		: dxdevice(dxdevice),
		dxdevice_context(dxdevice_context)
	{}

	//map to lightbuffer
	virtual void MapLightBuffer(
		ID3D11Buffer* light_buffer,
		vec3f pos,
		float4 color);

	virtual void Move(const vec3f& v);

private:

};

class pointLight_t : public light_t
{

};

class directionalLight_t : public light_t
{
public:
	vec3f direction;
};

class spotLight_t : public light_t
{
public:
	float4 ambient;
	float4 specular;
	float4 diffuse;
	float3 attenuation;
	int range;
};

class areaLight_t : public light_t
{
public:

};


#endif // !CAMERA_H

//class Light
//{
//public:
//	Light();
//	~Light();
//};

