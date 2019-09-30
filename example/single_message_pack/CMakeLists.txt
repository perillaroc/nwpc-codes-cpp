project(single_message_pack)

add_executable(single_message_pack)

target_sources(single_message_pack
	PRIVATE
		main.cpp
)

target_link_libraries(single_message_pack
	PUBLIC
		NwpcCodesCpp::GribCoder
)