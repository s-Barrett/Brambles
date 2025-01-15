#include "Gui.h"
#include "Core.h"
#include "Entity.h"
#include "Input.h"
#include "Component.h"
#include "Resources/Texture.h"
#include "Window.h"
#include <glm/glm.hpp>



namespace Brambles
{


	



	Gui::Gui()
	{
		meshCube();
		meshCircle();


	}
	Gui::~Gui()
	{

	}

	bool Gui::isMouseOverButton(glm::vec2 mousePos, glm::vec2 buttonPos, glm::vec2 buttonSize) {
		return (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
			mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y);
	}

	int Gui::button(glm::vec2 _position, glm::vec2 _size, std::shared_ptr<Brambles::Texture> _texture, std::shared_ptr<rend::Mesh> _shape)
	{
		glm::vec2 Position = _position - (_size * 0.5f); // Adjust position to center

		glm::mat4 guiModel(1.0f);
		guiModel = glm::translate(guiModel, glm::vec3(Position.x, Position.y, 0));
		guiModel = glm::scale(guiModel, glm::vec3(_size.x, _size.y, 1));

		guiShader->use();
		guiShader->uniform("u_Model", guiModel);

		
		
		glm::mat4 uiProjection = glm::ortho(0.0f, static_cast<float>(700), 0.0f, static_cast<float>(700), 0.0f, 1.0f);

		guiShader->uniform("u_Projection", uiProjection);
		guiShader->uniform("u_View", glm::mat4(1.0f)); // Identity matrix for 2D UI rendering

		glBindTexture(GL_TEXTURE_2D, _texture->getTexture()->id());

		// Draw the mesh (button) using your GUI mesh (assuming you've set it up)
		guiShader->draw(_shape->getVAOId(), _shape->vertexCount());

		

		return 0;
	}


	std::shared_ptr<rend::Mesh> Gui::meshCube()
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

	std::shared_ptr<rend::Mesh> Gui::meshCircle()
	{
		std::shared_ptr<rend::Mesh> guiMeshCircle = std::make_shared<rend::Mesh>();

		int numSegments = 36;
		float radius = 1.0f;

		// Loop over each segment to create faces of the circle
		for (int i = 0; i < numSegments; ++i)
		{
			float angle1 = 2.0f * glm::pi<float>() * i / numSegments;
			float angle2 = 2.0f * glm::pi<float>() * (i + 1) / numSegments;

			// Create the center vertex
			rend::Face face;
			face.a.position = glm::vec3(0.0f, 0.0f, 0.0f);
			face.a.texcoord = glm::vec2(0.5f, 0.5f);  // The center will always have the same texcoord

			// Calculate positions on the perimeter
			face.b.position = glm::vec3(radius * cos(angle1), radius * sin(angle1), 0.0f);
			face.c.position = glm::vec3(radius * cos(angle2), radius * sin(angle2), 0.0f);

			// Assign texcoords to the perimeter points, mapping them around the circle
			face.b.texcoord = glm::vec2(0.5f + 0.5f * cos(angle1), 0.5f + 0.5f * sin(angle1));
			face.c.texcoord = glm::vec2(0.5f + 0.5f * cos(angle2), 0.5f + 0.5f * sin(angle2));

			// Add the face to the mesh
			guiMeshCircle->addFace(face);
		}

		return guiMeshCircle;
	}
}