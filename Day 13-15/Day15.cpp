#include <bits/stdc++.h>

//Ques-1 Oliver and the game
//Time O(V+E) Space- O(V)
//Euler's tree flattening
#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100001];
int inTime[100001];
int outTime[100001];
bool visited[100001];
int timer = 0;
 
void dfs(int src){
    inTime[src]=timer++;
    visited[src] = true;
 
    for(auto child:adj[src]){
        if(!visited[child]){
            dfs(child);
        }
    }
    outTime[src]=timer++;
}
 
int main(){
    ios::sync_with_stdio(0);        //Without fast Io it gives tle
    cin.tie(0);
    int n, a, b, q;
    cin>>n;
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        inTime[a]=inTime[b]=0;
        outTime[a]=outTime[b]=0;
        visited[a]=visited[b]=false;
    }
    
    dfs(1);
    cin>>q;
    int opt, oliver, bob;
    while(q--){
        cin>>opt>>oliver>>bob;
        if(opt == 1)
            swap(oliver, bob);
        if(inTime[oliver]<inTime[bob] && outTime[oliver]>outTime[bob])
        {
            cout<<"YES"<<'\n';
        }else
            cout<<"NO"<<'\n';
 
    }
}

//Ques 2 Spiral Matrix
//Time-O(M*N) Space - O(M*N)
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    int m = matrix.size();
    int n = matrix[0].size();
    
    int t=0, l=0;
    int b=m-1, r=n-1;
    int k;
    
    while(l<=r and t<=b){
        k=l;
        while(k<=r){
            result.push_back(matrix[t][k]);
            
            k++;
        }
        t++;
        if(t>b)break;
        k=t;
        while(k<=b){
            result.push_back(matrix[k][r]);
            
            k++;
        }
        r--;
        if(r<l)break;
        k=r;
        while(k>=l){
            result.push_back(matrix[b][k]);
            
            k--;
        }
        b--;
        if(t>b)break;
        k=b;
        while(k>=t){
            result.push_back(matrix[k][l]);
            
            k--;
        }
        
        l++;
        if(r<l)break;
    }
    return result;
}

//Ques - 3 Search in a matrix
//Time - O(log(M)+log(N))    
bool searchRow(vector<vector<int>>& matrix, int target, int row)
{
    int m = matrix.size();
    int n = matrix[0].size();
    int low = 0;
    int high = n-1;
    while(low<=high){
        int mid = low+(high-low)/2;
        if(matrix[row][mid]==target)
            return true;
        else if(matrix[row][mid]>target)
            high = mid-1;
        else
            low = mid+1;
    }
    return false;
}
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    //first we can find row through binary search and then the column
    int low = 0;
    int high = m-1;
    while(low <= high){
        int mid = low+(high-low)/2;
        if(matrix[mid][0]<=target and matrix[mid][n-1]>=target)
            return searchRow(matrix, target, mid);
        else if(matrix[mid][0]>target)
            high = mid-1;
        else
            low = mid+1;
    }
   return false;
}

//Ques - 3 Search in a matrix
//Time - O(M+N)
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    int r = 0;
    int c = n-1;
    while(r < m and c >= 0){
        if(matrix[r][c]==target)
            return true;
        else if(matrix[r][c]>target)
            c--;
        else
            r++;
    }
    return false;
}

//Ques - 4 //Rotate a matrix 90deg cloclwise
//Time - O(M)
void rotate(vector<vector<int>>& matrix) {
    //transpose the matrix then reverse the rows
    int n = matrix.size();
    int m = matrix[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++)
            swap(matrix[i][j], matrix[j][i]);
    }
    
    for(int i=0;i<n;i++){
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

//Ques-5 //LCA of a binary tree
//Time - O(N)
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == NULL)
        return NULL;
    if(root->val == p->val || root->val==q->val)
        return root;
    
    TreeNode* lca_left = lowestCommonAncestor(root->left, p, q);
    TreeNode* lca_right = lowestCommonAncestor(root->right, p, q);
    
    if(lca_left and lca_right)
        return root;
    return (lca_left==NULL?lca_right:lca_left);
}

//Ques-6 //Longest path in a matrix
//Time O(M*N)
int dp[201][201];
bool isSafe(vector<vector<int>>& matrix, int i, int j, int pre){
    if(i<0 or j<0 or i>=matrix.size() or j>=matrix[0].size())
        return false;
    return matrix[i][j]>pre;
}

int dfs(vector<vector<int>>& matrix, int i, int j){
    if(dp[i][j]!=-1)
        return dp[i][j];
    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};
    
    int dist = 1;int mx =0;
    for(int k=0;k<4;k++){
        if(isSafe(matrix, i+dx[k], j+dy[k], matrix[i][j])){
            mx = max(mx, dfs(matrix, i+dx[k], j+dy[k]));
        }
    }
    return dp[i][j] = 1+mx;
    
}

int longestIncreasingPath(vector<vector<int>>& matrix) {
    memset(dp, -1, sizeof dp);
    int ans = INT_MIN;
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++){
            ans = max(ans, dfs(matrix, i, j));
        }
    }
    return ans;
}

//Ques-7 //House Robber 
//Time - O(N)
//Method -1
int rob(vector<int>& nums) {
    int n = nums.size();
    int dp[2][n];
    dp[0][0] = nums[0];
    dp[1][0] = 0;
    for(int j=1;j<n;j++){
        dp[0][j] = dp[1][j-1]+nums[j];
        dp[1][j] = max(dp[0][j-1], dp[1][j-1]);
    }
    return max(dp[0][n-1], dp[1][n-1]);
}

//Ques-8 //House Robber 2
//Time - O(N) Takes half the space
int rob(vector<int>& nums) 
{
    int n = nums.size();
    if(n==1)
        return nums[0];
    int profit[n];
    //First lets not take the first house
    profit[0]=0;
    profit[1]=nums[1];
    
    for(int i=2;i<n;i++){
        profit[i] = max(profit[i-1],nums[i]+profit[i-2]);
    }
    int tempAnsOne = profit[n-1];
    
    memset(profit, 0, sizeof profit);
    //Now lets take the first house
    profit[0] = nums[0];
    profit[1] = max(nums[1],nums[0]);
    
    for(int i=2;i<n-1;i++){
        profit[i] = max(profit[i-1],nums[i]+profit[i-2]);
    }
    profit[n-1]=0;
    int tempAnsTwo = profit[n-2];
    
    return max(tempAnsOne, tempAnsTwo);
}        