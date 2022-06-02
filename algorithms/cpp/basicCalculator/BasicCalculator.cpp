// 用 Basic Calculator II 解法
// 双栈解法
// nums 最好存放的是 long，而不是 int，防止溢出
// 链接：https://leetcode.cn/problems/basic-calculator-ii/solution/shi-yong-shuang-zhan-jie-jue-jiu-ji-biao-c65k/
// 时间复杂度：O(n),空间复杂度：O(n)
class Solution {
 public:
  // 使用 hash 维护一个运算符优先级
  unordered_map<char, int> oper_pri = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3}};
  stack<char> opers;      // 存放所有「非数字以外」的操作
  stack<long long> nums;  // 存放所有的数字

  int calculate(string s) {
    nums.push(0);  // 为了防止第一个数为负数，先往 nums 加个 0
    int n = s.size();
    for (int i = 0; i < n; i++) {
      if (s[i] == ' ') {  // 去掉空格
        continue;
      } else if (s[i] == '(') {
        opers.push('(');
        // 为防止()内出现的首个字符为运算符，将所有的空格去掉，并将 (- 替换为 (0-，(+ 替换为 (0+
        if (s[i + 1] == '-' || s[i + 1] == '+') {
          i++;
          nums.push(0);
          opers.push('-');
        }
      } else if (s[i] == ')') {
        while (opers.top() != '(') {
          cal();
        }
        opers.pop();
      } else if ('0' <= s[i] && s[i] <= '9') {
        int l = i;
        while (i + 1 < n && '0' <= s[i + 1] && s[i + 1] <= '9') {
          i++;
        }
        nums.push(stoll(s.substr(l, i - l + 1)));
      } else {
        // 有一个新操作要入栈时，先把栈内可以算的都算了
        // 只有满足「栈内运算符」比「当前运算符」优先级高/同等，才进行运算
        while (!opers.empty() && opers.top() != '(' && oper_pri[opers.top()] >= oper_pri[s[i]]) {
          cal();
        }
        opers.push(s[i]);
      }
    }
    // 将剩余的计算完
    while (!opers.empty() && opers.top() != '(') {
      cal();
    }
    return nums.top();
  }
  void cal() {
    long long b = nums.top();
    nums.pop();
    long long a = nums.top();
    nums.pop();
    char oper = opers.top();
    opers.pop();
    long long res = 0;
    switch (oper) {
      case '+':
        res = a + b;
        break;
      case '-':
        res = a - b;
        break;
      case '*':
        res = a * b;
        break;
      case '/':
        res = a / b;
        break;
      case '%':
        res = a % b;
        break;
      case '^':
        res = pow(a, b);
        break;
    }
    nums.push(res);  //计算完入栈
  }
};

// Source : https://leetcode.com/problems/basic-calculator/
// Author : Hao Chen
// Date   : 2015-06-12

/**********************************************************************************
 *
 * Implement a basic calculator to evaluate a simple expression string.
 *
 * The expression string may contain open ( and closing parentheses ), the plus + or minus sign -,
 * non-negative integers and empty spaces  .
 *
 * You may assume that the given expression is always valid.
 *
 * Some examples:
 *
 * "1 + 1" = 2
 * " 2-1 + 2 " = 3
 * "(1+(4+5+2)-3)+(6+8)" = 23
 *
 * Note: Do not use the eval built-in library function.
 *
 *
 **********************************************************************************/
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*
 * Sorry, I cannot help using Design Pattern  ;-)
 * (https://en.wikipedia.org/wiki/Interpreter_pattern)
 *
 * Two Stack is cheap, design pattern is powerful!   ;-)
 *
 * But WTF, Memory Limit Exceeded!! Shit!!
 */

class Expression {
 public:
  virtual int interpret() = 0;
  virtual ~Expression(){};
};

class Number : public Expression {
 public:
  Number(string num) {
    this->number = atoi(num.c_str());
  }
  ~Number() {
  }
  int interpret() {
    return number;
  }

 private:
  int number;
};

class Plus : public Expression {
 public:
  Plus(Expression* left, Expression* right) : leftOperand(left), rightOperand(right) {
  }
  ~Plus() {
    delete leftOperand;
    delete rightOperand;
  }
  int interpret() {
    return leftOperand->interpret() + rightOperand->interpret();
  }

 private:
  Expression* leftOperand;
  Expression* rightOperand;
};

class Minus : public Expression {
 public:
  Minus(Expression* left, Expression* right) : leftOperand(left), rightOperand(right) {
  }
  ~Minus() {
    delete leftOperand;
    delete rightOperand;
  }
  int interpret() {
    return leftOperand->interpret() - rightOperand->interpret();
  }

 private:
  Expression* leftOperand;
  Expression* rightOperand;
};

class Multiply : public Expression {
 public:
  Multiply(Expression* left, Expression* right) : leftOperand(left), rightOperand(right) {
  }
  ~Multiply() {
    delete leftOperand;
    delete rightOperand;
  }
  int interpret() {
    return leftOperand->interpret() * rightOperand->interpret();
  }

 private:
  Expression* leftOperand;
  Expression* rightOperand;
};

class Divide : public Expression {
 public:
  Divide(Expression* left, Expression* right) : leftOperand(left), rightOperand(right) {
  }
  ~Divide() {
    delete leftOperand;
    delete rightOperand;
  }
  int interpret() {
    return leftOperand->interpret() / rightOperand->interpret();
  }

 private:
  Expression* leftOperand;
  Expression* rightOperand;
};

bool isOperator(const string& c) {
  return (c == "+" || c == "-" || c == "*" || c == "/");
}
bool isOperator(const char& c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

class Evaluator : public Expression {
 private:
  Expression* syntaxTree;

 public:
  Evaluator(vector<string>& s) {
    vector<Expression*> stack;
    for (unsigned int i = 0; i < s.size(); i++) {
      if (isOperator(s[i])) {
        Expression* left = stack.back();
        stack.pop_back();
        Expression* right = stack.back();
        stack.pop_back();
        switch (s[i][0]) {
          case '+':
            stack.push_back(new Plus(right, left));
            break;
          case '-':
            stack.push_back(new Minus(right, left));
            break;
          case '*':
            stack.push_back(new Multiply(right, left));
            break;
          case '/':
            stack.push_back(new Divide(right, left));
            break;
        }

      } else {
        stack.push_back(new Number(s[i]));
      }
    }
    syntaxTree = stack.back();
  }
  ~Evaluator() {
    delete syntaxTree;
  }

  int interpret() {
    return syntaxTree->interpret();
  }
};

vector<string> Parse(string& s) {
  vector<string> exp;
  for (int i = 0; i < s.size();) {
    char c = s[i];
    string token;
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
      exp.push_back(token + c);
      i++;
      continue;
    }
    if (isdigit(c)) {
      while (isdigit(s[i])) {
        token.push_back(s[i++]);
      }
      exp.push_back(token);
      continue;
    }
    i++;
  }
  return exp;
}

int Priority(const string& c) {
  if (c == "*" || c == "/") {
    return 2;
  } else if (c == "+" || c == "-") {
    return 1;
  } else {
    return 0;
  }
}

vector<string> Infix2RPN(vector<string>& infix) {
  vector<string> rpn;
  stack<string> s;

  for (int i = 0; i < infix.size(); i++) {
    if (isdigit(infix[i][0])) {  // number
      rpn.push_back(infix[i]);
    } else if (infix[i] == "(") {
      s.push(infix[i]);
    } else if (infix[i] == ")") {
      while (!s.empty() && s.top() != "(") {
        rpn.push_back(s.top());
        s.pop();
      }
      s.pop();
    } else if (isOperator(infix[i])) {
      while (!s.empty() && Priority(s.top()) >= Priority(infix[i])) {
        rpn.push_back(s.top());
        s.pop();
      }
      s.push(infix[i]);
    }
  }
  while (!s.empty()) {
    rpn.push_back(s.top());
    s.pop();
  }

  return rpn;
}

// Design Pattern for RPN - Memory Limit Exceeded!!
int calculate_RPN_design_pattern(string& s) {
  vector<string> exp = Parse(s);
  // for (int i=0; i<exp.size(); i++){
  //    cout << exp[i] << " ";
  //}
  // cout << endl;
  exp = Infix2RPN(exp);
  for (int i = 0; i < exp.size(); i++) {
    cout << exp[i] << " ";
  }
  cout << endl;
  Evaluator sentence(exp);
  return sentence.interpret();
}

/*
 *  RPN - Reverse Polish Notation
 *  see:  https://en.wikipedia.org/wiki/Reverse_Polish_notation
 */

// RPN evluation - Memory Limit Exceeded!!
int calculate_RPN_evluation(string& s) {
  vector<string> exp = Parse(s);
  exp = Infix2RPN(exp);

  stack<int> ss;
  for (int i = 0; i < exp.size(); i++) {
    if (isdigit(exp[i][0])) {
      ss.push(atoi(exp[i].c_str()));
    }
    if (exp[i] == "+" || exp[i] == "-") {
      int rhs = ss.top();
      ss.pop();
      int lhs = ss.top();
      ss.pop();
      if (exp[i] == "-") rhs = -rhs;
      ss.push(lhs + rhs);
    }
  }
  return ss.top();
}

// Two stack solution - quick & dirty solution
inline void calculate_two_stacks(stack<int>& num_stack, stack<char>& op_stack) {
  int lhs = num_stack.top();
  num_stack.pop();
  int rhs = num_stack.top();
  num_stack.pop();
  char op = op_stack.top();
  op_stack.pop();
  if (op == '-') rhs = -rhs;
  num_stack.push(lhs + rhs);
}
int calculate_two_stacks(string& s) {
  stack<int> num_stack;  // put the number
  stack<char> op_stack;  // put the operations

  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == ')' || s[i] == '+' || s[i] == '-') {
      op_stack.push(s[i]);
    } else if (isdigit(s[i])) {
      string num;
      num += s[i];
      while (isdigit(s[i - 1])) {
        num.insert(num.begin(), s[i - 1]);
        i--;
      }
      num_stack.push(atoi(num.c_str()));
    } else if (s[i] == '(') {
      while (op_stack.top() != ')') {
        calculate_two_stacks(num_stack, op_stack);
      }
      op_stack.pop();
    }
  }
  while (!op_stack.empty()) {
    calculate_two_stacks(num_stack, op_stack);
  }
  return num_stack.top();
}

int calculate(string s) {
  return calculate_two_stacks(s);
  return calculate_RPN_evluation(s);
  return calculate_RPN_design_pattern(s);
}

int main(int argc, char** argv) {
  string s = " 15-(1+3)+(2+1) ";
  if (argc > 1) {
    s = argv[1];
  }
  cout << s << " = " << calculate(s) << endl;
  cout << "---------------" << endl;
  s = "(2+4)-(6+(1+5))";
  cout << s << " = " << calculate(s) << endl;
}
