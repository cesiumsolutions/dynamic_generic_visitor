set( TARGET shape_plugin )

set( SOURCE_FILES
    ${TARGET}.cpp
    Triangle.hpp
)
source_group(
    \\ FILES
    ${SOURCE_FILES}
)

add_library(
    ${TARGET} SHARED
    ${SOURCE_FILES}
)
