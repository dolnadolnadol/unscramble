#include <stdio.h>

int romanInt(char c) {
    switch(c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int toInt(char* Roman) {
    int result = 0;
    int i = 0;

    while (Roman[i]) {
        int current = romanInt(Roman[i]);
        int next = romanInt(Roman[i+1]);

        if (next > current) {
            result += (next - current);
            i += 2;
        } else {
            result += current;
            i += 1;
        }
    }
    return result;
}

int main() {
    char Roman[100];
    printf("Enter a Roman numeral: ");
    scanf("%s", Roman);
    
    int num = toInt(Roman);
    printf("Integer representation: %d\n", num);

    return 0;
}
