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