#include "elf64.h"
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern unsigned long int __TextStart;

int MAX_SIZE = 4194304;

int main(int argc, char** argv) 
{
    if(argc != 2) {
        printf("invalid argc: %d\n", argc);
        return -1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        printf("Err: %s\n", strerror(errno));
        return -1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        printf("Err: %s\n", strerror(errno));
        return -1;
    }

    if(sb.st_size > MAX_SIZE) {
        printf("permitted max byte is %d, but got %ld\n", MAX_SIZE, sb.st_size);
        return -1;
    }

    void *head = mmap(NULL, sb.st_size, PROT_WRITE | PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0);
    printf("ad: %p\n", head);

    if(head == MAP_FAILED) {
        printf("mapfile err.\n");
        return -1;
    }

    Elf64_Ehdr *ehdr = (Elf64_Ehdr*)(head);

    // Addr calculation
    unsigned long int address = (unsigned long int)&__TextStart;
    memcpy((void*)address, ehdr, sb.st_size);
    char *ent = (char*)(ehdr->e_entry);
    printf("__TextStart addr: 0x%08lx\n", address);
    printf("%s's ent addr: 0x%p\n", argv[1],ent);

    // TODO: hard code
    unsigned long int ent_addr = 1530 + address;

    printf("Addr to which jump: 0x%08lx\n",ent_addr);

    // jmp to binary
    asm volatile ("nop;");
    asm volatile ("lea 11(%rip), %r15");
    asm volatile ("pushq %r15");
    asm volatile ("jmp *%0"::"r"((void*)ent_addr));
    asm volatile ("nop;");

    printf("load done.\n");
    return 0;
}