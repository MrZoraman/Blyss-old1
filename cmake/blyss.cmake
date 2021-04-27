# --------------------------------------------------------- #
# Variables                                                 #
# --------------------------------------------------------- #
set(BLYSS_ARTIFACT_NAME blyss)
set(BLYSS_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# --------------------------------------------------------- #
# Create Executable                                         #
# --------------------------------------------------------- #
add_executable(${BLYSS_ARTIFACT_NAME} ${BLYSS_MAIN})

# --------------------------------------------------------- #
# C17 standard                                              #
# --------------------------------------------------------- #
set_property(TARGET ${BLYSS_ARTIFACT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${BLYSS_ARTIFACT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

# --------------------------------------------------------- #
# Set compile options                                       #
# --------------------------------------------------------- #
if(MSVC)
    target_compile_options(${BLYSS_ARTIFACT_NAME} PRIVATE /W4)
else()
    target_compile_options(${BLYSS_ARTIFACT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# --------------------------------------------------------- #
# Link Libraries                                            #
# --------------------------------------------------------- #
target_link_libraries(${BLYSS_ARTIFACT_NAME}
    ${LIBBLYSS_ARTIFACT_NAME}
)