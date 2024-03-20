#include <stdio.h>
int main() {
  // 다양한 데이터 타입별 변수 선언.
  char charType;
  int integerType;
  float floatType;
  double doubleType;
  // 선언한 각 데이터 타입의 변수를 sizeof()을 이용하여 데이터의 크기를 알아본다.
  printf("Size of char: %ld byte\n", sizeof(charType)); // >> 1 byte
  printf("Size of int: %ld bytes\n", sizeof(integerType));  // 4 bytes
  printf("Size of float: %ld bytes\n", sizeof(floatType));  // 4 bytes
  printf("Size of double: %ld bytes\n", sizeof(doubleType));  // 8 bytes
  printf("-----------------------------------------\n");
  // 데이터 타입을 sizeof()을 이용하여 데이터의 크기를 알아본다.
  printf("Size of char: %ld byte\n", sizeof(char));   // 위와 동일
  printf("Size of int: %ld bytes\n", sizeof(int));
  printf("Size of float: %ld bytes\n", sizeof(float));
  printf("Size of double: %ld bytes\n", sizeof(double));
  printf("-----------------------------------------\n");
  // 각 데이터 타입별 포인터의 크기를 sizeof()을 이용하여 크기를 알아본다.
  printf("Size of char*: %ld byte\n", sizeof(char*)); // 강의 내용 그대로 포인터는 8 bytes의 크기를 가진다.
  printf("Size of int*: %ld bytes\n", sizeof(int*));
  printf("Size of float*: %ld bytes\n", sizeof(float*));
  printf("Size of double*: %ld bytes\n", sizeof(double*));
  
  printf("[----- [이규민] [2021039002] -----]");
  return 0;
}