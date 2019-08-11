project(nwpc_codes_ls)

add_executable(nwpc_codes_ls
    main.cpp
	)

target_link_libraries(
	nwpc_codes_ls
	PUBLIC
	NwpcCodesCpp::GribCoder
	NwpcCodesCpp::vendor
)