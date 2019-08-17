project(nwpc_codes_ls)

add_executable(nwpc_codes_ls)

target_sources(nwpc_codes_ls
	PRIVATE
		main.cpp
)

target_link_libraries(nwpc_codes_ls
	PUBLIC
		NwpcCodesCpp::GribCoder
)