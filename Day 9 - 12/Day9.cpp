#include <bits/stdc++.h>

//Ques-1 Matrix Chain Multiplication
int dp[100][100];
int solve(int arr[], int i, int j){
    if(i>=j)
        return 0;
    
    if(dp[i][j]!=-1)
        return dp[i][j];
    int ans = INT_MAX;
    for(int k=i; k<=j-1; k++){
        int temp_ans = solve(arr, i, k) + solve(arr, k+1, j) + arr[k]*arr[j]*arr[i-1];
        ans = min (ans, temp_ans);
    }
    return dp[i][j]=ans;
    
}
    
int matrixMultiplication(int N, int arr[])
{
    memset(dp, -1, sizeof dp);
    return solve(arr, 1, N-1);
}

//Ques-2 Burst Balloon
int dp[504][504];
    
int solve(vector<int>& nums, int i, int j){
   
    if(i>=j)
        return 0;
    
    if(dp[i][j]!=-1)
        return dp[i][j];
    
    int ans = 0;
    for(int k=i;k<=j-1;k++){                
        int temp_ans = solve(nums, i, k) + solve(nums, k+1, j) + nums[i-1]*nums[k]*nums[j];
        ans = max(ans, temp_ans);
    }
    return dp[i][j]=ans;
}
int maxCoins(vector<int>& nums) {
    memset(dp, -1, sizeof dp);
    vector<int> A;
    A.push_back(1);
    for(auto i : nums){
        A.push_back(i);
    }
    A.push_back(1);
    return solve(A, 1, A.size()-1);
}

//Ques - 3 Snake and Ladder
int board[100];
bool visited[100];
int bfs(int src){
    queue<pair<int,int>> q;
    q.push({src,0});
    visited[src] = true;
    
    while(!q.empty()){
        int pos =q.front().first;
        int level = q.front().second;
        q.pop();
        if(pos == 99)
            return level;
        for(int j =pos; j<=(pos+6)&&j<100;j++)
        {
            if(visited[j]==false){
                visited[j] = true;
                if(board[j]!=-1)
                    {
                        visited[board[j]] = true;
                        q.push({board[j],level+1});
                    }
                else
                    q.push({j,level+1});
            }
                
        }
    }
    return -1;
}

int Solution::snakeLadder(vector<vector<int> > &A, vector<vector<int> > &B) {
    memset(board, -1, sizeof board);
    memset(visited, false, sizeof visited);

    for(int i=0;i<A.size();i++)
        board[A[i][0]-1]=board[A[i][1]-1];
    
    for(int i=0;i<B.size();i++)
        board[B[i][0]-1]=board[B[i][1]-1];
    
    return bfs(0);
}

//Ques-4 Knapsack all paths
struct node{
    int i;
    int j;
    string psf;
    
    node(int x, int y, string s):i(x),j(y),psf(s){}
};
int main(){
    int n, cap;
    cin>>n;
    int values[n], weights[n];
    
    for(int i=0;i<n;i++){
        cin>>values[i];
    }
    
    for(int i=0;i<n;i++){
        cin>>weights[i];
    }
    cin>>cap;
    //Step - 1 0/1 knapsack
    int dp[n+1][cap+1];
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=cap;j++){
            if(i==0 || j==0)
                dp[i][j] = 0;
            else if(weights[i-1]>j){
                dp[i][j] = dp[i-1][j];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], values[i-1]+dp[i-1][j-weights[i-1]]);
            }
        }
    }
    
    cout<<dp[n][cap]<<endl;
    //Step-2 BFS
    queue<node> q;
    if(dp[n][cap]==dp[n-1][cap])
        q.push(node(n, cap, " "));
        
    while(!q.empty()){
        node curr = q.front();
        int x = curr.i;
        int y = curr.j;
        string path = curr.psf;
        q.pop();
        if(x==0 || y==0)
        {
            cout<<path<<endl;
        }
        else{
            int exc = dp[x-1][y];
            int inc = y-weights[x-1]>=0?dp[x-1][y-weights[x-1]]+values[x-1]:INT_MIN;
            if(dp[x][y] == exc)
                q.push(node(x-1, y, path));
            if(dp[x][y] == inc){
                q.push(node(x-1, y-weights[x-1], to_string(x-1)+" "+path));
            }
        }
        
    }
}

//Ques-5 Distinct subsequences of a string
int main(){
    string s;
    cin>>s;
    unordered_map<char, int> hashMap;
    long long dp[s.length()+1];             //int wont be able to handle
    dp[0]=1;
    for(int i=1;i < s.length()+1;i++){
        dp[i] = 2*dp[i-1];
        char c = s[i-1];
        if(hashMap.find(c)!=hashMap.end()){
            dp[i] -= dp[hashMap[c]-1];
        }
        hashMap[c] = i;
    }
    cout<<dp[s.length()]-1;
}

//Ques-6 Catalan numbers
int main(){
    int n;
    cin>>n;
    
    int dp[n+1];
    dp[0]=dp[1]=1;
    int sum;
    for(int i=2;i<=n;i++){
        sum=0;
        for(int j=0;j<i;j++){
            sum+= dp[j]*dp[i-j-1];
        }
        dp[i]=sum;
    }
    cout<<dp[n];
}

//Ques-7 Knights tour
#include <bits/stdc++.h>
using namespace std;
int board[9][9];
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
 
void printBoard(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
}
 
bool isSafe(int x,int y){
    if(x<0 or y<0 or x>=8 or y>=8)
        return false;
    if(board[x][y]!=-1)
        return false;
    return true;
}
 
int degree(int x, int y){
    int d = 0;
    for(int i=0;i<8;i++){
        int newx = x +dx[i];
        int newy = y + dy[i];
        if(isSafe(newx, newy))
            d++;
    }
    return d;
}
 
bool dfs(int x, int y, int count)
{
    board[x][y] = count;
    if(count==64)
    {
        return true;
    }   
    vector<tuple<int,int,int>> v;
    for(int i=0;i<8;i++){
        int newx = x+dx[i];
        int newy = y+dy[i];
        if(isSafe(newx, newy))
        {   int d = degree(newx,newy);
            v.push_back({d,newx,newy});}
    }
 
    sort(v.begin(), v.end());
    for(auto [d, x1, y1]: v){
        if(dfs(x1, y1, count+1))
        {   return true;}
    }
    board[x][y] = -1;
    return false;
}
 
int main(){
    memset(board, -1, sizeof board);
    int x,y;
    cin>>x>>y;
    dfs(y-1,x-1,1);
    printBoard();
    return 0;
}

//Ques-8 // optimal strategy for a game
int dp[1000][1000];
int maxValue(int arr[], int low, int high){
    if(low > high)
        return 0;
        
    if(dp[low][high]!=-1)
        return dp[low][high];
        
    int val = max(arr[low]+min(maxValue(arr, low+1, high-1), maxValue(arr, low+2, high)), 
            arr[high]+min(maxValue(arr, low+1, high-1), maxValue(arr, low, high-2)));
    return dp[low][high] = val;
}

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    memset(dp, -1, sizeof dp);
    cout<<maxValue(arr, 0, n-1);
}

//Ques-9 Can an array represent an AP
bool tester(int arr[], int mn, int mx, int n, unordered_map<int, bool>& hashMap){
   int d = (mx - mn)/(n-1);
    for(int i=0;i<n;i++){
        if(hashMap[mn+i*d]==false)
        {   
            return false;
        }
    }
    return true; 
}
int main(){
    int n;
    cin>>n;
    int arr[n];
    int mn = INT_MAX;
    int mx = INT_MIN;
    unordered_map<int, bool> hashMap;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        mn = min(mn, arr[i]);
        mx = max(mx, arr[i]);
        hashMap[arr[i]] = true;
    }
    bool ans = (tester(arr, mn, mx, n, hashMap)==1)?true:false;
    cout<<ans;
}

//Ques 10 Mother vertex
vector<int> adj[100001];
bool visited[100001];
stack<int> s;
void dfs(int src){
    visited[src]=true;
    
    for(auto child:adj[src]){
        if(!visited[child]){
            dfs(child);
        }
    }
    
    s.push(src);
}

int main(){
    int n, m, a, b;
    cin>>n>>m;
    
    while(m--){
        cin>>a>>b;
        adj[a].push_back(b);
    }
    memset(visited, false, sizeof visited);
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            dfs(i);
        }
    }
    
    int possibleMother = s.top();
    while(!s.empty()){
        s.pop();
    }
    memset(visited, false, sizeof visited);
    dfs(possibleMother);
    for(int i=1;i<=n;i++){
        if(visited[i]!=true)
        {
            cout<<-1;return 0;
        }
    }
    cout<<possibleMother;
}