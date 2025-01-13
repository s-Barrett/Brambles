#include "DebugRenderer.h"
#include "BoxCollider.h"
#include <GL/gl.h> // Replace with your rendering API

namespace Brambles
{


    std::shared_ptr<rend::Mesh> DebugRenderer::generateBoxMesh(const glm::vec3& size)
    {
        auto mesh = std::make_shared<rend::Mesh>();

        glm::vec3 halfSize = size * 0.5f;


        glm::vec3 corners[8] = {
            {-halfSize.x, -halfSize.y, -halfSize.z},
            { halfSize.x, -halfSize.y, -halfSize.z},
            { halfSize.x,  halfSize.y, -halfSize.z},
            {-halfSize.x,  halfSize.y, -halfSize.z},
            {-halfSize.x, -halfSize.y,  halfSize.z},
            { halfSize.x, -halfSize.y,  halfSize.z},
            { halfSize.x,  halfSize.y,  halfSize.z},
            {-halfSize.x,  halfSize.y,  halfSize.z},
        };


        int edges[12][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 4}, 
            {0, 4}, {1, 5}, {2, 6}, {3, 7} 
        };

        for (const auto& edge : edges)
        {
            rend::Face face;

            face.a.position = corners[edge[0]];
            face.b.position = corners[edge[1]];
            face.c.position = corners[edge[0]]; 

            mesh->addFace(face);
        }

        return mesh;
    }

    void DebugRenderer::drawWireframeBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color)
    {
        auto mesh = generateBoxMesh(size);

        GLuint vao = mesh->getVAOId();
        GLsizei vertexCount = mesh->vertexCount();

        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);

        glColor3f(color.r, color.g, color.b);

        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, vertexCount);
        glBindVertexArray(0);

        glPopMatrix();
    }

    void DebugRenderer::drawBoxCollider(std::shared_ptr<BoxCollider> collider, const glm::vec3& color)
    {
        glm::vec3 position = collider->getPosition() + collider->getOffset();
        glm::vec3 size = collider->getSize();

        drawWireframeBox(position, size, color);
    }
}
