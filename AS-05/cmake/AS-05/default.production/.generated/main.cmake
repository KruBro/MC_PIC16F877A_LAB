include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(AS_05_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(AS_05_default_default_XC8_FILE_TYPE_assemble)
add_library(AS_05_default_default_XC8_assemble OBJECT ${AS_05_default_default_XC8_FILE_TYPE_assemble})
    AS_05_default_default_XC8_assemble_rule(AS_05_default_default_XC8_assemble)
    list(APPEND AS_05_default_library_list "$<TARGET_OBJECTS:AS_05_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(AS_05_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(AS_05_default_default_XC8_assemblePreprocess OBJECT ${AS_05_default_default_XC8_FILE_TYPE_assemblePreprocess})
    AS_05_default_default_XC8_assemblePreprocess_rule(AS_05_default_default_XC8_assemblePreprocess)
    list(APPEND AS_05_default_library_list "$<TARGET_OBJECTS:AS_05_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(AS_05_default_default_XC8_FILE_TYPE_compile)
add_library(AS_05_default_default_XC8_compile OBJECT ${AS_05_default_default_XC8_FILE_TYPE_compile})
    AS_05_default_default_XC8_compile_rule(AS_05_default_default_XC8_compile)
    list(APPEND AS_05_default_library_list "$<TARGET_OBJECTS:AS_05_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(AS_05_default_image_HN33FkDy ${AS_05_default_library_list})

set_target_properties(AS_05_default_image_HN33FkDy PROPERTIES
    OUTPUT_NAME "default-production"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${AS_05_default_output_dir}")
target_link_libraries(AS_05_default_image_HN33FkDy PRIVATE ${AS_05_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
AS_05_default_link_rule( AS_05_default_image_HN33FkDy)


