set( TARGET visitor )

set( HEADER_FILES
    Visitable.hpp
    Visitable.tpp
)
source_group(
    \\ FILES
    ${HEADER_FILES}
)

add_custom_target(
    ${TARGET}
    SOURCES
        ${HEADER_FILES}
)

