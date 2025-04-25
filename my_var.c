#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define FILE_NAME "testfile.txt"
#define SIZE 1024

void write_using_write() {
    int fd = open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    char buffer[SIZE];
    memset(buffer, 'A', SIZE);
    write(fd, buffer, SIZE);
    close(fd);
}

void write_using_mmap() {
    int fd = open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    ftruncate(fd, SIZE);

    char *map = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    memset(map, 'B', SIZE);
    msync(map, SIZE, MS_SYNC);
    munmap(map, SIZE);
    close(fd);
}

int main() {
    write_using_write();
    printf("File written using write().\n");

    write_using_mmap();
    printf("File written using mmap().\n");

    return 0;
}
