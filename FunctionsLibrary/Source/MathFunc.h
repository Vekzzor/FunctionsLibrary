#pragma once

class MathFunc
{
	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		float Dot(const Vector3& other) const
		{
			return this->x * other.x + this->y * other.y + this->z * other.z;
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