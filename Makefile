CC:= gcc
CCFLAGS := #

TARGETS	:= main
UTILS := utils.c stdtypes.c graphics.c sdl/sdlgraphics.c
MAINS := $(addsuffix .o, $(TARGETS))
OBJS := utils.o stdtypes.o # additional .o
LIBS := -pthread -lSDL #-w -lSDL2

all: #$(TARGETS)
	gcc -g main.c $(UTILS) -o main $(LIBS)

utils.o: 
	$(CC) $(CCFLAGS) -c utils.c
stdtypes.o:
	$(CC) $(CCFLAGS) -c stdtypes.c

clean:
	rm -f $(TARGETS) $(OBJS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJS)) %.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)
