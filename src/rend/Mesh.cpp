
#include "Mesh.h"
#include <stdexcept>

Mesh::Mesh()
{
	m_vboid = 0;
	m_vaoid = 0;
	m_dirty = false;
}

Mesh::~Mesh() {


}


void Mesh::addFace(Face _face) {
	m_faces.push_back(_face);
    m_dirty = true;
}

GLuint Mesh::getVAOId()
{
    if (!m_faces.size())
    {
        throw std::runtime_error("Model is empty");
    }

    if (!m_vboid)
    {
        glGenBuffers(1, &m_vboid);

        if (!m_vboid)
        {
            throw std::runtime_error("Failed to generate vertex buffer");
        }
    }

    if (!m_vaoid)
    {
        glGenVertexArrays(1, &m_vaoid);

        if (!m_vaoid)
        {
            throw std::runtime_error("Failed to generate vertex array");
        }
    }

    if (m_dirty)
    {
        std::vector<GLfloat> data;

        for (size_t fi = 0; fi < m_faces.size(); ++fi)
        {
            data.push_back(m_faces[fi].a.position.x);
            data.push_back(m_faces[fi].a.position.y);
            data.push_back(m_faces[fi].a.position.z);
            data.push_back(m_faces[fi].a.texcoord.x);
            data.push_back(m_faces[fi].a.texcoord.y);
            data.push_back(m_faces[fi].a.normal.x);
            data.push_back(m_faces[fi].a.normal.y);
            data.push_back(m_faces[fi].a.normal.z);

            data.push_back(m_faces[fi].b.position.x);
            data.push_back(m_faces[fi].b.position.y);
            data.push_back(m_faces[fi].b.position.z);
            data.push_back(m_faces[fi].b.texcoord.x);
            data.push_back(m_faces[fi].b.texcoord.y);
            data.push_back(m_faces[fi].b.normal.x);
            data.push_back(m_faces[fi].b.normal.y);
            data.push_back(m_faces[fi].b.normal.z);

            data.push_back(m_faces[fi].c.position.x);
            data.push_back(m_faces[fi].c.position.y);
            data.push_back(m_faces[fi].c.position.z);
            data.push_back(m_faces[fi].c.texcoord.x);
            data.push_back(m_faces[fi].c.texcoord.y);
            data.push_back(m_faces[fi].c.normal.x);
            data.push_back(m_faces[fi].c.normal.y);
            data.push_back(m_faces[fi].c.normal.z);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(m_vaoid);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboid);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            8 * sizeof(data.at(0)), (void*)0);

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
            8 * sizeof(data.at(0)), (void*)(3 * sizeof(GLfloat)));

        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
            8 * sizeof(data.at(0)), (void*)(5 * sizeof(GLfloat)));

        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_dirty = false;
    }

    return m_vaoid;

}


GLsizei Mesh::vertexCount() const
{
	return (GLsizei)m_faces.size() * 3;
}


//create the vaos and vbos for each fill with values in m_faces and retur id + set ID = false