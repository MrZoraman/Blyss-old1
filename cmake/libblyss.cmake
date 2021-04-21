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
macro(libblyss_add_class CLASS_NAME)
    list(APPEND LIBBLYSS_SOURCES ${LIBBLYSS_SRC_DIR}/${CLASS_NAME}.cpp)
    list(APPEND LIBBLYSS_HEADERS ${LIBBLYSS_HEADERS}/${CLASS_NAME}.hpp)
endmacro()