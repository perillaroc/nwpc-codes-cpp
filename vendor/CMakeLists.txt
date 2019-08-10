add_library(vendor INTERFACE)

target_include_directories(vendor
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    )

add_library(NwpcCodesCpp::vendor ALIAS vendor)