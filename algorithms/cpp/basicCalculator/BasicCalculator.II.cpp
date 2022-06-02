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

// Source : https://leetcode.com/problems/basic-calculator-ii/
// Author : Hao Chen
// Date   : 2015-06-24

/**********************************************************************************
 *
 * Implement a basic calculator to evaluate a simple expression string.
 *
 * The expression string contains only non-negative integers, +, -, *, / operators and empty spaces
 *. The integer division should truncate toward zero.
 *
 * You may assume that the given expression is always valid.
 *
 * Some examples:
 *
 * "3+2*2" = 7
 * " 3/2 " = 1
 * " 3+5 / 2 " = 5
 *
 * Note: Do not use the eval built-in library function.
 *
 * Credits:Special thanks to @ts for adding this problem and creating all test cases.
 **********************************************************************************/
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

/*
 * Acuatlly, everything I've already implemented in "Basic Calculator"(RPN way and Design pattern
 * way). So, here, I just use the quick-dirty way - just like the "two stacks solution" in "Basic
 * Calulator".
 */

// Quick & Dirty Solution
bool isOperator(const char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int Priority(const char c) {
  if (c == '*' || c == '/') {
    return 2;
  } else if (c == '+' || c == '-') {
    return 1;
  } else {
    return 0;
  }
}

long long calculate_exp(long long x, long long y, char op) {
  switch (op) {
    case '+':
      return x + y;
    case '-':
      return x - y;
    case '*':
      return x * y;
    case '/':
      return x / y;
  }
  return -1;
}

// Two Stacks solution
int calculate_two_stacks(string& s) {
  s += "+0";
  stack<long long> num_stack;  // put the number
  stack<char> op_stack;        // put the operations

#define CALCULATE_IT                         \
  {                                          \
    long long y = num_stack.top();           \
    num_stack.pop();                         \
    long long x = num_stack.top();           \
    num_stack.pop();                         \
    char op = op_stack.top();                \
    op_stack.pop();                          \
    num_stack.push(calculate_exp(x, y, op)); \
  }

  for (int i = 0; i < s.size(); i++) {
    char ch = s[i];
    if (isspace(ch)) continue;
    if (isdigit(ch)) {
      string num;
      num += s[i];
      while (isdigit(s[i + 1])) {
        num += s[i + 1];
        i++;
      }
      num_stack.push(stoll(num));
      continue;
    }
    if (isOperator(ch)) {
      while (!op_stack.empty() && Priority(op_stack.top()) >= Priority(ch)) {
        CALCULATE_IT;
      }

      op_stack.push(ch);
    }
  }

  while (!op_stack.empty()) {
    CALCULATE_IT;
  }

  return num_stack.top();
}

int calculate(string s) {
  return calculate_two_stacks(s);
}

int main(int argc, char** argv) {
  string exp = " 3+5 / 2 ";
  if (argc > 1) {
    exp = argv[1];
  }

  cout << "\"" << exp << "\" = " << calculate(exp) << endl;
}
