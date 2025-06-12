file(GLOB CPP_SOURCES
    "*.cpp"
    "*.ui"
    )

file(GLOB H_SOURCES
    "*.h"
    )

set(RESOURCE_FILES
    "resources.qrc"
)

target_sources(cs2d_client
    PRIVATE ${CPP_SOURCES}
    PUBLIC ${H_SOURCES}
    ${RESOURCE_FILES}
)

add_subdirectory(scenes/)
add_subdirectory(widgets/)