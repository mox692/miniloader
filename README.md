miniloader is a simple toy application loader.
It is for Linux and x86_64 arch.

### How to work
0. By using [chlfg](https://github.com/mox692/miniloader/blob/master/chflg.c), change miniloader's  
   segment permissions(currently all segments are set RWX). 
1. miniloader creates memory space by mmap to which binary loaded.
2. Load binary to it by memcpy.
3. Then, JMP to loaded binary's entry address.
4. Loaded binary starts.

### Test run
In author's environment, there operation successed.

```
$ ./chflg miniloader

$ ./miniloader loaded
```
By using debuging tool like gdb,  
you can check that miniloader jmp to loaded's instruction.

