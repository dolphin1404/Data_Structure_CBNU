#include <stdio.h>
void print_one(int *ptr, int rows); // stack 영역에 함수 선언
int main() {
  int one[] = {0, 1, 2, 3, 4};  // 정수형 배열 선언 및 초기화
  printf("one = %p\n", one);  // 배열의 시작 주소 출력
  printf("&one = %p\n", &one);  // 주소 출력 = 위 코드와 동일
  printf("&one[0] = %p\n", &one[0]);  // one 배열의 첫 번째 요소의 주소 = one 배열의 시작 주소
  printf("\n");
  printf("------------------------------------\n");
  printf(" print_one(&one[0], 5) \n");  
  printf("------------------------------------\n");
  print_one(&one[0], 5);  // print_one 함수 호출한다. 인자값으로 one 배열의 시작주소, n
  printf("------------------------------------\n");
  printf(" print_one(one, 5) \n");
  printf("------------------------------------\n");
  print_one(one, 5);  // print_one 함수 호출, 배열 이름은 그대로 주소를 의미한다. 따라서 값은 동일하게 출력될 것이다.
  printf("[----- [이 규 민] [2021039002] -----]");
  return 0;
}
void print_one(
    int *ptr,
    int rows) { /* print out a one-dimensional array using a pointer */
  int i;
  printf("Address \t Contents\n");
  for (i = 0; i < rows; i++) printf("%p \t %5d\n", ptr + i, *(ptr + i));  // 반복문을 통해 배열 주소와 저장된 값을 \t을 통해 칸을 구분하고 %5d를 통해 자릿수를 설정했다.
  printf("\n");
}