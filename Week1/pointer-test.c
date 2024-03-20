#include <stdio.h>

int main() {
  int i, *p;  // 정수 자료형인 i와 정수형 포인터인 p를 선언한다.
  i = 10;
  printf("value of i = %d\n", i); // 정수 자료형 i의 값은 앞에서 선언한 10이 나온다.
  printf("address of i = %p\n", &i);  // i가 저장된 메모리 위치(주소)를 알려준다.
  printf("value of p = %p\n", p); // 포인터 p의 값(향하고 있는 주소)을(를) 알려준다.
  printf("address of p = %p\n", &p);  // 포인터 p가 저장된 위치를 알려준다.
  p = &i; // 포인터 p를 i의 주소로 향하게 바꾼다.

  printf("\n\n----- after p = &i ------------\n\n");
  printf("value of p = %p\n", p);  // p의 값은 10행의 코드에 의해 i의 주소를 나타낸다.
  printf("address of p = %p\n", &p);  // p의 저장된 위치는 변함없다.
  printf("dereferencing *p = %d\n", *p);  
  // 포인터 p는 i가 위치하는 주소를 가리키고 있으므로 i의 값 10이 나온다.
  // 10행에서 p = &i 이므로 역참조하면 *p = i가 된다.
  return 0;
}