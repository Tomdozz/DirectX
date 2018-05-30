//
//  Geometry.h
//
//  (c) CJG 2016, cjgribel@gmail.com
//

#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "stdafx.h"
#include <vector>
#include "vec\vec.h"
#include "vec\mat.h"
#include "ShaderBuffers.h"
#include "drawcall.h"
#include "mesh.h"

using namespace linalg;

class Geometry_t
{
protected:
	// Pointers to the current device and device context
	ID3D11Device* const			dxdevice;
	ID3D11DeviceContext* const	dxdevice_context;

	// Pointers to the class' vertex & index arrays
	ID3D11Buffer* vertex_buffer = nullptr;
	ID3D11Buffer* index_buffer = nullptr;

	ID3D11Buffer* MaterialBuffer = nullptr;
	ID3D11SamplerState* samplerstate = nullptr;
	
	ID3D11SamplerState* samplerShadow = nullptr;

public:

	Geometry_t(
		ID3D11Device* dxdevice,
		ID3D11DeviceContext* dxdevice_context)
		: dxdevice(dxdevice),
		dxdevice_context(dxdevice_context)
	{
		HRESULT hr;
		D3D11_SAMPLER_DESC sd =
		{
				D3D11_FILTER_ANISOTROPIC,		//filter
				D3D11_TEXTURE_ADDRESS_WRAP,		//AdressU
				D3D11_TEXTURE_ADDRESS_WRAP,		//AdressV
				D3D11_TEXTURE_ADDRESS_WRAP,		//AdressW
				0.0f,							//MipLodBias
				4,								//MaxAnisotropy
				D3D11_COMPARISON_NEVER,			//ComparisonFunc
				{1.0f,1.0f,1.0f,1.0f},			//BorderColor
				-FLT_MAX,						//minLod
				FLT_MAX,						//maxLod
		};
		ASSERT(hr = dxdevice->CreateSamplerState(&sd, &samplerstate));

		HRESULT hr1;
		D3D11_SAMPLER_DESC sdShadow =
		{
			D3D11_FILTER_ANISOTROPIC,		//filter
			D3D11_TEXTURE_ADDRESS_WRAP,		//AdressU
			D3D11_TEXTURE_ADDRESS_WRAP,		//AdressV
			D3D11_TEXTURE_ADDRESS_WRAP,		//AdressW
			0.0f,							//MipLodBias
			4,								//MaxAnisotropy
			D3D11_COMPARISON_NEVER,			//ComparisonFunc
			{ 1.0f,1.0f,1.0f,1.0f },			//BorderColor
			-FLT_MAX,						//minLod
			FLT_MAX,						//maxLod
		};
		ASSERT(hr1 = dxdevice->CreateSamplerState(&sdShadow, &samplerstate));
	}

	//
	// Map and update the matrix buffer
	//
	virtual void MapMatrixBuffers(
		ID3D11Buffer* matrix_buffer,
		mat4f ModelToWorldMatrix,
		mat4f WorldToViewMatrix,
		mat4f ProjectionMatrix);

	virtual void MapMatrixBuffersShader(
		ID3D11Buffer* matrix_shadow_buffer,
		mat4f ModelToWorldMatrix,
		mat4f WorldToViewMatrix,
		mat4f ProjectionMatrix,
		mat4f lightView,
		mat4f lightProjection);

	virtual void MapLightbuffer1(
		ID3D11Buffer* shadow_light_buffer,
		float4 ambientColor,
		float4 diffuseColor);

	virtual void  LightBufferShadows2(
		ID3D11Buffer* light_pos_shadow,
		float4 position
	);

	
	//Map phongBuffer
	virtual void MapPhongBuffer(
		ID3D11Buffer* spectralHighlight,
		float4 ambientColor, 
		float4 diffuseColor, 
		float4 specularColor, 
		float shine,
		float hasTex);
	
	//
	//Map textureBuffer
	//
	//virtual void MapTextureBuffer(
	//	const std::string& objfile,
	//	ID3D11Device* dxdevice,
	//	ID3D11DeviceContext* dxdevice_context);

	//
	// Abstract render method: must be implemented by derived classes
	//
	virtual void render() const = 0;

	//
	// Destructor
	//
	virtual ~Geometry_t()
	{
		SAFE_RELEASE(vertex_buffer);
		SAFE_RELEASE(index_buffer);

	}
};

class Quad_t : public Geometry_t
{
	// our local vertex and index arrays
	std::vector<vertex_t> vertices;
	std::vector<unsigned> indices;
	unsigned nbr_indices = 0;

public:

	Quad_t(
		ID3D11Device* dx3ddevice,
		ID3D11DeviceContext* dx3ddevice_context);

	virtual void render() const;

	~Quad_t() { }
};

//make cube class
class Cube : public Geometry_t
{
	//vertex and index arrays
	std::vector<vertex_t> vertices;
	std::vector<unsigned> indices;
	unsigned nbr_indices = 0;
	
public:
	Cube(
		ID3D11Device* dx3ddevice,
		ID3D11DeviceContext* dx3ddevice_context);
		//: Geometry_t(dxdevice, dxdevice_context);

	virtual void render() const;

	~Cube()
	{

	}
};

class OBJModel_t : public Geometry_t
{
	// index ranges, representing drawcalls, within an index array
	struct index_range_t
	{
		size_t start;
		size_t size;
		unsigned ofs;
		int mtl_index;
	};

	std::vector<index_range_t> index_ranges;
	std::vector<material_t> materials;

	void append_materials(const std::vector<material_t>& mtl_vec)
	{
		materials.insert(materials.end(), mtl_vec.begin(), mtl_vec.end());
	}

public:

	OBJModel_t(
		const std::string& objfile,
		ID3D11Device* dxdevice,
		ID3D11DeviceContext* dxdevice_context);

	void MapTexture(const std::string& filePath);

	//void CalTangentBinormal();
	//lanygels method
	//void LengyelsMethod(unsigned indices1, unsigned indices2, unsigned indices3);
	void LengyelsMethod(vertex_t& v0, vertex_t& v1, vertex_t& v2);
	virtual void render() const;


	~OBJModel_t();
	// { }
};

#endif