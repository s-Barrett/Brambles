#include "DebugRenderer.h"
#include "BoxCollider.h"
#include "Renderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Entity.h"

#include "Core.h"



#include <iostream>
#include <GL/gl.h> 

namespace Brambles
{

	DebugRenderer::DebugRenderer()
        : debugShader("../assets/shaders/debugvert.glsl"
            , "../assets/shaders/debugfrag.glsl")
	{

	}
    

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

        debugShader.use();

        GLuint vao = mesh->getVAOId();
        GLsizei vertexCount = mesh->vertexCount();


        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, size);

        auto camera = getEntity()->getCore()->getCamera();
		if (camera)
		{
			glm::mat4 perspectiveProjection = camera->getProjectionMatrix();
			glm::mat4 view = camera->getViewMatrix();

			debugShader.uniform("u_Model", model);
			debugShader.uniform("u_Color", color);

			glBindVertexArray(vao);
			glDrawArrays(GL_LINES, 0, vertexCount);
		}
        else
        {
			std::cout << "No camera found" << std::endl;
        }

    }

    void DebugRenderer::drawBoxCollider(std::shared_ptr<BoxCollider> collider, const glm::vec3& color)
    {
        glm::vec3 position = collider->getPosition() + collider->getOffset();
		std::cout << collider->getOffset().x << " " << collider->getOffset().y << " " << collider->getOffset().z << std::endl;
        glm::vec3 size = collider->getSize();

        drawWireframeBox(position, size, color);
    }
}
