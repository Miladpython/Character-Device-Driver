#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[256] = {0};

    fd = open("/dev/mychardev", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    printf("Reading from driver...\n");
    read(fd, buf, sizeof(buf));
    printf("Kernel says: %s\n", buf);

    printf("Writing to driver...\n");
    write(fd, "Hello Kernel!", 14);

    close(fd);
    return 0;
}

