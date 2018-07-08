#include "..\Geometry\Ray.h"
#include <glm/glm.hpp>



namespace Scene {
	class Light
	{
	public:
		Light(glm::vec3 position);
		~Light();

		virtual Geometry::Ray &sampleLight();

	private:
		glm::vec3 position;
	};
}