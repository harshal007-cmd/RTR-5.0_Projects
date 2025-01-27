#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H

#include <gl/glew.h>
#include <gl/GL.h>

#include <vector>
#include <map>
#include <string>

extern FILE *gpFILE;

class ShaderProgramObject
{

private:
    GLuint programObject;
    std::map<std::string, int> uniforms;

    GLuint compileShader(const char **shaderSourceString, GLenum shaderType)
    {
        void uninitialise(void);
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, shaderSourceString, 0);
        glCompileShader(shader);

        //
        GLint status = 0;
        GLint infoLogLength = 0;
        GLchar *szInfoLog = NULL;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (status == GL_FALSE)
        {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0)
            {
                szInfoLog = (char *)malloc(infoLogLength + 1);
                if (szInfoLog != NULL)
                {
                    glGetShaderInfoLog(shader, infoLogLength + 1, NULL, szInfoLog);
                    fprintf(gpFILE, "Shader Compilation Error Log : %s\n", szInfoLog);
                    free(szInfoLog);
                    szInfoLog = NULL;
                }
            }
            uninitialise();
            exit(EXIT_FAILURE);
        }

        return shader;
    }

    void linkProgram()
    {
        void uninitialise(void);

        //  Link Shader Program
        glLinkProgram(programObject);

        // Error Checking
        int status = 0;
        int infoLogLength = 0;
        char *szInfoLog = NULL;

        glGetProgramiv(programObject, GL_LINK_STATUS, &status);

        if (status == GL_FALSE)
        {
            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0)
            {
                szInfoLog = (char *)malloc(infoLogLength + 1);
                if (szInfoLog != NULL)
                {
                    glGetProgramInfoLog(programObject, infoLogLength + 1, NULL, szInfoLog);
                    fprintf(gpFILE, "Shader Program Linking Error Log  : %s\n", szInfoLog);
                    free(szInfoLog);
                    szInfoLog = NULL;
                }
            }
            uninitialise();
        }
    }
    void queryUniforms()
    {
        void uninitialise(void);
        int num_uniforms, size;

        GLenum type;
        char uniform_name[1024];
        glGetProgramiv(programObject, GL_ACTIVE_UNIFORMS, &num_uniforms);

        for (int i = 0; i < num_uniforms; i++)
        {
            char uniform_name[1024];
            glGetActiveUniform(programObject, i, 1024, NULL, &size, &type, uniform_name);
            int loc = glGetUniformLocation(programObject, uniform_name);
            uniforms[uniform_name] = loc;
        }
    }

public:
    ShaderProgramObject(const char **vertexShaderSource, const char **fragmentShaderSource)
    {
        void uninitialise(void);
        // Create Program
        programObject = glCreateProgram();

        // Attach Shaders
        glAttachShader(programObject, compileShader(vertexShaderSource, GL_VERTEX_SHADER));
        glAttachShader(programObject, compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER));

        // Link Program
        linkProgram();

        // Query Uniforms
        queryUniforms();
    }

    int getUniformLocation(const char *uniform_name)
    {
        void uninitialise(void);
        if (uniforms.count(uniform_name) > 0)
        {
            return uniforms[uniform_name];
        }
        else
        {
            fprintf(gpFILE, "int ShaderProgramObject::getUniformLocation() - >failed , %s uniform name not found\n", uniform_name);
            uninitialise();
            exit(EXIT_FAILURE);
            return -1;
        }
    }
    void useProgram()
    {
        glUseProgram(programObject);
    }

    ~ShaderProgramObject()
    {

        if (programObject)
        {
            glUseProgram(programObject);
            GLint numshaders = 0;
            glGetProgramiv(programObject, GL_ATTACHED_SHADERS, &numshaders);

            if (numshaders > 0)
            {
                GLuint *pShaders = (GLuint *)malloc(sizeof(GLuint) * numshaders);

                glGetAttachedShaders(programObject, numshaders, NULL, pShaders);

                for (GLint i = 0; i < numshaders; i++)
                {
                    glDetachShader(programObject, pShaders[i]);
                    glDeleteShader(pShaders[i]);
                    pShaders[i] = 0;
                }
                free(pShaders);
                pShaders = NULL;
            }
            glUseProgram(0);
            glDeleteProgram(programObject);
            programObject = 0;
        }
    }
};

#endif
