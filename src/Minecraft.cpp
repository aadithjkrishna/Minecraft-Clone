#include "Minecraft.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

const float length = 1.0f;

static std::string getProjectDirectory() {
	// Go to the parent directory of the executable's current path
	std::filesystem::path projectDir = std::filesystem::current_path().parent_path().parent_path();
	return projectDir.parent_path().string();  // Parent of the executable's directory
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	if (camera) {
		camera->width = width;
		camera->height = height;
		camera->updateMatrix(45.0f, 0.1f, 1000.0f);
	}
}

Vertex vertices_cube[] = {
	// Front face
	Vertex{glm::vec3(0.0f, 0.0f,  length), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length, 0.0f,  length),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length,  length,  length),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f,  length,  length), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

	// Back face
	Vertex{glm::vec3(length, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f,  length, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length,  length, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

	// Right face
	Vertex{glm::vec3(length, 0.0f,  length),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length, 0.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length,  length, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length,  length,  length),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

	// Left face
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.0f,  length), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f,  length,  length), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f,  length, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

	// Top face
	Vertex{glm::vec3(0.0f,  length,  length), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length,  length,  length),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length,  length, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f,  length, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

	// Bottom face
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length, 0.0f, 0.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(length, 0.0f,  length),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.0f,  length), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
};

GLuint indices[] = {
		0,  1,  2,      2,  3,  0, // FRONT
		4,  5,  6,		6,  7,  4, // BACK
		8,  9,  10,     10, 11, 8, // RIGHT
		12, 13, 14,     14, 15, 12,// LEFT
		16, 17, 18,     18, 19, 16,// TOP
		20, 21, 22,     22, 23, 20,// BOTTOM
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft", glfwGetPrimaryMonitor(), NULL);
	GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	gladLoadGL();
	glViewport(0, 0, width, height);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460 core");

	ImGui::StyleColorsDark();

	const std::string project_directory = getProjectDirectory();

	std::cout << "Directory:  " << project_directory << "\n";

	Texture textures[]{
		Texture((project_directory + "/resources/textures/texture_atlas.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture((project_directory + "/resources/textures/texture_atlas_specular.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Shader shader((project_directory + "/shaders/default.vs").c_str(), (project_directory + "/shaders/default.fs").c_str());
	Shader lightShader((project_directory + "/shaders/light.vs").c_str(), (project_directory + "/shaders/light.fs").c_str());

	std::vector <Vertex> verts(vertices_cube, vertices_cube + sizeof(vertices_cube) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh light(verts, ind, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 sunLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-1.0f, 20.0f, -1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform4f(glGetUniformLocation(shader.ID, "sunLightColor"), sunLightColor.x, sunLightColor.y, sunLightColor.z, sunLightColor.w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	Camera camera(width, height, glm::vec3(0.0f, 20.0f, 0.0f));
	
	glm::vec2 current_chunk = glm::vec2(camera.Position.x / 16, camera.Position.z / 16);

	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	int renderDistance = 8;
	int totalChunks = 1 + 2 * renderDistance * (renderDistance + 1);
	Chunk chunkDefault(textures, totalChunks);

	std::unordered_map<std::pair<int, int>, Chunk*, HashFunction> chunks;
	std::deque<std::pair<int, int>> chunkQueue;

	int index = 0;
	std::vector<std::pair<int, int>> chunkPositions;

	auto start = std::chrono::high_resolution_clock::now();

	//Chunk chunk(glm::vec2(0.0f, 0.0f));

	for (int y = -renderDistance; y <= renderDistance; ++y) {
		int maxX = renderDistance - std::abs(y);

		for (int x = -maxX; x <= maxX; ++x) {
			chunkQueue.push_back({ x, y });
			++index;
		}
	}
	for (auto& pos : chunkQueue) {
		if (chunks.find(pos) == chunks.end()) {
			chunks[pos] = new Chunk(glm::vec2(pos.first, pos.second));
			chunks[pos]->updateChunk(chunks);
			// chunks[pos]->generateChunk(0.1f, 10.0f);
		}
	}
	std::cout << "SIZE: " << chunks.size() * sizeof(chunks[chunkQueue[0]]) << "\n";

	if (chunks.size() > totalChunks) {
		auto it = chunks.begin();
		delete it->second;
		chunks.erase(it);
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Total Processing Time: " << std::chrono::duration<double>(end - start).count() << "s\n";

	 //chunks[0]->totalChunks = chunks.size();

	bool run = true;
	float fps = 0.0f;
	float max_fps = 0.0f;

	std::string fpsLabel = "FPS: 0";
	auto lastUpdate = std::chrono::steady_clock::now();

	int limitter = 0;

	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetWindowUserPointer(window, &camera);

	while (!glfwWindowShouldClose(window) && run) {
		glClearColor(0.7f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		int value;

		static double lastTime = 0.0f;
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		int fps = 1.0 / deltaTime;
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() >= 100) {
			fpsLabel = "FPS: " + std::to_string(fps);
			lastUpdate = now;  
		}
		ImGui::Begin("DEBUG");
		ImGui::Button(fpsLabel.c_str());
		ImGui::Text("Enter an integer:");
		ImGui::InputInt("##intInput", &value);
		ImGui::Text("Current value: %d", value);
		ImGui::End();

		lastTime = currentTime;
		if (fps > max_fps) max_fps = fps;

		bool runOnce = true;

		static int oldChunkX = camera.Position.x / 16;
		static int oldChunkZ = camera.Position.z / 16;

		float camX = camera.Position.x;
		float camZ = camera.Position.z;
		int newChunkX, newChunkZ;

		if (camX < 0) newChunkX = (camX - 16) / 16;
		else newChunkX = camX / 16;
		if (camZ < 0) newChunkZ = (camZ - 16) / 16;
		else newChunkZ = camZ / 16;

		//Chunk* currentChunk = new Chunk(glm::vec2(newChunkX, newChunkZ)); // bad
		glm::vec2 current_chunk = glm::vec2(newChunkX, newChunkZ);

		if (newChunkX != oldChunkX || newChunkZ != oldChunkZ) {
			glm::vec2 current_chunk = glm::vec2(newChunkX, newChunkZ);

			int index = 0;

			int px = static_cast<int>(current_chunk.x);
			int pz = static_cast<int>(current_chunk.y);

			//currentChunk->position = glm::vec2(px, pz);

			std::cout << "Current Chunk: " << px << ", " << pz << '\n';

            auto updateChunks = [&](int px, int pz, int renderDistance, int totalChunks, std::unordered_map<std::pair<int, int>, Chunk*, HashFunction>& chunks, std::deque<std::pair<int, int>>& chunkQueue) {
                for (int y = -renderDistance; y <= renderDistance; ++y) {
                    int maxX = renderDistance - std::abs(y);
                    for (int x = -maxX; x <= maxX; ++x) {
                        chunkQueue.push_back({ px + x, pz + y });
                    }
                }

                for (auto& pos : chunkQueue) {
                    if (chunks.find(pos) == chunks.end()) {
                        chunks[pos] = new Chunk(glm::vec2(pos.first, pos.second));
                        chunks[pos]->updateChunk(chunks);
                    }
                }

                if (chunks.size() > totalChunks) {
                    auto it = chunks.begin();
                    delete it->second;
                    chunks.erase(it);
                }
            };

            // Usage example
            updateChunks(px, pz, renderDistance, totalChunks, chunks, chunkQueue);

			oldChunkX = newChunkX;
			oldChunkZ = newChunkZ;
		}

		camera.updateMatrix(45.0f, 0.1f, 1000.0f);
		camera.Inputs(window, deltaTime);

		float t = 1.0f;

		BLOCKS block_looking_at = AIR;

		bool exitLoop = false;

		//while(t < 25.0f && !exitLoop) {
		//	glm::vec3 Resultant = camera.Position + t * camera.Orientation;
		//	int blockX = floor(Resultant.x);
		//	int blockY = floor(Resultant.y);
		//	int blockZ = floor(Resultant.z);

		//	BLOCKS CURRENT_BLOCK;

		//	if (blockX < 0 || blockY < 0 || blockZ < 0) {
		//		//std::cout << "Out of bounds\n";
		//		exitLoop = true;
		//		break;
		//	}
		//	if (blockX >= 16 || blockY >= 16 || blockZ >= 16)
		//	{
		//		//std::cout << "Out of bounds\n";
		//		CURRENT_BLOCK = AIR;
		//		exitLoop = true;
		//		break;
		//	}

		//	auto it = chunks.find({ newChunkX, newChunkZ });
		//	if (it == chunks.end() || it->second == nullptr) {
		//		exitLoop = true;
		//		break; // Chunk does not exist, avoid a crash.
		//	}

		//	auto& currentChunk = it->second;
		//	CURRENT_BLOCK = currentChunk->block_data[blockX % 16][blockY][blockZ % 16];

		//	if (CURRENT_BLOCK == AIR) 
		//		t += 0.5f;

		//	switch (CURRENT_BLOCK) {
		//	case GRASS:
		//		//std::cout << "Grass\n";
		//		currentChunk->block_data[blockX % 16][blockY][blockZ % 16] = STONE;
		//		currentChunk->updateChunk(chunks);
		//		std::cout << "GRASS: " << '\n';
		//		exitLoop = true;
		//		break;
		//	case DIRT:
		//		std::cout << "Dirt\n";
		//		exitLoop = true;
		//		break;
		//	}

		//	/*if (++limitter >= fps * 2) */{
		//		std::cout << "Camera Position: " << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << '\n';
		//		std::cout << "Camera Orientation: " << camera.Orientation.x << ", " << camera.Orientation.y << ", " << camera.Orientation.z << '\n';
		//		std::cout << "Resultant: " << Resultant.x << ", " << Resultant.y << ", " << Resultant.z << '\n';
		//		std::cout << "Resultant_Floored: " << blockX << ", " << blockY << ", " << blockZ << '\n';
		//		limitter = 0;
		//	}
		//}


		lightPos = glm::vec3(cos(glfwGetTime()) * 10.0f, 20.0f, sin(glfwGetTime()) * 10.0f);
		lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);

		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

		shader.Activate();
		glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		//currentChunk->Draw(shader, camera);
		for (auto& pair : chunks) {
			pair.second->Draw(shader, camera);
		}
		light.Draw(lightShader, camera);

		//chunk.Draw(shader, camera);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "Size of chunks: " << sizeof(chunks) * chunks.size() << '\n';
	std::cout << "FPS: " << max_fps;
	shader.Delete();
	lightShader.Delete();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}