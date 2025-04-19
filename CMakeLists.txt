cmake_minimum_required(VERSION 3.10)

project(PseudorangeMultilaterationApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Eigen
find_package(Eigen3 REQUIRED)
find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)

# Include directories
include_directories(utils inc ${EIGEN3_INCLUDE_DIR})

# Add the library
add_executable(PseudorangeMultilateration
    src/BancroftSolver.cpp
    src/BeckSolver.cpp
    src/LinearSolver.cpp
    src/LSQSolver.cpp
    src/RtkLibSolver.cpp
    src/SimpleSolver.cpp
    src/ZhilSolver.cpp
    src/Vector3D.cpp
    
    src/common.cpp
    src/basics.cpp
    test/main.cpp
    )

# Link the library to the executable
target_link_libraries(PseudorangeMultilateration Eigen3::Eigen)
target_link_libraries(PseudorangeMultilateration ${LAPACK_LIBRARIES} ${BLAS_LIBRARIES})
