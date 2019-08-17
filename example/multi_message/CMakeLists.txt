project(multi_message)

add_executable(multi_message)

target_sources(multi_message
	PRIVATE
		main.cpp
)

target_link_libraries(multi_message
	PUBLIC
		NwpcCodesCpp::GribCoder
)