#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[10000];
    memset(buffer, 'a', sizeof(buffer));

    if (pipe(pipefd) == -1) return 1;

    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);

    while (1) {
        ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
        if (count == -1) break;
        printf("записано байтів: %zd\n", count);
        if (count < sizeof(buffer)) {
            printf("частковий запис\n");
            break;
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
