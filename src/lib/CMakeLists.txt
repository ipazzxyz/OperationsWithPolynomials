qt_add_library(OWP STATIC
    list.h
    monomial.cpp
    monomial.h
    node.h
    polynomial.cpp
    polynomial.h
    validator.cpp
    validator.h
)
target_include_directories(OWP INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})