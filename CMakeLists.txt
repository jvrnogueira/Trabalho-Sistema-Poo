cmake_minimum_required(VERSION 3.14)
project(Trabalho-Sistema-Poo)

# Exigência do TP3: C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- DEPENDÊNCIA: JSON (Q4) ---
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# --- EXECUTÁVEL PRINCIPAL ---
add_executable(MeuPrograma src/main.cpp)
target_link_libraries(MeuPrograma PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(MeuPrograma PRIVATE src)

# ==========================================
# Q5: TESTES AUTOMATIZADOS COM CATCH2 (+1,0 pt)
# ==========================================
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(testes tests/test_tp3.cpp)
target_include_directories(testes PRIVATE src)
target_link_libraries(testes PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

include(CTest)
include(Catch)
catch_discover_tests(testes)

# ==========================================
# Q6: INTERFACE GRÁFICA COM QT (+2,0 pts)
# ==========================================
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(gui src/gui_main.cpp)
target_include_directories(gui PRIVATE src)
target_link_libraries(gui PRIVATE Qt6::Widgets nlohmann_json::nlohmann_json)
