cmake_minimum_required(VERSION 3.25)

# 指定交叉编译工具链
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_VERBOSE_MAKEFILE ON)
# 项目信息
project(qemu C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_COMPILER "C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-g++.exe")
set(CMAKE_ASM_COMPILER "C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-g++.exe")
set(CMAKE_AR "C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-ar.exe")
set(CMAKE_OBJCOPY "C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-objcopy.exe")
set(CMAKE_OBJDUMP "C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-objdump.exe")
set(SIZE "C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-size.exe")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 包含目录
include_directories(
        galaxy_sdk/bsp/include
        galaxy_sdk/bsp/include/arch/riscv/n309
        galaxy_sdk/config/include
        galaxy_sdk/drivers/include
        galaxy_sdk/modules/include
        galaxy_sdk/modules/external/riscv_dsp/include
        galaxy_sdk/os/include
        galaxy_sdk/osal/include
        galaxy_sdk/prebuilts/bluetooth/health/include
        galaxy_sdk
)

# 添加所有源文件
file(GLOB_RECURSE SOURCES "galaxy_sdk/bsp/src/*.*"
        "galaxy_sdk/drivers/src/*.*"
        "galaxy_sdk/src/*.*"
        "galaxy_sdk/*.*")
message(STATUS "SOURCES: ${SOURCES}")

# 链接器脚本
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/galaxy_sdk/n309_iot_qemu.ld)

# 通用编译选项
set(COMMON_FLAGS "-march=rv32imafc_xxldsp -mabi=ilp32f -mtune=nuclei-300-series -mcmodel=medlow -mno-save-restore -O2 -ffunction-sections -fdata-sections -fno-common -Wall -Werror -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${COMMON_FLAGS} -x assembler-with-cpp")

# 输出编译选项
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_ASM_FLAGS: ${CMAKE_ASM_FLAGS}")

# 链接选项
add_link_options(
        -T ${LINKER_SCRIPT}
        -nostartfiles
        -Xlinker --gc-sections
        -Wl,-Map=${CMAKE_BINARY_DIR}/qemu.map
        -Wl,--no-warn-rwx-segments
)

# 设置库目录
link_directories(
        galaxy_sdk/bsp/lib
        galaxy_sdk/drivers/lib
        galaxy_sdk/modules/lib
        galaxy_sdk/modules/external/riscv_dsp
        galaxy_sdk/os/lib
        galaxy_sdk/osal/lib
        galaxy_sdk/prebuilts/bluetooth/health
)

# 添加可执行文件
add_executable(${PROJECT_NAME}.out ${SOURCES})

# 特定文件类型的编译选项
foreach(source IN LISTS SOURCES)
    if (source MATCHES "\\.S$")
        set_source_files_properties(${source} PROPERTIES COMPILE_FLAGS "${CMAKE_ASM_FLAGS}")
    endif()
endforeach()

# 链接库
target_link_libraries(${PROJECT_NAME}.out
        -Wl,--start-group
        c_nano
        gcc
        stdc++
        semihost
        osal_riscv
        os_riscv
        bsp_riscv
        driver_riscv
        common_riscv
        ble
        nmsis_dsp_rv32imafc_xxldsp
        -Wl,--end-group
)

# 生成HEX文件
add_custom_command(TARGET ${PROJECT_NAME}.out POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.out ${PROJECT_NAME}.hex
        COMMENT "Building ${PROJECT_NAME}.hex"
)

# 生成列表文件
add_custom_command(TARGET ${PROJECT_NAME}.out POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} --source --all-headers --demangle --line-numbers --wide ${PROJECT_NAME}.out > ${PROJECT_NAME}.lst
        COMMENT "Building ${PROJECT_NAME}.lst"
)

# 打印尺寸
add_custom_command(TARGET ${PROJECT_NAME}.out POST_BUILD
        COMMAND ${SIZE} --format=berkeley ${PROJECT_NAME}.out > ${PROJECT_NAME}.siz
        COMMENT "Building ${PROJECT_NAME}.siz"
)
# 打印内存使用情况
add_custom_command(TARGET ${PROJECT_NAME}.out POST_BUILD
        COMMAND ${SIZE} ${PROJECT_NAME}.out
        COMMENT "Memory usage:"
)

# 清理命令
add_custom_target(clean_all
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*.o ${CMAKE_BINARY_DIR}/*.d ${CMAKE_BINARY_DIR}/*.out ${CMAKE_BINARY_DIR}/*.hex ${CMAKE_BINARY_DIR}/*.lst ${CMAKE_BINARY_DIR}/*.siz
        COMMENT "Cleaning up generated files"
)
