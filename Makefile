CC:= gcc
CCFLAGS := #

TARGETS	:= main
MAINS := $(addsuffix .o, $(TARGETS))
OBJS := utils.o stdtypes.o # additional .o
LIBS := -pthread -lSDL2 #-w -lSDL2

all: $(TARGETS)

utils.o: 
	$(CC) $(CCFLAGS) -c utils.c
stdtypes.o:
	$(CC) $(CCFLAGS) -c stdtypes.c

clean:
	rm -f $(TARGETS) $(OBJS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJS)) %.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)
