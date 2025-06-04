file(GLOB CPP_SOURCES
    "*.cpp"
    "*.ui"
    )

file(GLOB H_SOURCES
    "*.h"
    )

target_sources(cs2d_editor
    PRIVATE ${CPP_SOURCES}
    PUBLIC ${H_SOURCES}
    )