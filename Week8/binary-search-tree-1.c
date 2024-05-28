/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>  // malloc, free 함수를 사용하기 위해

typedef struct node {
  int key;
  struct node* left;
  struct node* right;
} Node;

int initializeBST(Node** h);  // Binary Search Tree 초기화

/* functions that you have to implement */
void inorderTraversal(Node* ptr);        /* recursive inorder traversal */
void preorderTraversal(Node* ptr);       /* recursive preorder traversal */
void postorderTraversal(Node* ptr);      /* recursive postorder traversal */
int insert(Node* head, int key);         /* insert a node to the tree */
int deleteLeafNode(Node* head, int key); /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key); /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main() {
  char command;
  int key;
  Node* head = NULL;
  Node* ptr = NULL; /* temp */

  initializeBST(&head);  // z 입력 안하고도 초기화한 상태에서 입력하게 수정
  do {
    printf(
        "\n-----------[----- [Lee KyuMin] [2021039002] -----]------------\n");
    printf(
        "----------------------------------------------------------------\n");
    printf(
        "                   Binary Search Tree #1                        \n");
    printf(
        "----------------------------------------------------------------\n");
    printf(
        " Initialize BST       = z                                       \n");
    printf(
        " Insert Node          = n      Delete Node                  = d \n");
    printf(
        " Inorder Traversal    = i      Search Node Recursively      = s \n");
    printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
    printf(" Postorder Traversal  = t      Quit                         = q\n");
    printf(
        "----------------------------------------------------------------\n");

    printf("Command = ");
    scanf(" %c", &command);

    switch (command) {
      case 'z':
      case 'Z':
        initializeBST(&head);
        break;
      case 'q':
      case 'Q':
        freeBST(head);
        break;
      case 'n':
      case 'N':
        printf("Your Key = ");
        scanf("%d", &key);
        insert(head, key);
        break;
      case 'd':
      case 'D':
        printf("Your Key = ");
        scanf("%d", &key);
        deleteLeafNode(head, key);
        break;
      case 'f':
      case 'F':
        printf("Your Key = ");
        scanf("%d", &key);
        ptr = searchIterative(head, key);
        if (ptr != NULL)
          printf("\n node [%d] found at %p\n", ptr->key, ptr);
        else
          printf("\n Cannot find the node [%d]\n", key);
        break;
      case 's':
      case 'S':
        printf("Your Key = ");
        scanf("%d", &key);
        ptr = searchRecursive(head->left, key);
        if (ptr != NULL)
          printf("\n node [%d] found at %p\n", ptr->key, ptr);
        else
          printf("\n Cannot find the node [%d]\n", key);
        break;

      case 'i':
      case 'I':
        inorderTraversal(head->left);
        break;
      case 'p':
      case 'P':
        preorderTraversal(head->left);
        break;
      case 't':
      case 'T':
        postorderTraversal(head->left);
        break;
      default:
        printf("\n       >>>>>   Concentration!!   <<<<<     \n");
        break;
    }

  } while (command != 'q' && command != 'Q');

  return 1;
}

int initializeBST(Node** h) {  // 이진탐색트리 초기화

  /* if the tree is not empty, then remove all allocated nodes from the tree*/
  if (*h != NULL)
    freeBST(*h);  // freeBST 함수 호출하여 트리에 할당된 모든 노드 제거하기

  /* create a head node */
  *h = (Node*)malloc(sizeof(Node));
  (*h)->left = NULL; /* root */
  (*h)->right = *h;
  (*h)->key = -9999;
  return 1;
}

// infix와 같은 방식, 왼쪽 자식 노드를 먼저 출력 후 부모 노드로
void inorderTraversal(Node* ptr) {
  if (ptr) { // ptr가 존재하는 경우
    inorderTraversal(ptr->left);
    printf(" [%d] ", ptr->key);  // 중위순회
    inorderTraversal(ptr->right);
  }
}

// prefix와 같은 방식, 부모 노드를 먼저 출력 후 자식 노드로 경유
void preorderTraversal(Node* ptr) {
  if (ptr) {
    printf(" [%d] ", ptr->key);  // 전위순회
    preorderTraversal(ptr->left);
    preorderTraversal(ptr->right);
  }
}
// posftix와 같은 방식, 자식 노드들 먼저 출력 후 부모 노드로
void postorderTraversal(Node* ptr) {
  if (ptr) {
    postorderTraversal(ptr->left);
    postorderTraversal(ptr->right);
    printf(" [%d] ", ptr->key);  // 후위순회
  }
}

// 이진탐색트리에 노드를 삽입하는 함수
int insert(Node* head, int key) {
  Node* newNode = (Node*)malloc(sizeof(Node));  // 새로운 노드 동적할당
  newNode->key = key;  // 새로운 노드의 key값에 매개변수로 받은 key값을 넣음
  newNode->left = NULL;  // 새로운 노드의 왼쪽 자식 노드를 NULL로 초기화
  newNode->right = NULL;  // 새로운 노드의 오른쪽 자식 노드를 NULL로 초기화

  if (head == NULL)  // 오류 핸들링 : 헤더가 비어있는 경우
  {
    head = newNode;  // 헤더에 새로운 노드를 넣음
    return 1;
  }

  if (head->left == NULL) {  // 헤드의 왼쪽 자식이 비어있는 경우
    head->left = newNode;
    return 1;
  }

  Node* parent = NULL; // 부모 노드를 이용하여 새로운 노드를 삽입할 위치를 찾음
  Node* current = head->left; // 현재 노드를 헤더의 왼쪽 자식 노드로 초기화

  // 삽입할 위치를 찾는 반복문이다.
  while (current != NULL) { // 현재 노드가 Null이 아닌 경우 반복문 실행
    parent = current;   // 부모 노드에 현 노드를 넣어 다음 반복문에서 사용
    if (key < current->key) { // 삽입할 key값이 현재 노드의 key값보다 작은 경우 왼쪽으로 이동
      current = current->left; 
    } else if (key > current->key) { // 위 조건과 반대
      current = current->right;
    } else { // key값이 이미 존재하는 경우
      printf("Warning: [%d] 이미 존재함 다른 키 입력 바람\n", key);
      free(newNode); // 새로 생성한 노드를 free하고 종료
      return 0;
    }
  }

  if (key < parent->key) {  // 부모 노드의 key값보다 작은 경우 왼쪽에 삽입
    parent->left = newNode; // 부모 노드의 왼쪽 자식 노드에 새로운 노드를 넣음
  } else {
    parent->right = newNode;  // 오른쪽 자식 노드에.
  }
  // 같은 경우는 이미 위에서 처리했으므로 여기서는 처리하지 않음
  return 1;
}

  // 이진탐색트리에서 노드를 삭제하는 함수 (리프 노드란 자식 노드가 없는 노드를 의미)
  int deleteLeafNode(Node* head, int key) {
    if (head == NULL) { // 헤더가 비어있는 경우
          printf("The node [%d] does not exist.\n", key);
          return 0;
      }

      Node* parent = NULL;  // insert함수와 비슷하게 부모 노드를 이용하여 삭제할 노드를 찾음
      Node* current = head->left;

    // 삭제할 노드를 찾는 반복문
      while (current != NULL) {
          if (key == current->key) { // 입력받은 key값과 현재 노드의 key값이 같은 경우
              if (current->left == NULL && current->right == NULL) {
                  // 현재 노드가 리프 노드인 경우
                  if (parent == NULL) {
                      // 트리의 루트 노드가 리프 노드인 경우
                      head->left = NULL;
                  } else if (parent->left == current) { // 부모 노드의 왼쪽 자식 노드가 현재 노드인 경우
                      parent->left = NULL; 
                  } else { // 부모 노드의 오른쪽 자식 노드가 현재 노드인 경우
                      parent->right = NULL;
                  }
                  free(current); // 현재 노드를 free하고 종료
                  return 1;
              } else {
                  // 현재 노드가 리프 노드가 아닌 경우
                  printf("The node [%d] is not a leaf.\n", key);
                  return 0;
              }
          }
          parent = current; // 부모 노드에 현재 노드를 넣어 다음 반복문에서 사용
          if (key < current->key) {  // insert와 비슷함
              current = current->left;
          } else {
              current = current->right;
          }
      }
      printf("The node [%d] does not exist.\n", key);
      return 0;
  }

Node* searchRecursive(Node* ptr, int key) {
  if (ptr == NULL)  // ptr이 비어있는 경우
    return NULL;    // NULL 반환, not 0 (Node* 형식임)
  if (ptr->key == key)  // ptr의 key값이 매개변수로 받은 key값과 같은 경우
    return ptr;  // ptr 반환
  if (ptr->key > key)  // ptr의 key값이 매개변수로 받은 key값보다 큰 경우
    return searchRecursive(
        ptr->left, key);  // ptr의 왼쪽 자식 노드와 key값을 넣어서 재귀함수 호출
  else
    return searchRecursive(
        ptr->right,
        key);  // ptr의 오른쪽 자식 노드와 key값을 넣어서 재귀함수 호출
}

Node* searchIterative(Node* head, int key) {
  Node* ptr = head->left;  // 헤더의 왼쪽 자식 노드를 ptr에 넣음

  while (ptr != NULL) {  // ptr이 NULL이 아닌 경우
    if (ptr->key == key)  // ptr의 key값이 매개변수로 받은 key값과 같은 경우
      return ptr;  // ptr 반환
    else if (ptr->key > key)  // ptr의 key값이 매개변수로 받은 key값보다 큰 경우
      ptr = ptr->left;  // ptr의 왼쪽 자식 노드를 ptr에 넣음
    else
      ptr = ptr->right;  // ptr의 오른쪽 자식 노드를 ptr에 넣음
  }
  return NULL;  // ptr이 NULL인 경우 NULL 반환
}

int freeBST(Node* head) {
  if (head == NULL)  // 헤더가 비어있는 경우, 더 할 필요없이 0 반환하여 종료
    return 0;
  if (head->left != NULL) freeBST(head->left);
  // 왼쪽 자식 노드가 NULL이 아닌 경우, freeBST 함수에 넣음
  // 왜냐하면 왼쪽 자식 노드가 먼저 free되어야 하기 때문
  if (head->right != head) freeBST(head->right);
  // head와 비교하는 이유?
  // head->right가 head를 가리키고 있으면 트리가 초기화된 상태.
  // head->right가 head를 가리키고 있지 않으면 트리에 실제 데이터 노드가 아직
  // 존재하는 상태.
  free(head);  // 헤더를 free함
  return 1;
}
