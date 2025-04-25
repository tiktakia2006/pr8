#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.bin", O_RDONLY);
    unsigned char buffer[4];

    lseek(fd, 3, SEEK_SET);
    read(fd, buffer, 4);

    for (int i = 0; i < 4; i++)
        printf("%d ", buffer[i]);

    printf("\n");
    close(fd);
    return 0;
}
