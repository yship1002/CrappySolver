cmake_minimum_required(VERSION 3.16)
project(CRAPPYSOLVER LANGUAGES CXX)

# ---- Compiler / flags (match your g++ line) ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -O0 -g -w
add_compile_options(-w -g)

# ---- Paths (edit if needed) ----
set(PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(CPLEX_ROOT ${CPLEX_ROOT_DIR})  # e.g., /opt/ibm/ILOG/CPLEX_Studio2210
set(GUROBI_ROOT ${GUROBI_ROOT_DIR}) # e.g., /opt/gurobi/gurobi2210/linux64
set(GUROBI_INC "${GUROBI_ROOT}/include")
set(GUROBI_LIB "${GUROBI_ROOT}/lib")
set(CPLEX_INC_CONCERT "${CPLEX_ROOT}/concert/include")
set(CPLEX_INC_CPLEX   "${CPLEX_ROOT}/cplex/include")
set(IS_ARM64_OSX ${IS_ARM64_OSX})
if (IS_ARM64_OSX)
    message(STATUS "This CMakeLists.txt is configured for arm64_osx builds.")
    set(CPLEX_LIB_CONCERT "${CPLEX_ROOT}/concert/lib/arm64_osx/static_pic")
    set(CPLEX_LIB_CPLEX   "${CPLEX_ROOT}/cplex/lib/arm64_osx/static_pic")

else()
    message(STATUS "This CMakeLists.txt is configured for x86-64_linux builds.")
    set(CPLEX_LIB_CONCERT "${CPLEX_ROOT}/concert/lib/x86-64_linux/static_pic")
    set(CPLEX_LIB_CPLEX   "${CPLEX_ROOT}/cplex/lib/x86-64_linux/static_pic")
endif()

# ---- Sources (test.cpp + BB/*.cpp) ----
file(GLOB src_SOURCES
    "${PROJ_ROOT}/src/*.cpp"
)
file(GLOB EXAMPLE_SOURCES
    "${PROJ_ROOT}/example/*.cpp"
)

add_executable(test
    "${PROJ_ROOT}/happy.cpp"
    ${src_SOURCES}
    ${EXAMPLE_SOURCES}
)

# ---- Include directories (match your -I list) ----
target_include_directories(test PRIVATE
    "${PROJ_ROOT}"
    "${PROJ_ROOT}/cereal/include"
    "${PROJ_ROOT}/mcpp/src/3rdparty/fadbad++"
    "${CPLEX_INC_CONCERT}"
    "${CPLEX_INC_CPLEX}"
    "${GUROBI_INC}"
)

# ---- Library search paths (match your -L list) ----
target_link_directories(test PRIVATE
    "${CPLEX_LIB_CONCERT}"
    "${CPLEX_LIB_CPLEX}"
    "${GUROBI_LIB}"
)

# ---- Link libs (match your -l list) ----
target_link_libraries(test PRIVATE
    ilocplex
    concert
    cplex
    m
    pthread
    gurobi_c++
    gurobi130
)

# Optional: if your cluster needs it for static_pic objects
# target_link_options(test PRIVATE -Wl,--no-as-needed)
