MinecraftProject/
├── Dependencies/           # Third-party libraries
│   ├── glad/               # OpenGL loader
│   │   └── glad.h
│   ├── GLFW/               # GLFW headers
│   │   ├── glfw3.h
│   │   └── glfw3native.h
│   ├── glm/                # GLM math library (core + extensions)
│   ├── ImGui/              # Dear ImGui headers
│   ├── KHR/                # Khronos header
│   │   └── khrplatform.h
│   └── stb/                # stb_image
│       └── stb_image.h
│
├── lib/                    # Precompiled libs
│   ├── glfw3.lib
│   └── libglfw3.a
│
├── resources/              # Game assets
│   └── textures/
│       ├── grass_block.png
│       ├── grass_block_specular.png
│       ├── texture_atlas.png
│       └── texture_atlas_specular.png
│
├── shaders/                # GLSL shaders
│   ├── default.fs
│   ├── default.vs
│   ├── light.fs
│   ├── light.vs
│   └── shaderSingleColor.fs
│
└── src/                    # Main source code
    ├── BlockType.hpp
    ├── Camera.cpp / .hpp
    ├── Chunk.cpp / .hpp
    ├── EBO.cpp / .hpp
    ├── VAO.cpp / .hpp
    ├── VBO.cpp / .hpp
    ├── Mesh.cpp / .hpp
    ├── Shader.cpp / .hpp
    ├── Texture.cpp / .hpp
    ├── Minecraft.cpp / .h   # main entry & game loop
    ├── glad.c
    ├── stb_image.cpp
    ├── imgui.cpp
    ├── imgui_demo.cpp
    ├── imgui_draw.cpp
    ├── imgui_impl_glfw.cpp
    ├── imgui_impl_opengl3.cpp
    ├── imgui_tables.cpp
    └── imgui_widgets.cpp
"# Minecraft-Clone" 
