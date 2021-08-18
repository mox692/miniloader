TARG=miniloader
OBJS=miniloader.o
LDSCR=text_space.lds

CHFLG=chflg
CHFLG_OBJS=chflg.o

all: $(TARG) $(CHFLG)

$(TARG): $(OBJS) $(LDSCR)
	gcc -o $@ -T $(LDSCR) $(OBJS)

$(CHFLG): $(CHFLG_OBJS) elf64.h
	gcc -o $@ $^

clean:;
	rm *.o $(TARG)
