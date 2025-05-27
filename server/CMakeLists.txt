target_sources(cs2d_server
    PRIVATE
    # .cpp files
    main.cpp
    PUBLIC
    # .h files
    )

add_subdirectory(net/include/)
add_subdirectory(net/src/)
add_subdirectory(game/include/)
add_subdirectory(game/src/)
add_subdirectory(events/)