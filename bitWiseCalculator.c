#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 나눗셈 후 몫과 나머지를 입력받을 구조체 */
typedef struct RESULT {
    int result;
    int remainder;
} RESULT;

/* 10진수 숫자를 2진수로 변환하고, 왼쪽을 0으로 채우는 함수 */
void decimalToBinary(int inputDecimal, char* binaryArray, int size) {
    memset(binaryArray, '0', size);
    binaryArray[size - 1] = '\0';  //문자열 끝에 널 문자 추가

    int index = size - 2;           //문자열 끝의 널 문자 전부터 채울 인덱스

    while (inputDecimal > 0 && index >= 0) {                //2진수 to 10진수 계산법을 코드로 옮김
        binaryArray[index--] = (inputDecimal % 2) + '0';    //'0'을 더해서 ASCII로 바꿔 출력 쉽게함
        inputDecimal /= 2;
    }
}

/* 10진수 숫자를 입력받는 함수 */
int setInputDecimal(int sequence) {
    int inputDecimal = 0;
    printf("%d 번째 정수형 10진수 숫자를 입력하세요: ", sequence);
    scanf("%d", &inputDecimal);
    return inputDecimal;
}

/* 비트 연산자를 이용해 '덧셈'하는 함수 */
int bitWiseAdd(int decimal1, int decimal2) {
    int sum = 0;
    int carry = 0;

    while (decimal2 != 0) {
        sum = decimal1 ^ decimal2;           // XOR 연산을 통해 덧셈 수행
        carry = (decimal1 & decimal2) << 1;  // AND 연산과 왼쪽 시프트를 통해 캐리 계산
        decimal1 = sum;
        decimal2 = carry;
    }

    return decimal1;
}

/* 비트 연산자를 이용해 '뻴셈' 하는 함수 */
int bitWiseSub(int decimal1, int decimal2) { 
    int result = 0;
    decimal2 = ~decimal2;
    decimal2 += 1;

    result = bitWiseAdd(decimal1, decimal2); //초과한 자릿수는 따로 버리지 않아도 함수 계산 과정에서 int 자료형의 크기 이상으로 쉬프트되며 버려짐
}

/* 비트 연산자를 이용해 '곱셈' 하는 함수 */
int bitWiseMultiplication(int decimal1, int decimal2) {
    int result = 0;

    int count = 0;          //어떤 수의 비트 중에서 1이 한 개만 있는지 셀 변수
    int number = decimal2;
    while (number > 0) {     //counter가 1이면 2의 n승이다.
        if ((number & 1) == 1) {
            count++;
        }
        number >>= 1;
    }

    number = decimal2;
    int nCounter = 0;
    if (count == 1) {        //decimal2가 2의 n승이라면
        while (number > 1) { //n을 구해서 nCounter에 저장한다.
            number /= 2;
            nCounter++;
        }
        result = (decimal1 << nCounter);
    }
    else {
        result = decimal1 * decimal2; //2의 n승이 아닐 경우엔 사칙연산자를 사용한다.
    }
    return result;
}

/* 비트 연산자를 이용해 '나눗셈' 하는 함수 */
RESULT bitWiseDivision(int decimal1, int decimal2) {
    RESULT result = { 0,0 };

    int count = 0;          //어떤 수의 비트 중에서 1이 한 개만 있는지 셀 변수
    int number = decimal2;
    while (number > 0) {    //counter가 1이면 2의 n승이다.
        if ((number & 1) == 1) {
            count++;
        }
        number >>= 1;
    }

    number = decimal2;
    int nCounter = 0;
    if (count == 1) {        //decimal2가 2의 n승이라면
        while (number > 1) { //n을 구해서 nCounter에 저장한다.
            number /= 2;
            nCounter++;
        }
        result.result = (decimal1 >> nCounter);
    }
    else {
        result.result = decimal1 / decimal2;    //2의 n승이 아닐 경우엔 사칙연산자를 사용한다.
        result.remainder = decimal1 % decimal2;
    }
    return result; //몫과 나머지를 저장한 구조체를 반환한다.
}

int main() {
    int inputDecimal1 = 0, inputDecimal2 = 0;   //10진수를 입력받을 변수
    char inputOperator;                         //연산자를 입력받을 변수

    char binaryArray1[33];                      //널 문자를 고려한 배열 크기
    char binaryArray2[33];
    char resultArray[33] = { 0 };               //비트연산의 계산결과를 이진수로 저장할 배열
    int result = 0;                             //계산 결과를 저장한 변수

    while (1) {
        inputDecimal1 = setInputDecimal(1);
        putchar('\n');
        printf("연산자를 입력하세요: ");
        scanf("%*c%c", &inputOperator);
        putchar('\n');
        inputDecimal2 = setInputDecimal(2);

        switch (inputOperator) {
        case '+':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            result = bitWiseAdd(inputDecimal1, inputDecimal2);
            decimalToBinary(result, resultArray, 32);
            printf("첫 번째 input의 2진수 변환 결과: %s\n", binaryArray1);
            printf("두 번째 input의 2진수 변환 결과: %s\n", binaryArray2);
            printf("비트연산 결과의 2진수 변환 결과: %s\n", resultArray);
            printf("비트연산 결과의 10진수 표현: %d\n\n", result);
            break;
        case '-':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            result = bitWiseSub(inputDecimal1, inputDecimal2);
            decimalToBinary(result, resultArray, 32);
            printf("첫 번째 input의 2진수 변환 결과: %s\n", binaryArray1);
            printf("두 번째 input의 2진수 변환 결과: %s\n", binaryArray2);
            printf("비트연산 결과의 2진수 변환 결과: %s\n", resultArray);
            printf("비트연산 결과: %d\n\n", result);
            break;
        case '*':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            result = bitWiseMultiplication(inputDecimal1, inputDecimal2);
            decimalToBinary(result, resultArray, 32);
            printf("첫 번째 input의 2진수 변환 결과: %s\n", binaryArray1);
            printf("두 번째 input의 2진수 변환 결과: %s\n", binaryArray2);
            printf("비트연산 결과의 2진수 변환 결과: %s\n", resultArray);
            printf("비트연산 결과: %d\n\n", result);
            break;
        case '/':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            printf("첫 번째 input의 2진수 변환 결과: %s\n", binaryArray1);
            printf("두 번째 input의 2진수 변환 결과: %s\n", binaryArray2);
            RESULT result = bitWiseDivision(inputDecimal1, inputDecimal2);
            printf("비트연산 결과: 몫:%d, 나머지:%d\n\n", result.result, result.remainder);
            break;
        default:
            printf("지원하지 않는 연산자입니다.\n\n");
            break;
        }
    }

    return 0;
}
