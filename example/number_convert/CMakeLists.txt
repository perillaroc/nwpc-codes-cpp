project(number_convert)

add_executable(number_convert)

target_sources(number_convert
	PRIVATE
		main.cpp
)

target_link_libraries(number_convert
	PUBLIC
		NwpcCodesCpp::GribCoder
)