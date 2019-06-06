cmake_minimum_required(VERSION 3.12)
project(nwpc_codes_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(nwpc_codes_cpp
    main.cpp
	openjpeg_coder.cpp
	)

target_include_directories(
	nwpc_codes_cpp
	PUBLIC
	D:/lib/cpp/openjpeg/openjpeg-v2.3.0-windows-x64/include/openjpeg-2.3
)

target_link_libraries(
	nwpc_codes_cpp
	PUBLIC
	D:/lib/cpp/openjpeg/openjpeg-v2.3.0-windows-x64/lib/openjp2.lib
)