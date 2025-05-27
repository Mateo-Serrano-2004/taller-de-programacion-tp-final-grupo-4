file(GLOB CPP_SRC
    "*.cpp"
    )

file(GLOB H_SRC
    "*.h"
    )

target_sources(cs2d_client
    PRIVATE ${CPP_SRC}
    PUBLIC ${H_SRC}
    )

add_subdirectory(event/)
add_subdirectory(handler/)
add_subdirectory(exception/)
add_subdirectory(render/)
add_subdirectory(texture/)
add_subdirectory(window/)