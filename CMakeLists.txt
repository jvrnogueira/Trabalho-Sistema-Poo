cmake_minimum_required(VERSION 3.14)

# Nome do projeto
project(Trabalho-Sistema-Poo)

# Define padrão do C++ (Exigência do TP3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona a biblioteca nlohmann/json para serialização 
include(FetchContent)
FetchContent_Declare(json
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Arquivos fonte
add_executable(MeuPrograma
    src/main.cpp
)

# Linka a biblioteca JSON
target_link_libraries(MeuPrograma PRIVATE nlohmann_json::nlohmann_json)
