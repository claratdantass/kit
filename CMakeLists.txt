cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(TSP_Construcao VERSION 1.0 LANGUAGES CXX)

# Definir padrão do compilador como C++11 ou superior
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Diretório de origem
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Arquivos fonte e cabeçalhos
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Construcao.cpp
    ${SRC_DIR}/Data.cpp
)

set(HEADERS
    ${SRC_DIR}/Construcao.h
    ${SRC_DIR}/Data.h
)

# Adicionar executável
add_executable(tsp ${SOURCES} ${HEADERS})

# Opções de compilação
target_include_directories(tsp PRIVATE ${SRC_DIR})
