file(GLOB CPP_SRC
    "*.cpp"
    )

target_sources(cs2d_tests
    PRIVATE ${CPP_SRC}
    )