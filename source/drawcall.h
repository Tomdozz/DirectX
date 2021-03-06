//
//  drawcall.h
//
//  CJG 2016, cjgribel@gmail.com
//

#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "stdafx.h"
#include "vec/vec.h"

using namespace linalg;

struct vertex_t
{
	vec3f Pos;
	vec3f Normal, Tangent, Binormal;
	vec2f TexCoord;
};

//
// Phong-esque material
//
struct material_t
{
	//
	//  Phong color components: ambient, diffuse & specular
	vec3f Ka = { 0,0.5,0 }, Kd = { 0,0.5,0 }, Ks = { 1,1,1 };

	std::string name;		// Material name
	std::string map_Kd;		// Texture file path
	
	std::string map_bump;
	//= "C:/Users/Tom/Desktop/eduRend17v1_handout/assets/textures/wood.png";
	
	//std::string map_bump;	// Texture file path
	std::string map_Ks;
	std::string map_d;
	std::string map_Ka;

	std::string map_SkyBox = "C:/Users/Tom/Desktop/eduRend17v1_handout/assets/cubemaps/grasscube1024.dds";

	// Device texture pointers
	//diffuse
	ID3D11ShaderResourceView*	map_Kd_TexSRV	= nullptr;
	ID3D11Resource*				map_Kd_Tex		= nullptr;
	
	
	ID3D11ShaderResourceView*	map_Ks_TexSRV	= nullptr;
	ID3D11Resource*				map_Ks_Tex		= nullptr;

	
	ID3D11ShaderResourceView*	map_Ka_TexSRV	= nullptr;
	ID3D11Resource*				map_Ka_Tex		= nullptr;
	
	
	ID3D11ShaderResourceView*	map_d_TexSRV	= nullptr;
	ID3D11Resource*				map_d_Tex		= nullptr;
	
	//bump
	ID3D11ShaderResourceView*	map_bump_TexSRV = nullptr;
	ID3D11Resource*				map_bump_Tex	= nullptr;

	ID3D11ShaderResourceView*	map_SkyBox_TexSRV = nullptr;
	ID3D11Resource*				map_SkyBox_Tex = nullptr;
	// other map types here ...

	
};

static material_t default_mtl = material_t();

typedef std::unordered_map<std::string, material_t> mtl_hash_t;

struct triangle_t
{
	unsigned vi[3];
};

struct quad_t_
{
	unsigned vi[4];
};

struct drawcall_t
{
	std::string group_name;
	int mtl_index = -1;
	std::vector<triangle_t> tris;
	std::vector<quad_t_> quads;

	// make sortable
	bool operator < (const drawcall_t& dc) const
	{
		return mtl_index < dc.mtl_index;
	}
};

#endif
