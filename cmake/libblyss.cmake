# --------------------------------------------------------- #
# Variables                                                 #
# --------------------------------------------------------- #
set(LIBBLYSS_ARTIFACT_NAME libblyss)
set(LIBBLYSS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBBLYSS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBBLYSS_SOURCES "")
set(LIBBLYSS_HEADERS "")

# --------------------------------------------------------- #
# Macros                                                    #
# --------------------------------------------------------- #
macro(libblyss_add_source SOURCE_NAME)
    list(APPEND LIBBLYSS_SOURCES ${LIBBLYSS_SRC_DIR}/${SOURCE_NAME}.cpp)
    list(APPEND LIBBLYSS_HEADERS ${LIBBLYSS_INCLUDE_DIR}/${SOURCE_NAME}.hpp)
endmacro()

macro(libblyss_add_header HEADER_NAME)
    list(APPEND LIBBLYSS_HEADERS ${LIBBLYSS_INCLUDE_DIR}/${HEADER_NAME}.hpp)
endmacro()

# --------------------------------------------------------- #
# Sources                                                   #
# --------------------------------------------------------- #
libblyss_add_source(Rectangle)
libblyss_add_source(GLFWContext)
libblyss_add_source(exceptions/GLFWException)
libblyss_add_source(exceptions/OpenGLException)
libblyss_add_source(wrappers/glfw/BGlfwWindowW)

# --------------------------------------------------------- #
# Visual Studio Folder Hierarchy                            #
# --------------------------------------------------------- #
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
         PREFIX "sources"
         FILES ${LIBBLYSS_SOURCES} ${LIBBLYSS_HEADERS})

# --------------------------------------------------------- #
# Create Library                                            #
# --------------------------------------------------------- #
add_library(${LIBBLYSS_ARTIFACT_NAME} ${LIBBLYSS_SOURCES} ${LIBBLYSS_HEADERS})

# --------------------------------------------------------- #
# C17 standard                                              #
# --------------------------------------------------------- #
set_property(TARGET ${LIBBLYSS_ARTIFACT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${LIBBLYSS_ARTIFACT_NAME} PROPERTY Cxx_STANDARD_REQUIRED ON)

# --------------------------------------------------------- #
# Set compile options                                       #
# --------------------------------------------------------- #
if(MSVC)
    target_compile_options(${LIBBLYSS_ARTIFACT_NAME} PRIVATE /W4)
else()
    target_compile_options(${LIBBLYSS_ARTIFACT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# --------------------------------------------------------- #
# Includes                                                  #
# --------------------------------------------------------- #
target_include_directories(${LIBBLYSS_ARTIFACT_NAME} PUBLIC
    ${LIBBLYSS_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

# --------------------------------------------------------- #
# Link Libraries                                            #
# --------------------------------------------------------- #
target_link_libraries(${LIBBLYSS_ARTIFACT_NAME}
    ${Boost_LIBRARIES}
    glfw
    Glad
    Imgui
)