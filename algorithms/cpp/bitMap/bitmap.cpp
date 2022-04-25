// 给40亿个不重复的无符号整数，没排过序。给一个无符号整数，如何快 速判断一个数是否在这40亿个数中。
// https://blog.csdn.net/archyli/article/details/78573362
// 【腾讯】
// 一个整数是4个字节，40亿个整数就是160亿个字节，也就相当于16G内存，就一般的计算机而言很难实现这个加载，所以我们可以采取以下两种方案，一种是分割，一种是位图。

// 方法：
// ①分割，hash求余
// 采用分割处理，把40亿个数分批次处理完毕，当然可以实现我们最终的目标，但是这样做时间复杂度未免优点太高。
// ②位图BitMap
// 位图BitMap：位图是一个数组的每一个数据的每一个二进制位表示一个数据，0表示数据不存在，1表示数据存在。

// 大数据相关汇总 https://leetcode-cn.com/circle/article/94ypLw/

#include <iostream>
#include <vector>
using namespace std;

class BitMap {
 public:
  BitMap(size_t range) {
    //此时多开辟一个空间
    _bits.resize(range / 32 + 1);  // 申请的位图大小， 4E9/32+1 = 119MB
  }
  void Set(size_t x) {
    int index = x / 32;           //确定哪个数据（区间）
    int temp = x % 32;            //确定哪个Bit位
    _bits[index] |= (1 << temp);  //位操作即可
  }
  void Reset(size_t x) {
    int index = x / 32;
    int temp = x % 32;
    _bits[index] &= ~(1 << temp);  //取反
  }
  bool Test(size_t x) {
    int index = x / 32;
    int temp = x % 32;
    if (_bits[index] & (1 << temp))
      return 1;
    else
      return 0;
  }

 private:
  vector<int> _bits;
};

void TestBitMap() {
  // BitMap am(4e9);
  BitMap bm(200);

  bm.Set(136);
  bm.Set(1);
  bm.Set(static_cast<uint32_t>(-1));//如果是有符号数，先转换成无符号
  cout << bm.Test(136) << endl;
  bm.Reset(136);
  cout << bm.Test(136) << endl;
}

int main() {
  TestBitMap();
  return 0;
}