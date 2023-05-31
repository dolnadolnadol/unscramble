import sys

def count_letter_frequencies():
    frequencies = {chr(i): 0 for i in range(ord('a'), ord('z')+1)}
    for line in sys.stdin:
        line = line.lower()
        for char in line:
            if char.isalpha():
                frequencies[char] += 1
    return frequencies

def print_histogram(frequencies):
    max_frequency = max(frequencies.values())
    for i in range(max_frequency, 0, -1):
        line = ""
        for char in frequencies:
            if frequencies[char] >= i:
                line += "* "
            else:
                line += "  "
        print(line)
    print("a b c d e f g h i j k l m n o p q r s t u v w x y z")

frequencies = count_letter_frequencies()
print_histogram(frequencies)
