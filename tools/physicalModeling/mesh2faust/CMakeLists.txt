cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O2")

project(mesh2faust VERSION 1.0.0)

# Enable/disable building the `mesh2faust` executable. Defaults to ON.
# (Disable to only build the static library.)
option(INCLUDE_EXECUTABLE "Build the mesh2faust executable" ON)

set(VegaDir ${CMAKE_CURRENT_SOURCE_DIR}/vega/libraries)

set(LIBRARY_NAME ${PROJECT_NAME})

add_library(${LIBRARY_NAME} STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mesh2faust.cpp
  ${VegaDir}/objMesh/objMesh.cpp
  ${VegaDir}/objMesh/objMesh-disjointSet.cpp
  ${VegaDir}/objMesh/objMeshOctree.cpp
  ${VegaDir}/objMesh/objMeshOrientable.cpp
  ${VegaDir}/objMesh/boundingBox.cpp
  ${VegaDir}/objMesh/triangle.cpp
  ${VegaDir}/objMesh/tribox3.cpp
  ${VegaDir}/objMesh/octree.cpp
  ${VegaDir}/objMesh/simpleSphere.cpp
  ${VegaDir}/volumetricMesh/volumetricMesh.cpp
  ${VegaDir}/volumetricMesh/volumetricMeshParser.cpp
  ${VegaDir}/volumetricMesh/volumetricMeshENuMaterial.cpp
  ${VegaDir}/volumetricMesh/volumetricMeshOrthotropicMaterial.cpp
  ${VegaDir}/volumetricMesh/volumetricMeshMooneyRivlinMaterial.cpp
  ${VegaDir}/volumetricMesh/cubicMesh.cpp
  ${VegaDir}/volumetricMesh/tetMesh.cpp
  ${VegaDir}/volumetricMesh/generateMassMatrix.cpp
  ${VegaDir}/mesher/tetMesher.cpp
  ${VegaDir}/mesher/delaunayMesher.cpp
  ${VegaDir}/mesher/triangleTetIntersection.cpp
  ${VegaDir}/sparseMatrix/sparseMatrix.cpp
  ${VegaDir}/stvk/StVKElementABCD.cpp
  ${VegaDir}/stvk/StVKElementABCDLoader.cpp
  ${VegaDir}/stvk/StVKCubeABCD.cpp
  ${VegaDir}/stvk/StVKTetABCD.cpp
  ${VegaDir}/stvk/StVKTetHighMemoryABCD.cpp
  ${VegaDir}/stvk/StVKInternalForces.cpp
  ${VegaDir}/stvk/StVKStiffnessMatrix.cpp
  ${VegaDir}/wildMagic/rational/integer.cpp
  ${VegaDir}/wildMagic/rational/rational.cpp
  ${VegaDir}/windingNumber/windingNumber.cpp
  ${VegaDir}/wildMagic/geometryQuery/verticesQuery.cpp
  ${VegaDir}/wildMagic/geometryQuery/verticesQueryFiltered.cpp
  ${VegaDir}/wildMagic/geometryQuery/verticesQueryRational.cpp
  ${VegaDir}/wildMagic/meshKey/tetKey.cpp
  ${VegaDir}/wildMagic/meshKey/triKey.cpp
)

set_target_properties(${LIBRARY_NAME} PROPERTIES CXX_STANDARD 14)

target_include_directories(${LIBRARY_NAME} PUBLIC src vega/libraries/include spectra/include)
if(APPLE)
  target_include_directories(${LIBRARY_NAME} PRIVATE /opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3)
else()
  target_include_directories(${LIBRARY_NAME} PRIVATE /usr/include/eigen3)
endif()

find_package(OpenGL REQUIRED)
target_link_libraries(${LIBRARY_NAME} PRIVATE OpenGL::GL)
if(APPLE)
  target_link_libraries(${LIBRARY_NAME} PRIVATE "-framework Accelerate")
endif()

# Conditionally add the executable target.
if(INCLUDE_EXECUTABLE)
  add_executable(${PROJECT_NAME}-bin ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

  # Link static library to the executable.
  target_link_libraries(${PROJECT_NAME}-bin PRIVATE ${LIBRARY_NAME})
  # Remove the "-bin" suffix from the executable's name. (Only added to avoid name clash with the library.)
  set_target_properties(${PROJECT_NAME}-bin PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
endif()
