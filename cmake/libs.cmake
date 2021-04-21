  
# --------------------------------------------------------- #
# Boost                                                     #
# --------------------------------------------------------- #
SET(Boost_USE_STATIC_LIBS ON)  
SET(Boost_USE_MULTITHREADED ON)
if (MSVC)
  SET(BOOST_ROOT "changeme" CACHE PATH "Boost root directory")
endif()
find_package(Boost 1.71.0 COMPONENTS log program_options REQUIRED)
