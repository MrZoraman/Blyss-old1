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
# log.c                                                     #
# --------------------------------------------------------- #
add_library(log.c lib/log.c/src/log.c lib/log.c/src/log.h)
target_include_directories(log.c PUBLIC lib/log.c/src)
add_compile_definitions(LOG_USE_COLOR)