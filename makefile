CC := gcc
FLAGS := -Wall -pedantic -pedantic-errors -Wextra 

PROJDIR := $(realpath .)
SRCDIR := $(PROJDIR)/src
OBJDIR := $(PROJDIR)/obj
BINDIR := $(PROJDIR)/bin

TARGET := todoer


all: $(BINDIR)/$(TARGET)

$(BINDIR)/todoer: $(OBJDIR)/todoer.o $(OBJDIR)/data.o $(OBJDIR)/main.o 
	mkdir -p $(BINDIR)
	$(CC) $(FLAGS) -o $(BINDIR)/todoer $(OBJDIR)/main.o $(OBJDIR)/todoer.o $(OBJDIR)/data.o

$(OBJDIR)/todoer.o: $(SRCDIR)/todoer.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c -o $(OBJDIR)/todoer.o $(SRCDIR)/todoer.c

$(OBJDIR)/data.o: $(SRCDIR)/data.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c -o $(OBJDIR)/data.o $(SRCDIR)/data.c

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c -o $(OBJDIR)/main.o $(SRCDIR)/main.c

go: $(BINDIR)/todoer.exe
	$(BINDIR)/todoer.exe

clean: 
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(TARGET)
