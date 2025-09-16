cmake_minimum_required(VERSION 3.8)
project(Minecraft)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

# Collect source files
file(GLOB SOURCES src/*.cpp src/*.c) # Include C and C++ files

add_executable(Minecraft ${SOURCES})

target_include_directories(Minecraft PRIVATE 
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_SOURCE_DIR}/shaders
)

# Include and link directories
target_include_directories(Minecraft PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies)
target_link_directories(Minecraft PRIVATE ${CMAKE_SOURCE_DIR}/lib)

find_package(OpenGL REQUIRED)

target_link_libraries(Minecraft PRIVATE OpenGL::GL)

# Platform-specific GLFW linking
if (WIN32)
    target_include_directories(Minecraft PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/GLFW)
    target_link_directories(Minecraft PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/GLFW)
    target_link_libraries(Minecraft PRIVATE glfw3 opengl32)
elseif (UNIX AND NOT APPLE)
    find_package(glfw3 REQUIRED PATHS /usr/lib/x86_64-linux-gnu/cmake/glfw3)
    target_include_directories(Minecraft PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/GLFW)
    target_link_libraries(Minecraft PRIVATE glfw GL X11 Xrandr Xinerama Xxf86vm Xi Xcursor dl pthread)
endif()

add_compile_options(-Wa,--noexecstack)

# Set C++ standard
target_compile_features(Minecraft PRIVATE cxx_std_20)

# Optionally, install the executable
install(TARGETS Minecraft DESTINATION bin)
