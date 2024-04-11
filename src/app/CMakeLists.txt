qt_add_executable(OperationsWithPolynomials
    dividedialog.cpp
    dividedialog.h
    dividedialog.h
    inputdialog.cpp
    inputdialog.h
    inputdialog.ui
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    selectdialog.cpp
    selectdialog.h
    selectdialog.ui
    vardialog.cpp
    vardialog.h
    vardialog.ui
)

# -fsanitize=address, undefined ASAN

target_link_libraries(OperationsWithPolynomials PRIVATE
    OWP
    Qt6::Widgets
)

# target_compile_options(OperationsWithPolynomials PRIVATE -fsanitize=address)
# target_link_options(OperationsWithPolynomials PRIVATE -fsanitize=address)

set_target_properties(OperationsWithPolynomials PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)