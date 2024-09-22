#ifndef _LOADMODEL_H
#define _LOADMODEL_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h> //For Programmable Pipeline (Graphics Library Extension Wrangler) This must before gl.h header file
#include <gl/GL.h>

extern FILE *gpFILE;

struct vertices
{
    float v[3];
};

struct color
{
    float c[3];
};

struct normals
{
    float n[3];
};

struct texCoords
{
    float t[2];
};

struct faces
{
    unsigned v1, v2, v3;
};

class loadObjModel
{
private:
    std::vector<vertices> vertex_data;
    std::vector<color> color_data;
    std::vector<normals> normal_data;
    std::vector<texCoords> texcoord_data;

    std::vector<vertices> vertex_data_sorted;
    std::vector<color> color_data_sorted;
    std::vector<normals> normal_data_sorted;
    std::vector<texCoords> texcoord_data_sorted;

    std::vector<faces> faces_data;

    GLuint vao;
    GLuint vboElement;

public:
    loadObjModel(const char *filename)
    {

        std::ifstream modelFile(filename);

        std::string line;
        if (modelFile)
        {
            fprintf(gpFILE, "File Opening Successfull\n");
        }
        else
        {
            fprintf(gpFILE, "File Opening Failed\n");
        }

        if (modelFile.fail())
        {
            // Print a more detailed error message using
            // strerror
            fprintf(gpFILE, "Error details: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        while (std::getline(modelFile, line))
        {

            if (line[0] == 'v')
            {
                if (line[1] == ' ')
                {
                    vertices vertex;
                    color cl;
                    sscanf(line.c_str(), "v %f %f %f %f %f %f", &(vertex.v[0]), &(vertex.v[1]), &(vertex.v[2]), &(cl.c[0]), &(cl.c[1]), &(cl.c[2]));
                    vertex_data.push_back(vertex);
                    color_data.push_back(cl);
                }
                else if (line[1] == 'n')
                {
                    normals normal;
                    sscanf(line.c_str(), "vn %f %f %f", &(normal.n[0]), &(normal.n[1]), &(normal.n[2]));
                    normal_data.push_back(normal);
                }
                else if (line[1] == 't')
                {
                    texCoords tex;
                    sscanf(line.c_str(), "vt %f %f", &tex.t[0], &tex.t[1]);
                    texcoord_data.push_back(tex);
                }
            }
            else if (line[0] == 'f')
            {
                char *data = (char *)line.c_str();

                char *name = strtok(data, " ");
                name = strtok(NULL, " ");

                int v, t, n;

                while (name != NULL)
                {
                    sscanf(name, "%d/%d/%d", &v, &t, &n);

                    vertex_data_sorted.push_back(vertex_data[v - 1]);
                    color_data_sorted.push_back(color_data[v - 1]);
                    texcoord_data_sorted.push_back(texcoord_data[t - 1]);
                    normal_data_sorted.push_back(normal_data[n - 1]);

                    name = strtok(NULL, " ");
                }
            }

            line.clear();
        }

        fprintf(gpFILE, "Vertice_data size %llu\n", vertex_data_sorted.size());
        fprintf(gpFILE, "Vertice_data size %llu\n", texcoord_data_sorted.size());
        fprintf(gpFILE, "Vertice_data size %llu\n", normal_data_sorted.size());

        modelFile.close();

        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo;
        glCreateBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertex_data_sorted.size() * sizeof(vertices), vertex_data_sorted.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glCreateBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, normal_data_sorted.size() * sizeof(normals), normal_data_sorted.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(3);

        //   glCreateBuffers(1, &vboElement);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboElement);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces_data.size() * sizeof(GL_UNSIGNED_INT), faces_data.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void drawModel()
    {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertex_data_sorted.size());
        glBindVertexArray(0);
    }
};

// f v1/t1/n1 v2/t2/n2 v3/t3/n3

#endif
