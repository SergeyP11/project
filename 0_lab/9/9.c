#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void decimalToBase(long num, int base);

int main(int argc, char *argv[]) {
    char *curString = malloc(sizeof(long)); // Выделение памяти
    int base; // система счисления
    int Flag = 0; // Если всё будет введено правильно, флаг станет единицей, начнутся вычисления
    long curNum, maxNum = 0; // Минимум по модулю - ноль
    
    // Ввод системы счисления
    printf("Enter the number system from 2 to 36:\n");
    scanf("%d", &base);
    // Проверка на ошибку ввода
    if(base<2 || base>36){
        printf("You entered the wrong number system\n");
        return 1;
    }

    // Запрос чисел
    while(strcmp(curString, "Stop"))
    {
        printf("\nEnter a number in the specified number system (Input Stop to exit):\n");
        scanf("%s", curString);
        if(!strcmp(curString, "Stop"))
        {
            break;
        } 

        // Преобразование в десятичную сс текущей строки, второй параметр не используется поэтому Null
        curNum = strtol(curString, NULL, base); 
        
        // Возможная ошибка в вводе
        if(curNum == 0) 
        {
            printf("You entered an incorrect value or zero. Try again\n\n");
            continue;
        }
        // Все проверки пройдены, флаг делаем единицей
        Flag=1;
        // Поиск максимума
        if (labs(curNum) >= labs(maxNum)) 
        {
            maxNum = curNum;
        }
    }
    // Освобождение
    free(curString);
    // Печать чисел в другой сс
    if (Flag)
    {
        printf("\nMax number in 10 notation: %ld\n", maxNum);
        printf("This number in 9 notation: ");
        decimalToBase(maxNum, 9);
        
        printf("\nThis number in 18 notation: ");
        decimalToBase(maxNum, 18);

        printf("\nThis number in 27 notation: ");
        decimalToBase(maxNum, 27);
        
        printf("\nThis number in 36 notation: ");
        decimalToBase(maxNum, 36);
        printf("\n");
    }
    else printf("\nYou have not entered any values");
    return 0;
}

void decimalToBase(long num, int base) {
    char result[100];
    int index = 0;
    char sign[1];
    if (num<0)  // Проверка на отрицательность
    {
        sign[0] = '-';
    }
    num = labs(num);
    while (num > 0) {
        int remainder = num % base;
        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
        num = num / base;
    }
    printf("%c", sign[0]);
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
}
