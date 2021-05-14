# --------------------------------------------------------- #
# GLFW                                                      #
# --------------------------------------------------------- #
set(GLFW_BUILD_DOCS off)
set(GLFW_BUILD_EXAMPLES off)
set(GLFW_BUILD_TESTS off)
set(GLFW_INSTALL off)
set(GLFW_USE_HYBRID_HPG off)
set(GLFW_VULKAN_STATIC off)
add_subdirectory(lib/glfw)

# --------------------------------------------------------- #
# Glad                                                      #
# --------------------------------------------------------- #
add_library(Glad lib/glad/src/glad.c lib/glad/include/glad/glad.h lib/glad/include/KHR/khrplatform.h)
target_include_directories(Glad PUBLIC lib/glad/include)

# --------------------------------------------------------- #
# Boost                                                     #
# --------------------------------------------------------- #
SET(Boost_USE_STATIC_LIBS ON)  
SET(Boost_USE_MULTITHREADED ON)
if (MSVC)
  SET(BOOST_ROOT "changeme" CACHE PATH "Boost root directory")
endif()
find_package(Boost 1.71.0 COMPONENTS log REQUIRED)