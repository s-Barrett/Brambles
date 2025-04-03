#include "DebugRenderer.h"
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "Renderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
#include "Resources/Model.h"

#include <iostream>
#include <GL/gl.h>

namespace Brambles
{
    std::shared_ptr<rend::Mesh> DebugRenderer::generateBoxMesh(const glm::vec3& size)
    {
        auto mesh = std::make_shared<rend::Mesh>();
        glm::vec3 halfSize = size / 2.0f;

        glm::vec3 corners[8] = {
            {-halfSize.x, -halfSize.y, -halfSize.z}, { halfSize.x, -halfSize.y, -halfSize.z},
            { halfSize.x,  halfSize.y, -halfSize.z}, {-halfSize.x,  halfSize.y, -halfSize.z},
            {-halfSize.x, -halfSize.y,  halfSize.z}, { halfSize.x, -halfSize.y,  halfSize.z},
            { halfSize.x,  halfSize.y,  halfSize.z}, {-halfSize.x,  halfSize.y,  halfSize.z}
        };

        int edges[12][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4},
            {0, 4}, {1, 5}, {2, 6}, {3, 7} //creating edges
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
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glEnable(GL_LINE_SMOOTH);

        debugShader->use();
        auto mesh = generateBoxMesh(size);
        GLuint vao = mesh->getVAOId();
        GLsizei vertexCount = mesh->vertexCount();


        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);

        if (auto camera = getEntity()->getCore()->getCamera())
        {
            debugShader->uniform("debugview", camera->getViewMatrix());
            debugShader->uniform("debugprojection", camera->getProjectionMatrix());
            debugShader->uniform("debugmodel", modelMatrix);
            debugShader->uniform("debuglineColor", color);
            debugShader->uniform("debuglinewidth", 2.0f);
        }

        glLineWidth(2.0f);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, vertexCount);
        glBindVertexArray(0);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

    void DebugRenderer::drawBoxCollider(std::shared_ptr<BoxCollider> collider, const glm::vec3& color)
    {

        glm::vec3 position = collider->getTransform()->getPosition() + collider->getOffset();
        glm::vec3 size = collider->getSize();
 
        drawWireframeBox(position, size, color);
    }

    void DebugRenderer::drawMeshCollider(std::shared_ptr<MeshCollider> collider, const glm::vec3& color) {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glEnable(GL_LINE_SMOOTH); // Add for better line rendering on Linux

        debugShader->use();

        auto model = collider->getModel();
        if (!model) {
            std::cerr << "MeshCollider: No model found!" << std::endl;
            return;
        }

        // Get all transforms
        auto transform = collider->getTransform();
        glm::vec3 position = transform->getPosition();
        glm::vec3 scale = transform->getScale();
        glm::vec3 offset = collider->getOffset();

        // Get the mesh data
        const auto& faces = model->getFaces();
        std::vector<glm::vec3> lineVertices;

        for (const auto& face : faces) {
            // Apply scale and transform to each vertex
            glm::vec3 a = (face.a.position * scale) + position + offset;
            glm::vec3 b = (face.b.position * scale) + position + offset;
            glm::vec3 c = (face.c.position * scale) + position + offset;

            // Store triangle edges
            lineVertices.push_back(a);
            lineVertices.push_back(b);

            lineVertices.push_back(b);
            lineVertices.push_back(c);

            lineVertices.push_back(c);
            lineVertices.push_back(a);
        }

        // Setup VAO/VBO
        GLuint vao, vbo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(glm::vec3), lineVertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        // Set up shader uniforms
        glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix since we've already transformed vertices
        if (auto camera = getEntity()->getCore()->getCamera()) {
            debugShader->uniform("debugview", camera->getViewMatrix());
            debugShader->uniform("debugprojection", camera->getProjectionMatrix());
            debugShader->uniform("debugmodel", modelMatrix);
            debugShader->uniform("debuglineColor", color);
            debugShader->uniform("debuglinewidth", 2.0f); // Explicit width for Linux
        }

        // Draw with line width (important for Linux)
        glLineWidth(2.0f);
        glDrawArrays(GL_LINES, 0, lineVertices.size());

        // Cleanup
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);

        // Restore GL state
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }


}
