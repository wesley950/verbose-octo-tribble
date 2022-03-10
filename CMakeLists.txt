cmake_minimum_required(VERSION 3.16)
project(editor)
set(CMAKE_CXX_STANDARD 17)

# finds the files for the project
file(GLOB CORE_SRC "src/core/*.hpp" "src/core/*.cpp")
file(GLOB SCENE_SRC "src/scene/*.hpp" "src/scene/*.cpp")
file(GLOB EDITOR_SRC "src/editor/*.hpp" "src/editor/*.cpp")
file(GLOB GLFW_PLATFORM_SRC "src/platform/glfw/*.hpp" "src/platform/glfw/*.cpp")

# creates the editor executable
add_executable(editor 
                ${CORE_SRC}
                ${SCENE_SRC}
                
                ${EDITOR_SRC}
                
                
                ${GLFW_PLATFORM_SRC})

# vcpkg-provided packages
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(editor PRIVATE glfw imgui::imgui GLEW::GLEW
                                        
                                        EnTT::EnTT
                                        glm::glm)

if(IS_LINUX_BUILD EQUAL "ON")
target_link_libraries(editor dl)
endif()

# include directories
target_include_directories(editor PUBLIC 
                            src/)
