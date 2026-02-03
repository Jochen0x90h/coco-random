add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET headers TYPE HEADERS FILES
        Random.hpp
#	PRIVATE
)

if(${PLATFORM} STREQUAL "native" OR ${PLATFORM} STREQUAL "emu")
    # native platform (Windows, MacOS, Linux)
    target_sources(${PROJECT_NAME}
        PUBLIC FILE_SET platform_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/native FILES
            native/coco/platform/Random_random.hpp
        PRIVATE
            native/coco/platform/Random_random.cpp
        )
elseif(${PLATFORM} MATCHES "^nrf52")
    target_sources(${PROJECT_NAME}
        PUBLIC FILE_SET platform_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/rng FILES
            rng/coco/platform/Random32_rng.hpp
        PRIVATE
            rng/coco/platform/Random32_rng.cpp
    )
elseif(${PLATFORM} MATCHES "^stm32")
    target_sources(${PROJECT_NAME}
        PUBLIC FILE_SET platform_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/rng FILES
            rng/coco/platform/Random32_rng.hpp
            #stm32/coco/platform/Random_UID.hpp
        PRIVATE
            rng/coco/platform/Random32_rng.cpp
            #stm32/coco/platform/Random_UID.cpp
    )
endif()

target_link_libraries(${PROJECT_NAME}
    coco::coco
    coco-loop::coco-loop
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ..
)

# install the library
install(TARGETS ${PROJECT_NAME}
    FILE_SET headers DESTINATION include/coco
    FILE_SET platform_headers DESTINATION include
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
