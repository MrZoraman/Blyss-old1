# --------------------------------------------------------- #
# GLFW                                                      #
# --------------------------------------------------------- #
set(GLFW_BUILD_DOCS off CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES off CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS off CACHE BOOL "" FORCE)
set(GLFW_INSTALL off CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG off CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC off CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

# --------------------------------------------------------- #
# Glad                                                      #
# --------------------------------------------------------- #
add_library(Glad lib/glad/src/glad.c lib/glad/include/glad/glad.h lib/glad/include/KHR/khrplatform.h)
target_include_directories(Glad PUBLIC lib/glad/include)

# --------------------------------------------------------- #
# Boost                                                     #
# --------------------------------------------------------- #
SET(Boost_USE_STATIC_LIBS ON CACHE BOOL "" FORCE)  
SET(Boost_USE_MULTITHREADED ON CACHE BOOL "" FORCE)
if (MSVC)
  SET(BOOST_ROOT "changeme" CACHE PATH "Boost root directory")
endif()
find_package(Boost 1.71.0 COMPONENTS log REQUIRED)

# --------------------------------------------------------- #
# Dear Imgui                                                #
# --------------------------------------------------------- #
SET(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui)
add_library(Imgui 
  ${IMGUI_DIR}/imconfig.h
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui.h
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_internal.h
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/imstb_rectpack.h
  ${IMGUI_DIR}/imstb_textedit.h
  ${IMGUI_DIR}/imstb_truetype.h
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.h
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.h)
target_include_directories(Imgui PUBLIC
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends
)
target_link_libraries(Imgui
  glfw
  Glad
)

# --------------------------------------------------------- #
# Assimp                                                    #
# --------------------------------------------------------- #
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(IGNORE_GIT_HASH ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
add_subdirectory(lib/assimp)

# --------------------------------------------------------- #
# Glm                                                       #
# --------------------------------------------------------- #
add_subdirectory(lib/glm)

# --------------------------------------------------------- #
# GSL                                                       #
# --------------------------------------------------------- #
set(GSL_CXX_STANDARD 17 CACHE STRING "" FORCE)
add_subdirectory(lib/gsl)

# --------------------------------------------------------- #
# LibUV                                                     #
# --------------------------------------------------------- #
add_subdirectory(lib/libuv)
