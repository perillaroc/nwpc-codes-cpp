project(single_message)

add_executable(single_message
    main.cpp
	)

target_link_libraries(
	single_message
	PUBLIC
	NwpcCodesCpp::GribCoder
)