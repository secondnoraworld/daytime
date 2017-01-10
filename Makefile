#
#  Makefile
#

EXES    = daytime daytimed Daytime.class

CC      = gcc
CFLAGS  =
#CFLAGS  = -DNOREUSEADDR
        
all:	$(EXES)


Daytime.class: Daytime.java
	javac Daytime.java

clean: 
	rm -f $(EXES) *.o a.out core *~

.SUFFIXES: .o .c .java
.c.o:
	$(CC) $(CFLAGS) $<
