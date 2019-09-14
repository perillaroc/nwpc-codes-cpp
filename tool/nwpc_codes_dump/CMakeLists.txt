project(nwpc_codes_dump)

add_executable(nwpc_codes_dump)

target_sources(nwpc_codes_dump
	PRIVATE
		codes_dump.cpp
		main.cpp
)

target_link_libraries(nwpc_codes_dump
	PUBLIC
		NwpcCodesCpp::ToolUtil
)