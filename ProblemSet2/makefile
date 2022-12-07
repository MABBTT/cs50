# the compiler to use
CC = clang
  
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS= -Wall
  
#files to link:
LDLIBS = -lcs50

all: $(TARGET)
$(TARGET): $(TARGET).c ; $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDLIBS)

