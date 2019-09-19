add_library(vendor INTERFACE)

target_include_directories(vendor
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    )

target_compile_definitions(vendor
	INTERFACE
		-DFMT_HEADER_ONLY
)

add_library(NwpcCodesCpp::vendor ALIAS vendor)

install(TARGETS vendor EXPORT NwpcCodesCppTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)