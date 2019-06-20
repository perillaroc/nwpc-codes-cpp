project(sample_data)

add_executable(sample_data
    main.cpp
	)

target_link_libraries(
	sample_data
	PUBLIC
	NwpcCodesCpp::GribCoder
)