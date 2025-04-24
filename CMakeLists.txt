cmake_minimum_required(VERSION 3.10)

project(PseudorangeMultilaterationApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Eigen
find_package(Eigen3 REQUIRED)
if(NOT Eigen3_FOUND)
    message(FATAL_ERROR "Eigen3 not found. Please install it using your package manager.\n"
                        "For Ubuntu: sudo apt install libeigen3-dev\n"
                        "For Windows: Download from https://gitlab.com/libeigen/eigen/-/releases")
endif()

# Find LAPACK
find_package(LAPACK REQUIRED)
if(NOT LAPACK_FOUND)
    message(FATAL_ERROR "LAPACK not found. Please install it using your package manager.\n"
                        "For Ubuntu: sudo apt install liblapack-dev\n"
                        "For Windows: Install via vcpkg or download from netlib.org")
endif()

# Find BLAS
find_package(BLAS REQUIRED)
if(NOT BLAS_FOUND)
    message(FATAL_ERROR "BLAS not found. Please install it using your package manager.\n"
                        "For Ubuntu: sudo apt install libblas-dev\n"
                        "For Windows: Install via vcpkg or download from netlib.org")
endif()

# Include directories
include_directories(utils inc ${EIGEN3_INCLUDE_DIR})

# Add the library
add_executable(PseudorangeMultilateration
    src/BancroftSolver.cpp
    src/BeckSolver.cpp
    src/GradSolver.cpp
    src/LinearSolver.cpp
    src/LinearSolver_mul2.cpp
    src/LSQSolver.cpp
    src/RtkLibSolver.cpp
    src/SimpleSolver.cpp
    src/SimpleSolver_mul2.cpp
    src/ZhilSolver.cpp
    src/Vector3D.cpp
    src/common.cpp
    src/basics.cpp
    app/main.cpp
)

# Link the library to the executable
target_link_libraries(PseudorangeMultilateration Eigen3::Eigen)
target_link_libraries(PseudorangeMultilateration ${LAPACK_LIBRARIES} ${BLAS_LIBRARIES})

# Installation rules
install(TARGETS PseudorangeMultilateration DESTINATION bin)

# Specify the installation directory for the project
install(DIRECTORY include/ DESTINATION include)
