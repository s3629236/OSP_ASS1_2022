OBJS	= main.o task1.o task2.o task3.o task4.o task5.o
SOURCE	= main.c task1.c task2.c task3.c task4.c task5.c
HEADER	= main.h task1.h task2.h task3.h task4.h task5.h
OUT	= Assignment1.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

task1.o: task1.c
	$(CC) $(FLAGS) task1.c -std=c99

task2.o: task2.c
	$(CC) $(FLAGS) task2.c -std=c99

task3.o: task3.c
	$(CC) $(FLAGS) task3.c -std=c99

task4.o: task4.c
	$(CC) $(FLAGS) task4.c -std=c99

task5.o: task5.c
	$(CC) $(FLAGS) task5.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)