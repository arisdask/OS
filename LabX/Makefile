# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files
SOURCES = exe1_fork3times.c exe2_pipe.c exe3_kill.c exe4_file.c exe5_add.c

# Object files
OBJECTS = exe1_fork3times exe2_pipe exe3_kill exe4_file exe5_add

# Default target
all: $(OBJECTS)

# Targets for each file
exe1_fork3times: exe1_fork3times.c
	$(CC) $(CFLAGS) -o $@ $<

exe2_pipe: exe2_pipe.c
	$(CC) $(CFLAGS) -o $@ $<

exe3_kill: exe3_kill.c
	$(CC) $(CFLAGS) -o $@ $<

exe4_file: exe4_file.c
	$(CC) $(CFLAGS) -o $@ $<

exe5_add: exe5_add.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove compiled files
clean:
	rm -f $(OBJECTS)
