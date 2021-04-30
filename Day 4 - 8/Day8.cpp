#include <bits/stdc++.h>

//Ques1 Cycle in a directed graph
bool cycleHelper(int src, vector<int> adj[], vector<int>& vis){
    vis[src] = 1;
    vis[src] = 2;
    
    for(int child:adj[src]){
        if(vis[child]==0)
        {
            bool failure = cycleHelper(child, adj, vis);
            if(failure)
                return true;
        }
        else{
            if(vis[child]==2)
                return true;
        }
    }
    vis[src] = 1;
    return false;
}
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
//We can just check if a topological sort is possible or not
//Graph should be Directed acyclic graph
//Problem boils down to finding a cycle in a directed graph
int n = numCourses;

if(prerequisites.size()==0)
    return true;
vector<int> adj[n];
vector<int> vis(n, 0);

for(int i=0;i<prerequisites.size();i++)
    adj[prerequisites[i][1]].push_back(prerequisites[i][0]);

for(int i=0;i<n;i++){
    if(vis[i]==0)
    {
        bool failure = cycleHelper(i, adj, vis);
        if(failure)
            return false;
    }    
}
return true;
}

//Ques-2 Kahn's algo for topological sorting
bool cycleHelper(int src, vector<int> adj[], int vis[]){
    vis[src] = 1;
    vis[src] = 2;

    for(int child:adj[src]){
        if(vis[child]==0)
        {
            bool failure = cycleHelper(child, adj, vis);
            if(failure)
                return true;
        }
        else{
            if(vis[child]==2)
                return true;
        }
    }
    vis[src] = 1;
    return false;
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    //Adjacency list
    vector<int> adj[numCourses];
    
    int inDegree[numCourses];
    memset(inDegree, 0, sizeof inDegree);
    int visited[numCourses];
    memset(visited, 0, sizeof visited);
    vector<int> ans;
    //Forming the graph
    for(int i =0;i<prerequisites.size();i++){
        adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
        inDegree[prerequisites[i][0]]++;
    }
    //Checking for a cycle first
    for(int i=0;i<numCourses;i++){
        if(!visited[i]){
            bool cycleMili = cycleHelper(i, adj, visited);
            if(cycleMili)
                return ans;
        }
    }
    
    
    //Lets use Kahn's algorithm
    queue<int> q;
    for(int i=0;i<numCourses;i++){
        if(inDegree[i]==0)
            q.push(i);
    }
    
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        ans.push_back(curr);
        for(auto child:adj[curr]){
            inDegree[child]--;
            if(inDegree[child]==0)
                q.push(child);
        }
    }
    
    return ans;
}

//Ques-3 Longest subarray with sum divisible by k
int main(){
    int n, k;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
        if(i!=0)
            arr[i]+=arr[i-1];
    }
    cin>>k;
    unordered_map<int, int> hashMap;
    int length = 0;
    hashMap[0] = -1;
    for(int i=0;i<n;i++){
        int rem = arr[i]%k;
        while(rem < 0)
            rem = (rem+k);
            
        if(hashMap.find(rem)!=hashMap.end())
            length = max(length, i - hashMap[rem]);
        else
            hashMap[rem] = i;
    }
    
    cout<<length<<endl;
}

//Ques-4 Number of subarrays with sum divisible by k
int main(){
    int n, k;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
        if(i!=0)
            arr[i]+=arr[i-1];
    }
    cin>>k;
    unordered_map<int, int> hashMap;
    int count = 0;
    hashMap[0]++;
    for(int i=0;i<n;i++){
        int rem = arr[i]%k;
        while(rem < 0)
            rem = (rem+k);
            
        if(hashMap.find(rem)!=hashMap.end())
            count += hashMap[rem];
        hashMap[rem]++;
    }
    
    cout<<count<<endl;
}

//Ques-5 Josephus Problem
int printLast(int n, int k){
    if(n==1){
        return 0;
    }
    int x = printLast(n-1, k);
    int y = (x+k)%n;
    return y;
}

int main(){
    int n, k;
    cin>>n>>k;
    cout<<printLast(n, k);
}

//Ques-6 NQueen Solver
bool isSafe(int row, int col, vector<vector<char>>& board){
    int i = row;
    int j = col;
    
    while(i>=0){
        if(board[i][j]=='q')
            return false;
        i--;
    }
    i = row;
    
    while(i>=0 and j>=0){
        if(board[i][j]=='q')
            return false;
        i--;
        j--;
    }
    
    i = row;
    j = col;
    while(i>=0 and j<board.size()){
        if(board[i][j]=='q')
            return false;
        i--;
        j++;
    }
    return true;
}
void printBoard(vector<vector<char>>& board){
    int row = board.size();
    int col = board.size();
    
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<'\n';
    }
    cout<<'\n';
}

void NQueenSolver(int row, int n, vector<vector<char>>& board){
    if(row == n)
    {
        printBoard(board);
        return;
    }
    
    for(int j=0;j<n;j++){
        if(isSafe(row, j, board))
        {
            board[row][j] = 'q';
            NQueenSolver(row+1, n, board);
            board[row][j] = '-';
        }
    }
}

int main(){
    int n;
    cin>>n;
    vector<vector<char>> board(n, vector<char>(n, '-'));
    
    NQueenSolver(0, n, board);
}

//Ques - 7 Min deletions to form pallindrome
int main(){
    string s;
    cin>>s;
    
    //Calculate LPS and subtract from length
    
    string s2 = s;
    reverse(s.begin(), s.end());
    
    int dp[s.size()+1][s.size()+1];
    
    for(int i=0;i<=s.size();i++){
        for(int j=0;j<=s.size();j++){
            if(i==0 || j==0)
                dp[i][j] = 0;
            else if(s[i-1]==s2[j-1])
                dp[i][j]=1+dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    cout<<s.size()-dp[s.size()][s.size()]<<endl;
}

//Ques-8  Kadane's Algorithm
int main(){
    int n;
    cin>>n;
    int arr[n];
    
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    int local_max = 0;
    int global_max = INT_MIN;
    
    for(int i=0;i<n;i++){
        local_max = max(local_max+arr[i], arr[i]);
        global_max = max(global_max, local_max);
    }
    
    cout<<global_max;
}