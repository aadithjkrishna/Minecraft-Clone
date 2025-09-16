#include "Texture.hpp"
#include <iostream>

Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType) {
    type = texType;
    int widthImg, heightImg, numColCh;

    // Flip the image vertically (optional based on your texture file)
    // stbi_set_flip_vertically_on_load(true);

    // Load the image
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
    if (!bytes) {
        std::cerr << "ERROR: Failed to load texture: " << image << std::endl;
        return;
    }

    // Generate and bind the texture
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, ID);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "ERROR: OpenGL error during texture generation: " << error << std::endl;
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the image memory
    stbi_image_free(bytes);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    shader.Activate();
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    if (texUni == -1) {
        std::cerr << "ERROR: Uniform '" << uniform << "' not found in shader!" << std::endl;
    }
    glUniform1i(texUni, unit);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}
