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
                else
                {
					std::cout << "Using material: " << currentMaterialName << std::endl;
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

               

                // Parse the first vertex of the face
                split_string(tokens.at(1), '/', sub);
                if (sub.size() >= 1) {
                    int posIndex = atoi(sub.at(0).c_str()) - 1;
                    if (posIndex >= 0 && posIndex < positions.size()) {
                        f.a.position = positions.at(posIndex);
                    }
                    else {
                        std::cerr << "Warning: Invalid position index in face data." << std::endl;
                    }
                }
                if (sub.size() >= 2) {
                    int tcIndex = atoi(sub.at(1).c_str()) - 1;
                    if (tcIndex >= 0 && tcIndex < tcs.size()) {
                        f.a.texcoord = tcs.at(tcIndex);
                    }
                    else {
                        std::cerr << "Warning: Invalid texture coordinate index in face data." << std::endl;
                    }
                }
                if (sub.size() >= 3) {
                    int normalIndex = atoi(sub.at(2).c_str()) - 1;
                    if (normalIndex >= 0 && normalIndex < normals.size()) {
                        f.a.normal = normals.at(normalIndex);
                    }
                    else {
                        std::cerr << "Warning: Invalid normal index in face data." << std::endl;
                    }
                }

                // Parse the remaining vertices of the face
                for (size_t ti = 2; ti + 1 < tokens.size(); ti++) {
                    split_string(tokens.at(ti), '/', sub);
                    if (sub.size() >= 1) {
                        int posIndex = atoi(sub.at(0).c_str()) - 1;
                        if (posIndex >= 0 && posIndex < positions.size()) {
                            f.b.position = positions.at(posIndex);
                        }
                        else {
                            std::cerr << "Warning: Invalid position index in face data." << std::endl;
                        }
                    }
                    if (sub.size() >= 2) {
                        int tcIndex = atoi(sub.at(1).c_str()) - 1;
                        if (tcIndex >= 0 && tcIndex < tcs.size()) {
                            f.b.texcoord = tcs.at(tcIndex);
                        }
                        else {
                            std::cerr << "Warning: Invalid texture coordinate index in face data." << std::endl;
                        }
                    }
                    if (sub.size() >= 3) {
                        int normalIndex = atoi(sub.at(2).c_str()) - 1;
                        if (normalIndex >= 0 && normalIndex < normals.size()) {
                            f.b.normal = normals.at(normalIndex);
                        }
                        else {
                            std::cerr << "Warning: Invalid normal index in face data." << std::endl;
                        }
                    }

                    split_string(tokens.at(ti + 1), '/', sub);
                    if (sub.size() >= 1) {
                        int posIndex = atoi(sub.at(0).c_str()) - 1;
                        if (posIndex >= 0 && posIndex < positions.size()) {
                            f.c.position = positions.at(posIndex);
                        }
                        else {
                            std::cerr << "Warning: Invalid position index in face data." << std::endl;
                        }
                    }
                    if (sub.size() >= 2) {
                        int tcIndex = atoi(sub.at(1).c_str()) - 1;
                        if (tcIndex >= 0 && tcIndex < tcs.size()) {
                            f.c.texcoord = tcs.at(tcIndex);
                        }
                        else {
                            std::cerr << "Warning: Invalid texture coordinate index in face data." << std::endl;
                        }
                    }
                    if (sub.size() >= 3) {
                        int normalIndex = atoi(sub.at(2).c_str()) - 1;
                        if (normalIndex >= 0 && normalIndex < normals.size()) {
                            f.c.normal = normals.at(normalIndex);
                        }
                        else {
                            std::cerr << "Warning: Invalid normal index in face data." << std::endl;
                        }
                    }

                    if (materialIndexMap.find(currentMaterialName) != materialIndexMap.end()) {
                        f.materialIndex = materialIndexMap[currentMaterialName];
                    }
                    else {
                        f.materialIndex = -1; // Assign a default value if material isn't found
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
        if (m_faces.empty()) {
            throw std::runtime_error("Model is empty");
        }

        if (!m_vboid) {
            glGenBuffers(1, &m_vboid);
            if (!m_vboid) {
                throw std::runtime_error("Failed to generate vertex buffer");
            }
            std::cout << "Generated VBO with ID: " << m_vboid << std::endl;
        }

        if (!m_vaoid) {
            glGenVertexArrays(1, &m_vaoid);
            if (!m_vaoid) {
                throw std::runtime_error("Failed to generate vertex array");
            }
            std::cout << "Generated VAO with ID: " << m_vaoid << std::endl;
        }

        if (m_dirty) {
            std::vector<GLfloat> data;

            std::cout << "Number of faces: " << m_faces.size() << std::endl;
            if (m_faces.empty()) {
                throw std::runtime_error("No faces found in model.");
            }

            // Populate data with vertex attributes
            for (const auto& face : m_faces) {
                std::vector<Vertex> vertices = { face.a, face.b, face.c };
                for (const auto& vertex : vertices) {
                    data.push_back(vertex.position.x);
                    data.push_back(vertex.position.y);
                    data.push_back(vertex.position.z);
                    data.push_back(vertex.texcoord.x);
                    data.push_back(vertex.texcoord.y);
                    data.push_back(vertex.normal.x);
                    data.push_back(vertex.normal.y);
                    data.push_back(vertex.normal.z);
                }
            }

            if (data.empty()) {
                throw std::runtime_error("Vertex data is empty, cannot create VBO");
            }

            glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            std::cout << "Uploaded vertex data to VBO (size: " << data.size() * sizeof(GLfloat) << " bytes)" << std::endl;

            glBindVertexArray(m_vaoid);
            glBindBuffer(GL_ARRAY_BUFFER, m_vboid);

            // Vertex attributes
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            std::cout << "VAO setup complete." << std::endl;

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

                materials.push_back(Material());
                currentMaterial = &materials.back();
                currentMaterial->name = materialName;
                materialIndexMap[materialName] = materials.size() - 1;

                std::cout << "Loaded material: " << materialName << std::endl;
            }
            else if (currentMaterial) {
                if (prefix == "Ka") {  // Ambient color
                    iss >> currentMaterial->ambientColor.r >> currentMaterial->ambientColor.g >> currentMaterial->ambientColor.b;
                    std::cout << "  Ambient color: " << currentMaterial->ambientColor.r << ", "
                        << currentMaterial->ambientColor.g << ", " << currentMaterial->ambientColor.b << std::endl;
                }
                else if (prefix == "Kd") {  // Diffuse color
                    iss >> currentMaterial->diffuseColor.r >> currentMaterial->diffuseColor.g >> currentMaterial->diffuseColor.b;
                    std::cout << "  Diffuse color: " << currentMaterial->diffuseColor.r << ", "
                        << currentMaterial->diffuseColor.g << ", " << currentMaterial->diffuseColor.b << std::endl;
                }
                else if (prefix == "Ks") {  // Specular color
                    iss >> currentMaterial->specularColor.r >> currentMaterial->specularColor.g >> currentMaterial->specularColor.b;
                    std::cout << "  Specular color: " << currentMaterial->specularColor.r << ", "
                        << currentMaterial->specularColor.g << ", " << currentMaterial->specularColor.b << std::endl;
                }
                else if (prefix == "Ns") {  // Specular exponent
                    iss >> currentMaterial->specularExponent;
                    std::cout << "  Specular exponent: " << currentMaterial->specularExponent << std::endl;
                }
                else if (prefix == "map_Kd") {  // Diffuse texture file
                    iss >> currentMaterial->diffuseTexturePath;
                    std::cout << "  Texture file: " << currentMaterial->diffuseTexturePath << std::endl;

               
					LoadTexture(currentMaterial->diffuseTexturePath);

                }
            }
        }
    }



    GLuint Model::LoadTexture(const std::string& path) {
        std::cout << "Attempting to load texture: " << path << std::endl;

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4); // Force 4 channels (RGBA)

        if (!data) {
            std::cerr << "Failed to load texture: " << path << std::endl;
            return 0; // Return 0 to indicate failure
        }

        std::cout << "Successfully loaded texture: " << path << " (Size: " << width << "x" << height << ")" << std::endl;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);


        stbi_image_free(data);
        return textureID;
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