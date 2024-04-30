/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */
#include<stdio.h>
#include<stdlib.h>
#include<windows.h> // 추가 : 콘솔창 초기화를 위해
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;  // 값
	struct Node* link;  // 다음으로 연결된 리스트
} listNode;

typedef struct Head {
	struct Node* first; // 리스트의 헤더 즉 리스트의 첫 번째를 뜻함.
} headNode;

// 추가 : 리스트노드의 사이즈를 미리 선언
int sizeofLNode = sizeof(listNode);

/* 함수 리스트 */
// 원래 코드였던 int 함수들을 모두 void 자료형을 바꾸었다.
// 리턴 값이 필요없는 함수들이였기에 그에 맞게 코드를 수정했다.
headNode* initialize(headNode* h);
void freeList(headNode* h);

void insertFirst(headNode* h, int key);
void insertNode(headNode* h, int key);
void insertLast(headNode* h, int key);

void deleteFirst(headNode* h);
void deleteNode(headNode* h, int key);
void deleteLast(headNode* h);
void invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command; // 이용자로부터 입력받을 커맨드 값
	int key; // 이후 함수에서 사용될, 값을 찾고 수정하기 위한 입력 값을 저장하는 변수
	headNode* headnode=NULL; // 현 헤더는 비어있다. 일종의 초기화.
  headnode = initialize(headnode); // 반복문 시작하기 전 미리 초기화
  printf("[----- [이규민] [2021039002] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
    //메인 메뉴
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q'); // q, Q를 입력하기전까지 반복

	return 1;
}

headNode* initialize(headNode* h) { // 헤더 초기화

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL; // temp라는 헤더를 선언하여 NULL를 향하게 함.
  system("cls"); // 추가 : 콘솔창 초기화
	return temp; // temp라는 헤더를 반환
}

void freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;
  // 헤더의 첫 번째를 받음
	listNode* prev = NULL;
  // 삭제할 노드를 null로 초기화
	while(p != NULL) { // 노드 p가 헤더에서 시작해서 리스트의 끝에 도달할 때까지 반복
		prev = p; // 삭제할 노드에 현재 p를 가리킴
		p = p->link; // 현재 p에 다음 노드를 가리킴
		free(prev); // 삭제할 노드를 free해서 동적할당을 해제함
	}
	free(h); // 반복이 종료되면 헤더도 해제
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
void insertFirst(headNode* h, int key) {

	listNode* firstNode = (listNode*)malloc(sizeofLNode); // 처음 선언했던 sizeofLNode를 이용하여 동적할당함
	firstNode->key = key; // 새로 만든 노드의 key 값에 매개변수로 받은 key값을 넣음.

	firstNode->link = h->first; // 원래 헤더가 가리키는 노드를 새로 만든 노드의 링크에 넣음
	h->first = firstNode; // 헤더의 처음을 새로 만든 노드로 지정
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
void insertNode(headNode* h, int key) {
	listNode *newNode = (listNode*)malloc(sizeofLNode);
	// 삽입할 리스트노드 동적할당, 헤드노드의 사이즈를 받는 것이 아님.
	newNode->key = key; // 매개변수로 받은 key 값을 새 노드의 key값에 넣음
	newNode->link = NULL; // 아직 주소가 미정임.
	// headNode의 first가 비어있거나, 헤더가 가리키는 노드의 키 값이 매개변수로 받은 키 값보다 같거나 큰 경우
	if(h->first == NULL || h->first->key >= key){ 
		newNode->link = h->first; // 새 노드의 링크는 헤더의 처음을 가리킨다.
		h->first = newNode; //헤더의 첫번째는 새로 선언한 새 노드이다.
	}
	else {
		listNode *now = h->first; // 조건을 만족하는 노드를 찾기 위해 선언한 리스트노드
      // 순환문에 사용될 노드 now를 헤더가 가리키는 첫 번째노드에서 시작하게 한다.
			//위 조건과 반대되는 조건으로 조건식이 false일때까지 반복
			//now->link가 null이고, now->link_>key 가 매개변수로 받은 key보다 커야한다.
		while (now->link != NULL && now->link->key < key ) now = now->link; //링크를 타고 확인
		newNode->link = now->link; // 반복이 종료된 이후 검색 완료한 노드 now의 링크를 새로운 노드의 링크에 넣는다.
		now->link = newNode; // now의 링크에 새로운 노드를 넣는다.
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
// 전체적인 구조는 insertNode와 유사. 대신 key값을 비교하지 않음.
void insertLast(headNode* h, int key) {  // 리스트의 마지막에 노드 추가
	listNode *newNode = (listNode*)malloc(sizeofLNode); // 새로운 노드 동적할당
	newNode->key = key; // 새로운 노드의 key값에 매개변수로 받은 key값을 넣는다.
	newNode->link = NULL; // 새로운 노드의 링크는 NULL로 초기화

	if(h->first == NULL) h->first = newNode;  // 리스트가 비어있을 경우
	else{
		listNode *now = h->first; // 리스트노드 now를 선언하고, 헤더가 가리키는 첫 번째 노드를 가리키게 한다.
		while (now->link != NULL) now = now->link; // now의 링크가 NULL이 될 때까지 반복
		now->link = newNode; // now의 링크에 새로운 노드를 넣는다.
	}
}


/**
 * list의 첫번째 노드 삭제
 */
void deleteFirst(headNode* h) { 
	if(h->first == NULL){printf("Headernode is NULL!! Plz Check your node\n"); return;} // 리스트가 비어있을 경우 리턴

	listNode *temp = h->first;  // 지울 노드를 temp에 저장
	h->first = h->first->link; // 헤더의 첫번째를 두번째로 변경

	free(temp); // 지울 노드를 free해서 동적할당을 해제한다.

}


/**
 * list에서 key에 대한 노드 삭제
 * 지정된 key 값을 가진 노드를 찾아 리스트에서 삭제
 * 해당 key를 가진 노드가 없다면 return으로 빠져나온다.
 * 첫 번째 노드가 해당 key를 가진 경우도 생각한다.
 */
void deleteNode(headNode* h, int key) {
	listNode *now = h->first; // 비교할 리스트노드
	listNode *prev = NULL; // 이전 노드를 가리킬 리스트노드
  if(h->first == NULL){printf("Headernode is NULL!! Plz Check your node\n"); return;} // 리스트가 비어있을 경우 리턴
  // now가 NULL이 아니고, now의 key값이 매개변수로 받은 key값과 같지 않을 때까지 반복
	while ( now != NULL && now->key != key){ 
		prev = now;
		now = now->link;
	}
  // now가 NULL이면 해당 key를 가진 노드가 없다는 것이므로 리턴
	if(now == NULL) return; // 못 찾았을 경우 리턴

	if(prev == NULL ) h->first = now->link; // 첫 번째 노드가 해당 key를 가진 경우
  else prev->link = now->link;
  // 이전 노드의 링크에 현재 노드의 링크를 넣는다.
	free(now); // 현재 노드를 free해서 동적할당을 해제
}

/**
 * list의 마지막 노드 삭제
 * 리스트에 노드가 없을 때와, 하나 남았을 때의 경우를 생각했다.
 */
void deleteLast(headNode* h) { 
	if(h->first == NULL){printf("Headernode is NULL!! Plz Check your node\n"); return;} // 리스트가 비어있을 경우 리턴
	if(h->first->link == NULL){ // 노드가 하나 남았을 때. first만 남았을 경우.
		free(h->first); // 헤더의 first를 free해서 동적할당을 해제
		h->first = NULL; // 헤더의 first를 NULL로 초기화
		return;
	}
	listNode *now = h->first; // now를 선언하고, 헤더가 가리키는 첫 번째 노드를 가리킴
  // now의 링크가 NULL이 아닐 때까지 반복
	while (now->link && now->link->link != NULL) now = now->link;
	free(now->link); 
	now->link = NULL;  // now의 링크를 NULL로 초기화
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
void invertList(headNode* h) {
	listNode *prev = NULL; // 이전 노드를 가리킬 노드를 null로 초기화
	listNode *now = h->first; // 현재 노드를 가리킬 노드, 헤더의 첫 번째 노드를 가리킴
	listNode *next = NULL; // 다음 노드를 가리킬 임시 노드로 null로 초기화

//리스트의 첫번째부터 마지막까지 순차적으로 이동하면서 노드의 링크를 수정.
	while (now != NULL)
	{
		next = now->link; // 다음 노드를 가리키는 next에 현재 노드의 링크를 넣는다.
		now->link = prev; // 현재 노드의 링크에 이전 노드를 넣는다.
		prev = now; // 이전 노드에 현재 노드를 넣는다.
		now = next; // 현재 노드에 다음 노드를 넣는다.
  }
	h->first = prev; 
  // now가 NULL이 되면 prev가 마지막 노드를 가리키므로 헤더의 first를 prev로 지정한다.
}


void printList(headNode* h) {
	int i = 0; // 순서를 나타내는 변수
	listNode* p; // 노드 p를 선언

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤더가 비어있을 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // 

	while(p != NULL) { // p가 NULL이 아닐 때까지 반복 => 리스트의 끝까지
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; // p를 다음 노드로 이동
		i++; 
	}

	printf("  items = %d\n", i);
}