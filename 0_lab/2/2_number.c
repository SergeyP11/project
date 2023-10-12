#include <stdio.h>
#include <string.h>
#include <math.h>

char arr[2];
int num=0, res=0;
void text(void);
int check_flag(char array[2]);
int code_for_q();
int code_for_m();
int code_for_t();

int main() {
    text();
    if (scanf("%s", arr) == 1){
        res = check_flag(arr);
        if (res==1){
            if (strcmp(arr, "-q") == 0) {
                code_for_q(num);
            } else if (strcmp(arr, "-m") == 0) {
               code_for_m(num);
               }
            else if (strcmp(arr, "-t") == 0) {
               code_for_t(num);
               }
        }
        else{
            printf("You have entered a non-existent flag\n");
            }
    }
    else{
            printf("You have entered a non-existent flag\n");
            }
return 0;
}

void text(){
printf("Enter a flag. The flag starts with the symbol “-”\n");
printf("-q the three parameters entered are the coefficients of the quadratic equation, it is necessary to derive solutions to this equation for all possible parameter values;\n");
printf("-m must specify two non-zero integers, then determine whether the first number is a multiple of the second;\n");
printf("-t reads 3 non-zero values and checks whether they can be sides of a right triangle.\n\n");
}

int check_flag(char array[2]){
    int check=0;
    char flag_q[]= "-q", flag_m[] = "-m", flag_t[] = "-t";
    if (strcmp(array, flag_q) == 0 || strcmp(array, flag_m) == 0 || strcmp(array, flag_t) == 0){
        check=1;
    } else{
        check=0;
    }
    return check;
}

int code_for_q(){
    double a, b, c; 
    double discriminant, x1, x2; 
    printf("Enter the coefficients of the quadratic equation:\n");
    printf("a = ");
    if (scanf("%lf", &a)==0) {
        printf("You entered no digits\n");
        return 0;
    }
    printf("b = ");
     if (scanf("%lf", &b)==0) {
        printf("You entered no digits\n");
        return 0;
    }
    printf("c = ");
     if (scanf("%lf", &c)==0) {
        printf("You entered no digits\n");
        return 0;
    }
    discriminant = b*b - 4*a*c;
    if (discriminant > 0) {
        x1 = (-b + sqrt(discriminant)) / (2*a);
        x2 = (-b - sqrt(discriminant)) / (2*a);
        printf("The equation has two solutions:\n");
        printf("x1 = %.2lf\n", x1);
        printf("x2 = %.2lf\n", x2);
    }
    else if (discriminant == 0) {
        x1 = -b / (2*a);
        printf("The equation has one solutions:\n");
        printf("x = %.2lf\n", x1);
    }
    else {
        printf("The equation has no solutions.\n");
    }
    return 0;
}

int code_for_m(){
    int num1, num2;
    printf("Enter two non-zero integers: ");
    if (scanf("%d %d", &num1, &num2)==0) {
        printf("You entered no digits\n");
        return 0;
    }
    if (num1 % num2 == 0) {
        printf("%d multiple %d\n", num1, num2);
    } else {
        printf("%d not multiple %d\n", num1, num2);
    }
    return 0;
}
int code_for_t(){
    float a, b, c;
    printf("Enter the value of the first side: ");
    if (scanf("%f", &a)==0) {
        printf("You entered no digits\n");
        return 0;
    }
    printf("Enter the value of the second side: ");
    if (scanf("%f", &b)==0) {
        printf("You entered no digits\n");
        return 0;
    }
    printf("Enter the value of the third side: ");
    if (scanf("%f", &c)==0) {
        printf("You entered no digits\n");
        return 0;
    }
    if (a > 0 && b > 0 && c > 0) {
        if (a * a == b * b + c * c || b * b == a * a + c * c || c * c == a * a + b * b) {
            printf("These values can be the sides of a right triangle.\n");
        } else {
            printf("These values cannot be sides of a right triangle.\n");
        }
    } else {
        printf("The values of the sides of the triangle must be non-zero.\n");
    }
    return 0;
}