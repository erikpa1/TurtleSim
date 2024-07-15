import os
import subprocess

# Global set of folder patterns to ignore
IGNORE_PATTERNS = {"external/imgui"}

def find_cpp_files(directory, main_file):
    cpp_files = []
    for root, dirs, files in os.walk(directory):
        # Skip directories that match any of the ignore patterns
        if any(pattern in root for pattern in IGNORE_PATTERNS):
            continue
        for file in files:
            if file.endswith('.cpp'):
                cpp_files.append(os.path.join(root, file))
    
    # Ensure the main file is included first
    if main_file in cpp_files:
        cpp_files.remove(main_file)
    cpp_files.insert(0, main_file)
    
    return cpp_files

def build_command(cpp_files, output_file):
    # Join all .cpp files with a space and form the build command
    files_str = ' '.join(cpp_files)
    command = f"emcc {files_str} -o {output_file} -std=c++20 -msse -msse2 -msse3 -msimd128 "
    return command

def main():
    # Specify the output file name
    output_file = "SimStudio.js"
    
    # Specify the main cpp file
    main_file = "./main.cpp"
    
    # Check if the main file exists
    if not os.path.exists(main_file):
        print(f"Main file {main_file} does not exist.")
        return
    
    # Find all .cpp files starting from the src directory, excluding ignored directories
    cpp_files = find_cpp_files('./src', main_file)
    
    if not cpp_files:
        print("No .cpp files found.")
        return
    
    # Add the main file explicitly to the start of the list
    cpp_files.insert(0, main_file)
    
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
