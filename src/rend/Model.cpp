#include "Model.h"
#include "stb_image.h"

namespace rend {

    Model::Model()
        : m_vaoid(0), m_vboid(0), m_dirty(false) {}

    Model::Model(const std::string& _path)
        : m_vaoid(0), m_vboid(0), m_dirty(false) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> tcs;
        std::vector<glm::vec3> normals;
        std::string currentline;
        std::string currentMaterialName;

        std::ifstream file(_path.c_str());
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open model [" + _path + "]");
        }

        std::cout << "Loading model: " << _path << std::endl;

        while (std::getline(file, currentline)) {
            if (currentline.empty()) continue;

            std::vector<std::string> tokens;
            split_string_whitespace(currentline, tokens);
            if (tokens.empty()) continue;

            if (tokens[0] == "mtllib") {
                std::string objDirectory = _path.substr(0, _path.find_last_of("/\\") + 1);
                std::string mtlFilePath = objDirectory + tokens[1];
                LoadMTL(mtlFilePath);
            }
            else if (tokens[0] == "usemtl") {
                currentMaterialName = tokens[1];
                if (materialIndexMap.find(currentMaterialName) == materialIndexMap.end()) {
                    std::cerr << "Warning: Material '" << currentMaterialName << "' not found in MTL file." << std::endl;
                    currentMaterialName = "";
                }
                else {
                    std::cout << "Using material: " << currentMaterialName << std::endl;
                }
            }
            else if (tokens[0] == "v" && tokens.size() >= 4) {
                positions.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            }
            else if (tokens[0] == "vt" && tokens.size() >= 3) {
                tcs.emplace_back(std::stof(tokens[1]), 1.0f - std::stof(tokens[2]));
            }
            else if (tokens[0] == "vn" && tokens.size() >= 4) {
                normals.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            }
            else if (tokens[0] == "f" && tokens.size() >= 4) {
                size_t currentVertexIndex = 0; // Removed static

                for (size_t i = 1; i < tokens.size() - 2; ++i) {
                    Face f;
                    f.materialIndex = materialIndexMap[currentMaterialName];
                    f.startIndex = m_faces.size() * 3;  // Each face has 3 vertices

                    std::vector<std::string> sub;
                    for (int j = 0; j < 3; ++j) {
                        split_string(tokens[i + j], '/', sub);
                        Vertex v;
                        if (!sub[0].empty()) v.position = positions[std::stoi(sub[0]) - 1];
                        if (sub.size() > 1 && !sub[1].empty()) v.texcoord = tcs[std::stoi(sub[1]) - 1];
                        if (sub.size() > 2 && !sub[2].empty()) v.normal = normals[std::stoi(sub[2]) - 1];

                        if (j == 0) f.a = v;
                        else if (j == 1) f.b = v;
                        else f.c = v;
                    }

                    m_faces.push_back(f);
                }

                m_dirty = true;
            }
        }
    }

    Model::~Model() {
        if (m_vaoid) glDeleteVertexArrays(1, &m_vaoid);
        if (m_vboid) glDeleteBuffers(1, &m_vboid);
    }

    rend::Model::Vertex::Vertex()
        : position(0.0f), texcoord(0.0f), normal(0.0f) {}

    GLsizei Model::vertex_count() const {
        return static_cast<GLsizei>(m_faces.size() * 3);
    }

    GLuint Model::vao_id() {
        if (m_faces.empty()) throw std::runtime_error("Model is empty");

        if (!m_vboid) glGenBuffers(1, &m_vboid);
        if (!m_vaoid) glGenVertexArrays(1, &m_vaoid);

        if (m_dirty) {
            std::vector<GLfloat> data;
            for (const auto& face : m_faces) {
                for (const auto& vertex : { face.a, face.b, face.c }) {
                    data.insert(data.end(), { vertex.position.x, vertex.position.y, vertex.position.z,
                                             vertex.texcoord.x, vertex.texcoord.y,
                                             vertex.normal.x, vertex.normal.y, vertex.normal.z });
                }
            }

            glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

            glBindVertexArray(m_vaoid);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
            m_dirty = false;
        }

        return m_vaoid;
    }

    void Model::LoadMTL(const std::string& mtlFilePath) {
        std::ifstream file(mtlFilePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open MTL file: " << mtlFilePath << std::endl;
            return;
        }

        std::string line;
        Material* currentMaterial = nullptr;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "newmtl") {
                std::string materialName;
                iss >> materialName;
                materials.emplace_back();
                currentMaterial = &materials.back();
                currentMaterial->name = materialName;
                materialIndexMap[materialName] = materials.size() - 1;

                std::cout << "Loaded material: " << materialName << std::endl;
            }
            else if (currentMaterial) {
                if (prefix == "map_Kd") {
                    iss >> currentMaterial->diffuseTexturePath;
                    std::string fullTexturePath = mtlFilePath.substr(0, mtlFilePath.find_last_of("/\\") + 1) + currentMaterial->diffuseTexturePath;

                    int width, height, channels;
                    unsigned char* data = stbi_load(fullTexturePath.c_str(), &width, &height, &channels, 0);
                    if (data) {
                        glGenTextures(1, &currentMaterial->diffuseTextureID);
                        glBindTexture(GL_TEXTURE_2D, currentMaterial->diffuseTextureID);
                        glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA : GL_RGB,
                            width, height, 0, channels == 4 ? GL_RGBA : GL_RGB,
                            GL_UNSIGNED_BYTE, data);
                        glGenerateMipmap(GL_TEXTURE_2D);
                        stbi_image_free(data);
                    }
                    else {
                        std::cerr << "Failed to load texture: " << fullTexturePath << std::endl;
                    }
                }
            }
        }
    }

    void Model::split_string_whitespace(const std::string& _input, std::vector<std::string>& _output) {
        std::istringstream stream(_input);
        std::string token;
        _output.clear();
        while (stream >> token) _output.push_back(token);
    }

    void Model::split_string(const std::string& _input, char _splitter, std::vector<std::string>& _output) {
        std::istringstream stream(_input);
        std::string token;
        _output.clear();
        while (std::getline(stream, token, _splitter)) _output.push_back(token);
    }

} // namespace rend