省流：能代码补全，编译结果有问题，CLion的远程调试能接上qemu，但是程序都似了有没有什么用，建议ntr开发，Clion写代码Esclipse编译Debug。
# 为什么要做IDE替换
众所周知，基于Eclipse开发的嵌入式IDE，像Ti的CCS，英飞凌的ADS，瑞萨(~~史中史~~) ，以及ST的STM32CubeIDE，虽然厂商做了一定程度上的支持，但是用起来非常的一眼难尽。
![](https://picx.zhimg.com/80/v2-9d8193126d77f9575c62e1a8440fd370_1440w.png)
而STM32早已支持Cmake与Clion搭配进行项目配置与开发，开发体验有了质的提升，因此，***我想探索一种通用性的解决办法，即Eclipse在编译时生成的Makefile文件进行逆推导得到Cmakelist，进而能够搭配代码开发体验较好的IDE进行开发编译与调试。***
需要提醒的是，在撰写本文时，虽然能够得到编译成功的结果，但是与Eclipse编译结果不同，仍然在解决中，但是可以将Clion作为代码编辑器进行代码编写，在Eclipse进行编译运行与调试。
# 开发环境
Nuclei Studio IDE for C/C++ Developers
Version: 2024-02.DEV
ToolChain来自Nuclei IDE自带的编译器，路径如图所示，就是在芯原官方提供的压缩包的toolchain文件夹内。
![](https://pic1.zhimg.com/80/v2-c0bd065f7dc4ec399a60089a9d7b5f00_1440w.png)

使用工程如图所示，实际上就是官方提供的sdk工程,我把doc文件夹删除了。
![](https://picx.zhimg.com/80/v2-b7c0585a82e5e68ff61bcde37ca98eb8_1440w.png)
![](https://pica.zhimg.com/80/v2-02050e38c71f0557d74709fa86c9b3d0_1440w.png)
# 替换开发步骤
## 添加环境变量
![](https://pic1.zhimg.com/80/v2-c0bd065f7dc4ec399a60089a9d7b5f00_1440w.png)
IDE解压完成后，将NucleiStudio/toolchain/gcc/bin添加到系统环境变量PATH中，别管gcc13，那是个空文件夹。
![](https://picx.zhimg.com/80/v2-7e2bee2fddca204771876edb3b0b8cee_1440w.png)
我这里把qemu加进去的原因是，原来是在qemu上运行程序的，我想着一起移植到CLion上（~~但是似了~~）
在终端中确认环境变量是否添加成功，运行
```bash
riscv64-unknown-elf-gcc -v
```
如果成功添加了应该会出现下图这样
![](https://pica.zhimg.com/80/v2-1d30dc50f6f5d8c09fd9d035c10ad504_1440w.png)
## Clion项目配置
具体的工程我已经上传到github，仓库地址[GitHub - WwWangGuan/VeriTest: 芯原杯对原有基于Esclipe IDE用CMake替换的测试工程](https://github.com/WwWangGuan/VeriTest)
![](https://picx.zhimg.com/80/v2-e49322cff1eca8876b7acab2a014b769_1440w.png)
### 工具链配置
![](https://pic1.zhimg.com/80/v2-2e41cf8b0f99f35857344c1b33a5f835_1440w.png)

直接新建一个工具链就好，C/C++编译器指定到原来Eclipse的编译器，gdb是我自认为应该加上去的，准确性未知。
但是，需要在Cmake的选项卡中指定一下工具链，这样CLion才会用新添加的工具链
![](https://picx.zhimg.com/80/v2-fa47f635b53309b1c9c54a0230dbfd2d_1440w.png)
Q：为啥用Release？
A：他原来就用的Release。
PS：勾上图里的那个选项开发体验有巨大提升。
### Cmakelist.txt
重头戏来了（太折磨了）
```Cmake
cmake_minimum_required(VERSION 3.25)  
  
# 指定交叉编译工具链  
set(CMAKE_SYSTEM_NAME Generic)  
set(CMAKE_SYSTEM_VERSION 1)  
# 项目信息  
project(qemu C CXX ASM)  
set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_C_STANDARD 11)  
  
set(CMAKE_C_COMPILER riscv64-unknown-elf-gcc)  
set(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++)  
set(CMAKE_ASM_COMPILER riscv64-unknown-elf-gcc)  
set(CMAKE_AR riscv64-unknown-elf-ar)  
set(CMAKE_OBJCOPY riscv64-unknown-elf-objcopy)  
set(CMAKE_OBJDUMP riscv64-unknown-elf-objdump)  
set(SIZE riscv64-unknown-elf-size)  
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
        galaxy_sdk)  
  
# 添加所有源文件  
file(GLOB_RECURSE SOURCES "galaxy_sdk/bsp/src/*.*"  
        "galaxy_sdk/drivers/src/*.*"        "galaxy_sdk/src/*.*"        "galaxy_sdk/*.*")  
  
# 链接器脚本  
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/galaxy_sdk/n309_iot_qemu.ld)  
  
# 通用编译选项  
set(COMMON_FLAGS "-march=rv32imafc_xxldsp -mabi=ilp32f -mtune=nuclei-300-series -mcmodel=medlow -mno-save-restore -O2 -ffunction-sections -fdata-sections -fno-common -Wall -Werror -g")  
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS}")  
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${COMMON_FLAGS} -x assembler-with-cpp")  
  
# 链接选项  
add_link_options(  
        -T ${LINKER_SCRIPT}  
        -nostartfiles  
        -Xlinker --gc-sections        -Wl,-Map=${CMAKE_BINARY_DIR}/qemu.map  
        -Wl,--no-warn-rwx-segments)  
  
# 设置库目录  
link_directories(  
        galaxy_sdk/bsp/lib  
        galaxy_sdk/drivers/lib
        galaxy_sdk/modules/lib
        galaxy_sdk/modules/external/riscv_dsp
        galaxy_sdk/os/lib
        galaxy_sdk/osal/lib
        galaxy_sdk/prebuilts/bluetooth/health)  
  
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
        -Wl,--end-group)  
  
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
```
#### 几个需要强调的地方
~~1. 我这里是手动指定了编译器的位置，因为我测试的时候发现即使我添加了环境变量Cmake仍然识别不到~~
byd，又好使了
1. 项目信息看个人，要不要改随意，在第7行改就可以。
2. 官方给的都是.a，链接的时候有顺序问题，我这里抄了一下原来的makefile，加上了-Wl,--start-group 和-Wl,--end-group ，让编译器自己找链接顺序。
3. 如果需要添加新文件夹，添加方式和STM32的方式相同。
### 配置效果
如果准确无误，应该会有如下信息（Cmake）：
```bash
C:\Users\34789\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-gcc.exe -DCMAKE_CXX_COMPILER=C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-c++.exe -G "MinGW Makefiles" -S G:\VeriSilicon\VeriHealthi_QEMU_SDK.202405_preliminary\VeriHealthi_QEMU_SDK.202405_preliminary\VeriTest -B G:\VeriSilicon\VeriHealthi_QEMU_SDK.202405_preliminary\VeriHealthi_QEMU_SDK.202405_preliminary\VeriTest\cmake-build-release-verisilicon
-- The C compiler identification is GNU 13.1.1
-- The CXX compiler identification is GNU 13.1.1
-- The ASM compiler identification is GNU
-- Found assembler: C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-gcc.exe
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-gcc.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Embedded_tools/NucleiStudio/toolchain/gcc/bin/riscv64-unknown-elf-c++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.3s)
-- Generating done (0.0s)
-- Build files have been written to: G:/VeriSilicon/VeriHealthi_QEMU_SDK.202405_preliminary/VeriHealthi_QEMU_SDK.202405_preliminary/VeriTest/cmake-build-release-verisilicon

[已完成]

```

![](https://picx.zhimg.com/80/v2-ce4e264a02aaf26dac9eeab5b5ad606f_1440w.png)
### 最终效果
![](https://picx.zhimg.com/80/v2-ebca35fb7dd940600576cc6480127534_1440w.png)

愉 快 的 代 码 书 写 体 验（~~双手指天~~）
# 编译问题
![](https://pic1.zhimg.com/80/v2-f0233efd30cc57f321198df0f2433521_1440w.png)

上图是CLion的编译结果，但是呢，让我们看看原来IDE是啥结果

![](https://picx.zhimg.com/80/v2-098c6110c4509d8b4f65e0841992b496_1440w.png)

不是，哥们，怎么最终程序大小都不一样啊。
我试图把CLion编译的qemu.out搬到Esclipe里用，结果直接告诉我QEMU运行不了。
这是我写这个文章时候感到最大的挫败点，折腾了半天CLion变成了代码编辑器~~早知道还不如Vscode来的实在。~~
来个大佬教教我咋解决吧。
