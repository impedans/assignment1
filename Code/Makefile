# Compiler flags
CC := gcc
CFLAGS := -Wall
LINKER_FLAGS := -lm


# make all
.PHONY : all
all : app


# Compilation rule
app : main.c filters.c sensor.c
	$(CC) main.c sensor.c filters.c qsr.c $(LINKER_FLAGS) -o app
	@echo; echo $@ compiled; echo

# make clean
.PHONY : clean
clean :
	rm -rf app
	rm -rf app.o
