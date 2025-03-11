import os
import subprocess

# Read file and look for line to modify
with open("functions_rot13.s", "r") as file:
    lines = file.readlines()
    for k in range(len(lines)):
        if "jmp rot13" in lines[k]:
            lines[k] = lines[k].replace("jmp rot13", "jmp finish_rot13")

# Write the changes
with open("functions_rot13.s", "w") as file:
    file.writelines(lines)

# Compile and run modified program
# Here the command run to compile is .asm file_name
# .asm is an alias we gave to a script which runs the following commands:
# 
# output_file=$(basename "$1" .s).o
# nasm -f elf64 -g "$1" -o "$output_file"
# ld -m elf_x86_64 -o $(basename "$1" .s) "$output_file"
subprocess.run(".asm functions_rot13.s", check=True)
subprocess.run("./functions_rot13", check=True)