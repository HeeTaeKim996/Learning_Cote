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

int main()
{
	//test2();

	test3("4 + 7.5");
	test3("(4 - 2) * 3.5");

}

