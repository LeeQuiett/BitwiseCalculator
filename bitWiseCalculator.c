#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ������ �� ��� �������� �Է¹��� ����ü */
typedef struct RESULT {
    int result;
    int remainder;
} RESULT;

/* 10���� ���ڸ� 2������ ��ȯ�ϰ�, ������ 0���� ä��� �Լ� */
void decimalToBinary(int inputDecimal, char* binaryArray, int size) {
    memset(binaryArray, '0', size);
    binaryArray[size - 1] = '\0';  //���ڿ� ���� �� ���� �߰�

    int index = size - 2;           //���ڿ� ���� �� ���� ������ ä�� �ε���

    while (inputDecimal > 0 && index >= 0) {                //2���� to 10���� ������ �ڵ�� �ű�
        binaryArray[index--] = (inputDecimal % 2) + '0';    //'0'�� ���ؼ� ASCII�� �ٲ� ��� ������
        inputDecimal /= 2;
    }
}

/* 10���� ���ڸ� �Է¹޴� �Լ� */
int setInputDecimal(int sequence) {
    int inputDecimal = 0;
    printf("%d ��° ������ 10���� ���ڸ� �Է��ϼ���: ", sequence);
    scanf("%d", &inputDecimal);
    return inputDecimal;
}

/* ��Ʈ �����ڸ� �̿��� '����'�ϴ� �Լ� */
int bitWiseAdd(int decimal1, int decimal2) {
    int sum = 0;
    int carry = 0;

    while (decimal2 != 0) {
        sum = decimal1 ^ decimal2;           // XOR ������ ���� ���� ����
        carry = (decimal1 & decimal2) << 1;  // AND ����� ���� ����Ʈ�� ���� ĳ�� ���
        decimal1 = sum;
        decimal2 = carry;
    }

    return decimal1;
}

/* ��Ʈ �����ڸ� �̿��� '�y��' �ϴ� �Լ� */
int bitWiseSub(int decimal1, int decimal2) { 
    int result = 0;
    decimal2 = ~decimal2;
    decimal2 += 1;

    result = bitWiseAdd(decimal1, decimal2); //�ʰ��� �ڸ����� ���� ������ �ʾƵ� �Լ� ��� �������� int �ڷ����� ũ�� �̻����� ����Ʈ�Ǹ� ������
}

/* ��Ʈ �����ڸ� �̿��� '����' �ϴ� �Լ� */
int bitWiseMultiplication(int decimal1, int decimal2) {
    int result = 0;

    int count = 0;          //� ���� ��Ʈ �߿��� 1�� �� ���� �ִ��� �� ����
    int number = decimal2;
    while (number > 0) {     //counter�� 1�̸� 2�� n���̴�.
        if ((number & 1) == 1) {
            count++;
        }
        number >>= 1;
    }

    number = decimal2;
    int nCounter = 0;
    if (count == 1) {        //decimal2�� 2�� n���̶��
        while (number > 1) { //n�� ���ؼ� nCounter�� �����Ѵ�.
            number /= 2;
            nCounter++;
        }
        result = (decimal1 << nCounter);
    }
    else {
        result = decimal1 * decimal2; //2�� n���� �ƴ� ��쿣 ��Ģ�����ڸ� ����Ѵ�.
    }
    return result;
}

/* ��Ʈ �����ڸ� �̿��� '������' �ϴ� �Լ� */
RESULT bitWiseDivision(int decimal1, int decimal2) {
    RESULT result = { 0,0 };

    int count = 0;          //� ���� ��Ʈ �߿��� 1�� �� ���� �ִ��� �� ����
    int number = decimal2;
    while (number > 0) {    //counter�� 1�̸� 2�� n���̴�.
        if ((number & 1) == 1) {
            count++;
        }
        number >>= 1;
    }

    number = decimal2;
    int nCounter = 0;
    if (count == 1) {        //decimal2�� 2�� n���̶��
        while (number > 1) { //n�� ���ؼ� nCounter�� �����Ѵ�.
            number /= 2;
            nCounter++;
        }
        result.result = (decimal1 >> nCounter);
    }
    else {
        result.result = decimal1 / decimal2;    //2�� n���� �ƴ� ��쿣 ��Ģ�����ڸ� ����Ѵ�.
        result.remainder = decimal1 % decimal2;
    }
    return result; //��� �������� ������ ����ü�� ��ȯ�Ѵ�.
}

int main() {
    int inputDecimal1 = 0, inputDecimal2 = 0;   //10������ �Է¹��� ����
    char inputOperator;                         //�����ڸ� �Է¹��� ����

    char binaryArray1[33];                      //�� ���ڸ� ����� �迭 ũ��
    char binaryArray2[33];
    char resultArray[33] = { 0 };               //��Ʈ������ ������� �������� ������ �迭
    int result = 0;                             //��� ����� ������ ����

    while (1) {
        inputDecimal1 = setInputDecimal(1);
        putchar('\n');
        printf("�����ڸ� �Է��ϼ���: ");
        scanf("%*c%c", &inputOperator);
        putchar('\n');
        inputDecimal2 = setInputDecimal(2);

        switch (inputOperator) {
        case '+':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            result = bitWiseAdd(inputDecimal1, inputDecimal2);
            decimalToBinary(result, resultArray, 32);
            printf("ù ��° input�� 2���� ��ȯ ���: %s\n", binaryArray1);
            printf("�� ��° input�� 2���� ��ȯ ���: %s\n", binaryArray2);
            printf("��Ʈ���� ����� 2���� ��ȯ ���: %s\n", resultArray);
            printf("��Ʈ���� ����� 10���� ǥ��: %d\n\n", result);
            break;
        case '-':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            result = bitWiseSub(inputDecimal1, inputDecimal2);
            decimalToBinary(result, resultArray, 32);
            printf("ù ��° input�� 2���� ��ȯ ���: %s\n", binaryArray1);
            printf("�� ��° input�� 2���� ��ȯ ���: %s\n", binaryArray2);
            printf("��Ʈ���� ����� 2���� ��ȯ ���: %s\n", resultArray);
            printf("��Ʈ���� ���: %d\n\n", result);
            break;
        case '*':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            result = bitWiseMultiplication(inputDecimal1, inputDecimal2);
            decimalToBinary(result, resultArray, 32);
            printf("ù ��° input�� 2���� ��ȯ ���: %s\n", binaryArray1);
            printf("�� ��° input�� 2���� ��ȯ ���: %s\n", binaryArray2);
            printf("��Ʈ���� ����� 2���� ��ȯ ���: %s\n", resultArray);
            printf("��Ʈ���� ���: %d\n\n", result);
            break;
        case '/':
            decimalToBinary(inputDecimal1, binaryArray1, 32);
            decimalToBinary(inputDecimal2, binaryArray2, 32);
            printf("ù ��° input�� 2���� ��ȯ ���: %s\n", binaryArray1);
            printf("�� ��° input�� 2���� ��ȯ ���: %s\n", binaryArray2);
            RESULT result = bitWiseDivision(inputDecimal1, inputDecimal2);
            printf("��Ʈ���� ���: ��:%d, ������:%d\n\n", result.result, result.remainder);
            break;
        default:
            printf("�������� �ʴ� �������Դϴ�.\n\n");
            break;
        }
    }

    return 0;
}
