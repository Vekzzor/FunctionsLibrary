#include "FunctionsLibraryPCH.h"
#include "MathFunc.h"


MathFunc::Vector3 MathFunc::Lerp(const Vector3& start, const Vector3& end, float percent)
{
	return (start + (end - start) * percent);
}

MathFunc::Vector3 MathFunc::SLerp(const Vector3& start, const Vector3& end, float percent)
{
	float dot = start.Dot(end);
	dot = std::clamp(dot, -1.0f, 1.0f);

	float theta = std::acosf(dot)*percent;

	Vector3 relativeVec = end - start*dot;
	relativeVec.Normalize();

	start *= std::cos(theta);

	relativeVec *= std::sin(theta);

	return (start + relativeVec);
}

MathFunc::Vector3 MathFunc::NLerp(const Vector3& start, const Vector3& end, float percent)
{
	Vector3 result = MathFunc::Lerp(start, end, percent);
	result.Normalize();
	return result;
}


//Vector3 Functions
float MathFunc::Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

void MathFunc::Vector3::Normalize()
{
	float invLen = 1.0f / this->Length();
	*this = *this * invLen;
}
