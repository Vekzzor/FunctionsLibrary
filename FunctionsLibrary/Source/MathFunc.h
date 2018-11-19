#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
class MathFunc
{
	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		Vector3(DirectX::XMFLOAT3 vector)
		{
			this->x = vector.x;
			this->y = vector.y;
			this->z = vector.z;
		}
		float Dot(const Vector3& other) const
		{
			return this->x * other.x + this->y * other.y + this->z * other.z;
		}

		float Distance(const Vector3& other)
		{
			return sqrtf(pow(other.x - this->x,2) +
				pow(other.y - this->y, 2) +
				pow(other.z - this->z, 2));
		}

		Vector3& CrossProduct(const Vector3& other)
		{
			Vector3 result;
			result.x = this->y * other.z - this->z * other.y; // Y to Z minus Z to Y
			result.y = this->z * other.x - this->x * other.z; // Z to X minus X to Z
			result-z = this->x * other.y - this->y * other.z; // X to Y minus Y to X
			return result;
		}

		Vector3 operator-(const Vector3& b) const
		{
			Vector3 result = *this;
			result.x -= b.x;
			result.y -= b.y;
			result.z -= b.z;
			return result;
		}
		Vector3 operator+(const Vector3& b) const
		{
			Vector3 result = *this;
			result.x += b.x;
			result.y += b.y;
			result.z += b.z;
			return result;
		}
		Vector3 operator*(const float& b) const
		{
			Vector3 result = *this;
			result.x *= b;
			result.y *= b;
			result.z *= b;
			return result;
		}
		Vector3 operator*=(const float& b) const
		{
			Vector3 result = *this;
			result.x *= b;
			result.y *= b;
			result.z *= b;
			return result;
		}
		float Length() const;

		void Normalize();
	};

	//Lerps
	static Vector3 Lerp (const Vector3& start, const Vector3& end, float percent); //Linear Interpolation
	static Vector3 SLerp(const Vector3& start, const Vector3& end, float percent); //Spherical Linear Interpolation
	static Vector3 NLerp(const Vector3& start, const Vector3& end, float percent); //Naive Spherical Linear Interpolation
};