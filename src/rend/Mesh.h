#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

namespace rend
{
    struct Vertex
    {

        glm::vec3 position;
        glm::vec2 texcoord;
        glm::vec3 normal;
    };

    struct Face
    {
        Vertex a;
        Vertex b;
        Vertex c;
    };

    class Mesh {
    public:
        Mesh();
        ~Mesh();

        void addFace(Face _face);
        GLuint getVAOId();
        GLsizei vertexCount() const;




    private:
        std::vector<Face> m_faces;
        GLuint m_vboid;
        GLuint m_vaoid;
        bool m_dirty = false;


    };
}
 #endif // MESH_HPP
