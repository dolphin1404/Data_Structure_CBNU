#include <stdio.h>
#include <stdlib.h>
void main() {
  int list[5];  // 정수형 배열 list 선언, 초기화를 안했기 때문에 쓰레기값이 저장됨.
  int *plist[5];  // 포인터 배열 plist 선언
  list[0] = 10; // list[0]에 10 저장
  list[1] = 11; // list[1]에 11 저장
  plist[0] = (int *)malloc(sizeof(int));  // plist 첫번째에 동적 메모리 (int 크기만큼) 할당

  printf("list[0] \t= %d\n", list[0]);  // list[0] 값 10 출력
  printf("list \t\t= %p\n", list);  // 배열 list 시작주소 출력
  printf("&list[0] \t= %p\n", &list[0]);  // 주소 연산자를 이용하여 list[0]의 위치 출력 = 11번 코드
  printf("list + 0 \t= %p\n", list + 0);  // list(=시작주소) + 0 (int) = list
  
  printf("list + 1 \t= %p\n", list + 1);  // list[0] + 1 * 4 (int 4 bytes)
  printf("list + 2 \t= %p\n", list + 2);  // list[0] + 2 * 4 (int 4 bytes)
  printf("list + 3 \t= %p\n", list + 3);  // list[0] + 3 * 4 (int 4 bytes)

  printf("list + 4 \t= %p\n", list + 4);  // list[0] + 4 * 4 (int 4 bytes)
  printf("&list[4] \t= %p\n", &list[4]);  // 주소 연산자를 이용하여 list[4]의 위치 출력 = list + 4 * 4 bytes
  free(plist[0]); // 동적 할당한 메모리 해제
  printf("[----- [이 규 민] [2021039002] -----]");
}