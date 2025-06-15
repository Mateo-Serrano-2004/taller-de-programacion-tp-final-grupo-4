file(GLOB CPP_SRC
    "*.cpp"
    )

target_sources(cs2d_editor
    PRIVATE ${CPP_SRC}
    )

add_subdirectory(scenes/)
add_subdirectory(menu/)
add_subdirectory(widgets/)