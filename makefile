CC := gcc
FLAGS := -Wall -pedantic -pedantic-errors -Wextra 

PROJDIR := $(realpath .)
SRCDIR := $(PROJDIR)/src
OBJDIR := $(PROJDIR)/obj
BINDIR := $(PROJDIR)/bin

TARGET := todoer


all: $(BINDIR)/$(TARGET)

$(BINDIR)/todoer: $(OBJDIR)/todoer.o $(OBJDIR)/main.o
	$(CC) $(FLAGS) -o $(BINDIR)/todoer $(OBJDIR)/main.o $(OBJDIR)/todoer.o

$(OBJDIR)/todoer.o: $(SRCDIR)/todoer.c
	$(CC) $(FLAGS) -c -o $(OBJDIR)/todoer.o $(SRCDIR)/todoer.c

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(FLAGS) -c -o $(OBJDIR)/main.o $(SRCDIR)/main.c

go: $(BINDIR)/todoer.exe
	$(BINDIR)/todoer.exe

clean: 
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(TARGET)
