#include <stdio.h>
#define MAX_SIZE 100  // 상수 선언

// 실수형 함수 sum1, sum2, sum3 생성 stack 영역에 변수 선언
float sum1(float list[], int);
float sum2(float *list, int);
float sum3(int n, float *list);

float input[MAX_SIZE], answer;  // 전역변수 생성 stack 영역

int i;  // for문용
void main(void) {
  for (i = 0; i < MAX_SIZE; i++) input[i] = i;  // 호출 시 input(=&input[0])은 주소를 담고 > 주소가 sum 함수의 list에 복사
  /* for checking call by reference */
  printf("--------------------------------------\n");
  printf(" sum1(input, MAX_SIZE) \n");
  printf("--------------------------------------\n");
  printf("input \t= %p\n", input);  // input의 시작 주소
  answer = sum1(input, MAX_SIZE); // sum1(list[], int)에서 매개변수(파라미터)가 배열이기에 input은 주소값
  printf("The sum is: %f\n\n", answer); // sum1의 결과

  printf("--------------------------------------\n");
  printf(" sum2(input, MAX_SIZE) \n");
  printf("--------------------------------------\n");
  printf("input \t= %p\n", input);  // input의 시작 주소
  answer = sum2(input, MAX_SIZE); // sum2 함수 호출
  printf("The sum is: %f\n\n", answer); // sum2의 결과

  printf("--------------------------------------\n");
  printf(" sum3(MAX_SIZE, input) \n");
  printf("--------------------------------------\n");
  printf("input \t= %p\n", input);  // input의 시작 주소
  answer = sum3(MAX_SIZE, input);   // sum3 함수 호출
  printf("The sum is: %f\n\n", answer); // sum3 결과
  printf("[----- [이 규 민] [2021039002] -----]");
}

// sum1은 배열 받아 합 계산하는 함수
float sum1(float list[], int n) {
  printf("list \t= %p\n", list);  // 인자 list[]은 배열의 시작주소를 뜻함 >> input의 시작 주소
  printf("&list \t= %p\n\n", &list);  //sum1 함수에 전달된 포인터 변수의 주소를 출력 / list 배열의 시작 주소와 다르다.

  int i;
  float tempsum = 0;
  for (i = 0; i < n; i++) tempsum += list[i]; // 배열의 요소를 순회하며 합을 계산한다.
  return tempsum;
}

float sum2(float *list, int n) {    // sum2은 포인터를 받아 합 계산하는 함수
  printf("list \t= %p\n", list);  // 포인터가 가리키는 주소 출력
  printf("&list \t= %p\n\n", &list); // 함수에 전달된 포인터 변수의 주소를 출력

  int i;
  float tempsum = 0;
  for (i = 0; i < n; i++) tempsum += *(list + i); 
  // 포인터를 사용하여 배열의 요소를 순회하며 합을 계산
  return tempsum;
}

/* stack variable reuse test*/
// sum3 함수는 배열 크기와 포인터를 받아서 합을 계산하는 함수
float sum3(int n, float *list) {
  printf("list \t= %p\n", list);
  printf("&list \t= %p\n\n", &list);  // sum3 함수에 전달된 포인터 변수의 주소 출력 : list 배열의 시작 주소와 다름.

  int i;
  float tempsum = 0;
  for (i = 0; i < n; i++) tempsum += *(list + i);
  // 포인터를 사용하여 배열의 요소를 순회하며 합을 계산
  return tempsum;
}