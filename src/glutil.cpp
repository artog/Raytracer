#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "dirent.h"
#include <string>

#include "glutil.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

using std::vector;
using namespace glm;

namespace glutil {

	// Reads, compiles, links and returns a shader from the given paths
	GLuint loadShader(const std::string &vertexPath, const std::string &fragmentPath) {

		cout << "Loading shader program with shaders:" << endl;
		cout << "    Vertex:   " << vertexPath << endl;
		cout << "    Fragment: " << fragmentPath << endl;

        
        
        // Read our shaders into the appropriate buffers
		std::ifstream vs_file(vertexPath);
        std::string vertexSource{
            std::istreambuf_iterator<char>(vs_file),
            std::istreambuf_iterator<char>()
        };

		std::ifstream fs_file(fragmentPath);
        std::string fragmentSource{
            std::istreambuf_iterator<char>(fs_file), 
            std::istreambuf_iterator<char>()
        };

#if 0
        DIR* vertFile = opendir(vertexPath.c_str());
        if (vertFile == nullptr) {
            glutil::fatal_error("Vertex file not found.");
        }

        DIR* fragFile = opendir(fragmentPath.c_str());
        if (fragFile == nullptr) {
            glutil::fatal_error("Fragment file not found.");
        }
#endif // 0
#if 1
        const char *vs = vertexSource.c_str();
        const char *fs = fragmentSource.c_str();
        cout << "Vertex shader:" << endl
            << vs << endl
            << endl
            << "Fragment shader:" << endl
            << fs << endl;
#endif // 0



		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = (const GLchar *)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, NULL);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Time to use the infoLog.
			for (unsigned int i = 0; i < infoLog.size(); i++)
			{
				std::cerr << infoLog[i];
			}
			std::cerr << endl;


			// In this simple program, we'll just leave
			return -1;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar *)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, NULL);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Time to use the infoLog.
			for (unsigned int i = 0; i < infoLog.size(); i++)
			{
				std::cerr << infoLog[i];
			}
			std::cerr << endl;
			// In this simple program, we'll just leave
			return -1;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Time to use the infoLog.
			for (unsigned int i = 0; i < infoLog.size(); i++)
			{
				std::cerr << infoLog[i];
			}
			std::cerr << endl;
            
			// In this simple program, we'll just leave
			return -1;
		}

		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		if (maxLength > 0) {

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			for (unsigned int i = 0; i < infoLog.size(); i++)
			{
				std::cerr << infoLog[i];
			}
			std::cerr << endl;
		
		}
		// Detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);


		cout << "Shader loaded." << endl;
		return program;
	}

    void consoleErrorCallback(int error, const char * description)
    {
        std::cerr << "Error " << error << ": " << description << std::endl;
    }

    mat4x4 perspectiveMatrix(float fov, float aspectRatio, float n, float f) /* field of view, aspect ratio, near clipping plane, far clipping plane */
    {
        // This matrix is created identically to gluPerspective()
        // and takes identical parameters.
        return mat4(0.f);// make_perspective(fov, aspectRatio, n, f);
    }



    mat4x4 lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
    {
        vec3 dir =   normalize(eye - center);
        vec3 right = normalize(cross(up, normalize(dir)));
        vec3 newup = normalize(cross(dir, right));
        mat3 R = transpose(mat3(right, newup, dir));
        mat4 invrot = mat4(
            vec4(R[0], 0.f), 
            vec4(R[1], 0.f), 
            vec4(R[2], 0.f), 
            vec4(0.0f)
        );
        return invrot * mat4(vec4(0.f), vec4(0.f), vec4(0.f), vec4(-eye,0.f));
    }

    // startupGLDiagnostics
    void startupGLDiagnostics()
    {
        // print diagnostic information
        std::cout << "GL  VENDOR: " << glGetString(GL_VENDOR)   << std::endl;
        std::cout << "   VERSION: " << glGetString(GL_VERSION)  << std::endl;
        std::cout << "  RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    }

    // Error reporting
    void fatal_error(std::string errorString, std::string title)
    {
        if (title.empty())
        {
            title = "Error";
        }
        if (errorString.empty())
        {
            errorString = "(unknown error)";
        }

        cerr << "FATAL ERROR (" << title << "): " << errorString << endl;
        //throw std::runtime_error(errorString.c_str());
    }


    const char* textFileRead(const char *fn, bool fatalError)
    {
        /* Note: the `fatalError' thing is a bit of a hack, The proper course of
        * action would be to have people check the return values of textFileRead,
        * but lets avoid cluttering the lab-code even further.
        */

        FILE *fp;
        char *content = NULL;
        size_t count = 0;

        if (fn != NULL)
        {
            fp = fopen(fn, "rt");
            if (fp != NULL)
            {
                fseek(fp, 0, SEEK_END);
                count = ftell(fp);
                fseek(fp, 0, SEEK_SET);

                if (count > 0)
                {
                    content = new char[count + 1];
                    count = fread(content, sizeof(char), count, fp);
                    content[count] = '\0';
                }
                else
                {
                    if (fatalError)
                    {
                        char buffer[256];
                        sprintf(buffer, "File '%s' is empty\n", fn);
                        fatal_error(buffer);
                    }
                }

                fclose(fp);
            }
            else
            {
                if (fatalError)
                {
                    char buffer[256];
                    sprintf(buffer, "Unable to read file '%s'\n", fn);
                    fatal_error(buffer);
                }
            }
        }
        else
        {
            if (fatalError)
                fatal_error("textFileRead - argument NULL\n");
        }

        return content;
    }



    std::string GetShaderInfoLog(GLuint obj) {
        int logLength = 0;
        int charsWritten = 0;
        char *tmpLog;
        std::string log;

        glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            tmpLog = new char[logLength];
            glGetShaderInfoLog(obj, logLength, &charsWritten, tmpLog);
            log = tmpLog;
            delete[] tmpLog;
        }

        return log;
    }


    void linkShaderProgram(GLuint shaderProgram)
    {
        glLinkProgram(shaderProgram);
        GLint linkOk = 0;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkOk);
        if (!linkOk)
        {
            std::string err = GetShaderInfoLog(shaderProgram);
            fatal_error(err);
            return;
        }
    }


    GLuint createAddAttribBuffer(GLuint vertexArrayObject, const void *data, const size_t dataSize, GLuint attributeIndex, GLsizei attributeSize, GLenum type, GLenum bufferUsage)
    {
        GLuint buffer = 0;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, bufferUsage);
        //CHECK_GL_ERROR();

        // Now attach buffer to vertex array object.
        glBindVertexArray(vertexArrayObject);
        glVertexAttribPointer(attributeIndex, attributeSize, type, false, 0, 0);
        glEnableVertexAttribArray(attributeIndex);
        //CHECK_GL_ERROR();

        return buffer;
    }




    void setUniformSlow(GLuint shaderProgram, const char *name, const mat4x4 &matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, false, &matrix[0].x);
    }
    void setUniformSlow(GLuint shaderProgram, const char *name, const float value)
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name), value);
    }
    void setUniformSlow(GLuint shaderProgram, const char *name, const GLint value)
    {
        int loc = glGetUniformLocation(shaderProgram, name);
        glUniform1i(loc, value);
    }
    void setUniformSlow(GLuint shaderProgram, const char *name, const vec3 &value)
    {
        glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, &value.x);
    }

    void debugDrawLight(const mat4x4 &viewMatrix,
        const mat4x4 &projectionMatrix,
        const vec3 &worldSpaceLightPos)
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        GLint temp;
        glColor3f(1.0, 1.0, 0.0);
        glGetIntegerv(GL_CURRENT_PROGRAM, &temp);
        glUseProgram(0);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(&projectionMatrix[0].x);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&viewMatrix[0].x);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 52428);
        glBegin(GL_LINES);
        glVertex3fv(&worldSpaceLightPos.x);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
        glTranslatef(worldSpaceLightPos.x, worldSpaceLightPos.y, worldSpaceLightPos.z);
        glBegin(GL_POINTS);
        glPointSize(40);
        glVertex3fv(&worldSpaceLightPos.x);
        glEnd();
        glUseProgram(temp);
        glPopAttrib();
    }

#if defined(__linux__)
    void linux_initialize_cwd()
    {
        const unsigned kMaxPath = 1024; // Oh, well.

                                        /* Attempt to change CWD (current working directory) to
                                        * 		- ${BINDIR}/../share/${BINNAME}/
                                        * 		- ${BINDIR}
                                        *	where ${BINDIR} refers to the path of the directory where the binary
                                        *	is located, and ${BINNAME} refers to the name of the binary.
                                        *
                                        *	For example, if we launch `bin/lab2' in `/home/foo/labs':
                                        * 		$ cd /home/foo/labs
                                        * 		$ bin/lab2
                                        *	we'll try to change to
                                        *		- /home/foo/labs/share/lab2
                                        *		- /home/foo/labs/bin
                                        *	(in this case, it's assumed that the former succeeds.)
                                        */

                                        // try to get the path to the binary
        char pathToBin[kMaxPath];
        ssize_t ret = readlink("/proc/self/exe", pathToBin, kMaxPath - 1);

        if (ret == -1)
            return;

        pathToBin[ret] = '\0';

        // extract parts
        char* dirsep = strrchr(pathToBin, '/');
        if (dirsep) *dirsep = '\0';

        const char* bindir = pathToBin;
        const char* binname = dirsep + 1;

        // attempt first ${BINDIR}/../share/${BINNAME}
        char pathToData[kMaxPath];
        snprintf(pathToData, kMaxPath, "%s/../share/%s", bindir, binname);

        if (0 == chdir(pathToData))
        {
            fprintf(stderr, "Note: expecting to find data in `%s'\n", pathToData);
            return;
        }

        // then attempt ${BINDIR}
        if (0 == chdir(pathToBin))
        {
            fprintf(stderr, "Note: expecting to find data in `%s'\n", pathToBin);
            return;
        }

        // neither seems to exist; give up.
        char currentCWD[kMaxPath];
        if (!getcwd(currentCWD, kMaxPath))
            strncpy(currentCWD, "???", kMaxPath);

        fprintf(stderr, "Note: expecting to find data in `%s'\n", currentCWD);
        return;
    }

#endif // ! __linux__


}
