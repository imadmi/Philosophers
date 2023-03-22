# Philo

Threading in programming refers to the concept of dividing a processor into smaller sections, with each section having its own thread. These threads can perform tasks concurrently, and can give out output at the same time. The priority of each thread can be assigned as needed, with certain threads given priority over others. For instance, a user interface (UI) thread can be given high priority to ensure that the UI is always responsive, while a background thread can be assigned lower priority to perform tasks such as retrieving data from the internet.

Threading is an essential part of programming, as it allows for efficient use of resources and can improve the user experience. However, it is important to be aware of the potential issues that can arise when working with multiple threads. One common issue is that foreground threads cannot communicate with background threads, which can result in crashes if code is executed on the wrong thread.

To avoid these issues, it is important to carefully manage threads and ensure that each task is executed on the appropriate thread. For example, data retrieval can be performed on a background thread, and the retrieved data can then be passed to the foreground thread for display on the UI. By properly managing threads, developers can ensure that their applications are responsive and stable.

threads are used to execute multiple concurrent operations within a single program. However, when multiple threads access a shared resource simultaneously, it can cause unpredictable behavior and race conditions. To prevent this, mutual exclusion (mutex) is used, which ensures that only one thread can access a shared resource at a time.

A mutex is a synchronization object that acts like a lock, allowing only one thread to access a shared resource at a time. When a thread acquires a mutex, any other thread that attempts to access the same mutex will block until the mutex is released. This ensures that no more than one thread at a time is accessing a resource.

However, deadlocks can occur when a thread attempts to lock a mutex that it has already locked. To avoid this, programmers must be careful when locking and unlocking mutexes to ensure that a program cannot be in a situation where it attempts to lock the same mutex it has already locked.

In C, to use a mutex, you create a pthread_mutex_t object and initialize it using the pthread_mutex_init() function. You can then lock the mutex using pthread_mutex_lock() and unlock it using pthread_mutex_unlock().

To illustrate the use of mutexes in C, a simple program is provided that counts to 100,000 using 12 threads. Without mutexes, the program produces random results because multiple threads are trying to increment the same variable simultaneously. However, when mutexes are used, only one thread can access the variable at a time, producing consistent and expected results.

It is important to note that mutexes should be locked for the minimum amount of time possible to avoid blocking other threads. Additionally, mutexes are only necessary when multiple threads are accessing the same resource simultaneously.

**`pthread_mutex_init**(`”the address of the mutex object to be initialized”, ”a pointer to a struct that specifies the attributes of the mutex”`)`

The function returns zero on success and a non-zero error code on failure. After the mutex is initialized, it can be used to synchronize access to shared resources or critical sections of code using the **`pthread_mutex_lock`** and **`pthread_mutex_unlock`** functions.

**`gettimeofday(`”**a pointer to a struct timeval object that will hold the current time **”,  “**a struct timezone variable that can be set to **`NULL`** to indicate that the timezone information is not needed**”`)`**

The **`struct timeval`** object is defined in the **`sys/time.h`** header file and contains two fields: **`tv_sec`** and **`tv_usec`**. The **`tv_sec`** field holds the number of seconds since the Unix epoch (January 1, 1970), and the **`tv_usec`** field holds the number of microseconds within the current second. Together, these fields represent the current time and date with high precision.

1- **`* 1000`** is used to convert **`tv_sec`** value from sec to milliseconds

2- `/ 1000` is used to convert **`tv_usec`** value from microseconds to milliseconds

The **`gettimeofday()`** function returns 0 on success and -1 on failure.

The **`pthread_create()`** function is used to create a new thread in a multi-threaded program. It takes four arguments:

1. A pointer to a **`pthread_t`** variable that will be used to store the thread ID of the new thread.
2. A pointer to a **`pthread_attr_t`** variable that specifies the attributes of the new thread. This argument can be NULL, in which case default attributes are used.
3. A pointer to a function that will be executed by the new thread. This function must have a single **`void*`** argument and return a **`void*`**.
4. An argument that will be passed to the function specified in the previous argument.

The **`pthread_create()`** function returns zero on success, or an error code on failure.

`pthread_join(`"the thread you want to wait for" , pointer to void saves the return value of the joined thread can be of any data type`)`

Joining threads is a mechanism for synchronizing the execution of threads in a program. When a thread is joined, the program waits until that thread completes its execution before moving on to the next task. This ensures that all threads complete their work before the program terminates.

In other words, joining threads allows you to wait for the completion of all threads before proceeding with the rest of the program
