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

target_include_directories(cs2d_client PRIVATE ${CMAKE_SOURCE_DIR}/client/game)

add_subdirectory(game/)