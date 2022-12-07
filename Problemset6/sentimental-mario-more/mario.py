from cs50 import get_int

# TODO
while True:
    h = get_int("Height - Positive integer between 1 and 8: ")
    if h <= 8 and h >= 1:
        break

for i in range(h):
    print((h - i - 1) * " ", end="")
    print("#" * (i + 1), end="  ")
    print("#" * (i + 1))
