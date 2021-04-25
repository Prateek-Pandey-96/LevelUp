#include <bits/stdc++.h>

//Ques-1
bool isSafe(vector<vector<char>>& grid, int i, int j, int m, int n){
    if( i<0 or i>=m or j<0 or j>=n)
        return false;
    if(grid[i][j]=='0')
        return false;
    return true;
}

void dfs(vector<vector<char>>& grid, int x, int y, int rows, int cols){
    grid[x][y] = '0';   //Mark the cell as visited
    
    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};
    
    for(int i=0;i<4;i++){
        int newX = x + dx[i];
        int newY = y + dy[i];
        if(isSafe(grid, newX, newY, rows, cols))
            dfs(grid, newX, newY, rows, cols);
    }
}

int numIslands(vector<vector<char>>& grid) {
    //We have to find number of connected components in a grid
    //Direct application of Dfs on a grid
    
    int m = grid.size();
    int n = grid[0].size();
    
    int islands = 0;
    //I wont be using an extra viited array instead i will use the grid itself to save space
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            if(grid[i][j]=='1')
                islands++,dfs(grid, i, j, m, n);
    }
    
    return islands;
}

//Ques-2
//I am skipping the use of viited array -1 is for unvisited, 0 is for color1 and 1 is for color2
//This improves the runtie a lot
bool dfsHelper(int src, vector<int> adj[], vector<int> &color, int currentColor){
    color[src] = currentColor;
    
    for(auto child:adj[src]){
        if(color[child]==-1)
        {
            bool problemMili = dfsHelper(child, adj, color, !currentColor);
            if(problemMili)
                return true;
        }    
        else
        {
           if(color[child]==color[src]) 
                return true;
        }
    }
    return false;
}

//I will be using two coloring method for bipartite check
bool isBipartite(vector<vector<int>>& graph) {
    int vertices = graph.size();
    vector<int> adj[vertices];
    
    //Lets form the adjacency list first
    for(int i=0;i<vertices;i++)
        for(int j=0;j<graph[i].size();j++)
            adj[i].push_back(graph[i][j]);
    
    vector<int> color(vertices,-1);
    int currentColor = 0;
    
    bool problemMili;
    for(int i=0;i<vertices;i++){
        if(color[i]==-1)
        {
            problemMili =  dfsHelper(i, adj, color, currentColor);
            if(problemMili==true)
                return false;
        }
    }
    return true;
}

//Ques-3
bool dfsUtil(int src, vector<int>adj[], bool visited[], int parent){
    visited[src] = true;
    
    for(auto child:adj[src])
    if(visited[child]==false)
       {
           bool cycleMila = dfsUtil(child,adj,visited,src);
            if(cycleMila)
                return true;
       }
     else if(child != parent)
        return true;
return false;
}

bool isCycle(int V, vector<int>adj[]){
    bool visited[V];
    memset(visited, false, sizeof visited);
    bool result = false;
    
    for(int i=0;i<V;i++){
        if(visited[i]==false)
         {
             result = dfsUtil(i,adj,visited,-1);
             if(result==true)break;
       }// -1 is the parent here for first node of disconnected components
    }
    
    return result;
}

//Ques-4
int dfs(int src,vector<int> adj[],int visited[]){
    visited[src] = 1;
    visited[src] = 2;
    
    for(auto child:adj[src]){
        if(visited[child]==0)
        {
            int cycleFound = dfs(child,adj,visited);
            if(cycleFound==1)
                return 1;
        }
        else
        {
            if(visited[child]==2)
                return 1;
        }
    }
    visited[src] = 1;
    return 0;
}


int Solution::solve(int A, vector<vector<int> > &B) {
    vector<int> adj[A+1];
    for(int i =0;i<B.size();i++){
        adj[B[i][0]].push_back(B[i][1]);
    }
    
    int visited[A+1];
    memset(visited, 0, sizeof visited);
    //We can run a dfs, we will just need an extra boolan array
    int cycle = false;
    for(int i=1;i<=A;i++)
    {
        cycle=dfs(i,adj,visited);
        if(cycle)
            return 1;
    }
    return 0;
}

//Ques-5 
int main(){
    vector<int> arr;
    int n, element;
    cin>>n;

    for(int i=0;i<n;i++){
        cin>>element;
        arr.push_back(element);
    }
    //Stack will help us in doing it in O(N)
    stack<int> s;
        
    for(int i=0;i<n;i++){
        while(s.empty()==false and s.top() >= arr[i] ){  //Just change the sign here for nearest greater on the left
            s.pop();
        }
        if(s.empty())
            cout<<-1<<" ";
        else
            cout<<s.top()<<" ";
        
        s.push(arr[i]);
    }
    return 0;
}

//Ques-6
int trap(vector<int>& height) {
    //knive algo will give O(N^2)
    //Stacks will give O(N) but O(N) space
    //There is a two pointer technique which gives O(1) space
    if(height.size() == 0 || height.size()==1 || height.size()==2)
        return 0;
    
    int low = 0;
    int high = height.size()-1;
    
    int lMax = height[0];
    int rMax = height[height.size()-1];
    int water = 0;                      //0 on first and last bar
    while(low <= high){
        if(height[low]<height[high]){
            if(height[low]>lMax)
                lMax = height[low];
            water+= lMax - height[low];
            low++;
        }
        else{
            if(height[high]>rMax)
                rMax = height[high];
            water+= rMax - height[high];
            high--;
        }
    }
    return water;
}

//Ques-7
int largestRectangleArea(vector<int>& heights) {
    //We need to find the nex smaller on the left and the right
    //Can be done in O(1) space as well
    vector<int> left;
    stack<int> s;
    
    int h = heights.size();
    
    for(int i=0;i<h;i++){
        while(!s.empty() and heights[s.top()]>=heights[i])
        {
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
    
    while(!s.empty())
    {
        s.pop();
    }
    vector<int> right;
    for(int i = h-1;i>=0;i--){
        while(!s.empty() and heights[s.top()]>=heights[i])
        {
            s.pop();
        }
        if(s.empty()){
            right.push_back(h);
        }
        else{
            right.push_back(s.top());
        }
        s.push(i);
    }
    reverse(right.begin(), right.end());
    
    vector<int> width;
    for(int i=0;i<h;i++){
        width.push_back(right[i]-left[i]-1);
    }
    int ans = 0;
    for(int i=0;i<h;i++){
        ans = max(ans, heights[i]*width[i]);
    }
    
    return ans;
}

//Ques-8
vector <int> calculateSpan(int price[], int n)
{
   //Can be done in O(N) using stack
   stack<int> s;                       //Stack will store index
   vector<int> result;
   for(int i=0;i<n;i++){
       while(!s.empty() and price[s.top()]<=price[i]){
           s.pop();
       }
       if(s.empty()){
           result.push_back(i+1);
       }
       else
        {
            result.push_back(i-s.top());
        }
        s.push(i);
   }
   return result;
}