set(target_name checker)

add_compile_options(-lpthread)

add_library(${target_name} STATIC
    CheckFile.cpp
    ${PROJECT_SOURCE_DIR}/include/Check/CheckFile.hpp)

    include(CompileOptions)
    set_compile_options(${target_name})

    target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}/include/
    )

   