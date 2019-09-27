cmake_minimum_required(VERSION 3.12)
project(nwpc_codes_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(CLI11 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

find_package(GSL REQUIRED)

add_subdirectory(src)
add_subdirectory(tool)
add_subdirectory(example)

install(EXPORT NwpcCodesCppTargets
	FILE NwpcCodesCppTargets.cmake
	NAMESPACE NwpcCodesCpp::
	DESTINATION lib/cmake/NwpcCodesCpp

)