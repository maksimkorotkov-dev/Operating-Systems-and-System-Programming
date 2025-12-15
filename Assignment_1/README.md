# Filesystem Information Utility

## Description

Filesystem Information Utility is a C program for Linux that demonstrates interaction with the operating system to retrieve system information and work with the filesystem.

The program displays basic system data such as the operating system name and version, computer hostname, and current system time. It also enumerates mounted filesystems and shows their storage characteristics, including total and free space.

Additionally, the application lists the contents of the current directory, displaying file metadata such as size, permissions, and last modification time in a neatly aligned table format.
The program is intended for learning Linux system calls, filesystem structures, and console output formatting.

## Key Features:

- Retrieval of operating system name and kernel version using uname().
- Display of computer (host) name.
- Output of current local system time.
- Enumeration of mounted filesystems.
- Calculation of total and free disk space for each mount point.
- Directory listing with file metadata: file name, file size, permissions, last modification time.
- Table-formatted output using aligned columns for better readability.
- Use of standard Linux and POSIX system interfaces.

## Compilation
```bash
gcc filesystem.c -o filesystem
```

## Usage
Run the program in the terminal
```bash
 ./filesystem 
```

Example Output 
```bash
OS: Linux 6.6.87
Computer name: my-linux-host
Current time: Mon Dec 15 12:57:23 2025

Mount points:
  /                    total=1031018 MB  free=1010241 MB
  /home                total=512000 MB   free=320000 MB
  /proc                total=0 MB        free=0 MB
  /sys                 total=0 MB        free=0 MB

Name                           Size      Permissions  Modified
filesystem.c                   3053      644          Mon Dec 15 12:52:21 2025
task1.c                        6994      644          Mon Dec 15 10:17:47 2025
filesystem                     16968     755          Mon Dec 15 12:52:30 2025

```

## Notes on Mounted Filesystems

On Linux systems, the program may display a large number of mount points.
This is normal behavior and may include:
- Virtual filesystems (/proc, /sys)
- Temporary runtime mounts
- Device-specific or network mounts

The program intentionally displays all detected mount points to reflect the actual system state.

# Virtual Memory and Shared Library Processing

## Description

Virtual Memory and Shared Library Processing is a Linux-based C project demonstrating the use of shared libraries, explicit runtime loading, and memory-mapped file I/O.

The project consists of two separate components:
1. A shared library (.so) that processes a large text file using memory-mapped I/O (mmap), without loading the entire file into memory.

2. A console application that explicitly loads the shared library at runtime using dlopen(), calls the processing function, and displays the results.

The library processes a file containing 3D coordinates (x y z) and finds the point that is farthest from the origin (0, 0, 0). This project is designed to demonstrate virtual memory concepts, efficient large-file processing, and dynamic linking in Linux.

## Project Structure
```bash
libprocessfile.c     → Shared library implementation
libprocessfile.so    → Compiled shared library
main_app.c           → Console application loading the library
big_file.txt         → Large input file with coordinates
```

## Key Features:

- Creation of a shared library (.so) on Linux.
- Explicit (runtime) loading of the library using dlopen().
- Symbol resolution using dlsym().
- Processing of large files using memory-mapped I/O (mmap).
- File processing in parts without reading the entire file into RAM.
- Efficient calculation of distances using virtual memory.
- Clear separation between library logic and application logic.
- Detailed console output showing progress and results.

## Shared Library Functionality
The shared library exports a function that:
- Opens a large text file.
- Maps the file into memory using mmap().
- Parses the file line by line.
- Interprets each line as three floating-point values (x y z).
- Calculates the Euclidean distance from the origin.
- Tracks the farthest point and its line number.
- Returns the result to the calling application.

Memory-mapped I/O allows the operating system to load file pages on demand, making the solution scalable for very large files.

## Application Using the Library
The console application:
- Loads the shared library explicitly at runtime using dlopen().
- Retrieves the processing function using dlsym().
- Passes the file path to the library function.
- Prints detailed information: file being processed, farthest point coordinates, distance from origin, line number of the result

## Compilation
Build the Shared Library
```bash
gcc -fPIC -shared libprocessfile.c -o libprocessfile.so -lm
```
Build the Application
```bash
gcc main_app.c -o main_app -ldl
```

## Usage
Run the application and explicitly provide the shared library and input file:
```bash
./main_app ./libprocessfile.so input_file.txt
```

## Example Output

```bash
Processing file: big_file.txt
Processed 1000 lines...
Processed 2000 lines...
Processed 3000 lines...
Processed 4000 lines...
Processed 5000 lines...

Farthest point found at line 4872341
Coordinates: x=32765.000000 y=31984.000000 z=32712.000000
Distance from origin: 56341.217896

```

## Notes on Large File Processing

- The file is not read entirely into memory.
- mmap() maps the file into virtual memory and loads pages on demand.
- This approach is efficient and scalable for files hundreds of megabytes or larger.
- Progress output helps verify that the program is running correctly and not stalled.
