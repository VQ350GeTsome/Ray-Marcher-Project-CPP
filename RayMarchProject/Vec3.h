#pragma once

#include <cmath>

struct vec3 
{
	float x, y, z;

	vec3() : x(0), y(0), z(0) {}
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	//Define addition operator
	vec3 operator+(const vec3& other) const
	{
		return vec3(x + other.x, y + other.y, z + other.z);
	}
	//Define subtraction operator
	vec3 operator-(const vec3& other) const
	{
		return vec3(x - other.x, y - other.y, z - other.z);
	}
	//Define scalar multiplication operator
	vec3 operator*(float scalar) const
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}
	//Define scalar division operator
	vec3 operator/(float scalar) const			
	{
		return vec3(x / scalar, y / scalar, z / scalar);
	}
	//Define dot product
	float dot(const vec3& other) const			
	{
		return x * other.x + y * other.y + z * other.z;
	}
	//Define cross product
	vec3 cross(const vec3& other) const			
	{
		return vec3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}
	//Define length (magnitude) of the vector
	float length() const						
	{
		return sqrt(x * x + y * y + z * z);
	}
	//Define normalization of the vector
	vec3 normalize() const
	{
		float len = length();
		return vec3(x / len, y / len, z / len);
	}
	//Clamp each component between min and max
	vec3 clamp(float min, float max) const		
	{
		return vec3(
			(x < min) ? min : (x > max) ? max : x,
			(y < min) ? min : (y > max) ? max : y,
			(z < min) ? min : (z > max) ? max : z
		);
	}
	//Cast to int vector
	vec3 toInt() const							
	{
		return vec3((int)x, (int)y, (int)z);
	}
};