// 链接：https://leetcode.cn/problems/restore-ip-addresses/solution/fu-yuan-ipdi-zhi-by-leetcode-solution/
// 回溯
class Solution {
 private:
  static constexpr int CNT = 4;

 private:
  vector<string> ans;
  vector<int> segments;

 public:
  void dfs(const string& s, int segid, int sid) {
    // 如果找到了 4 段 IP 地址并且遍历完了字符串，那么就是一种答案
    if (segid == CNT) {
      if (sid == s.size()) {
        string ipAddr;
        for (int i = 0; i < CNT; ++i) {
          ipAddr += to_string(segments[i]);
          if (i != CNT - 1) {
            ipAddr += ".";
          }
        }
        ans.push_back(move(ipAddr));
      }
      return;
    }

    // 如果还没有找到 4 段 IP 地址就已经遍历完了字符串，那么提前回溯
    if (sid == s.size()) {
      return;
    }

    // 由于不能有前导零，如果当前数字为 0，那么这一段 IP 地址只能为 0
    if (s[sid] == '0') {
      segments[segid] = 0;
      dfs(s, segid + 1, sid + 1);
    }

    // 一般情况，枚举每一种可能性并递归
    int addr = 0;
    for (int segEnd = sid; segEnd < s.size(); ++segEnd) {
      addr = addr * 10 + (s[segEnd] - '0');
      if (addr > 0 && addr <= 0xFF) {
        segments[segid] = addr;
        dfs(s, segid + 1, segEnd + 1);
      } else {
        break;
      }
    }
  }

  vector<string> restoreIpAddresses(string s) {
    segments.resize(CNT);
    dfs(s, 0, 0);
    return ans;
  }
};

// Source : https://oj.leetcode.com/problems/restore-ip-addresses/
// Author : Hao Chen
// Date   : 2014-08-26

/**********************************************************************************
 *
 * Given a string containing only digits, restore it by returning all possible valid IP address
 *combinations.
 *
 * For example:
 * Given "25525511135",
 *
 * return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
 *
 *
 **********************************************************************************/

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void restoreIpAddressesHelper(string& s, int start, int partNum, string ip, vector<string>& result);

vector<string> restoreIpAddresses(string s) {
  vector<string> result;
  string ip;
  restoreIpAddressesHelper(s, 0, 0, ip, result);
  return result;
}

void restoreIpAddressesHelper(string& s, int start, int partNum, string ip,
                              vector<string>& result) {
  int len = s.size();
  if (len - start < 4 - partNum || len - start > (4 - partNum) * 3) {
    return;
  }

  if (partNum == 4 && start == len) {
    ip.erase(ip.end() - 1, ip.end());
    result.push_back(ip);
    return;
  }

  int num = 0;
  for (int i = start; i < start + 3; i++) {
    num = num * 10 + s[i] - '0';
    if (num < 256) {
      ip += s[i];
      restoreIpAddressesHelper(s, i + 1, partNum + 1, ip + '.', result);
    }
    // 0.0.0.0 valid, but 0.1.010.01 is not
    if (num == 0) {
      break;
    }
  }
}

int main(int argc, char** argv) {
  string s = "25525511135";
  if (argc > 1) {
    s = argv[1];
  }

  vector<string> result = restoreIpAddresses(s);

  cout << s << endl;
  for (int i = 0; i < result.size(); i++) {
    cout << '\t' << result[i] << endl;
  }
  return 0;
}
