#include <stdio.h>
int main() {
  int i;  // 정수형 변수 i를 선언
  int *ptr; // 정수형 포인터 ptr 선언, 초기화는 하지 않음 > 쓰레기값 저장
  int **dptr; // 정수형 이중 포인터 dptr 선언, 초기화는 하지 않음 > 쓰레기값 저장

  i = 1234; // i에 값 1234 할당

  // 포인터 ptr에 i 주소 값 넣기 이전의 프로세스
  printf("[checking values before ptr = &i] \n"); 
  printf("value of i == %d\n", i);  // i의 값은 1234가 출력된다.
  printf("address of i == %p\n", &i); // i의 주소를 loc1이라 하겠다.
  printf("value of ptr == %p\n", ptr);  // ptr 값을 할당하지 않았으므로 쓰레기값이 저장되어있다.
  printf("address of ptr == %p\n", &ptr); // ptr의 주소를 loc2이라 하겠다.
  ptr = &i; /* ptr is now holding the address of i */

  // 포인터 ptr에 i 주소 값 넣은 이후의 프로세스
  printf("\n[checking values after ptr = &i] \n");
  printf("value of i == %d\n", i);  // i의 값은 변하지 않는다
  printf("address of i == %p\n", &i); // loc1
  printf("value of ptr == %p\n", ptr);  // ptr = &i 이후 이므로 i의 주소인 loc1를 가리킨다.
  printf("address of ptr == %p\n", &ptr); // loc2는 변하지 않는다
  printf("value of *ptr == %d\n", *ptr);  // *는 역참조 연산자로 *ptr은 ptr이 가리키는 주소 loc1에 저장된 값 1234를 가리킨다.
  dptr = &ptr; /* dptr is now holding the address of ptr */
  // 이중 포인터 dptr에 포인터 ptr 주소 값 넣은 이후의 프로세스
  printf("\n[checking values after dptr = &ptr] \n");
  printf("value of i == %d\n", i);  // i의 값은 변하지 않는다
  printf("address of i == %p\n", &i); // 위와 동일하다.
  printf("value of ptr == %p\n", ptr);  
  printf("address of ptr == %p\n", &ptr);
  printf("value of *ptr == %d\n", *ptr);
  printf("value of dptr == %p\n", dptr);  // dptr은 24번줄에서 주소연산자를 이용하여 &ptr를 받아왔기에 ptr의 주소 loc2를 받는다.
  printf("address of dptr == %p\n", &dptr); // dptr의 주소를 loc3이라 하겠다.
  printf("value of *dptr == %p\n", *dptr);  // 역참조연산자를 이용한 *dptr은 ptr의 값을 나타낸다. ptr의 값은 현재 주소 loc1이다.
  printf("value of **dptr == %d\n", **dptr);  // 이중으로 역참조 연산자를 이용한 **dptr은 i의 값을 나타낸다.
  
  *ptr = 7777; /* changing the value of *ptr */
  printf("\n[after *ptr = 7777] \n"); // i의 값이 7777로 바뀌었다.
  printf("value of i == %d\n", i);  // *ptr은 i의 value를 가리키므로 7777로 출력된다.
  printf("value of *ptr == %d\n", *ptr);  // 마찬가지이다.
  printf("value of **dptr == %d\n", **dptr);  // 이중포인터 **dptr이 가리키는 것은 결국 i이다.

  **dptr = 8888; /* changing the value of **dptr */ 
  printf("\n[after **dptr = 8888] \n"); // **dptr도 위와 동일하게 i의 value를 가리킨다.
  printf("value of i == %d\n", i);
  printf("value of *ptr == %d\n", *ptr);
  printf("value of **dptr == %d\n", **dptr);  // 따라서 i, *ptr, **dptr 모두 8888을 나타낸다.

  return 0;
}
  // 추가로 해본 것들
  /*
  *dptr = 9999;
  printf("\n[after *dptr = 9999] \n"); 
  printf("value of i == %d\n", i);
  printf("value of *ptr == %d\n", *ptr);
  printf("value of **dptr == %d\n", **dptr);  
    printf("[----- [이규민] [2021039002] -----]");
  */