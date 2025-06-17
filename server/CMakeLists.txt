file(GLOB CPP_SRC
    "*.cpp"
    )

target_sources(cs2d_server
    PRIVATE ${CPP_SRC}
    )

add_subdirectory(net/)
add_subdirectory(game/)
add_subdirectory(events/)
add_subdirectory(parser/)