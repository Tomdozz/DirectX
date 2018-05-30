
#pragma once
#ifndef MATRIXBUFFERS_H
#define MATRIXBUFFERS_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

struct LightBuffer_t
{
	float4 color_t;
	float4 lightpos_t;
	float4 cameraPos_t;	
};

struct Lambert_t
{
	float4 Pos;
	float3 Normal;
	float2 TexCoord;
};

struct SpectralHighlightBuffer_t
{
	//mat4f modelMatrix_t;
	//mat4f viewMatrix_t;
	//mat4f projectionMatrix_t;
	//float4 ambientLight_t;
	//float4 directionalLight_t;
	//float4 lightDirection_t;
	float4 AmbientColor_t;
	float4 DiffuseColor_t;
	float4 SpecularColor_t;
	float Shine_t;
	float hasTex;
	float2 padding_t;
};

struct MatrixBuffer_t
{
	mat4f ModelToWorldMatrix;
	mat4f WorldToViewMatrix;
	mat4f ProjectionMatrix;
};

struct MatrixBufferShadows_t
{
	mat4f ModelToWorldMatrix;
	mat4f WorldToViewMatrix;
	mat4f ProjectionMatrix;
	mat4f lightView;
	mat4f lightprojection;
};

struct LightBufferShadows_t
{
	float4 AmbientColor;
	float4 DiffuseColor;
};

struct LightBufferShadows2_t
{
	float4 lightPos;
};


#endif