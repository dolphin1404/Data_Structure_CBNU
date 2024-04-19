/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> // isdigit을 사용하기 위해서

#define MAX_STACK_SIZE 10 // 스택 최대 사이즈
#define MAX_EXPRESSION_SIZE 20 // 수식 최대 사이즈

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


// 수식 저장 및 스택 조작을 위한 전역변수 선언
char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */
int evalResult = 0;	   /* 계산 결과를 저장 */

// 함수들 미리 선언
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
//precedence getToken(char symbol);
precedence getPriority(char symbol);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command; // 이용자로부터 입력 받을 command 값

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { // 입력 받은 command 값에 따라 이용할 함수 결정
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 잘못 기입했을 때
			break;
		}

	}while(command != 'q' && command != 'Q'); // q를 입력하기 전까지 반복
	printf("[----- [이규민] [2021039002] -----]");
	return 1;
}

// postfix 스택에 푸시하는 함수
void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; // postfix 스택 top에 1을 먼저 더한 값을 인덱스로 가짐
		// 그리고 이 인덱스를 가진 스택에 x를 넣음
}

// postfix 스택에서 팝하는 함수
char postfixPop()
{
    char x;
    if(postfixStackTop == -1) // 스택이 비어 있다는 것
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; // 현 스택의 탑 인덱스에서의 값을 x에 넣고 인덱스값을 감소시킨다.
    }
    return x; // 뺀 값을 리턴
}

// eval 스택에 푸시하는 함수
void evalPush(int x)
{
    evalStack[++evalStackTop] = x; // 입력 받은 연산 값을 스택에 푸시함 
}
// eval 스택에 팝하는 함수
int evalPop()
{
    if(evalStackTop == -1)	// 스택에 비어있을 경우 리턴
        return -1;
    else
        return evalStack[evalStackTop--]; // 현 탑 인덱스의 연산 값을 반환
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}
// 위에서 선언한 우선순위를 입력 받은 연산자에 맞게 반환하는 함수 
precedence getPriority(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}
/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')	// postfixExp가 null값이라면
		strncpy(postfixExp, c, 1); // postfixExp에 복사
	else
		strncat(postfixExp, c, 1); // postfixExp에 추가
}
/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{ 
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		x = *exp;
		precedence token = getPriority(x);

		if (token == operand) { // 문자가 피연산자라면, postfixExp에 추가
			charCat(&x);
		}else if(token == lparen){	// 왼쪽 괄호인 경우 푸시
			postfixPush(x);
		} 
		else if (token == rparen) { // 오른쪽 괄호인 경우, 왼쪽 괄호가 나올때까지 팝한다.
			while (postfixStackTop != -1 && postfixStack[postfixStackTop] != '(') {	// postfixStackTop != -1은 스택이 비어있는 지 확인
				char y = postfixPop();
        charCat(&y);	// 팝한 걸 postfixExp에 추가한다.
			}
			postfixPop(); // pop '('
		} else { // 연산자의 경우, 우선순위에 따라 스택에서 postfixExp로 팝한다.
			while (postfixStackTop != -1 && getPriority(postfixStack[postfixStackTop]) >= getPriority(x)) {	// 우선순위 비교
				char y = postfixPop();
        charCat(&y);
			}
			postfixPush(x); // 현재 연산자를 스택에 푸시한다. 
		}
		exp++; // 다음 글자로 넘어감.
	}
	// 마지막으로 스택에 남아있는 모든 연산자를 팝한다.
	while (postfixStackTop != -1) {
		char y = postfixPop();
    charCat(&y);
	}
	/* 필요한 로직 완성 */
}

// 변수 및 스택의 현 상태를 출력하고 디버깅 하는 함수.
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}
// 모든 변수와 스택을 처음상태로 리셋시키는 함수
void reset()
{
	infixExp[0] = '\0';	// null 값을 통해 리셋
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}
// postfix 수식을 계산하는 함수
void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	int operand1, operand2;
	int result;
	char *token = postfixExp; // postfix 수식을 탐색할 포인터

	while (*token != '\0') {
		if (isdigit(*token)) { // 문자가 숫자이면, 해당 값을 스택에 푸시한다.
			evalPush(*token - '0'); // 0은 ASCII에서 48을 가진다. 만약 숫자라면 49부터 57까지 1부터 9를 의미한다.
			// 우린 char 값을 받았기에 빼야한다. isdigit을 사용하지 않는 코드는 아래와 같다.
			/*
			if(*token >= '0' && *token <='9'){
				evalPush(*token-'0');
			}
			*/
		} else {	// 문자가 연산자라면, 두 피연산자를 팝하고, 연산자를 적용한다.
			operand2 = evalPop();
			operand1 = evalPop();

			switch (*token) { // 연산자에 맞게 계산한다.
				case '+':
					result = operand1 + operand2;
					break;
				case '-':
					result = operand1 - operand2;
					break;
				case '*':
					result = operand1 * operand2;
					break;
				case '/':
					if(operand2 == 0) {
					printf("ERROR : This expression cannot run. So, Reset this expression.\n");
					reset();
					return;
					}
					result = operand1 / operand2;
					break;
			}
			evalPush(result); // 연산값을 스택에 푸시한다.
		}
		token++; // 다음으로 넘어간다.
	}
	evalResult = evalPop(); // 결과를 팝한다.
}

