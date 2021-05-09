#include <bits/stdc++.h>

//Ques -1 Longest path in a Dag
//O(V+E)
const int mn =  INT_MIN;
int main()
{
   int n, m, a, b, c;
   cin>>n>>m;
   vector<pair<int,int>> adj[n];
   vector<int> in;
   vector<int> dist;
   for(int i=0;i<n;i++){
    dist.push_back(mn);
    in.push_back(0);
   }
   while(m--){
       cin>>a>>b>>c;
       adj[a].push_back({b, c});
       in[b]++;
   }
   
   cout<<dist[1];
   //I am taking source to be vertex 1;
   int src = 1;
   dist[src] = 0;
   queue<int> q;
   for(int i=0;i<n;i++){
       if(in[i]==0)
            q.push(i);
   }
   //I will be using Kahn's algo for top sort
   vector<int> topoSortedOrder;
   while(!q.empty()){
       int u = q.front();
       topoSortedOrder.push_back(u);
       q.pop();
       for(auto [v, w]:adj[u]){
           in[v]--;
           if(in[v]==0)
                q.push(v);
       }
   }
   
   //Time to update dist
   for(int i=0;i<topoSortedOrder.size();i++){
       for(auto [child, w]:adj[topoSortedOrder[i]]){
           if(dist[child]<dist[topoSortedOrder[i]]+w)
                dist[child] = dist[topoSortedOrder[i]]+w;
       }
   }
  for(int i=0;i<n;i++){
      cout<<"Longest Distance till node "<<i<<" from node "<<src<<" is "<<dist[i]<<'\n';
  }

}

//Ques-2 Cheapest Flights
//O((V+E)*Log(K))
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    vector<pair<int, int>> adj[n];
    //Forming adjacency list
    for(auto flight:flights){
        adj[flight[0]].push_back({flight[1], flight[2]});
    }
    //MinHeap
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    //Tuple -> {cost, node, stoppage}
    pq.push({0,src,0});
    
    while(!pq.empty()){
        auto [cost, u, stops]=pq.top();
        pq.pop();
        if(u == dst)
            return cost;
        if(stops > K)
            continue;
        for(auto [v, w]:adj[u]){
            pq.push({w+cost, v, stops+1});
        }
    }
    //If no path was found with atmax k stopages
    return -1;
}

//Ques-3 Paint Fence
//O(N)
long long countWays(int n, int k){
    const int MOD = 1000000007;
    long long dp[3][n];
    memset(dp, 0, sizeof dp);
    //First row will store result for n when i and i-1 are of same color
    //Second row will store result for n when i and i-1 are of different color
    //Third row will store the total
    if(n==1)
        return k;
    dp[0][1]=k, dp[1][1]=k*(k-1), dp[2][1]=k*k;
    
    for(int j=2;j<n;j++){
        dp[0][j]=dp[1][j-1];
        dp[1][j]=(dp[2][j-1]*(k-1))%MOD;
        dp[2][j]=(dp[0][j]+dp[1][j])%MOD;
    }
    return dp[2][n-1];
}


//Ques 4 Binary strings with no consequtive 1
//O(N)
ll countStrings(int n) {
   const int MOD = 1000000007;
   ll dp[2][n];
   dp[0][0]=dp[1][0]=1;
   for(int j=1;j<n;j++){
       dp[0][j]=(dp[0][j-1]+dp[1][j-1])%MOD;
       dp[1][j]=dp[0][j-1];
   }
   return (dp[0][n-1]+dp[1][n-1])%MOD;
}

//Ques 5 Check whether strings are rotations of each other

bool areRotations(string str1, string str2)
{
   
   if (str1.length() != str2.length())
        return false;
  
   string temp = str1 + str1; 
    return (temp.find(str2) != string::npos);
}
  

//Ques 5 Min edges to reverse
int main()
{
    int n, m, a, b, src, destination;
    cin>>n>>m;
    vector<pair<int,int>> adj[n];
    while(m--)
    {
        cin>>a>>b;
        adj[a].push_back({b, 0});
        adj[b].push_back({a, 1});
    }
  
    cin>>src>>destination;
    vector<int> dist(n,INT_MAX);
    priority_queue<iPair,vector<iPair>,greater<iPair>> pq;
    pq.push(make_pair(0,src));
    dist[src]=0;
    //vector<bool> vis(v,false);
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        for(auto [v, w]:adj[u]){
            if(dist[v]>dist[u]+w)
                {
                    dist[v]=dist[u]+w\;
                    pq.push(make_pair(dist[v],v));
                
                }
        }
      }
    
    cout<<dist[destination]<<endl;      
}

//Ques 6 Search in a bitonic array
//O(logN)
int Solution::solve(vector<int> &A, int B) {
    int l = 0;
    int h = A.size()-1;
    
    while( l <= h ){
        int mid = l +(h-l)/2;
        if(A[mid]==B)
            return mid;
        
        if(A[mid]<B){
            if(A[mid]<A[mid+1])
                l = mid+1;
            else
                h = mid-1;
        }
        else{ 
            if( A[mid]>A[mid+1])
                l = mid+1;
            else
                h = mid-1;
        }
    }
    return -1;
}

//Ques 7 Find peak element O(logN)
int findPeakElement(vector<int>& nums) {
      //Excellent binary search question
      int low = 0, high =nums.size()-1;
      
      while(low < high){
          int mid = low+(high-low)/2;
          if(nums[mid]>nums[mid+1]){
              high = mid;
          }
          else
          {
              low = mid+1;
          }
      }
      return low;
}

//Ques 8 Word Search
//O(M*N*lengthofword)

bool dfs(vector<vector<char>> board,string word,int i,int j,int level)
{
  if(level>=word.length()-1){
      return true;
  }

  int di[]={-1,0,1,0};
  int dj[]={0,1,0,-1};

  char t = board[i][j];
  board[i][j]='#';

  for(int m=0; m<4; m++){
      int pi=i+di[m];
      int pj=j+dj[m];
      if(pi>=0&&pi<board.size()&&pj>=0&&pj<board[0].size()&&board[pi][pj]==word[level+1]){
          if(dfs(board,word,pi,pj,level+1)){
              return true;
          }
      }
  }

  board[i][j]=t;

  return false;
  }

  bool exist(vector<vector<char>>& board, string word) {
      int m = board.size();
      int n = board[0].size();


  for(int i=0; i<m; i++){
      for(int j=0; j<n; j++){
         if(board[i][j]==word[0])
          {
              //Make a dfs call
              bool exists = dfs(board,word,i,j,0);
              if(exists)
                  return 1;
          }
      }
  }

  return 0;
}

//Ques-9 Maximum sub subarray with no adjacent elements
int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    int dp[2][n];
    dp[0][0]=arr[0];    //Include ith
    dp[1][0]=0;         //Exclude ith
    
    for(int i=1;i<n;i++){
        dp[0][i] = dp[1][i-1]+arr[i];
        dp[1][i] = max(dp[1][i-1], dp[0][i-1]);
    }
    
    cout<<max(dp[0][n-1], dp[1][n-1]);
}

//Ques-10 Paint house
//Time - O(N)
int main(){
    int n, a, b, c;
    cin>>n;
    int dp[n][3];
    for(int i=0;i<n;i++){
        cin>>a>>b>>c;
        if(i==0)
            dp[i][0]=a, dp[i][1]=b, dp[i][2]=c;
        else{
            dp[i][0] = a + min(dp[i-1][1], dp[i-1][2]);
            dp[i][1] = b + min(dp[i-1][0], dp[i-1][2]);
            dp[i][2] = c + min(dp[i-1][0], dp[i-1][1]);
        }
    }
    
    cout<< min(dp[n-1][0], min(dp[n-1][1], dp[n-1][2]));
}

//Ques 11 Paint house - 2 (Extension of ques 10)
//O(N^3)
int main(){
    int n, k, a, b, c;
    cin>>n>>k;
    int arr[n][k];
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            cin>>arr[i][j]; 
        }
    }
    int dp[n][k];
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            if(i==0)
                dp[i][j]=arr[i][j];
            else
            {
                dp[i][j] = arr[i][j];
                int mn = INT_MAX;
                for(int a=0;a<k;a++){
                    if(a==j)continue;
                    mn = min(mn,dp[i-1][a]);
                }
                dp[i][j]+=mn;
            }
        }
    }
    
    int ans = dp[n-1][0];
    for(int j=1;j<k;j++){
        ans = min(ans, dp[n-1][j]);
    }
    
    cout<<ans;
}

//Ques-12 Tiling 1
//O(N)
//Fibonnaci