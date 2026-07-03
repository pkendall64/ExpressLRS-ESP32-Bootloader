cmake_minimum_required(VERSION 3.22)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
idf_build_set_property(MINIMAL_BUILD ON)
project(ExpressLRS_ESP32_Bootloader)

idf_build_get_property(idf_path IDF_PATH)
idf_build_get_property(python PYTHON)
idf_build_get_property(target IDF_TARGET)

if(CONFIG_BOOTLOADER_FLASH_DC_AWARE)
    set(bootloader_flash_mode dout)
else()
    set(bootloader_flash_mode ${CONFIG_ESPTOOLPY_FLASHMODE})
endif()

set(bootloader_elf2image_args
    --flash_mode ${bootloader_flash_mode}
    --flash_freq ${CONFIG_ESPTOOLPY_FLASHFREQ}
    --flash_size ${CONFIG_ESPTOOLPY_FLASHSIZE}
    --dont-append-digest
    --min-rev-full ${CONFIG_ESP_REV_MIN_FULL}
    --max-rev-full ${CONFIG_ESP_REV_MAX_FULL}
)

if(CONFIG_IDF_TARGET_ESP32)
    math(EXPR bootloader_min_rev "${CONFIG_ESP_REV_MIN_FULL} / 100")
elseif(CONFIG_IDF_TARGET_ESP32C3)
    math(EXPR bootloader_min_rev "${CONFIG_ESP_REV_MIN_FULL} % 100")
endif()

if(DEFINED bootloader_min_rev AND NOT bootloader_min_rev EQUAL 0)
    list(APPEND bootloader_elf2image_args --min-rev ${bootloader_min_rev})
endif()

if(CONFIG_SECURE_BOOT_V2_ENABLED AND NOT CONFIG_SECURE_BOOT_BUILD_SIGNED_BINARIES)
    list(APPEND bootloader_elf2image_args --pad-to-size 4KB)
endif()

add_custom_target(bootloader_nodigest
    COMMAND ${python} "${idf_path}/components/esptool_py/esptool/esptool.py" --chip ${target}
            elf2image ${bootloader_elf2image_args}
            -o "${CMAKE_BINARY_DIR}/bootloader/bootloader.bin"
            "${CMAKE_BINARY_DIR}/bootloader/bootloader.elf"
    DEPENDS bootloader
    USES_TERMINAL
    VERBATIM
)
