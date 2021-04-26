#include <bits/stdc++.h>

//Ques-1 Min Jumps  
int jump(vector<int>& nums) {
    int n = nums.size();
    int dp[n];
    memset(dp, INT_MAX-1, sizeof dp);
    dp[n-1] = 0;
    int m;
    for(int i=n-2;i>=0; i--){
        int steps = nums[i];
        m = INT_MAX-1;
        for(int j=1;j<=steps and i+j<=n-1;j++){
            if(dp[i+j]!=INT_MAX-1)             		//To avoid overflow
              m = min(m, dp[i+j]+1);
        } 
        if(m!=INT_MAX-1);
            dp[i] = m;
    }
    return dp[0];
}

//Ques-2 Best time to buy & sell stocks(1 Transaction allowed)	
int maxProfit(vector<int>& prices) {
    if(prices.size()==1)
        return 0;
    int minTillNow = prices[0];
    int ans = INT_MIN;
    
    for(int i = 1; i< prices.size();i++){
        minTillNow = min(minTillNow,prices[i]);
        ans = max(ans, prices[i]-minTillNow);
        
    }
    return ans;     
}

//Ques-3 Best time to buy & sell stocks(INF Transaction allowed)	
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int bd = 0;
    int sd = 0;
    int profit = 0;
    
    for(int i=1;i<n;i++){
        if(prices[i]>prices[i-1]){
            sd++;
        } else {
            profit += prices[sd]-prices[bd];
            bd = sd = i;
        }
    }
    profit += prices[sd]-prices[bd];
    return profit;
}

//Ques-4 Best time to buy & sell stocks(Transaction fee)
int maxProfit(vector<int>& prices, int fee) {
    //We can do it in O(1) space and O(N) time
    
    int obsp = -prices[0];
    int ossp = 0;
    
    for(int i=1;i<prices.size();i++){
        int nbsp,nssp;
        if(ossp - prices[i] > obsp){
            nbsp = ossp - prices[i];
        } else {
            nbsp = obsp;
        }
        
        if(obsp + prices[i] - fee > ossp){
            nssp = obsp + prices[i] - fee;
        } else {
            nssp = ossp;
        }
        obsp = nbsp;
        ossp = nssp;
    }
    return ossp;
}
//Ques-5 Largest area in a binary matrix
int maxAreaHistogram(vector<int> heights){
    vector<int> left;
    vector<int> right;
    stack<int> s;
    int h = heights.size();
    for(int i=0;i<h;i++){
        while(!s.empty() and heights[s.top()]>=heights[i]){
            s.pop();
        }
        if(s.empty()){
            left.push_back(-1);
        }
        else{
            left.push_back(s.top());
        }
        s.push(i);
    }
    while(!s.empty()){
        s.pop();
    }
    for(int i=h-1;i>=0;i--){
        while(!s.empty() and heights[s.top()]>=heights[i]){
            s.pop();
        }
        if(s.empty()){
            right.push_back(h);
        }
        else {
            right.push_back(s.top());
        }
        s.push(i);
    }
    reverse(right.begin(), right.end());
    
    vector<int> widths;
    for(int i=0;i<h;i++){
        widths.push_back(right[i]-left[i]-1);
    }
    int ans =0;
    for(int i=0;i<h;i++){
        ans = max(ans, heights[i]*widths[i]);
    }
    return ans;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    if(matrix.size()==0)
        return 0;
    vector<int> temp;
    for(int i=0;i<matrix[0].size();i++){
        if(matrix[0][i]=='1')
            temp.push_back(1);
        else
            temp.push_back(0);
    }
    int ans = maxAreaHistogram(temp);
    for(int i=1;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++){
            if(matrix[i][j]=='1')
                temp[j] += 1;
            else
                temp[j] = 0;
        }
        ans = max(ans, maxAreaHistogram(temp));
    }
    return ans;
}

//Ques-6 Best time to buy & sell stocks(Cooldown time)
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    
    int obsp = -prices[0];
    int ossp = 0;
    int ocsp = 0;
    
    for(int i=1;i<n;i++){
        int nbsp, nssp, ncsp;
        
        if(ocsp - prices[i] > obsp){
            nbsp = ocsp - prices[i];
        }else{
            nbsp = obsp;
        }
        
        if(obsp + prices[i] > ossp){
            nssp = obsp + prices[i];
        }else{
            nssp = ossp;
        }
        
        if(ossp > ocsp){
            ncsp = ossp;
        }else{
            ncsp = ocsp;
        }
        
        obsp = nbsp;
        ossp = nssp;
        ocsp = ncsp;
    }
    
    return ossp;
}

//Ques-7 Best time to buy and sell stocks two transactions
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    
    int maxProfitForward[n];
    int maxProfitBackward[n];
    
    int minSoFar = prices[0];
    maxProfitForward[0] = 0;
    
    for(int i=1;i<n;i++){
        minSoFar = min(minSoFar, prices[i]);
        maxProfitForward[i] = max(prices[i]-minSoFar, maxProfitForward[i-1]);            
    }
    
    int maxSoFar = prices[n-1];
    maxProfitBackward[n-1] = 0;
    for(int i=n-2;i>=0;i--){
        maxSoFar = max(maxSoFar, prices[i]);
        maxProfitBackward[i] = max(maxSoFar-prices[i], maxProfitBackward[i+1]);
    }
    
    int result = 0;
    
    for(int i=0;i<n;i++){
        result = max(result, maxProfitForward[i]+ maxProfitBackward[i]);
    }
    
    return result;
}

//Ques-8 Max Profit when k transactions are allowed
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    if(k >=n )
        return 0;
    int dp[k+1][n];
    
    memset(dp, 0, sizeof dp);
    
    for(int i=1;i<=k;i++){
        for(int j=1;j<n;j++){
            //All the transactions were complete by i-1 day
             
            int m = dp[i][j-1];;             //max when last transation ocurs b/w day j-1 to day j
            //Check for other days
            for(int d=0;d<j;d++){
                m = max(m, dp[i-1][d]+prices[j]-prices[d]);
            }   
            dp[i][j] = m;
        }
    }
    
    return dp[k][n-1];
}