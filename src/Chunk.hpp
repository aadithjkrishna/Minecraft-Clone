#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Mesh.hpp"
#include "BlockType.hpp"
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>

struct HashFunction {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

class Chunk {
    public:
        static const int chunk_size = 16;
        static const int world_height = 16;
        static const unsigned int textureWidth = 128, textureHeight = 128;
        static constexpr float tex_x_offset = 16 / static_cast<float> (textureWidth);
        static constexpr float tex_y_offset = 16 / static_cast<float> (textureHeight);
        int totalChunks;
        glm::vec2 position;
        BLOCKS ***block_data;
        Mesh *self;
        static Texture* textures;
        Chunk* leftChunk = nullptr;
        Chunk* rightChunk = nullptr;
        Chunk* frontChunk = nullptr;
        Chunk* backChunk = nullptr;
        Chunk(Texture textures[], int totalChunks);
        Chunk();
        Chunk(glm::vec2 position);
        ~Chunk();
        Mesh* toGenerateMesh(BLOCKS ***leftChunk, BLOCKS ***rightChunk, BLOCKS ***frontChunk, BLOCKS ***backChunk);
        void generateChunk(float frequency, float amplitude);
        std::vector<FACES> checkNeighbours(int i, int j, int k, BLOCKS ***leftChunk, BLOCKS ***rightChunk, BLOCKS ***frontChunk, BLOCKS ***backChunk);
        const std::vector<glm::vec2>& texCoordinates(BLOCKS block);
        void Draw(Shader &shader, Camera &camera);
        // void updateChunk(std::vector<Chunk*>& chunks);
        void updateChunk(std::unordered_map<std::pair<int, int>, Chunk*, HashFunction>& chunks);
        void updateChunk(Chunk* chunks);
        void checkNeighbourChunks(std::vector<Chunk*>& chunks);
        void checkNeighbourChunks(std::unordered_map<std::pair<int, int>, Chunk*, HashFunction>& chunks);
        // void updateChunk(Chunk** chunks);
        // void checkNeighbourChunks(Chunk** chunks);
        void saveChunk();
        bool loadChunk();
        void update();

        void setChunk(Chunk *chunk, FACES faces);
    private:
        float perlinNoise(float x, float z, float frequency, float amplitude);
        BLOCKS ***createChunk();
        void unloadChunk();
};

#endif