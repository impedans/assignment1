CC := gcc
CFLAGS := -g
LINKER_FLAGS := -lm


# make all
.PHONY : all
all : app

# Intemediate object file
app.o : main.c filters.c sensor.c
	$(CC) $(CLFLAGS) $(LINKER_FLAGS) main.c filters.c sensor.c -o app.o

# make clean
.PHONY : clean
clean :
	rm -rf app
	rm -rf app.o
