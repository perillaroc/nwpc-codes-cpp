project(sample_data)

add_executable(sample_data)

target_sources(sample_data
	PRIVATE
		main.cpp
)

target_link_libraries(sample_data
	PUBLIC
		NwpcCodesCpp::GribCoder
)