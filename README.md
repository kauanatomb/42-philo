# philo

## 🧠 Objective
This project is part of the 42 core curriculum and aims to simulate the Dining Philosophers Problem — a classic concurrency challenge — using threads or processes and synchronization primitives in C.

It was developed using only the allowed standard C library and focuses on mastering:
- Concurrent programming
- Thread and process creation/management
- Synchronization with mutexes and semaphores
- Deadlock avoidance and starvation prevention
- Manual memory management and clean resource handling

## 🧩 Features
Mandatory version (threads + mutexes):
- Creates one thread per philosopher
- Synchronized access to forks using `pthread_mutex_t`
- Dedicated monitor thread checks if a philosopher has died
- Precise timing and sleeping control with `usleep` and timestamps
- No data races or memory leaks (verified with Valgrind)

Bonus version (processes + semaphores):
- Uses processes instead of threads for philosophers
- Global synchronization with named semaphores (`sem_open`)
- Accurate and centralized death detection using a monitor
- Clean termination via `kill()` + `waitpid()` on failure
- Prevents multiple `died` messages using a dedicated semaphore

---

## ⚙️ Compilation

Make targets:

```bash
make        # builds philo and philo_bonus
make clean  # removes object files
make fclean # removes object files and binaries
make re     # rebuilds everything from scratch
```
## 🚀 Usage
Mandatory version and bonus:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Example:

```bash
./philo 5 800 200 200
```
Bonus version:
Example:

```bash
./philo_bonus 5 800 200 200 3
```
> Each philosopher tries to eat 3 times, and the program exits once all are done or one dies.

## 🧩 Challenges Faced
- Designing non-blocking synchronization to prevent deadlocks
- Managing precise sleep and timing in multithreaded code
- Handling orphaned processes and cleanup on early exit
- Ensuring correctness of output with concurrent print operations
- Debugging issues specific to process-based concurrency (e.g., zombie processes)

## ✅ Key Learnings & Solutions
- Gained deep understanding of classical synchronization problems
- Applied mutexes and semaphores in a real concurrency scenario
- Built a clean system for launching, monitoring, and terminating threads/processes
- Improved debugging and resource cleanup practices in concurrent C applications
