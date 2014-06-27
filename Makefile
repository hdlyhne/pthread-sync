#
#  comp 3231  lab excersises -- week3
#
#	author  : Alex Sayle <alexs@cse>
#	created : Mon Aug 11 14:40:23 EST 2003
#	modified: Mon Aug 11 14:55:23 EST 2003	
#	version : 1.0
#
#

# clean out suffix list
.SUFFIXS:

# we're interested in .c .o files.
.SUFFIXS: .c .o

CC	 	:=gcc
STDCFLAGS 	:=  -O2 -Wall  -pipe -D__USE_GNU

DEBUGFLAGS	:= -D_DEBUGG_
INCFLAGS	:=

LIBS		:= -lpthread

CFLAGS		:=$(STDCFLAGS) $(DEBUGFLAGS) $(INCFLAGS) 

ALL_TARGETS	:= mutex deadlock
OBJ_THREAD	:=$(ALL_TARGETS:%=%.o)

TMPFILES	:= *~ *.o


# override implicit rules
.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) 

.o:
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)



all : $(ALL_TARGETS)


mutex.o: mutex.c
deadlock.o: deadlock.c

#
# cleaning up 
#
clean:
	@echo --- cleaning up...
	rm -f  $(TARGETS) $(TMPFILES) $(ALL_TARGETS)


