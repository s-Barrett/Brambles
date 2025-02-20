#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include <iostream>



namespace rend {

    struct Model 
    {
    public:
        Model();
        Model(const std::string& _path);
        Model(const Model& _copy);
        Model& operator=(const Model& _assign);
        virtual ~Model();

      
        GLsizei vertex_count() const;
        GLuint vao_id();
        void LoadMTL(const std::string& mtlFilePath);


        struct Material {
            std::string name;
            glm::vec3 ambientColor;
            glm::vec3 diffuseColor;
            glm::vec3 specularColor;
            float specularExponent;
            std::string diffuseTexturePath;
            GLuint diffuseTextureID;

            Material()
                : ambientColor(0.0f), diffuseColor(0.0f), specularColor(0.0f), specularExponent(0.0f), diffuseTextureID(0) {}
        };

        struct Vertex {
            Vertex(); // Declaration only
            glm::vec3 position;
            glm::vec2 texcoord;
            glm::vec3 normal;
        };

        struct Face {
            Vertex a, b, c;
            size_t materialIndex;
			size_t startIndex;
        };

        std::vector<Material> materials;
        std::vector<Face> m_faces;

    private:



        std::unordered_map<std::string, size_t> materialIndexMap;
        GLuint m_vaoid, m_vboid;
        bool m_dirty;

        void split_string_whitespace(const std::string& _input, std::vector<std::string>& _output);
        void split_string(const std::string& _input, char _splitter, std::vector<std::string>& _output);
    };

} // namespace rend

#endif // MODEL_H