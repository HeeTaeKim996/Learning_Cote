#include "pch.h"
#include "OpBinaryNode.h"
#include "NumNode.h"
#include "Parser.h"

//void test1(OpBinaryType type, float v1, float v2)
//{
//	OpBinaryNode* opNode = new OpBinaryNode(type);
//
//	NumNode* num1;
//	NumNode* num2;
//
//	if (v1 - static_cast<int>(v1) == 0)
//	{
//		num1 = new NumNode(static_cast<INT>(v1));
//	}
//	else
//	{
//		num1 = new NumNode(v1);
//	}
//
//	if (v2 - static_cast<int>(v2) == 0)
//	{
//		num2 = new NumNode(static_cast<INT>(v2));
//	}
//	else
//	{
//		num2 = new NumNode(v2);
//	}
//
//	char c;
//	switch (opNode->opBinaryType)
//	{
//	case OpBinaryType::plus:
//		c = '+';
//		break;
//	case OpBinaryType::minus:
//		c = '-';
//		break;
//	case OpBinaryType::mul:
//		c = '*';
//		break;
//	case OpBinaryType::divv:
//		c = '/';
//		break;
//	case OpBinaryType::res:
//		c = '%';
//		break;
//	case OpBinaryType::quot:
//		c = 'q';
//		break;
//	default:
//		c = '?';
//		break;
//	}
//
//	int leftInt = num1->intVal;
//	float leftFloat = num1->floatVal;
//
//	int rightInt = num2->intVal;
//	float rightFloat = num2->floatVal;
//
//	opNode->left = num1;
//	opNode->right = num2;
//
//	NumNode* result = static_cast<NumNode*>(opNode->operate());
//
//	printf("\n----\n");
//	printf("[%d][%f] %c [%d][%f] = [%d][%f]",
//		leftInt, leftFloat,
//		c,
//		rightInt, rightFloat,
//		result->intVal, result->floatVal
//	);
//}
//
//void test2()
//{
//	// 1. plus (+)
//	test1(OpBinaryType::plus, 4, 2);
//	test1(OpBinaryType::plus, 4, 2.5f);
//	test1(OpBinaryType::plus, 4.5f, 2);
//	test1(OpBinaryType::plus, 4.5f, 2.5f);
//
//	// 2. minus (-)
//	test1(OpBinaryType::minus, 4, 2);
//	test1(OpBinaryType::minus, 4, 2.5f);
//	test1(OpBinaryType::minus, 4.5f, 2);
//	test1(OpBinaryType::minus, 4.5f, 2.5f);
//
//	// 3. mul (*)
//	test1(OpBinaryType::mul, 4, 2);
//	test1(OpBinaryType::mul, 4, 2.5f);
//	test1(OpBinaryType::mul, 4.5f, 2);
//	test1(OpBinaryType::mul, 4.5f, 2.5f);
//
//	// 4. divv (/)
//	test1(OpBinaryType::divv, 4, 2);
//	test1(OpBinaryType::divv, 4, 2.5f);
//	test1(OpBinaryType::divv, 4.5f, 2);
//	test1(OpBinaryType::divv, 4.5f, 2.5f);
//
//	// 5. res (%)
//	test1(OpBinaryType::res, 4, 2);
//
//	// 6. quot (q)
//	test1(OpBinaryType::quot, 4, 2);
//}

void test3(string query)
{
	Parser::instance()->parse(query);
}


// TODO : 추후 필요시 so 로 빌드하고 안드로이드 자바에서 사용해보자


/*
■ 개요
Arithemetic Interpreter 를 직접 구현해보고자 만들었다.
핵심 내용은 아래와 같다.

1) string을 순차 읽어드리며, Node(숫자, 오퍼레이터..) 로 변환한다.
   수식의 인접한 항목들끼리를 Node 의 left, right 로 서로 연결한다.
   (Linked List 방식)

2) '(' 를 만날시 level++, ')' 를 만날시 level-- 로 하고, operaotr 를 만날시,
   현 level 을 기준으로 operator 를 vector 에 할당한다.

3) OpNode(operator 노드) 에는 int priority 가 할단된다. OpNode 상속자별로
  prioriy 값이 다르다

4) 2), 3) 을 기준으로, OpNode 의 연산순위를 정한다. level 이 클수록, 우선.
   동일 레벨일시, priority 가 낮을 수록 우선이다.

5) 4)까지 작업 완료후, 우선순위가 높은 OpNode 부터 연산을 시작한다.
   예를 들어 OpBinaryNode 의 경우, left Node, rightNode 는 모둔 numNode여야 하며,
   연산 결과로 자신, left, right 노드를 모두 삭제하고, left->left 와 right->right 에
   연산 결과로 새로 생성된 numNode 를 연결한다

6) OpNode 별 5) 작업을 모두 처리하면, rootNode 에 연결된 노드는 유일한 numNode다.
  해당 노드가 연산 결과다


※ 내가 구현한 방식은 표준 Arithmetic Interpreter 방식과 많이 다르다 한다.
  우선 전통방식은 수식을 객체로 트리 구조로 저장하기 때문에, 
  파싱 후 일부 내용이 수정되면, 일부 수정된 부분만 기존 트리 구조에 재배치하면 된다 함

  하지만 내 방식은 파싱 -> LinkedList 로 구현하기 때문에, 재배치시 다시 파싱해야 하는
  단점이 있음.

  정리하면 내 (LinkedList + Level) 방식보다 정석인 AST(트리구조) 가 더 우월한 것 같ㅌ다.

  추후 더 구현하고 싶다면 표준 패턴을 배워서 다시 시도해보자
*/


int main()
{
	//test2();

	test3("4 + 7.5");
	test3("(4 - 2) * 3.5");

	return 0;
}

