# --------------------------------------------------------- #
# Variables                                                 #
# --------------------------------------------------------- #
set(BLYSS_ARTIFACT_NAME BLYSS)
set(BLYSS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BLYSS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BLYSS_SOURCES "${BLYSS_SRC_DIR}/main.cpp")
set(BLYSS_HEADERS "")

# --------------------------------------------------------- #
# Macros                                                    #
# --------------------------------------------------------- #
macro(blyss_add_source SOURCE_NAME)
    list(APPEND BLYSS_SOURCES ${BLYSS_SRC_DIR}/${SOURCE_NAME}.cpp)
    list(APPEND BLYSS_HEADERS ${BLYSS_INCLUDE_DIR}/${SOURCE_NAME}.hpp)
endmacro()

macro(blyss_add_header HEADER_NAME)
    list(APPEND BLYSS_HEADERS ${BLYSS_INCLUDE_DIR}/${HEADER_NAME}.hpp)
endmacro()

# --------------------------------------------------------- #
# Sources                                                   #
# --------------------------------------------------------- #
blyss_add_source(core/App)
blyss_add_header(core/IAppFrontend)
blyss_add_header(core/IGameClient)
blyss_add_header(core/IGameHost)
blyss_add_source(core/DeltaTimer)
blyss_add_source(host/local/LocalGameHost)
blyss_add_source(client/local/LocalGameClient)
blyss_add_header(client/local/GladGLFW)
blyss_add_source(client/local/OpenGLException)
blyss_add_source(client/local/GLFWException)
blyss_add_source(core/Logging)

# --------------------------------------------------------- #
# Visual Studio Folder Hierarchy                            #
# --------------------------------------------------------- #
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
         PREFIX "sources"
         FILES ${BLYSS_SOURCES} ${BLYSS_HEADERS})

# --------------------------------------------------------- #
# Create Library                                            #
# --------------------------------------------------------- #
add_executable(${BLYSS_ARTIFACT_NAME} ${BLYSS_SOURCES} ${BLYSS_HEADERS})

# --------------------------------------------------------- #
# C17 standard                                              #
# --------------------------------------------------------- #
set_property(TARGET ${BLYSS_ARTIFACT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${BLYSS_ARTIFACT_NAME} PROPERTY Cxx_STANDARD_REQUIRED ON)

# --------------------------------------------------------- #
# Set compile options                                       #
# --------------------------------------------------------- #
if(MSVC)
    target_compile_options(${BLYSS_ARTIFACT_NAME} PRIVATE /W4)
else()
    target_compile_options(${BLYSS_ARTIFACT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# --------------------------------------------------------- #
# Includes                                                  #
# --------------------------------------------------------- #
target_include_directories(${BLYSS_ARTIFACT_NAME} PUBLIC
    ${BLYSS_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    lib/gsl/include
    lib/assimp/contrib/irrXML
)

# --------------------------------------------------------- #
# Link Libraries                                            #
# --------------------------------------------------------- #
target_link_libraries(${BLYSS_ARTIFACT_NAME}
    ${Boost_LIBRARIES}
    glfw
    Glad
    Imgui
    assimp::assimp
    glm
    IrrXML
    uv_a
)