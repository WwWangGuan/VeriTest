import os
import subprocess
import sys

def parse_size_output(output):
    lines = output.splitlines()
    text, data, bss, dec, hex_size, _ = lines[-1].split()
    text = int(text)
    data = int(data)
    bss = int(bss)
    dec = int(dec)
    hex_size = int(hex_size, 16)

    return text, data, bss, dec, hex_size

def print_memory_usage(executable):
    result = subprocess.run(["riscv64-unknown-elf-size", executable], capture_output=True, text=True)
    text, data, bss, dec, hex_size = parse_size_output(result.stdout)

    ram_used = data + bss
    ram_size = 20 * 1024  # 20 KB
    ram_usage = (ram_used / ram_size) * 100

    flash_used = text + data
    flash_size = 128 * 1024  # 128 KB
    flash_usage = (flash_used / flash_size) * 100

    print(f"Memory region    Used Size    Region Size    %age Used")
    print(f"RAM:             {ram_used} B    {ram_size / 1024} KB    {ram_usage:.2f}%")
    print(f"FLASH:           {flash_used} B    {flash_size / 1024} KB    {flash_usage:.2f}%")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: memory_usage.py <executable>")
        sys.exit(1)

    executable = sys.argv[1]
    print_memory_usage(executable)
