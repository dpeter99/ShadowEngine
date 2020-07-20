

file(GLOB_RECURSE ENGINE_SOURCES
    "./**/**.h"
    "./**/**.cpp"
)


add_library(ShadowEngine ${ENGINE_SOURCES})
target_compile_features(ShadowEngine PUBLIC cxx_std_17)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SOURCES})