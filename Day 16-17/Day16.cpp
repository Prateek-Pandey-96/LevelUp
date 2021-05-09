#include<bits/stdc++.h>

//Ques 1 Queue Monk and time Hackerearth
//Time - O(N)
int main(){
	int n, a;
	cin>>n;
	queue<int> q;
	for(int i=0;i<n;i++){
		cin>>a;
		q.push(a);
	}
	int time =0;
	for(int i=0;i<n;i++){
		cin>>a;
		while(a!=q.front())
		{
			int front = q.front();
			q.pop();
			q.push(front);
			time+=1;
		}
		q.pop();
		time++;
	}
	cout<<time;
}

//Ques-2 Topo Sort Course Schedule Cses
//Time - O(V+E)
#define int long long
const int N = 100001;
vector<int> adj[N];
int visited[N];
int inDegree[N];
//Cycle in a directed graph
bool findCycle(int src){
	visited[src]=1;
	visited[src]=2;

	for(auto child:adj[src]){
		if(visited[child]==0)
		{
			bool check = findCycle(child);
			if(check)
				return true;
		} else if(visited[child]==2)
		{
			return true;
		}	
	}
	visited[src] = 1;
	return false;
}

signed main(){
	int n,m, a, b;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		adj[a].push_back(b);
		inDegree[b]++;
	}

	//First check for cycle 
	bool check;
	for(int i=1;i<=n;i++){
		if(visited[i]==0)
		{
			check = findCycle(i);
			if(check)
			{
				break;
			}
		}	
	}

	if(check){
		cout<<"IMPOSSIBLE";
	} else {
		//Now apply Kahns top sort
		queue<int> q;
		for(int i=1;i<=n;i++){
			if(inDegree[i]==0)
				q.push(i);
		}

		while(!q.empty()){
			int curr = q.front();
			q.pop();
			cout<<curr<<" ";

			for(auto child:adj[curr]){
				inDegree[child]--;
				if(inDegree[child]==0)
					q.push(child);
			}
		}
	}

}

//Ques-3 Longest Flight CSES
#define int long long
const int N = 100001;
vector<int> adj[N];
int dist[N], parent[N];
int inDegree[N];

signed main(){
	int n,m, a, b;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		adj[a].push_back(b);
		inDegree[b]++;
	}
	queue<int> q;
	//Pruning
	for(int i=2;i<=n;i++){
		if(inDegree[i]==0)
			q.push(i);
	}
	while(!q.empty()){
		int src = q.front();
		q.pop();
		for(auto child:adj[src]){
			inDegree[child]--;
			if(inDegree[child]==0)
				q.push(child);
		}
	}
	//---------
	
	q.push(1);
	parent[1] = 0;

	while(!q.empty()){
		int src = q.front();
		q.pop();
		for(auto child:adj[src]){
			if(dist[child]<dist[src]+1)
			{
				dist[child] = dist[src] + 1;
				parent[child] = src;
			}
			inDegree[child]--;
			if(inDegree[child]==0)
				q.push(child);
		}
	}
	if(dist[n]==0)
		cout<<"IMPOSSIBLE";
	else{
		cout<<dist[n]+1<<endl;
		vector<int> result;
		result.push_back(n);
		while(n!=1){
			n = parent[n];
			result.push_back(n);
		}
		reverse(result.begin(), result.end());
		for(auto i:result){
			cout<<i<<" ";
		}
	}

}

//Ques 4 Game routes
#define int long long
const int N = 100001;
vector<int> adj[N];
int ways[N];
int inDegree[N];

signed main(){
	int n,m, a, b;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		adj[a].push_back(b);
		inDegree[b]++;
	}
	queue<int> q;
	//Pruning
	for(int i=2;i<=n;i++){
		if(inDegree[i]==0)
			q.push(i);
	}
	while(!q.empty()){
		int src = q.front();
		q.pop();
		for(auto child:adj[src]){
			inDegree[child]--;
			if(inDegree[child]==0)
				q.push(child);
		}
	}
	//---------
	
	q.push(1);
	ways[1] = 1;
	while(!q.empty()){
		int src = q.front();
		q.pop();
		for(auto child:adj[src]){
			ways[child]=(ways[child]+ways[src])%1000000007;
			inDegree[child]--;
			if(inDegree[child]==0)
				q.push(child);
		}
	}
	
		cout<<ways[n];


}

//Ques-5 Shortest Paths 1 CSES
//Time O(V+ELogV)
#define int long long
signed main(){
	int n, m, u, v, w;
	cin>>n>>m;
	vector<pair<int,int>> adj[n+1];
	std::vector<int> dist(n+1, LONG_MAX);
	while(m--){
		cin>>u>>v>>w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	dist[1] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
	pq.push({0, 1});

	while(!pq.empty()){
		int src = pq.top().second;
		int d = pq.top().first;
		pq.pop();
		if(dist[src]<d)continue;
		for(auto [child, w]:adj[src]){
			if(dist[child]>d+w)
			{
				dist[child] = d+w;
				pq.push({dist[child], child});
			}
		}
	}

	for(int i=1;i<=n;i++){
		cout<<dist[i]<<" ";
	}
}

//Ques-6 Shortest Paths 2 CSES
//Time - O(V^3)
const int INF = 9e15;
#define int long long
signed main(){
	int n, m, q, u, v, w;
	cin>>n>>m>>q;
	vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			dp[i][j]=dp[j][i] = INF;
		}
	}
	while(m--){
		cin>>u>>v>>w;
		dp[u][v] = dp[v][u] = min(w, dp[u][v]);
	}

	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);
			}
		}
	}

	while(q--){
		cin>>u>>v;
		cout<<(dp[u][v]!=INF?dp[u][v]:-1)<<endl;
	}
}

//Ques-7 WordBreak using Trie
unordered_map<string, bool> dp;
struct TrieNode{
    bool isEndOfWord;
    TrieNode* arr[26];

    TrieNode(){
        isEndOfWord = false;
        for(int i=0;i<26;i++)
            arr[i] = NULL;
    }
};

void addWord(TrieNode* root, string word){
    TrieNode* crawl = root;
    for(int i=0;i<(int)word.length();i++){
        char c = word[i];
        if(crawl->arr[c-'a']==NULL){
            crawl->arr[c-'a']=new TrieNode();
        }
        crawl = crawl->arr[c-'a'];
    }
    crawl->isEndOfWord = true;
}
bool findWord(TrieNode* root, string word){
    TrieNode* crawl = root;
    for(int i=0;i<(int)word.length();i++){
        char c = word[i];
        if(crawl->arr[c-'a']==NULL)
            return false;
        crawl = crawl->arr[c-'a'];
    }
    return crawl->isEndOfWord;
}
bool solver(string s, TrieNode* root){
    if(dp.count(s))
        return dp[s];
    if(s == "")
        return true;
    for(int i=1;i<=s.length();i++){
        if(findWord(root, s.substr(0, i)) and solver(s.substr(i, s.size()-i), root))
        {return dp[s]=true;}
    }
    
    return dp[s]=false;
} 

bool wordBreak(string s, vector<string>& wordDict) {
    //Lets use Trie
    TrieNode* root = new TrieNode();
    for(int i=0;i<wordDict.size();i++)
        addWord(root, wordDict[i]);
    
    return solver(s, root);
}

//Ques-8 Max Depth of an N-Array tree
//Time - O(logN)
int maxDepth(Node* root) {
    if(root == NULL)
        return 0;
    int mx = 0;
    for(auto child : root->children)
        mx = max(mx, maxDepth(child));
    
    return 1+mx;
}

//Ques-9 Sorted array to BST
//Time -O(N)
TreeNode* helper(vector<int>& nums, int i, int j){
    if(i>j)
        return NULL;
    if(i==j)
        return new TreeNode(nums[i]);
    int mid = i + (j - i)/2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = helper(nums, i, mid-1);
    root->right = helper(nums, mid+1, j);
    return root;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return helper(nums, 0, nums.size()-1);
}

//Ques-10 Binary Tree from inorder and preorder traversal
TreeNode* construct_binary_tree_preorder_inorder(int& pre_idx, int l, int h, unordered_map<int,int>& m, vector<int>& preorder, vector<int>& inorder)
{
	if(l>h)
	    return NULL;

	TreeNode* root = new TreeNode(preorder[pre_idx]);
	int in_idx = m[preorder[pre_idx]];
	pre_idx++;
	//Order matters but why?
	root->left = construct_binary_tree_preorder_inorder(pre_idx, l, in_idx-1, m, preorder, inorder);
	root->right = construct_binary_tree_preorder_inorder(pre_idx, in_idx+1, h, m, preorder, inorder);
	return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	unordered_map<int,int> m;
	for(int i=0; i<inorder.size();i++){
	    m[inorder[i]]=i;
	}
	int pre_idx = 0;
	return construct_binary_tree_preorder_inorder(pre_idx, 0, preorder.size()-1, m, preorder, inorder);
}