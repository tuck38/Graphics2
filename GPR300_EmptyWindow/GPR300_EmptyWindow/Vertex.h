#pragma once

struct Vec3
{
	//position
	float x, y, z;
};

struct Color
{
    //RGBa
	float r, g, b, a;
};

struct Vertex
{
	Vec3 position;
	Color color;
};
