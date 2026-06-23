memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
![alt text](image.png)

![alt text](image-1.png)

concurrent programming
https://mohitmishra786.github.io/chessman/2024/09/24/Implementing-Threads-in-C-Designing-Concurrent-Programs-with-pthreads.html

Debugging
valgrind --tool=helgrind ./philo 4 410 200 200
valgrind --tool=drd ./philo 4 410 200 200
valgrind --track-origins=yes ./philo 4 410 200 200

cc -fsanitize=thread -g *.c -o philo_tsan
./philo_tsan 4 410 200 200


philo with 200 410 200 200 10

[+] Testing philo with 199 610 200 200 10
[+] Philosopher 1 ate 1 times
[-] Test #15 Failed: Philosopher 1 has not eaten enough times or has eaten too many times
[-] Test #15 Failed: Failed with 199 610 200 200 10 
[+] Test #15 Valgrind Test Succeeded !
[+] Test #15 Helgrind Test Succeeded !


[+] Testing philo with 199 610 200 80 10
[+] Philosopher 1 ate 1 times
[-] Test #16 Failed: Philosopher 1 has not eaten enough times or has eaten too many times
[-] Test #16 Failed: Failed with 199 610 200 80 10 
[+] Test #16 Valgrind Test Succeeded !
[+] Test #16 Helgrind Test Succeeded !


[+] Testing philo with 200 410 200 80 10
[+] Philosopher 1 ate 1 times
[-] Test #17 Failed: Philosopher 1 has not eaten enough times or has eaten too many times
[-] Test #17 Failed: Failed with 200 410 200 80 10 
[+] Test #17 Valgrind Test Succeeded !
[+] Test #17 Helgrind Test Succeeded !
