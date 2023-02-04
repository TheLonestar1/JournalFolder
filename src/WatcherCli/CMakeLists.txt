
set(target_name main)

add_executable(${target_name})
include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    main.cpp
)

target_include_directories(
    ${target_name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/external/CLI11)



target_link_libraries(
  ${target_name}
  
  PRIVATE
    checker
    CLI11
    Threads::Threads
)
