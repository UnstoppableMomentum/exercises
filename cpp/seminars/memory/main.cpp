#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>

#define N (128 * 1024 * 1024)

int main(int argc, char *argv[])
{ 
    int l = atoi(argv[1]);
    int fd = open("big", O_RDWR);
    char *p = static_cast<char*>(mmap(NULL, N, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0));
    for(char *pp = p; pp -p <  l*1024 * 1024; pp += 4096) {
        char x = *pp;
    }

    for (;;);
    return 0;
}
