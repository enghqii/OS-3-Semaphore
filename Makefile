
TARGETS := test dining

SEM_OBJS    := sem.o
TEST_OBJS   := test.o
DINING_OBJS := dining.o

OBJS := $(SEM_OBJS) $(TEST_OBJS) $(DINING_OBJS)

CC := gcc

CFLAGS += -D_REENTRANT -D_LIBC_REENTRANT -D_THREAD_SAFE
CFLAGS += -Wall
CFLAGS += -Wunused
CFLAGS += -Wshadow
CFLAGS += -Wdeclaration-after-statement
CFLAGS += -Wdisabled-optimization
CFLAGS += -Wpointer-arith
CFLAGS += -Wredundant-decls
CFLAGS += -g -O2

LDFLAGS += -lpthread

%.o: %.c
	$(CC) -o $*.o $< -c $(CFLAGS)

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm -f $(TARGETS) $(OBJS) *~ *.bak core*

$(OBJS): sem.h

test: $(SEM_OBJS) $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

dining: $(SEM_OBJS) $(DINING_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

