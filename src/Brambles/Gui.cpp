#include "Gui.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Input.h"
#include "Component.h"
#include "Resources/Texture.h"
#include "Window.h"
#include <glm/glm.hpp>



namespace Brambles
{


	Gui::Gui()
	{
		meshCube(); //initializes the mesh functions
		meshCircle();
		meshTriangle();
		meshStar();

	}
	Gui::~Gui()
	{

	}

	int Gui::button(glm::vec2 _position, glm::vec2 _size, std::shared_ptr<Brambles::Texture> _texture, std::shared_ptr<rend::Mesh> _shape)
	{
		glm::vec2 Position = _position - (_size * 0.5f);

		glm::mat4 guiModel(1.0f);
		guiModel = glm::translate(guiModel, glm::vec3(Position.x, Position.y, 0));
		guiModel = glm::scale(guiModel, glm::vec3(_size.x, _size.y, 1));

		guiShader->use();
		guiShader->uniform("u_Model", guiModel);

		guiShader->uniform("u_ViewPos", glm::vec3(0.0f, 0.1f, 0.9f));//Not accurate but will do for now

		
		glm::mat4 uiProjection = glm::ortho(0.0f, static_cast<float>(700), 0.0f, static_cast<float>(700), 0.0f, 1.0f);

		guiShader->uniform("u_Projection", uiProjection);
		guiShader->uniform("u_View", glm::mat4(1.0f));

		glBindTexture(GL_TEXTURE_2D, _texture->getTexture()->id());//binds the texture to the shader

		guiShader->draw(_shape->getVAOId(), _shape->vertexCount());



		//calling a read acsess violation going to hard code in controller for now 
		glm::vec2 mousePosition;
		m_core.lock()->getInput()->getMousePosition(mousePosition.x, mousePosition.y);

		if (getEntity() )
		{
			if (mousePosition.x > Position.x && mousePosition.x < Position.x + _size.x && mousePosition.y > Position.y && mousePosition.y < Position.y + _size.y)
			{
				if (m_core.lock()->getInput()->isKey(SDLK_f))
				{
					return 1;
				}
				else if (m_core.lock()->getInput()->isKey(SDLK_e))
				{
					return 2;
				}
			}
		}

		return 0;
	}

	std::shared_ptr<rend::Mesh> Gui::meshCube()//creates a cube mesh
	{
		std::shared_ptr<rend::Mesh> guiMeshCube = std::make_shared<rend::Mesh>();

		rend::Face face;
		face.a.position = glm::vec3(1.0f, 0.0f, 0.0f);
		face.b.position = glm::vec3(0.0f, 1.0f, 0.0f);
		face.c.position = glm::vec3(0.0f, 0.0f, 0.0f);
		face.a.texcoord = glm::vec2(1.0f, 0.0f);
		face.b.texcoord = glm::vec2(0.0f, 1.0f);
		face.c.texcoord = glm::vec2(0.0f, 0.0f);
		guiMeshCube->addFace(face);

		rend::Face face2;
		face2.a.position = glm::vec3(1.0f, 0.0f, 0.0f);
		face2.b.position = glm::vec3(1.0f, 1.0f, 0.0f);
		face2.c.position = glm::vec3(0.0f, 1.0f, 0.0f);
		face2.a.texcoord = glm::vec2(1.0f, 0.0f);
		face2.b.texcoord = glm::vec2(1.0f, 1.0f);
		face2.c.texcoord = glm::vec2(0.0f, 1.0f);
		guiMeshCube->addFace(face2);

		return guiMeshCube;
	}

	std::shared_ptr<rend::Mesh> Gui::meshCircle()//creates a circle mesh
	{
		std::shared_ptr<rend::Mesh> guiMeshCircle = std::make_shared<rend::Mesh>();

		int numSegments = 36;
		float radius = 1.0f;

		for (int i = 0; i < numSegments; ++i)
		{
			float angle1 = 2.0f * glm::pi<float>() * i / numSegments;
			float angle2 = 2.0f * glm::pi<float>() * (i + 1) / numSegments;

			// Create the center vertex
			rend::Face face;
			face.a.position = glm::vec3(0.0f, 0.0f, 0.0f);
			face.a.texcoord = glm::vec2(0.5f, 0.5f); 

			
			face.b.position = glm::vec3(radius * cos(angle1), radius * sin(angle1), 0.0f);
			face.c.position = glm::vec3(radius * cos(angle2), radius * sin(angle2), 0.0f);

			face.b.texcoord = glm::vec2(0.5f + 0.5f * cos(angle1), 0.5f + 0.5f * sin(angle1));
			face.c.texcoord = glm::vec2(0.5f + 0.5f * cos(angle2), 0.5f + 0.5f * sin(angle2));

			
			guiMeshCircle->addFace(face);
		}

		return guiMeshCircle;
	}
	std::shared_ptr<rend::Mesh> Gui::meshTriangle()//creates a triangle mesh
	{
		std::shared_ptr<rend::Mesh> guiMeshTriangle = std::make_shared<rend::Mesh>();

		rend::Face face;
		face.a.position = glm::vec3(0.0f, 1.0f, 0.0f);  
		face.b.position = glm::vec3(-1.0f, -1.0f, 0.0f);  
		face.c.position = glm::vec3(1.0f, -1.0f, 0.0f);  

		
		face.a.texcoord = glm::vec2(0.5f, 1.0f);  
		face.b.texcoord = glm::vec2(0.0f, 0.0f);  
		face.c.texcoord = glm::vec2(1.0f, 0.0f);  

		guiMeshTriangle->addFace(face);

		return guiMeshTriangle;
	}

	std::shared_ptr<rend::Mesh> Gui::meshStar()//creates a star mesh
	{
		std::shared_ptr<rend::Mesh> guiMeshStar = std::make_shared<rend::Mesh>();

		int numPoints = 5;  
		float outerRadius = 1.0f;
		float innerRadius = 0.4f;  

		for (int i = 0; i < numPoints; ++i)
		{
	
			float angleOuter1 = 2.0f * glm::pi<float>() * i / numPoints;
			float angleOuter2 = 2.0f * glm::pi<float>() * (i + 1) / numPoints;
			float angleInner = angleOuter1 + glm::pi<float>() / numPoints;  
			
			glm::vec3 outer1 = glm::vec3(outerRadius * cos(angleOuter1), outerRadius * sin(angleOuter1), 0.0f);
			glm::vec3 outer2 = glm::vec3(outerRadius * cos(angleOuter2), outerRadius * sin(angleOuter2), 0.0f);
			glm::vec3 inner = glm::vec3(innerRadius * cos(angleInner), innerRadius * sin(angleInner), 0.0f);

		
			rend::Face face1, face2;

			
			face1.a.position = outer1;
			face1.b.position = inner;
			face1.c.position = outer2;

			face1.a.texcoord = glm::vec2(0.5f + 0.5f * cos(angleOuter1), 0.5f + 0.5f * sin(angleOuter1));
			face1.b.texcoord = glm::vec2(0.5f + 0.5f * cos(angleInner), 0.5f + 0.5f * sin(angleInner));
			face1.c.texcoord = glm::vec2(0.5f + 0.5f * cos(angleOuter2), 0.5f + 0.5f * sin(angleOuter2));

			guiMeshStar->addFace(face1);

			
			face2.a.position = outer2;
			face2.b.position = inner;
			face2.c.position = outer1;

			face2.a.texcoord = glm::vec2(0.5f + 0.5f * cos(angleOuter2), 0.5f + 0.5f * sin(angleOuter2));
			face2.b.texcoord = glm::vec2(0.5f + 0.5f * cos(angleInner), 0.5f + 0.5f * sin(angleInner));
			face2.c.texcoord = glm::vec2(0.5f + 0.5f * cos(angleOuter1), 0.5f + 0.5f * sin(angleOuter1));

			guiMeshStar->addFace(face2);
		}

		return guiMeshStar;
	}



}