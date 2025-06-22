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

target_include_directories(cs2d_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} .)

add_subdirectory(handler/)
add_subdirectory(dto_handler/)
add_subdirectory(utils/)
add_subdirectory(render/)
add_subdirectory(asset/)
add_subdirectory(animation/)
add_subdirectory(sound/)
add_subdirectory(event/)
add_subdirectory(command/)
add_subdirectory(model/)
add_subdirectory(entity/)
add_subdirectory(interface/)
add_subdirectory(controller/)
add_subdirectory(context/)