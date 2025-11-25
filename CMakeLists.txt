cmake_minimum_required(VERSION 3.15)
project(GLFW_Tie_Fighter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adicione os diretórios de include
include_directories(include)

# Encontre as bibliotecas necessárias
find_package(OpenGL REQUIRED)

# GLFW
find_package(glfw3 CONFIG)
if(NOT glfw3_FOUND)
    message(STATUS "GLFW não encontrado via find_package, tentando via vcpkg ou paths manuais")
endif()

# GLEW
find_package(GLEW CONFIG)
if(NOT GLEW_FOUND)
    message(STATUS "GLEW não encontrado via find_package, tentando via vcpkg ou paths manuais")
endif()

# GLM
find_package(glm CONFIG)
if(NOT glm_FOUND)
    message(STATUS "GLM não encontrado via find_package, tentando via vcpkg ou paths manuais")
endif()

# Arquivos fonte
set(SOURCES
    main.cpp
    src/Application.cpp
    src/Cube.cpp
    src/Cylinder.cpp
    src/Hexagon.cpp
    src/HexagonalPrism.cpp
    src/Mesh.cpp
    src/Plate.cpp
    src/Skybox.cpp
    src/Sphere.cpp
    src/stb_image.cpp
    src/Texture.cpp
    src/TieFighter.cpp
    src/TieWing.cpp
    src/XWing.cpp
    src/XWingClosed.cpp
)

# Arquivos header
set(HEADERS
    include/Application.h
    include/Cube.h
    include/Cylinder.h
    include/Hexagon.h
    include/HexagonalPrism.h
    include/HexPrism.h
    include/Mesh.h
    include/Object.h
    include/Plate.h
    include/Shader.h
    include/Skybox.h
    include/Sphere.h
    include/stb_image.h
    include/stb_image_write.h
    include/Texture.h
    include/TieFighter.h
    include/TieWing.h
    include/XWing.h
    include/XWingClosed.h
)

# Criar o executável
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Linkar as bibliotecas
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
)

# Linkar GLFW
if(glfw3_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)
endif()

# Linkar GLEW
if(GLEW_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glew32)
endif()

# GLM é header-only, não precisa linkar
if(glm_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
endif()

# Copiar shaders e recursos para o diretório de build
file(GLOB SHADER_FILES "*.glsl")
foreach(SHADER ${SHADER_FILES})
    configure_file(${SHADER} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

# Copiar pasta de imagens se existir
if(EXISTS ${CMAKE_SOURCE_DIR}/imagens)
    file(COPY ${CMAKE_SOURCE_DIR}/imagens DESTINATION ${CMAKE_BINARY_DIR})
endif()
