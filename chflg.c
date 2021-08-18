#include "elf64.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Invalid argc, %d\n", argc);
    }
    char *filename = argv[1];

    int fd = open(filename, O_RDWR);
    if(fd == -1) {
        printf("Err: %s\n", strerror(errno));
    }

    struct stat sb;
    if(fstat(fd, &sb) == -1) {
        printf("Err: %s\n", strerror(errno));
    }

    void* head = mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if((int)head == -1) {
        printf("Err: %s\n", strerror(errno));
        return -1;
    }

    Elf64_Ehdr *ehdr = (Elf64_Ehdr*)(head);

    for(int i = 0; i < ehdr->e_phnum; i++) {
        Elf64_Phdr *phdr = (Elf64_Phdr*)(((char*)ehdr + ehdr->e_phoff + (i * ehdr->e_phentsize)));
        phdr->p_flags = 0x7;
    }

    printf("write done\n");
    return 0;
}