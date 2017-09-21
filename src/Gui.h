
#include "imgui/imgui.h"

struct GLFWwindow;

class 	Gui
{
public:
		Gui();
	~	Gui();
		
		void init(GLFWwindow *window);
		void render();
        void finish();
};