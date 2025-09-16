#ifndef MESH_CLASS_HPP
#define MESH_CLASS_HPP

#include <string>

#include "VAO.hpp"
#include "EBO.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

class Mesh {
    public:
        std::vector <Vertex> vertices;
        std::vector <GLuint> indices;
        std::vector <Texture> textures;

        VAO vao;
        Mesh(std::vector <Vertex> &vertices, std::vector <GLuint> &indices, std::vector <Texture> &textures);
        void Draw(Shader &shader, Camera &camera);
};

#endif