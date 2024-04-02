#include <stdio.h>
#include <stdlib.h> // 사용되지 않는다.
void main() {
  int **x;  // 이중 포인터 선언. 단 초기화를 하지 않았기에 쓰레기값이 저장되어있음.
  printf("sizeof(x) = %lu\n", sizeof(x)); // x 의 크기 출력, 포인터인 x는 포인터 크기인 8바이트 출력
  printf("sizeof(*x) = %lu\n", sizeof(*x)); // *x의 크기를 출력, 이중 포인터이므로 여전히 포인터 크기 8바이트 출력
  printf("sizeof(**x) = %lu\n", sizeof(**x)); // **x의 크기를 출력, int형이기에 4바이트 출력
  printf("[----- [이규민] [2021039002] -----]\n");
  //for 2nd commit
}