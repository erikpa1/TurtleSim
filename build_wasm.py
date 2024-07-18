import os
import subprocess

# Global set of folder patterns to ignore
IGNORE_PATTERNS = {"external/imgui"}

def find_cpp_files(directory):
    cpp_files = []
    for root, dirs, files in os.walk(directory):
        # Skip directories that match any of the ignore patterns
        if any(pattern in root for pattern in IGNORE_PATTERNS):
            continue
        for file in files:
            if file.endswith('.cpp'):
                print("Adding: ", file)
                cpp_files.append(os.path.join(root, file))
    
    return cpp_files

def build_command(cpp_files, output_file):
    # Join all .cpp files with a space and form the build command
    files_str = ' '.join(cpp_files)

    build_configs1 = "-msse -msse2 -msse3 -msimd128 -pthread -s PTHREAD_POOL_SIZE=10"
    build_configs2 = "-IS_WASM=1"

    command = f"emcc {files_str} -o {output_file} -std=c++20 {build_configs1} {build_configs2} "
    return command

def main():
    # Specify the output file name
    output_file = "SimStudio.js"
    


    # Find all .cpp files starting from the src directory, excluding ignored directories
    cpp_files = find_cpp_files('./src')
    
    if not cpp_files:
        print("No .cpp files found.")
        return
    
    # Add the main file explicitly to the start of the list
    cpp_files.insert(0, "main.cpp")
    
    # Generate the build command
    command = build_command(cpp_files, output_file)
    
    # Print the command (for verification)
    print("Running command:", command)
    
    # Execute the build command
    result = subprocess.run(command, shell=True)
    
    if result.returncode == 0:
        print(f"Build successful. Output file: {output_file}")
    else:
        print("Build failed.")

if __name__ == "__main__":
    main()
