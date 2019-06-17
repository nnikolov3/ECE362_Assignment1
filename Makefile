#Nikolay Nikolov
#ECE362
#Assignment 1
#01/17/2019

#This is the makefile for the first assignment 
#it compiles the file main.c where the main program is run


#The compiler: gcc
CC = gcc


#compiler flags:
# -g adds debugging information to the executable file
#  -Wall turns on most, but not all , compiler warnings

TARGET = main

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)



