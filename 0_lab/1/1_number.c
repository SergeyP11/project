#include <stdio.h>
#include <string.h>
#include <math.h>

int num=0, res=0;
double intPart;
char arr[2];
void text(void);
int check_flag(char array[2]);
int code_for_h(int num);
int code_for_p(int num);
int code_for_s(int num);
int code_for_e(int num);
int code_for_a(int num);
int code_for_f(int num);


int main() {
    text();
    if (scanf("%d", &num) == 1 && num > 0) {
        if (scanf("%s", arr) == 1){
            res = check_flag(arr);
            if (res==1){
                if (strcmp(arr, "-h") == 0) {
                    code_for_h(num);
                } else if (strcmp(arr, "-p") == 0) {
                    code_for_p(num);
                } else if (strcmp(arr, "-s") == 0) {
                    code_for_s(num);
                } else if (strcmp(arr, "-e") == 0) {
                    code_for_e(num);
                } else if (strcmp(arr, "-a") == 0) {
                    code_for_a(num);
                } else if (strcmp(arr, "-f") == 0) {
                    code_for_f(num);
                }     
            }
            else{
                printf("You have entered a non-existent flag\n");
            }
        }  
    }
    else{
        printf("You didn't enter a positive integer\n");
    }
return 0;
}

void text(){
printf("Enter a positive integer and a flag defining the action with this number. The flag starts with the symbol “-”\n");
printf("-h output to the console numbers within 100, multiples of the entered. If there are none – display the corresponding message;\n");
printf("-p determine whether the entered number is simple or composite;\n");
printf("-s divides the number into separate digits and output each digit separately, separating them with a space;\n");
printf("-e output numbers from 1 to 10 to the console, raising them to all powers from 1 to a given number (for this flag, the limit on the entered number works: it should be no more than 10);\n");
printf("-a sums all numbers from 1 to the specified number inclusive;\n");
printf("-f calculates the factorial of the entered number.\n");
}

int check_flag(char array[2]){
    int check=0;
    char flag_h[]= "-h", flag_p[] = "-p", flag_s[] = "-s", flag_e[] = "-e", flag_a[] = "-a", flag_f[] = "-f";
    if (strcmp(array, flag_h) == 0 || strcmp(array, flag_p) == 0 || strcmp(array, flag_s) == 0 || strcmp(array, flag_e) == 0 || strcmp(array, flag_a) == 0 || strcmp(array, flag_f) == 0){
        check=1;
    } else{
        check=0;
    }
    return check;
}

int code_for_h(int num){
    int found = 0; 
    printf("Numbers within 100, multiples %d:\n", num);
    for (int i = 1; i <= 100; i++) {
        if (i % num == 0) {
            printf("%d ", i);
            found = 1; 
        }
    }
    if (!found) {
        printf("No multiples within 100 were found.\n");
    }
    printf("\n");
    return 0;
}
int code_for_p(int num){
    int result=0, count=0;
    if(num <= 1) {
        result=0;
    }
    int sqrt_num = sqrt(num);
    for(int i=2; i<=sqrt_num; i++) {
        if(num % i == 0) {
            result=1;
            count+=1;
        }
        if (count<1) {
        result=0;
        }
    }
    if(result==0) {
        printf("%d is a prime number\n", num);
    } else {
        printf("%d is a composite number\n", num);
    }
    printf("\n");
    return 0;
}
int code_for_s(int num){
    printf("Separated digits: ");
    while (num > 0) {
        int digit = num % 10; 
        printf("%d ", digit);
        num /= 10; 
    }
    printf("\n");
    return 0;
}
int code_for_e(int num){
    if (num > 10) {
        printf("A number greater than 10 has been entered.\n");
        return 0;
    }
    for (int i = 1; i <= 10; i++) {
        printf("%d:\t", i);
        for (int j = 1; j <= num; j++) {
            printf("%.0f\t", pow(i, j));
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
int code_for_a(int num){
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        sum += i;
    }
    printf("The sum of all numbers from 1 to %d equal to %d\n", num, sum);
    printf("\n");
    return 0;
}
int code_for_f(int num){
    long long factor= 1;
    for (int i = 1; i <= num; i++) {
        factor *= i;
        printf("Factorial of number %d equal to %d\n", num, factor);
    }
    printf("Factorial of number %d equal to %d\n", num, factor);
    printf("\n");
    return 0;
}