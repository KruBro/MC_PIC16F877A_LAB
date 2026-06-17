# The following variables contains the files used by the different stages of the build process.
set(AS_02_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${AS_02_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${AS_02_default_default_XC8_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(AS_02_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${AS_02_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${AS_02_default_default_XC8_FILE_TYPE_assemblePreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(AS_02_default_default_XC8_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../initconfig.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../pattern1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../pattern2.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../pattern3.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../pattern4.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../read_digital_keypad.c")
set_source_files_properties(${AS_02_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(AS_02_default_default_XC8_FILE_TYPE_link)
set(AS_02_default_image_name "default.elf")
set(AS_02_default_image_base_name "default")

# The output directory of the final image.
set(AS_02_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/AS-02")

# The full path to the final image.
set(AS_02_default_full_path_to_image ${AS_02_default_output_dir}/${AS_02_default_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .hxl
    .mum
    .o
    .sdb
    .sym
    .cmf)
list(TRANSFORM output_extensions PREPEND "${AS_02_default_output_dir}/${AS_02_default_image_base_name}")
