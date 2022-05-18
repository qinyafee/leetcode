// 逆波兰表达式严格遵循「从左到右」的运算。
// 计算逆波兰表达式的值时，使用一个栈存储操作数，从左到右遍历逆波兰表达式，进行如下操作：
// 1.如果遇到操作数，则将操作数入栈；
// 2.如果遇到运算符，则将两个操作数出栈，其中先出栈的是右操作数，后出栈的是左操作数。然后进行运算，结果入栈。
// 遍历完毕之后，栈内只有一个元素，即为逆波兰表达式的值。
// https://leetcode.cn/problems/evaluate-reverse-polish-notation/solution/ni-bo-lan-biao-da-shi-qiu-zhi-by-leetcod-wue9/

class Solution {
 public:
  int evalRPN(vector<string>& tokens) {
    stack<string> s;
    for (auto token : tokens) {
      if (!is_operator(token)) {
        s.push(token);
      } else {
        // 转成int
        int y = stoi(s.top());  // 右操作数，-/运算不可交换
        s.pop();
        int x = stoi(s.top());  // 左操作数
        s.pop();
        switch (token[0]) {  // 或者 token.front()，取里面的字符
          case '+':
            x += y;
            break;
          case '-':
            x -= y;
            break;
          case '*':
            x *= y;
            break;
          case '/':
            x /= y;
            break;
          default:
        }
        s.push(to_string(x));  // 计算结果入栈
      }
    }
    return stoi(s.top());
  }

 private:
  bool is_operator(const string& op) {
    return op.size() == 1 && string("+-*/").find(op) != string::npos;
  }
};

// Source : https://oj.leetcode.com/problems/evaluate-reverse-polish-notation/
// Author : Hao Chen
// Date   : 2014-06-16

/**********************************************************************************
 *
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 *
 * Valid operators are +, -, *, /. Each operand may be an integer or another expression.
 *
 * Some examples:
 *
 *   ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
 *   ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 *
 *
 **********************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  int evalRPN(vector<string>& tokens) {
    int i = 0;
    bool err = false;
    vector<int> exp;
    for (int i = 0; i < tokens.size() && !err; i++) {
      if (isNum(tokens[i])) {
        exp.push_back(value);
      } else if (isOp(tokens[i]) == true) {
        if (exp.size() < 2) {
          return 0;  // ERROR
        }
        int lhs, rhs;
        rhs = exp.back();
        exp.pop_back();
        lhs = exp.back();
        exp.pop_back();

        int evlValue;
        if (tokens[i] == "+") {
          evlValue = lhs + rhs;
        } else if (tokens[i] == "-") {
          evlValue = lhs - rhs;
        } else if (tokens[i] == "*") {
          evlValue = lhs * rhs;
        } else if (tokens[i] == "/") {
          evlValue = lhs / rhs;
        }

        exp.push_back(evlValue);

      } else {
        return 0;  // ERROR
      }
    }

    if (exp.size() == 1) {
      return exp.back();
    }
    return 0;
  }

 private:
  long value;

  bool isOp(string& op) {
    return (op == "+" || op == "-" || op == "*" || op == "/");
  }

  bool isNum(string& num) {
    char* end;
    value = strtol(num.c_str(), &end, 10);
    if (end == num.c_str() || *end != '\0' || errno == ERANGE) {
      return false;
    }
    return true;
  }
};

int main() {
  Solution s;
  char exps[5][3] = {"42", "9", "6", "-", "+"};
  vector<string> expression;

  cout << "Expression: \n    ";
  for (int i = 0; i < 5; i++) {
    expression.push_back(exps[i]);
    cout << exps[i] << " ";
  }
  cout << endl;
  cout << s.evalRPN(expression) << endl;
  ;

  char exps2[5][3] = {"2", "1", "+", "3", "*"};
  expression.clear();

  cout << "Expression: \n    ";
  for (int i = 0; i < 5; i++) {
    expression.push_back(exps2[i]);
    cout << exps2[i] << " ";
  }
  cout << endl;
  cout << s.evalRPN(expression) << endl;

  return 0;
}
