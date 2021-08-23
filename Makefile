TARG=miniloader
OBJS=miniloader.o
LDSCR=text_space.lds

CHFLG=chflg
CHFLG_HDR=elf64.h
CHFLG_OBJS=chflg.o

LOADED=loaded
LOADED_OBJ=loaded.o

all: $(TARG) $(CHFLG) $(LOADED)

$(TARG): $(OBJS) $(LDSCR)
	gcc -o $@ -T $(LDSCR) $(OBJS)
	./$(CHFLG) $(TARG)

$(CHFLG): $(CHFLG_OBJS) $(CHFLG_HDR)
	gcc -o $@ $^ 

$(LOADED): $(LOADED_OBJ)
	gcc -o $@ $^

clean:;
	rm *.o $(TARG)
