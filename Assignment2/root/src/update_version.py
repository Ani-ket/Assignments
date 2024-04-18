import os
import shutil
import re

def update_file(file_path, pattern, replacement):
    """Update a file by replacing text matching the pattern."""
    temp_file_path = file_path + '.tmp'
    with open(file_path, 'r') as fin, open(temp_file_path, 'w') as fout:
        for line in fin:
            updated_line = re.sub(pattern, replacement, line)
            fout.write(updated_line)
    shutil.move(temp_file_path, file_path)

def update_sconstruct(build_num, source_path):
    """Update the build number in the SConstruct file."""
    sconstruct_path = os.path.join(source_path, 'develop', 'global', 'src', 'SConstruct')
    update_file(sconstruct_path, r'point=\d+', f'point={build_num}')

def update_version(build_num, source_path):
    """Update the build number in the VERSION file."""
    version_path = os.path.join(source_path, 'develop', 'global', 'src', 'VERSION')
    update_file(version_path, r'ADLMSDK_VERSION_POINT=\d+', f'ADLMSDK_VERSION_POINT={build_num}')

def main():
    build_num = os.environ.get('BuildNum')
    source_path = os.environ.get('SourcePath')
    
    # Prompt the user for input if environment variables are not set
    if not build_num:
        build_num = input("Enter the build number: ")
    if not source_path:
        source_path = input("Enter the source path: ")
    
    # Check if build_num and source_path are provided
    if not build_num or not source_path:
        print("Error: Build number and source path are required.")
        return

    try:
        update_sconstruct(build_num, source_path)
        update_version(build_num, source_path)
        print("Version numbers updated successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()

