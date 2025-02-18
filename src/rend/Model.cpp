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

        while (!file.eof()) {
            std::getline(file, currentline);
            if (currentline.length() < 1) continue;

            std::vector<std::string> tokens;
            split_string_whitespace(currentline, tokens);
            if (tokens.size() < 1) continue;

            if (tokens.at(0) == "mtllib") {
                // Get directory of the OBJ file
                std::string objDirectory = _path.substr(0, _path.find_last_of("/\\") + 1);

                // Construct full MTL file path
                std::string mtlFilePath = objDirectory + tokens.at(1);

                // Load MTL file
                LoadMTL(mtlFilePath);
            }
            else if (tokens.at(0) == "usemtl") {
                currentMaterialName = tokens.at(1);

                // Check if the material exists in the map
                if (materialIndexMap.find(currentMaterialName) == materialIndexMap.end()) {
                    std::cerr << "Warning: Material '" << currentMaterialName << "' not found in MTL file." << std::endl;
                    currentMaterialName = ""; // Reset material name if not found
                }
            }
            else if (tokens.at(0) == "v" && tokens.size() >= 4) {
                glm::vec3 p(
                    atof(tokens.at(1).c_str()),
                    atof(tokens.at(2).c_str()),
                    atof(tokens.at(3).c_str()));
                positions.push_back(p);
            }
            else if (tokens.at(0) == "vt" && tokens.size() >= 3) {
                glm::vec2 tc(
                    atof(tokens.at(1).c_str()),
                    1.0f - atof(tokens.at(2).c_str()));
                tcs.push_back(tc);
            }
            else if (tokens.at(0) == "vn" && tokens.size() >= 4) {
                glm::vec3 n(
                    atof(tokens.at(1).c_str()),
                    atof(tokens.at(2).c_str()),
                    atof(tokens.at(3).c_str()));
                normals.push_back(n);
            }
            else if (tokens.at(0) == "f" && tokens.size() >= 4) {
                Face f;
                std::vector<std::string> sub;

                split_string(tokens.at(1), '/', sub);
                if (sub.size() >= 1) f.a.position = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) f.a.texcoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) f.a.normal = normals.at(atoi(sub.at(2).c_str()) - 1);

                for (size_t ti = 2; ti + 1 < tokens.size(); ti++) {
                    split_string(tokens.at(ti), '/', sub);
                    if (sub.size() >= 1) f.b.position = positions.at(atoi(sub.at(0).c_str()) - 1);
                    if (sub.size() >= 2) f.b.texcoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                    if (sub.size() >= 3) f.b.normal = normals.at(atoi(sub.at(2).c_str()) - 1);

                    split_string(tokens.at(ti + 1), '/', sub);
                    if (sub.size() >= 1) f.c.position = positions.at(atoi(sub.at(0).c_str()) - 1);
                    if (sub.size() >= 2) f.c.texcoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                    if (sub.size() >= 3) f.c.normal = normals.at(atoi(sub.at(2).c_str()) - 1);

                    if (materialIndexMap.find(currentMaterialName) != materialIndexMap.end()) {
                        f.materialIndex = materialIndexMap[currentMaterialName];
                    }
               


                    m_faces.push_back(f);
                    m_dirty = true;
                }
            }
        }
    }

    rend::Model::Vertex::Vertex()
        : position(0.0f), texcoord(0.0f), normal(0.0f) {}

    Model::~Model() {
        if (m_vaoid) glDeleteVertexArrays(1, &m_vaoid);
        if (m_vboid) glDeleteBuffers(1, &m_vboid);
    }

    Model::Model(const Model& _copy)
        : m_vaoid(0), m_vboid(0), m_faces(_copy.m_faces), m_dirty(true) {}

    Model& Model::operator=(const Model& _assign) {
        m_faces = _assign.m_faces;
        m_dirty = true;
        return *this;
    }

    GLsizei Model::vertex_count() const {
        return (GLsizei)m_faces.size() * 3;
    }

    GLuint Model::vao_id() {
        if (!m_faces.size()) throw std::runtime_error("Model is empty");

        if (!m_vboid) {
            glGenBuffers(1, &m_vboid);
            if (!m_vboid) throw std::runtime_error("Failed to generate vertex buffer");
        }

        if (!m_vaoid) {
            glGenVertexArrays(1, &m_vaoid);
            if (!m_vaoid) throw std::runtime_error("Failed to generate vertex array");
        }

        if (m_dirty) {
            std::vector<GLfloat> data;
            for (const auto& face : m_faces) {
                // Push vertex data for each face
                // (Same as your existing implementation)
            }

            glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(m_vaoid);
            glBindBuffer(GL_ARRAY_BUFFER, m_vboid);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(data.at(0)), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(data.at(0)), (void*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(data.at(0)), (void*)(5 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            m_dirty = false;
        }

        return m_vaoid;
    }

    void Model::Draw() {
        glBindVertexArray(m_vaoid);

        for (size_t i = 0; i < m_faces.size(); i++) {
            glDrawArrays(GL_TRIANGLES, i * 3, 3); // Each face has 3 vertices
        }

        glBindVertexArray(0);
    }


    void Model::LoadMTL(const std::string& mtlFilePath) {
        std::ifstream file(mtlFilePath);
        std::string line;
        Material* currentMaterial = nullptr;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "newmtl") {
                std::string materialName;
                iss >> materialName;
                materials.push_back(Material());
                currentMaterial = &materials.back();
                currentMaterial->name = materialName;
                materialIndexMap[materialName] = materials.size() - 1;


            }

            else if (prefix == "Ka" && currentMaterial) {
                iss >> currentMaterial->ambientColor.x >> currentMaterial->ambientColor.y >> currentMaterial->ambientColor.z;
            }
            else if (prefix == "Kd" && currentMaterial) {
                iss >> currentMaterial->diffuseColor.x >> currentMaterial->diffuseColor.y >> currentMaterial->diffuseColor.z;
            }
            else if (prefix == "Ks" && currentMaterial) {
                iss >> currentMaterial->specularColor.x >> currentMaterial->specularColor.y >> currentMaterial->specularColor.z;
            }
            else if (prefix == "Ns" && currentMaterial) {
                iss >> currentMaterial->specularExponent;
            }
            else if (prefix == "map_Kd" && currentMaterial) {
                iss >> currentMaterial->diffuseTexturePath;

                // Debug output
                std::cout << "Original texture path from MTL: " << currentMaterial->diffuseTexturePath << std::endl;

                // Ensure path is properly set
                if (currentMaterial->diffuseTexturePath.find('/') == std::string::npos &&
                    currentMaterial->diffuseTexturePath.find('\\') == std::string::npos) {
                    std::string objDirectory = mtlFilePath.substr(0, mtlFilePath.find_last_of("/\\") + 1);
                    currentMaterial->diffuseTexturePath = objDirectory + currentMaterial->diffuseTexturePath;
                }

                std::cout << "Final texture path: " << currentMaterial->diffuseTexturePath << std::endl;

                currentMaterial->diffuseTextureID = LoadTexture(currentMaterial->diffuseTexturePath);
            }

        }
    }

    GLuint Model::LoadTexture(const std::string& path) {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
        else {
            std::cerr << "Failed to load texture: " << path << ". Using default texture.\n";

            // Load default texture if not already loaded
            if (defaultTextureID == 0) {
                defaultTextureID = generateDefaultTexture("assets/map/1.png"); // Change this to your default PNG path
            }
            textureID = defaultTextureID;
        }

        return textureID;
    }

    GLuint Model::generateDefaultTexture(const std::string& defaultTexturePath) {
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(defaultTexturePath.c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
        else {
            std::cerr << "Critical Error: Default texture missing (" << defaultTexturePath << "). Using white fallback.\n";
            unsigned char whitePixel[4] = { 255, 255, 255, 255 }; // White RGBA pixel
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texID;
    }


    void Model::split_string_whitespace(const std::string& _input, std::vector<std::string>& _output) {
        std::string curr;
        _output.clear();

        for (size_t i = 0; i < _input.length(); i++) {
            if (_input.at(i) == ' ' || _input.at(i) == '\r' || _input.at(i) == '\n' || _input.at(i) == '\t') {
                if (curr.length() > 0) {
                    _output.push_back(curr);
                    curr = "";
                }
            }
            else {
                curr += _input.at(i);
            }
        }

        if (curr.length() > 0) {
            _output.push_back(curr);
        }
    }

    void Model::split_string(const std::string& _input, char _splitter, std::vector<std::string>& _output) {
        std::string curr;
        _output.clear();

        for (size_t i = 0; i < _input.length(); i++) {
            if (_input.at(i) == _splitter) {
                _output.push_back(curr);
                curr = "";
            }
            else {
                curr += _input.at(i);
            }
        }

        if (curr.length() > 0) {
            _output.push_back(curr);
        }
    }

} // namespace rend