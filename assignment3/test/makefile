#===========================Makefile================================#

CC=gcc
CFLAGS= -Wall -std=c99 -g
OBJS = mark4.o BST.o genPlane.o

all: assignment

# assignment: $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o mark3
#
# mark3.o: genPlane.h BST.h plane.h
# 	$(CC) $(CFLAGS) -c mark3.c

assignment: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o mark4

mark4.o: genPlane.h BST.h plane.h
	$(CC) $(CFLAGS) -c mark4.c


assignment3.o: genPlane.h BST.h plane.h
	$(CC) $(CFLAGS) -c assignment3.c

genPlane.o: genPlane.c genPlane.h plane.h
	$(CC) $(CFLAGS) -c genPlane.c

BST.o: BST.c BST.h plane.h
	$(CC) $(CFLAGS) -c BST.c

plane.o: plane.h
	$(CC) $(CFLAGS) -c plane.h

clean:
	rm -rf *.o
