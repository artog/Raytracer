#include "Light.h"

namespace Scene {
	using namespace Geometry;
	using namespace glm;

	Light::Light(vec3 position)
		: position(position)
	{
	}

	Light::~Light()
	{
	}

	Ray & Light::sampleLight()
	{
		Ray ray = Ray(position, vec3(0, 0, 1));
		return ray;
	}


}