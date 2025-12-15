# Process IPC

## Description

Process IPC is a C program demonstrating process creation and inter-process communication (IPC) in Linux using fork() and unnamed pipes. The program creates a child process, sends a string from the parent to the child, the child processes the string (reverses it), and sends the result back. Detailed console output shows PIDs of both processes. This project is useful for learning Linux process management, IPC mechanisms, and debugging concurrent programs.

## Key Features:

- Creation of child processes using fork().
- Communication between parent and child using pipes.
- Demonstration of data processing in child processes.
- Console logging of process IDs (PID) and communication flow.
- Pause with sleep() to allow runtime inspection of processes using ps or pstree.

## Compilation
```bash
gcc process_ipc.c -o process_ipc
```

## Usage
Run the program in the terminal
```bash
 ./process_ipc 
```

Example Output 
```bash
Parent (PID: 6021) created child (PID: 6022)
Parent (PID: 6021) sleeping 20 seconds. Check with ps...
Child (PID: 6022, PPID: 6021) started
Child (PID: 6022) sleeping 20 seconds. 
Check with ps...
Parent (PID: 6021) sending data: Hello from Parent         
Child (PID: 6022) received data: Hello from Parent
Child (PID: 6022) processed data
Parent (PID: 6021) received result: tneraP morf olleH
```

## Checking Processes

While the program is sleeping, you can open a new terminal and run 
```bash 
ps -o pid,ppid,stat,cmd -C process_ipc
```

Expected output
```bash
 PID  PPID  STAT     CMD
6021  4890   S  ./process_ipc   ← parent
6022  6021   S  ./process_ipc   ← child
```

# Thread Synchronization

## Description

Thread Synchronization is a C program demonstrating multithreading, race conditions, and thread synchronization in Linux using pthread and mutexes.

The program creates multiple threads (4 by default) that access a shared global counter. It first demonstrates a race condition when threads update the counter without synchronization, producing an incorrect result. Then it applies a mmutex to synchronize access, ensuring the correct final value. This project is useful for learning thread management, race conditions, and synchronization mechanisms in Linux.

## Key Features

- Creation of multiple threads using pthread_create().
- Access to a shared resource (global counter) from multiple threads.
- Demonstration of race condition without synchronization.
- Correct synchronization using pthread mutex.
- Logging of thread IDs and work progress.
- Verification of threads in runtime using ps -L or top -H.

## Compilation
```bash
gcc thread_sync.c -o thread_sync -pthread
```

## Usage

Run the program in the terminal
```bash
./thread_sync
```

Example Output Running 
```bash
Running WITHOUT synchronization...
Expected: 4000000
Actual:   2374912  ← incorrect due to race condition

Running WITH mutex synchronization...
Expected: 4000000
Actual:   4000000  ← correct
```

## Checking Processes

While the program is running, open a new terminal and run 
```bash
ps -L -o pid,tid,stat,cmd -C thread_sync
```

Expected output
```bash
 PID   TID  STAT     CMD
7123  7123   Sl   ./thread_sync
7123  7124   Sl   ./thread_sync
7123  7125   Sl   ./thread_sync
7123  7126   Sl   ./thread_sync
```

- PID – same for all threads 
- TID – unique thread ID 
- STAT – state of thread 
- CMD – command name This demonstrates that all threads belong to the same process but have unique IDs.
