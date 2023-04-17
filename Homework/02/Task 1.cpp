#include "../../vector/stack.h"
#include <string>
#include <cctype>
#include <cstdlib>
#include <cstring>
#define N_OPTR 9 // 运算符总数
typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    FAC,
    L_P,
    R_P,
    EOE
} Operator;
Operator optr2rank(char op)
{ // 由运算符转译出编号
    switch (op)
    {
    case '+':
        // pass RPN as a reference to a pointer to char
        return ADD; // 加
    case '-':
        return SUB; // 减
    case '*':
        return MUL; // 乘
    case '/':
        return DIV; // 除
    case '^':
        return POW; // 乘幂
    case '!':
        return FAC; // 阶乘
    case '(':
        return L_P; // 左括号
    case ')':
        return R_P; // 右括号
    case '\0':
        return EOE; // 起始符与终止符
    default:
        exit(-1); // 未知运算符
    }
}

char orderBetween(char a, char b)
{
    const char pri[N_OPTR][N_OPTR] = {
        // 运算符优先等级 [栈顶] [弼前]
        /* |-------------------- 当 前 运 算 符 --------------------| */
        /* + - * / ^    !     (     )   \0 */
        /* -- + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /* | - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /* 栈 * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* 顶 / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* 运 ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
        /* 算 ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
        /* 符 ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
        /* | ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* -- \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='};
    return pri[optr2rank(a)][optr2rank(b)];
}

void readNumber(char *&p, Stack<float> &stk)
{
    stk.push((float)(*p - '0'));
    while (isdigit(*(++p)))
        stk.push(stk.pop() * 10 + (*p - '0'));
    if ('.' != *p)
        return;
    float fraction = 1;
    while (isdigit(*(++p)))
        stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
}

void append(char *&rpn, float opnd)
{
    int n = strlen(rpn);
    char buf[64];
    if (opnd != (float)(int)opnd)
        sprintf(buf, "%.2f \0", opnd);
    else
        sprintf(buf, "%d \0", (int)opnd);
    rpn = (char *)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1));
    strcat(rpn, buf);
    rpn[n + strlen(buf)] = '\0';
}
void append(char *&rpn, char optr)
{
    int n = strlen(rpn);
    rpn = (char *)realloc(rpn, sizeof(char) * (n + 3));
    sprintf(rpn + n, "%c ", optr);
    rpn[n + 2] = '\0';
}

float calcu(char op, float a)
{
    if (floor(a) == a)
        if (a == 0)
            return 1.0;
        else
        {
            float b = 1.0;
            for (float i = 1.0; i <= a; i++)
            {
                b *= i;
            }
            return b;
        }
    else
    {
        cout << "非整数无法阶乘" << endl;
        exit(-1);
    }
}

float calcu(float a, char op, float b)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            cout << "除数不能为0" << endl;
            exit(-1);
        }
        return a / b;
    case '%':
        if ((int)b == 0)
        {
            cout << "除数不能为0" << endl;
            exit(-1);
        }
        return (int)a % (int)b;
    case '^':
        return pow(a, b);
    default:
        cout << "无效的运算符" << endl;
        exit(-1);
    }
}

float evaluate(char *S, char *&RPN)
{
    Stack<float> opnd;
    Stack<char> optr;
    optr.push('\0');
    while (!optr.empty())
    {
        if (isdigit(*S))
        {
            readNumber(S, opnd);
            append(RPN, opnd.top());
        }
        else
            switch (orderBetween(optr.top(), *S))
            {
            case '<':
                optr.push(*S);
                S++;
                break;
            case '=':
                optr.pop();
                S++;
                break;
            case '>':
            {
                char op = optr.pop();
                append(RPN, op);
                if (op == '!')
                {
                    float pOpnd = opnd.pop();
                    opnd.push(calcu(op, pOpnd));
                }
                else
                {
                    float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
                    opnd.push(calcu(pOpnd1, op, pOpnd2));
                }
                break;
            }
            default:
                exit(-1);
            }
    }
    return opnd.pop();
}

int main()
{

    cout << "输入表达式(长度不超过64)" << endl;
    char input[64], *RPN = new char[64];
    cin >> input;
    cout << evaluate(input, RPN) << endl;
    delete[] RPN;
    return 0;
}