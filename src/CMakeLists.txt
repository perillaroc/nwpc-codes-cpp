

add_executable(nwpc_codes_cpp
    main.cpp
	openjpeg_helper.cpp
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