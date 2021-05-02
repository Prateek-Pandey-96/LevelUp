#include <bits/stdc++.h>

//Ques-1 Spiral matrix
vector<vector<int> > Solution::prettyPrint(int A) {
    int n = 2*A-1;
    int t = 0, l = 0;
    int b = n-1, r = n-1;
    int count = 0, k;
    vector<vector<int>> res(n, vector<int>(n, 0));
    //We will go in spiral until we get count = n*n or A=0
    while(l<=r and t<=b){
        k = l;
        while(k<=r){
            res[t][k]=A;
            k++;
        }
        t++;
        k=t;
        while(k<=b){
            res[k][r]=A;
            k++;
        }
        r--;
        k=r;
        while(k>=l){
            res[b][k]=A;
            k--;
        }
        b--;
        k=b;
        while(k>=t){
            res[k][l]=A;
            k--;
        }
        l++;
        A--;
    }
    
    return res;
}

//Ques-2 All LIS paths
struct node{
  int i;
  string psf;
  
  node(int x, string s):i(x),psf(s){}
};
int main(){
    int n, x;
    cin>>n;
    vector<int> arr;
    for(int i=0;i<n;i++){
        cin>>x;
        arr.push_back(x);
    }
    int dp[n];
    dp[0] = 1;
    
    for(int i=1;i<n;i++){
        dp[i]=1;
        for(int j=0;j<i;j++){
            if(arr[i]>arr[j] and dp[i]<dp[j]+1)
                dp[i] = dp[j]+1;
        }
    }
    
    queue<node> q;
    int mx = 0;
    for(auto element:dp){
        mx = max(element, mx);
    }
    cout<<mx<<endl;
    for(int i=0;i<n;i++){
        if(dp[i] == mx){
            q.push(node(i, to_string(arr[i])));
        }
    }
    
    while(!q.empty()){
        int index = q.front().i;
        string path = q.front().psf;
        q.pop();
        
        if(dp[index] == 1){
            cout<<path<<endl;
        }
        
        for(int i=0;i<index;i++){
            if(dp[i]==dp[index]-1){
                q.push(node(i,to_string(arr[i])+" -> "+path));
            }
        }
    }
}

//Ques-3 Max consequtive ones with a twist
vector<int> Solution::maxone(vector<int> &A, int B) {
    int i=0,j=0;
    int count=0;
    int l = INT_MIN;
    int windowEnd;
    while(j<A.size()){
        if(A[j]==0)
            count++;
        
        while(count > B){
            if(A[i]==0)
                count--;
            i++;
        }
        if(l < j-i+1){
            l = j-i+1;
            windowEnd = j;
        }
        j++;
    }
    vector<int> result;
    for(int i=windowEnd-l+1;i<=windowEnd;i++){
        result.push_back(i);
    }
    return result;
}

//Ques- 4 Longest Consequtive Sequence
int longestConsecutive(vector<int>& nums) {
    if(nums.size()==0)
        return 0;
    unordered_set<int> hashSet;
    for(int i=0;i<nums.size();i++)
        hashSet.insert(nums[i]);
    
    int currentNum;
    int longestStreak = 0 ;
    int currentStreak;
    for(int i=0;i<nums.size();i++){
        if(hashSet.find(nums[i]-1)==hashSet.end()){
            currentNum = nums[i];
            currentStreak = 1;
            
            while(hashSet.find(currentNum+1)!=hashSet.end())
            {currentStreak+=1;currentNum = currentNum+1;}    
            
            longestStreak = max(longestStreak,currentStreak);
        }
    }
    
    return longestStreak;
}

//Ques-5 Painters partition problem
long long getSum(vector<int>& C){
    long long sum = 0;
    for(auto element:C)
        sum+=element;
        
    return sum;
}
 
long long getMax(vector<int>& C){
    int mx = C[0];
    
    for(int i=1;i<C.size();i++){
        mx = max(mx, C[i]);
    }
    return mx;
}
 
long long getPainters(vector<int>& C, int timeAllowed){
    int painters = 1;
    long long sum = 0;
    
    for(int i=0;i<C.size();i++){
        sum+=C[i];
        if(sum>timeAllowed){
            sum = C[i];
            painters++;
        }
    }
    return painters;
}
int Solution::paint(int A, int B, vector<int> &C) {
    long long high = getSum(C);   // one painter paints
    long long low = getMax(C);    // max possible painters paint
    long long ans = INT_MAX;
    while(low<=high){
        long long mid = low + (high-low)/2;
        int paintersRequired = getPainters(C, mid);
        
        if(paintersRequired > A)
            low = mid+1;
        else
            ans = min(ans, mid),high = mid-1;
    }
    return (ans*B)%10000003;
}

//Ques-6 Target sum
#include <bits/stdc++.h>
using namespace std;
struct node{
    int i;
    int j;
    string psf;
    
    node(int x, int y, string s):i(x),j(y),psf(s){}
};
int main(){
    int n, tar;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cin>>tar;
    bool dp[n+1][tar+1];
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=tar;j++){
            if(j==0 and i==0)
                dp[i][j] = true;
            else if(i==0)
                dp[i][j] = false;
            else if(j==0)
                dp[i][j]=true;
            else if(arr[i-1]<=j)
                dp[i][j] = dp[i-1][j] or dp[i-1][j-arr[i-1]];
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    
    cout<<std::boolalpha<<dp[n][tar]<<endl;
    if(dp[n][tar]){
        queue<node> q;
        q.push(node(n, tar, ""));
    
    
    while(!q.empty()){
        node curr = q.front();
        q.pop();
        int x = curr.i;
        int y = curr.j;
        string path = curr.psf;
        if(y==0 and x==0)
            cout<<path<<endl;
        else{
            bool exc = dp[x-1][y];
            bool inc = (y-arr[x-1]>=0)?dp[x-1][y-arr[x-1]]:false;
            if(dp[x][y]==inc){
                q.push(node(x-1, y-arr[x-1], to_string(x-1)+" "+path));
            }
            if(dp[x][y]==exc){
                q.push(node(x-1, y, path));
            }
        }
    }
    }
}

//Ques-7 Word Break
unordered_map<string,bool> dp;

bool solve(string s, unordered_set<string>& words){
    if(s=="")
        return true;
    if(dp.count(s))
        return dp[s];
    
    for(int i=1;i<=s.length();i++){
        string temp = s.substr(0,i);
        if(words.find(temp)!=words.end()){
            bool checkRemaining = solve(s.substr(i,s.length()-i), words);
            if(checkRemaining)
                return dp[s]=true;
        }
    }
    return dp[s]=false;
}

bool wordBreak(string s, vector<string>& wordDict) {
    dp.clear();
    
    unordered_set<string> words;
    for(int i=0;i<wordDict.size();i++){
        words.insert(wordDict[i]);
    }
    
    return solve(s,words);
}

//Ques-8 Word Break modified
int wordBreak(string s, vector<string> &wordDict) {
    unordered_set<string> hashSet;
        for(auto word:wordDict)
            hashSet.insert(word);
        
        int dp[s.length()];
        memset(dp, 0, sizeof dp);
        
        string temp;
        for(int i=0;i<s.length();i++){
            for(int j=0;j<=i;j++){
                temp = s.substr(j,i-j+1);
                if(hashSet.find(temp)!=hashSet.end())
                {   
                    if(j==0)
                        dp[i] = 1;
                    else
                        dp[i] += dp[j-1];
                 }
            }
        }
        return dp[s.length()-1] > 0;
}