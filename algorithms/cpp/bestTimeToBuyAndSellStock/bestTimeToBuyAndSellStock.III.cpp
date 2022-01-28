// Source : https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
// Author : Hao Chen
// Date   : 2014-08-22

/***************************************************************************************************** 
 *
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * 
 * Design an algorithm to find the maximum profit. You may complete at most two transactions.
 * 
 * Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock 
 * before you buy again).
 * 
 * Example 1:
 * 
 * Input: [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 *              Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
 * 
 * Example 2:
 * 
 * Input: [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
 *              Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
 *              engaging multiple transactions at the same time. You must sell before buying again.
 * 
 * Example 3:
 * 
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 ******************************************************************************************************/
/**
设状态 f(i)，表示区间[0, i](0 ≤ j ≤ i − 1)的最大利润; 状态 g(i)， 表示区间[i, n − 1](i ≤ j ≤ n − 1)的
最大利润， 则最终答案为 max(f(i) + g(i)) , 0 ≤ i ≤ n − 1。
允许在一天内买进又卖出， 相当于不交易， 因为题目的规定是最多两次， 而不是一定要两次。
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) return 0;

        const int n = prices.size();
        vector<int> f(n,0);
        vector<int> g(n,0);
        
        //valley， 当前最小price
        for(int i = 1, valley = prices[0]; i < n; ++i){
            // valley = min(valley, prices[i]); //这句放到这里也行
            f[i] = max(f[i-1], prices[i] - valley);
            valley = min(valley, prices[i]);
        }

        //从后往前扫。peak，当前最高price
        for(int i = n-2, peak = prices[n-1]; i >= 0; --i){
            // peak = max(peak, prices[i]); //这句放到这里也行
            g[i] = max(g[i+1], peak - prices[i]);
            peak = max(peak, prices[i]);

        }

        int total_max = 0;
        for(int i = 0; i < n; ++i){
            total_max = max(total_max, f[i]+g[i]);
        }
        return total_max;
    }
};

//我的原始实现，结果应该正确，但是超时，O(n^2)
/*
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) return 0;

        const int n = prices.size();
        vector<int> f(n,0);
        vector<int> g(n,0);

        for(int i = 0; i < n; ++i){
            int profit_max = 0; //当前最大利润 
            int price_min = INT_MAX; //当前最小价格             
            for(int j = 0; j <= i; ++j){
                profit_max = max(profit_max, prices[j] - price_min);
                price_min = min(price_min, prices[j]);  
            }
            f[i] = profit_max;
        }

        for(int i = 0; i < n; ++i){
            int profit_max = 0; //当前最大利润 
            int price_min = INT_MAX; //当前最小价格 

            for(int j = i+1; j < n; ++j){
                profit_max = max(profit_max, prices[j] - price_min);
                price_min = min(price_min, prices[j]);  
            }
            g[i] = profit_max;
        }

        int total_max = 0;
        for(int i = 0; i < n; ++i){
            total_max = max(total_max, f[i]+g[i]);
        }
        return total_max;
    }

};
*/
class Solution {
public:
    // Dynamic Programming
    //
    //     Considering prices[n], and we have a position "i", we could have
    //       1) the maxProfit1 for prices[0..i]  
    //       2) the maxProfit2 for proices[i..n]
    //
    //    So, 
    //      for 1) we can go through the prices[n] forwardly.
    //          forward[i] = max( forward[i-1], price[i] - lowestPrice[0..i] ) 
    //      for 2) we can go through the prices[n] backwoardly.
    //          backward[i] = max( backward[i+1], highestPrice[i..n] - price[i]) 
    //
    int maxProfit(vector<int> &prices) {
        if (prices.size()<=1) return 0;
        
        int n = prices.size();
        
        vector<int> forward(n);
        forward[0] = 0;
        int lowestBuyInPrice = prices[0];
        for(int i=1; i<n; i++){
            forward[i] = max(forward[i-1], prices[i] - lowestBuyInPrice);
            lowestBuyInPrice = min(lowestBuyInPrice, prices[i]);
        }
        
        vector<int> backward(n);
        backward[n-1] = 0;
        int highestSellOutPrice = prices[n-1];
        for(int i=n-2; i>=0; i--){
            backward[i] = max(backward[i+1], highestSellOutPrice - prices[i]);
            highestSellOutPrice = max(highestSellOutPrice, prices[i]);
        }
        
        int max_profit = 0;
        for(int i=0; i<n; i++){
            max_profit = max(max_profit, forward[i]+backward[i]);
        }
        
        return max_profit;
    }
};
