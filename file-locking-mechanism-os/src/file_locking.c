#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void write_file(int fd, int user) {
    struct flock lock;

    /* Configure an exclusive write lock for the entire file */
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("User%d is trying to acquire lock...\n", user);

    /* Wait until the lock becomes available */
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Lock failed");
        exit(1);
    }

    printf("User%d acquired lock and is writing...\n", user);

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "User%d wrote to file\n", user);

    write(fd, buffer, strlen(buffer));

    /* Simulate work while holding the lock */
    sleep(2);

    printf("User%d releasing lock...\n", user);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
}

int main(void) {
    int fd = open("shared_file.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);

    if (fd < 0) {
        perror("File open error");
        return 1;
    }

    /* Create three user processes */
    for (int i = 1; i <= 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            write_file(fd, i);
            close(fd);
            exit(0);
        } else if (pid < 0) {
            perror("fork failed");
            close(fd);
            return 1;
        }
    }

    /* Wait for all child processes */
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    close(fd);
    return 0;
}
