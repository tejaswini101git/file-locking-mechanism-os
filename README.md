# File Locking Mechanism Simulation11

A C-based Operating Systems PBL project that demonstrates **file locking, process synchronization, mutual exclusion, and safe concurrent access**.

## Overview

The project simulates three users/processes attempting to write to the same shared file. Each process must acquire an exclusive write lock before entering the critical section.

The implementation uses:

- `fork()` — creates child processes representing users
- `fcntl()` — applies and waits for file locks
- `wait()` — waits for child processes to finish
- `O_APPEND` — appends each user's output to the shared file

Only one process can hold the write lock at a time. Other processes wait until the lock is released.

## Project Structure

```text
file-locking-mechanism-os/
├── README.md
├── .gitignore
├── src/
│   └── file_locking.c
└── docs/
    └── OS_PBL_Report.docx
```

## How It Works

1. The program opens/creates `shared_file.txt`.
2. Three child processes are created using `fork()`.
3. Each child attempts to acquire an exclusive write lock.
4. `fcntl(..., F_SETLKW, ...)` makes a process wait if another process owns the lock.
5. The process writes its message to the shared file.
6. A short delay simulates work inside the critical section.
7. The process releases the lock.
8. Waiting processes proceed one at a time.

Example file output:

```text
User1 wrote to file
User2 wrote to file
User3 wrote to file
```

The exact order can vary because process scheduling is controlled by the operating system.

## Requirements

This program uses POSIX/Unix system calls (`fork`, `fcntl`, `unistd`, `sys/wait.h`), so it should be compiled in a Linux/Unix environment or WSL rather than a standard native Windows C environment.

Required tools:

- GCC
- Linux/Unix or WSL

## Compile and Run

```bash
gcc src/file_locking.c -o file_locking
./file_locking
```

After execution, inspect:

```bash
cat shared_file.txt
```

Run again to observe additional appended entries.

## Concepts Demonstrated

- Mutual exclusion
- Critical sections
- Process creation
- Process synchronization
- File locking
- Blocking synchronization
- Safe resource sharing
- Race-condition prevention

## Academic Project

This repository contains the implementation and the original Operating Systems PBL report.
