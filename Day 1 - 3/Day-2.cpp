#include <bits/stdc++.h>
//Binary Search

//Ques-1
int getIndex(vector<int>& seq, int element){
    int low = 0;
    int high = seq.size()-1;
    
    while(low<=high){
        int mid = low + (high - low)/2;
        if(seq[mid] == element)
            return mid;
        else if(seq[mid]>element)
            high = mid-1;
        else
            low = mid+1;
    }
    return low;
}
//Function to find length of longest increasing subsequence.
int longestSubsequence(int n, int a[])
{
   //Lets try to do it O(NLogN)
   vector<int> seq;
   
   for(int i=0;i<n;i++){
        if(seq.empty() or a[i]>seq.back())
            seq.push_back(a[i]);
        else{
            int index = getIndex(seq, a[i]);
            seq[index] = a[i];
        }
   }
   return seq.size();
}

//Ques-2
int maxSumIS(int arr[], int n)  
{  
    int dp[n];
    dp[0] = arr[0];
    
    for(int i=1;i<n;i++){
        dp[i] = arr[i];
        for(int j=0;j<i;j++){
            if(arr[j]<arr[i] and dp[i] < dp[j]+arr[i])
                dp[i] = dp[j]+arr[i];
        }
    }
    int res = dp[0];
    for(int i=1;i<n;i++){
        if(dp[i]>res)
            res = dp[i];
    }
    return res;
}

//Ques-3
int countSubstrings(string s) {
//using gap strategy
int l = s.length();
bool dp[l][l];
int count = 0;

for(int gap=0;gap<l;gap++){
    for(int i=0,j=gap; j<l; i++,j++){
        if(gap==0)
            dp[i][j] = true;
        else if(gap==1){
            dp[i][j] = s[i]==s[j] ;
        }
        else{
            if(s[i]==s[j]){
                dp[i][j] = dp[i+1][j-1];
            }
            else
                dp[i][j] = false;
        }
        if(dp[i][j])
            count++;
    }
}
return count;
}  

//Ques-4

//Ques-5
bool static compare(vector<int> a, vector<int> b){
    return a[1]<b[1];        
}

int maxEnvelopes(vector<vector<int>>& envelopes) {
    //O(NlogN) failing so going with O(N^2)
    
    int l = envelopes.size();
    int dp[l];
    dp[0] = 1;
    sort(envelopes.begin(), envelopes.end(), compare);
    for(int i=1;i<l;i++){
        dp[i] = 1;
        for(int j=0;j<i;j++){
            if(envelopes[i][0]>envelopes[j][0] and envelopes[i][1]>envelopes[j][1] and dp[i]<dp[j]+1)
                dp[i] = dp[j]+1;
        }
    }
    int ans = dp[0];
    for(int i=1;i<l;i++){
        ans = max(ans, dp[i]);
    }
    return ans;
}

//Ques-6
signed main(){
    int N;
    cin>>N;
    
    int prices[N+1];
    prices[0] = 0;
    for(int i=1;i<=N;i++){
        cin>>prices[i];
    }
    
    int dp[N+1];
    dp[0] = 0;
    dp[1] = prices[1];
    for(int i=2;i<=N;i++){
        int value = prices[i];
        for(int j=1;j<=N;j++){
            if(j>i)continue;
            value = max(value, prices[j]+dp[i-j]);
        }
        dp[i] = value;
    }
    
    cout<<dp[N]<<endl;
}

//Ques-7
int minCut(string s) {
    //Step-1 First use gap method for finding all the pallindromic substrings
    int l = s.length();
    bool dp[l][l];
    for(int gap = 0; gap < l; gap++){
        for(int i=0, j=gap; j < l; i++,j++){
            if(gap==0){
                dp[i][j] = true;
            } else if (gap==1){
                dp[i][j] = s[i]==s[j];
            } else {
                if(s[i]==s[j])
                    dp[i][j] = dp[i+1][j-1];
                else
                    dp[i][j] = false;
            }
        }
    }
    
    //Step-2 Apply cuts
    //Using the name cache as dp is already used
    int cache[l];
    cache[0] = 0;
    
    for(int j=1;j<l;j++){
        if (dp[0][j])
            cache[j] = 0;
        else
        {
            int m = INT_MAX;
            for(int i=j;i>=1;i--){
               if(dp[i][j])
                  m = min(m, cache[i-1]);
                   
            }
            cache[j] = m+1;
        }
    }
    return cache[l-1];
}

//Ques-8
//max(lis[i]+lds[i]-1) Bitonic Sequence 
//First Increasing then decreasing
