project(single_message)

add_executable(single_message)

target_sources(single_message
	PRIVATE
		main.cpp
)

target_link_libraries(single_message
	PUBLIC
		NwpcCodesCpp::GribCoder
)