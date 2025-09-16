#include "Chunk.hpp"

unsigned int seed = 2;

std::unordered_map<BLOCKS, std::vector<glm::vec2>> blockTexCoords = {
    {GRASS, {{0, 0}, {1, 0}, {2, 0}}},
    {DIRT, {{2, 0}}},
    {STONE, {{3, 0}}},
    {IRON, {{4, 0}}},
};

const float length = 1.0f;

Vertex vertices[] = {
    // Front face
    Vertex{glm::vec3(0.0f, 0.0f, length), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, 0.0f, length), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, length, length), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, length, length), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

    // Back face
    Vertex{glm::vec3(length, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, length, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, length, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

    // Right face
    Vertex{glm::vec3(length, 0.0f, length), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, length, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, length, length), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

    // Left face
    Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, 0.0f, length), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, length, length), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, length, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

    // Top face
    Vertex{glm::vec3(0.0f, length, length), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, length, length), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, length, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, length, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

    // Bottom face
    Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(length, 0.0f, length), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, 0.0f, length), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
};

Texture *Chunk::textures = nullptr;

Chunk::Chunk(Texture textures[], int totalChunks)
    : position(0.0f, 0.0f), block_data(nullptr), self(nullptr)
{
    Chunk::textures = textures;
    Chunk::totalChunks = totalChunks;
}

Chunk::Chunk() : position(0.0f, 0.0f), block_data(nullptr), self(nullptr)
{
    position = glm::vec2(0.0f, 0.0f); // Default position
    block_data = createChunk();       // Initialize pointer or set to default value
    self = nullptr;                   // Initialize pointer or set to default value
    // Initialize other members if necessary
}

// Chunk::Chunk(glm::vec2 position) {
//     this->position = position;
//     block_data = createChunk();
//     if (!loadChunk())
//     {
//         generateChunk(0.1f, 10.0f);
//         saveChunk();
//     }
//     self = toGenerateMesh(nullptr, nullptr, nullptr, nullptr);
// }

Chunk::Chunk(glm::vec2 position)
{
    this->position = position;
    block_data = createChunk();

    generateChunk(0.09f, 3.0f);

    self = toGenerateMesh(nullptr, nullptr, nullptr, nullptr);
}

Chunk::~Chunk()
{
    unloadChunk();
}

// void Chunk::generateChunk(float frequency, float amplitude) {
//     // srand(seed);
//     int tempX = rand();
//     int tempZ = rand();
//     for (int x = 0; x < chunk_size; x++) {
//         for (int z = 0; z < chunk_size; z++) {
//             float offsetX = (rand() % 100 - 50) / 100.0f;
//             float offsetZ = (rand() % 100 - 50) / 100.0f;

//             float noiseHeight =
//                 perlinNoise(x + offsetX + position.x * chunk_size + tempX, z + offsetZ + position.y * chunk_size + tempZ, frequency, amplitude) +
//                 0.5f * perlinNoise((x + offsetX + position.x * chunk_size + tempX) * 2, (z + offsetZ + position.y * chunk_size + tempZ) * 2, frequency * 2, amplitude * 0.5f);

//             int height = static_cast<int>(world_height / 2 + noiseHeight);

//             for (int y = 0; y < world_height; y++) {
//                 if (y > height - 1) block_data[x][y][z] = AIR; // Air
//                 else if (y == height - 1) block_data[x][y][z] = (rand() % 10 < 2 ? GRASS : GRASS); // Grass with flowers
//                 else if (y > height - 4) block_data[x][y][z] = (rand() % 10 < 3 ? DIRT : DIRT); // Dirt with gravel
//                 else block_data[x][y][z] = STONE; // Stone
//             }
//         }
//     }
// }

void Chunk::generateChunk(float frequency, float amplitude)
{
    for (int x = 0; x < chunk_size; x++)
    {
        for (int z = 0; z < chunk_size; z++)
        {
            float noiseHeight =
                perlinNoise(x + position.x * chunk_size,
                            z + position.y * chunk_size,
                            frequency, amplitude) +
                0.5f * perlinNoise((x + position.x * chunk_size) * 2,
                                   (z + position.y * chunk_size) * 2,
                                   frequency * 2, amplitude * 0.5f);

            int height = static_cast<int>(world_height / 2 + noiseHeight);

            // Populate block data based on height
            for (int y = 0; y < world_height; y++)
            {
                if (y > height - 1)
                    block_data[x][y][z] = AIR; // Air
                else if (y == height - 1)
                    block_data[x][y][z] = GRASS; // Grass
                else if (y > height - 4)
                    block_data[x][y][z] = DIRT; // Dirt
                else
                    block_data[x][y][z] = STONE; // Stone
            }
        }
    }
}

Mesh *Chunk::toGenerateMesh(BLOCKS ***leftChunk, BLOCKS ***rightChunk, BLOCKS ***frontChunk, BLOCKS ***backChunk)
{
    std::vector<Vertex> vertices_temp;
    std::vector<GLuint> indices_temp;
    std::vector<Texture> textures_temp;

    textures_temp.push_back(textures[0]);
    textures_temp.push_back(textures[1]);

    int count = 0;

    for (int i = 0; i < chunk_size; i++)
    {
        for (int j = 0; j < world_height; j++)
        {
            for (int k = 0; k < chunk_size; k++)
            {
                BLOCKS current_block = block_data[i][j][k];
                if (current_block == AIR)
                    continue;

                std::vector<FACES> faces_temp = checkNeighbours(i, j, k,
                                                                leftChunk, rightChunk,
                                                                frontChunk, backChunk);
                const std::vector<glm::vec2> blockTexCoords = texCoordinates(current_block);

                for (FACES face_temp : faces_temp)
                {
                    // Determine texture coordinates for the current face
                    int faceX, faceY;
                    if (blockTexCoords.size() != 1)
                    {
                        if (face_temp < 4)
                        { // Sides
                            faceX = blockTexCoords.at(0).x;
                            faceY = blockTexCoords.at(0).y;
                        }
                        else if (face_temp == 4)
                        { // Top
                            faceX = blockTexCoords.at(1).x;
                            faceY = blockTexCoords.at(1).y;
                        }
                        else
                        { // Bottom
                            faceX = blockTexCoords.at(2).x;
                            faceY = blockTexCoords.at(2).y;
                        }
                    }
                    else
                    {
                        faceX = blockTexCoords.at(0).x; // Use the only available texture coordinate
                        faceY = blockTexCoords.at(0).y;
                    }

                    // Calculate UV offsets
                    float temp_x = faceX * tex_x_offset;
                    float temp_y = faceY * tex_y_offset;

                    // Add vertices for the face
                    for (int vert = 0; vert < 4; vert++)
                    {
                        Vertex v = vertices[face_temp * 4 + vert]; // Copy the vertex
                        v.position += glm::vec3(i, j, k);          // Adjust position based on block
                        switch (vert)
                        {
                        case 0:
                            v.texUV = glm::vec2(temp_x, temp_y + tex_y_offset);
                            break;
                        case 1:
                            v.texUV = glm::vec2(temp_x + tex_x_offset, temp_y + tex_y_offset);
                            break;
                        case 2:
                            v.texUV = glm::vec2(temp_x + tex_x_offset, temp_y);
                            break;
                        case 3:
                            v.texUV = glm::vec2(temp_x, temp_y);
                            break;
                        }
                        vertices_temp.push_back(v);
                    }

                    indices_temp.push_back(count);
                    indices_temp.push_back(count + 1);
                    indices_temp.push_back(count + 2);
                    indices_temp.push_back(count);
                    indices_temp.push_back(count + 2);
                    indices_temp.push_back(count + 3);
                    count += 4;
                }
            }
        }
    }

    return new Mesh(vertices_temp, indices_temp, textures_temp);
}

float Chunk::perlinNoise(float x, float z, float frequency, float amplitude)
{
    return amplitude * std::sin(frequency * x) * std::cos(frequency * z);
}

std::vector<FACES> Chunk::checkNeighbours(int i, int j, int k,
    BLOCKS*** leftChunk, BLOCKS*** rightChunk,
    BLOCKS*** frontChunk, BLOCKS*** backChunk)
{
    std::vector<FACES> visibleFaces;

    // Check within the current chunk
    if (i > 0 && block_data[i - 1][j][k] == AIR)
        visibleFaces.push_back(FACES::LEFT);
    if (i < chunk_size - 1 && block_data[i + 1][j][k] == AIR)
        visibleFaces.push_back(FACES::RIGHT);
    if (j > 0 && block_data[i][j - 1][k] == AIR)
        visibleFaces.push_back(FACES::BOTTOM);
    if (j < chunk_size - 1 && block_data[i][j + 1][k] == AIR)
        visibleFaces.push_back(FACES::TOP);
    if (k > 0 && block_data[i][j][k - 1] == AIR)
        visibleFaces.push_back(FACES::BACK);
    if (k < chunk_size - 1 && block_data[i][j][k + 1] == AIR)
        visibleFaces.push_back(FACES::FRONT);

    // Check boundaries and neighbors
    if (i == 0 && (!leftChunk || leftChunk[chunk_size - 1][j][k] == AIR))
        visibleFaces.push_back(FACES::LEFT);
    if (i == chunk_size - 1 && (!rightChunk || rightChunk[0][j][k] == AIR))
        visibleFaces.push_back(FACES::RIGHT);
    if (k == 0 && (!backChunk || backChunk[i][j][chunk_size - 1] == AIR))
        visibleFaces.push_back(FACES::BACK);
    if (k == chunk_size - 1 && (!frontChunk || frontChunk[i][j][0] == AIR))
        visibleFaces.push_back(FACES::FRONT);

    // Handle top and bottom boundaries explicitly
    if (j == chunk_size - 1)
        visibleFaces.push_back(FACES::TOP); // Always render the top face if at the top boundary
    if (j == 0)
        visibleFaces.push_back(FACES::BOTTOM); // Always render the bottom face if at the bottom boundary

    return visibleFaces;
};

const std::vector<glm::vec2> &Chunk::texCoordinates(BLOCKS block)
{
    return blockTexCoords.at(block);
}

void Chunk::Draw(Shader &shader, Camera &camera)
{
    GLint modelLoc = glGetUniformLocation(shader.ID, "model");

    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, glm::vec3(position.x * 16, 0.0f, position.y * 16));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(objectModel));
    if (self)
    {
        self->Draw(shader, camera);
    }
}

BLOCKS ***Chunk::createChunk()
{
    BLOCKS ***temp = new BLOCKS **[chunk_size];
    for (int i = 0; i < chunk_size; i++)
    {
        temp[i] = new BLOCKS *[world_height];
        for (int j = 0; j < world_height; j++)
        {
            temp[i][j] = new BLOCKS[chunk_size];
        }
    }
    return temp;
}

void Chunk::unloadChunk()
{
    if (!block_data)
        return;

    for (int i = 0; i < chunk_size; i++)
    {
        for (int j = 0; j < world_height; j++)
        {
            if (block_data[i][j])
            {
                delete[] block_data[i][j];
                block_data[i][j] = nullptr;
            }
        }
        if (block_data[i])
        {
            delete[] block_data[i];
            block_data[i] = nullptr;
        }
    }
    delete[] block_data;
    block_data = nullptr; // Prevent dangling pointers at the top level
}

void Chunk::updateChunk(std::unordered_map<std::pair<int, int>, Chunk*, HashFunction>& chunks) {
    // Update neighbor references
    for (auto& [key, chunk] : chunks) {
        chunk->checkNeighbourChunks(chunks);
    }
    self = toGenerateMesh(
        leftChunk ? leftChunk->block_data : nullptr,
        rightChunk ? rightChunk->block_data : nullptr,
        frontChunk ? frontChunk->block_data : nullptr,
        backChunk ? backChunk->block_data : nullptr);
}

void Chunk::updateChunk(Chunk *chunks) {
    self = toGenerateMesh(
        leftChunk ? leftChunk->block_data : nullptr,
        rightChunk ? rightChunk->block_data : nullptr,
        frontChunk ? frontChunk->block_data : nullptr,
        backChunk ? backChunk->block_data : nullptr);
}


// void Chunk::updateChunk(std::vector<Chunk *> &chunks)
// {
//     if (!loadChunk())
//     {
//         generateChunk(0.1f, 10.0f);
//         saveChunk();
//     }
//     checkNeighbourChunks(chunks);
    // self = toGenerateMesh(
    //     leftChunk ? leftChunk->block_data : nullptr,
    //     rightChunk ? rightChunk->block_data : nullptr,
    //     frontChunk ? frontChunk->block_data : nullptr,
    //     backChunk ? backChunk->block_data : nullptr);
// }

void Chunk::checkNeighbourChunks(std::unordered_map<std::pair<int, int>, Chunk*, HashFunction>& chunks) {
    int x = static_cast<int>(position.x);
    int z = static_cast<int>(position.y);

    leftChunk = (chunks.find({x - 1, z}) != chunks.end()) ? chunks[{x - 1, z}] : nullptr;
    rightChunk = (chunks.find({x + 1, z}) != chunks.end()) ? chunks[{x + 1, z}] : nullptr;
    frontChunk = (chunks.find({x, z + 1}) != chunks.end()) ? chunks[{x, z + 1}] : nullptr;
    backChunk = (chunks.find({x, z - 1}) != chunks.end()) ? chunks[{x, z - 1}] : nullptr;
}

void Chunk::checkNeighbourChunks(std::vector<Chunk *> &chunks)
{
    for (Chunk *chunk : chunks)
    {
        if (position + glm::vec2(1.0f, 0.0f) == chunk->position)
            setChunk(chunk, RIGHT);
        else if (position + glm::vec2(-1.0f, 0.0f) == chunk->position)
            setChunk(chunk, LEFT);
        else if (position + glm::vec2(0.0f, 1.0f) == chunk->position)
            setChunk(chunk, FRONT);
        else if (position + glm::vec2(0.0f, -1.0f) == chunk->position)
            setChunk(chunk, BACK);
    }
}

// void Chunk::updateChunk(Chunk** chunks) {
//     if (!loadChunk()) {
//         generateChunk(0.1f, 10.0f);
//         // saveChunk();
//     }
//     checkNeighbourChunks(chunks);
//     self = toGenerateMesh(
//         leftChunk ? leftChunk->block_data : nullptr,
//         rightChunk ? rightChunk->block_data : nullptr,
//         frontChunk ? frontChunk->block_data : nullptr,
//         backChunk ? backChunk->block_data : nullptr
//     );
// }

// void Chunk::checkNeighbourChunks(Chunk** chunks) {
//     for (int i = 0; i < totalChunks; i++) {
//         if (position + glm::vec2(1.0f, 0.0f) == chunks[i]->position) setChunk(chunks[i], RIGHT);
//         if (position + glm::vec2(-1.0f, 0.0f) == chunks[i]->position) setChunk(chunks[i], LEFT);
//         if (position + glm::vec2(0.0f, 1.0f) == chunks[i]->position) setChunk(chunks[i], FRONT);
//         if (position + glm::vec2(0.0f, -1.0f) == chunks[i]->position) setChunk(chunks[i], BACK);
//     }
// }

void Chunk::setChunk(Chunk *chunk, FACES faces)
{
    switch (faces)
    {
    case FRONT:
        frontChunk = chunk;
        break;
    case LEFT:
        leftChunk = chunk;
        break;
    case BACK:
        backChunk = chunk;
        break;
    case RIGHT:
        rightChunk = chunk;
        break;
    }
}

void Chunk::saveChunk()
{
    // Create a unique filename based on chunk position
    const std::string filename = "chunk_" + std::to_string(static_cast<int>(position.x)) + "_" + std::to_string(static_cast<int>(position.y)) + ".dat";

    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile)
    {
        // std::cerr << "Error opening file for writing.\n";
        return;
    }

    // Iterate through the 3D array and write each block to the file
    for (int x = 0; x < chunk_size; ++x)
    {
        for (int y = 0; y < world_height; ++y)
        {
            for (int z = 0; z < chunk_size; ++z)
            {
                outFile.write(reinterpret_cast<char *>(&block_data[x][y][z]), sizeof(BLOCKS));
            }
        }
    }
    outFile.close();
    // std::cout << "Chunk saved to " << filename << "\n";
}

bool Chunk::loadChunk()
{
    const std::string filename = "chunk_" + std::to_string(static_cast<int>(position.x)) + "_" + std::to_string(static_cast<int>(position.y)) + ".dat";

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        // std::cerr << "Error opening file for reading: " << filename << "\n";
        return false;
    }

    if (block_data == nullptr) {
        // std::cerr << "Error: block_data not allocated.\n";
        return false;
    }

    for (int x = 0; x < chunk_size; ++x) {
        for (int y = 0; y < world_height; ++y) {
            for (int z = 0; z < chunk_size; ++z) {
                inFile.read(reinterpret_cast<char *>(&block_data[x][y][z]), sizeof(BLOCKS));
                if (!inFile) {
                    // std::cerr << "Error reading chunk data from file at (" << x << ", " << y << ", " << z << ")\n";
                    return false;
                }
            }
        }
    }

    inFile.close();
    // std::cout << "Chunk loaded from " << filename << "\n";
    return true;
}

void Chunk::update()
{
    if (!loadChunk())
    {
        generateChunk(0.1f, 10.0f);
        saveChunk();
    }
    self = toGenerateMesh(nullptr, nullptr, nullptr, nullptr);
}