CC = clang
CFLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow
LDLIBS = -lcs50 -lm -lcrypt -speller.o -speller.c - dictionary.o -dictionary.c
all: $(TARGET)
$(TARGET): $(TARGET).c ; $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDLIBS)
