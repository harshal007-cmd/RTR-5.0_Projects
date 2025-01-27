#ifndef _SPHERE_H
#define _SPHERE_H
#include <vector>
#include <iostream>

// OpenGL Funcitons declarations
#include <GL/glew.h>
#include <GL/GL.h>

#include "vmath.h"

#define _USE_MATH_DEFINES
#include <math.h>

using std::vector;

class sphere
{
private:
    GLuint vao;
    GLuint ebo;
    GLuint numIndices;

public:
    sphere(float radius, unsigned stackCount, unsigned sectorCount)
    {

        vector<float> sphere_vertices;
        vector<float> sphere_normals;
        vector<float> sphere_texCoords;
        vector<float> sphere_tangent;

        vector<unsigned> face_indices;
        vector<unsigned> line_indices;

        vmath::vec3 pos1, pos2, pos3, edge1, edge2, tangent;
        vmath::vec2 uv1, uv2, uv3, deltaUV1, deltaUV2;

        sphere_vertices.clear();
        sphere_texCoords.clear();
        sphere_normals.clear();

        float x, y, z, xy; // Vertex position
        float nx, ny, nz;  // Vertex Normal
        float s, t;        // Vertex Texcoords

        float sectorStep = 2.0f * M_PI / sectorCount;
        float stackStep = M_PI / stackCount;

        float stackAngle = 0.0f;
        float sectorAngle = 0.0f;

        int k = 0;

        for (int i = 0; i <= stackCount; i++)
        {
            stackAngle = M_PI_2 - i * stackStep;

            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for (int j = 0; j <= sectorCount; j++)
            {
                sectorAngle = j * sectorStep;

                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);

                sphere_vertices.push_back(x);
                sphere_vertices.push_back(y);
                sphere_vertices.push_back(z);

                // Normals
                nx = x / radius;
                ny = y / radius;
                nz = z / radius;

                sphere_normals.push_back(nx);
                sphere_normals.push_back(ny);
                sphere_normals.push_back(nz);

                // TexCoords
                s = (float)j / (float)sectorCount;
                t = (float)i / (float)stackCount;

                sphere_texCoords.push_back(s);
                sphere_texCoords.push_back(t);
            }
        }

        // Indices
        face_indices.clear();
        line_indices.clear();

        int k1, k2;

        for (int i = 0; i < stackCount; i++)
        {
            k1 = i * (sectorCount + 1); // beginning of current stack
            k2 = k1 + sectorCount + 1;  // beginning of next stack

            for (int j = 0; j < sectorCount; j++, k1++, k2++)
            {
                if (i != 0)
                {
                    face_indices.push_back(k1);
                    face_indices.push_back(k2);
                    face_indices.push_back(k1 + 1);
                }

                if (i != (stackCount - 1))
                {
                    face_indices.push_back(k1 + 1);
                    face_indices.push_back(k2);
                    face_indices.push_back(k2 + 1);
                }
            }
        }

        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo;
        // Position
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(GL_FLOAT), sphere_vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        

        // Color(1)

        // TexCoords(2)
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sphere_texCoords.size() * sizeof(GL_FLOAT), sphere_texCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);

        
        // Normals(3)
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sphere_normals.size() * sizeof(GL_FLOAT), sphere_normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(3);

      

        // Element Array
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_indices.size() * sizeof(GL_UNSIGNED_INT), face_indices.data(), GL_STATIC_DRAW);

        numIndices = face_indices.size();

       

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        sphere_vertices.clear();
        sphere_texCoords.clear();
        sphere_normals.clear();
        face_indices.clear();
    }

    void draw()
    {
        glBindVertexArray(vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

    ~sphere()
    {
    }
};

#endif
