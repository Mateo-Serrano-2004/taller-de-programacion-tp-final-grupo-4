file(GLOB CPP_SRC
    "*.cpp"
    )

file(GLOB H_SRC
    "*.h"
    )

target_sources(cs2d_common
    PRIVATE ${CPP_SRC}
    PUBLIC ${H_SRC}
    )

add_subdirectory(DTO/)
add_subdirectory(model/)