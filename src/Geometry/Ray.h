
#include <glm/glm.hpp>


namespace Geometry {

	class Ray
	{
	public:
		Ray(glm::vec3 origin, glm::vec3 direction);
		~Ray();

		glm::vec3 direction;
		glm::vec3 origin;


	}

}