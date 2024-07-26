import os
import re
import tkinter as tk
from tkinter import filedialog, messagebox

class IncludeProcessor:
    def __init__(self, source_dir, common_dir, output_file):
        self.source_dir = source_dir
        self.common_dir = common_dir
        self.output_file = output_file
        self.not_found_includes = set()
        self.includes_from_headers = []
        self.includes_from_cpp = set()
        self.includes_from_common = set()
        self.cpp_from_common = set()
        self.processed_files = set()
        self.main_file = None

    def find_main_cpp(self):
        for directory in [self.source_dir, self.common_dir]:
            for root, _, files in os.walk(directory):
                for file in files:
                    if file == 'main.cpp':
                        return os.path.join(root, file)
        return None

    def extract_includes(self, file_path):
        includes = []
        file_dir = os.path.dirname(file_path)
        
        with open(file_path, 'r') as file:
            for line in file:
                include_match = re.match(r'^\s*#include\s*[<"](.*)[">]', line)
                if include_match:
                    include = include_match.group(1).strip()
                    include_path = os.path.normpath(os.path.join(file_dir, include))
                    if os.path.isfile(include_path):
                        includes.append(include_path)
                    else:
                        include_path_common = os.path.normpath(os.path.join(self.common_dir, include))
                        if os.path.isfile(include_path_common):
                            self.includes_from_common.add(include_path_common)
                            includes.append(include_path_common)
                        else:
                            # Track includes that are not found in both directories
                            self.not_found_includes.add(include)
        return includes

    def collect_includes_recursively(self, file_path):
        if file_path in self.processed_files:
            return
        self.processed_files.add(file_path)

        include_paths = self.extract_includes(file_path)
        for path in include_paths:
            self.collect_includes_recursively(path)
            if path not in self.includes_from_headers:
                self.includes_from_headers.append(path)

    def collect_includes_from_cpp(self, directory, file_to_process = []):
        for root, _, files in os.walk(directory):
            for file in files:
                if file.endswith('.cpp'):
                    file_path = os.path.join(root, file)
                    if not file_to_process or file_path in file_to_process:
                        self.includes_from_cpp.update(self.extract_includes(file_path))

    def process_common_headers(self):
        for header_file in self.includes_from_common:
            if header_file.endswith('.h'):
                cpp_file = header_file.replace('.h', '.cpp')
                if os.path.isfile(cpp_file):
                    self.cpp_from_common.add(cpp_file)
                else:
                    print(f"Warning: {header_file} has no corresponding .cpp implementation.")

    def read_file_content(self, file_path):
        content = []
        with open(file_path, 'r') as file:
            for line in file:
                if not re.match(r'^\s*#include\s*[<"](.*)[">]', line):
                    content.append(line)
        content.append('\n')
        return ''.join(content)
    
    def write_output_file(self):
        with open(self.output_file, 'w') as output:
            # Write not found includes
            if self.not_found_includes:
                output.write("// =============================\n")
                output.write("// Not Found Includes\n")
                output.write("// =============================\n")
                for include in self.not_found_includes:
                    output.write(f'#include <{include}>\n')
    
            # Write includes independent of .cpp files
            independent_includes = self.includes_from_cpp - set(self.includes_from_headers)
            if independent_includes:
                output.write("\n// =============================\n")
                output.write("// Independent Includes\n")
                output.write("// =============================\n")
                for include in independent_includes:
                    output.write(self.read_file_content(include))
    
            # Write includes from headers in the right order
            if self.includes_from_headers:
                output.write("\n// =============================\n")
                output.write("// Includes from Headers\n")
                output.write("// =============================\n")
                for include in self.includes_from_headers:
                    output.write(self.read_file_content(include))
    
            # Write content of used .cpp files of common
            if self.cpp_from_common:
                output.write("\n// =============================\n")
                output.write("// Content of Used .cpp Files from Common\n")
                output.write("// =============================\n")
                for file in self.cpp_from_common:
                    output.write(self.read_file_content(file))
    
            # Write content of all .cpp files except main.cpp
            cpp_files_except_main = [
                os.path.join(root, file)
                for root, _, files in os.walk(self.source_dir)
                for file in files if file.endswith('.cpp') and file != 'main.cpp'
            ]
            if cpp_files_except_main:
                output.write("\n// =============================\n")
                output.write("// Content of All .cpp Files Except main.cpp\n")
                output.write("// =============================\n")
                for file_path in cpp_files_except_main:
                    output.write(self.read_file_content(file_path))
    
            # Write content of main.cpp
            if self.main_file:
                output.write("\n// =============================\n")
                output.write("// Content of main.cpp\n")
                output.write("// =============================\n")
                output.write(self.read_file_content(self.main_file))


    def process(self):
        # Step 1: Find main.cpp
        self.main_file = self.find_main_cpp()
        if not self.main_file:
            print("main.cpp not found.")
            return
        
        # Step 2: Collect includes recursively starting from main.cpp
        self.collect_includes_recursively(self.main_file)

        # Step 3: Collect includes from .cpp files in src
        self.collect_includes_from_cpp(self.source_dir)

        # Step 4: Process headers and collect corresponding .cpp files from common
        self.process_common_headers()

        # Step 5: Collect includes from .cpp files in common
        self.collect_includes_from_cpp(self.common_dir, self.cpp_from_common)

        # Step 6: Write output file
        self.write_output_file()
        
def browse_folder(title, initial_dir):
    root = tk.Tk()
    root.withdraw()
    folder_path = filedialog.askdirectory(title=title, initialdir=initial_dir)
    root.destroy()
    return folder_path

def browse_file(title, initial_dir):
    root = tk.Tk()
    root.withdraw()
    file_path = filedialog.asksaveasfilename(
        title=title, initialdir=initial_dir, defaultextension=".ino",
        filetypes=(("Arduino files", "*.ino"), ("All files", "*.*"))
    )
    root.destroy()
    return file_path

def main():
    # Get the directory where the script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Ask user for input
    source_dir = browse_folder("Select Project Source Folder", initial_dir=script_dir)
    if not source_dir:
        messagebox.showwarning("No Folder Selected", "No source directory selected. Exiting.")
        return

    common_dir = browse_folder("Select Common Folder", initial_dir=source_dir)
    if not common_dir:
        messagebox.showwarning("No Folder Selected", "No common directory selected. Exiting.")
        return

    output_file = browse_file("Select Output File", initial_dir=script_dir)
    if not output_file:
        messagebox.showwarning("No File Selected", "No output file selected. Exiting.")
        return

    # Process the files
    processor = IncludeProcessor(source_dir, common_dir, output_file)
    processor.process()

if __name__ == "__main__":
    main()