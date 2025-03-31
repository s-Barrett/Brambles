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
            face.c.position = corners[edge[0]]; // Duplicate point to maintain structure
            mesh->addFace(face);
        }

        return mesh;
    }

    void DebugRenderer::drawWireframeBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color)
    {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        debugShader->use();

        glm::vec3 boxOffset = getEntity()->getComponent<BoxCollider>()->getOffset();
        glm::vec3 boxSize = getEntity()->getComponent<BoxCollider>()->getSize();
        glm::vec3 genBoxSize = boxSize; // Use the actual size

        auto mesh = generateBoxMesh(genBoxSize);
        GLuint vao = mesh->getVAOId();
        GLsizei vertexCount = mesh->vertexCount();

        glm::mat4 m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, getTransform()->getPosition() + boxOffset);

        auto camera = getEntity()->getCore()->getCamera();
        if (camera)
        {
            glm::mat4 perspectiveProjection = camera->getProjectionMatrix();
            glm::mat4 view = camera->getViewMatrix();

            debugShader->uniform("debugview", view);
            debugShader->uniform("debugprojection", perspectiveProjection);
            debugShader->uniform("debugmodel", m_modelMatrix);
            debugShader->uniform("debuglineColor", glm::vec3(0, 1, 0));
            debugShader->uniform("debuglinewidth", 2.0f);
        }
        else
        {
            std::cerr << "No camera found" << std::endl;
        }

		debugShader->drawOutline(vao, vertexCount);// Draw function to bind this is in rend shader.cpp
    }

    void DebugRenderer::drawBoxCollider(std::shared_ptr<BoxCollider> collider, const glm::vec3& color)
    {
        glm::vec3 position = collider->getPosition() + collider->getOffset();
        glm::vec3 size = collider->getSize();
        drawWireframeBox(position, size, color);
    }

    void DebugRenderer::drawMeshCollider(std::shared_ptr<MeshCollider> collider, const glm::vec3& color) {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        debugShader->use();

        auto model = collider->getModel();
        if (!model) {
            std::cerr << "MeshCollider: No model found!" << std::endl;
            return;
        }

        // Get the mesh data
        const auto& faces = model->getFaces();

        std::vector<glm::vec3> lineVertices;

        for (const auto& face : faces) {
            // Store each triangle's edges as line segments
            lineVertices.push_back(face.a.position);
            lineVertices.push_back(face.b.position);

            lineVertices.push_back(face.b.position);
            lineVertices.push_back(face.c.position);

            lineVertices.push_back(face.c.position);
            lineVertices.push_back(face.a.position);
        }

        GLuint vao, vbo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(glm::vec3), lineVertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        // Apply transformation
        glm::mat4 m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, collider->getTransform()->getPosition() + collider->getOffset());

        auto camera = getEntity()->getCore()->getCamera();
        if (camera) {
            glm::mat4 perspectiveProjection = camera->getProjectionMatrix();
            glm::mat4 view = camera->getViewMatrix();

            debugShader->uniform("debugview", view);
            debugShader->uniform("debugprojection", perspectiveProjection);
            debugShader->uniform("debugmodel", m_modelMatrix);
            debugShader->uniform("debuglineColor", color);
        }
        else {
            std::cerr << "No camera found" << std::endl;
        }

		debugShader->drawMeshOutline(vao, vbo, lineVertices.size());

    }


}
