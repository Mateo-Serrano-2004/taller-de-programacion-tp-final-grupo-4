file(GLOB H_SOURCES
    "*.h"
    )

target_sources(cs2d_editor
    PUBLIC ${H_SOURCES}
    )