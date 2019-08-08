project(multi_message)

add_executable(multi_message
    main.cpp
	)

target_link_libraries(
	multi_message
	PUBLIC
	NwpcCodesCpp::GribCoder
)