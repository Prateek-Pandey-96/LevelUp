#include<bits/stdc++.h>

//Ques -1 Subordiates of each node
//Time - O(N) 
const int N= 200000;
vector<int> adj[N+1];
int sub[N+1];
 
int dfs(int src, int parent){
	sub[src] = 0;
 
	for(auto child:adj[src]){
		if(child == parent)continue;
        sub[src] += 1+dfs(child, src);
	}
	return sub[src];
}
 
int main(){
	int n, a;
	cin>>n;
	//Tree Formation
	for(int i=2;i<=n;i++){
		cin>>a;
		adj[a].push_back(i);
		adj[i].push_back(a);
	}
	dfs(1, 0);
 
	for(int i=1;i<=n;i++){
		cout<<sub[i]<<" ";
	}
}

//Ques-2 Diameter of a binary tree
vector<int> tree[200001];
int ans[200001], depth[200001];
 
void dfs(int src, int parent)
{
	int m1 = -1, m2 = -1;    //max and second max depth
	for(auto child:tree[src]){
		if(child == parent)continue;
		dfs(child, src);
		//after dfs of child we have all the info of the child
		if(depth[child]>=m1){
			m2 = m1;
			m1 = depth[child];
		}
		else if(depth[child > m2])
		{
			m2 = depth[child];
		}
	}
	ans[src] = m1+m2+2;
	depth[src] = max(m1, m2)+1;
}
 
signed main(){
	int n;
	cin>>n;
	int a, b;
	// n-1 edges
	for(int i=1;i<n;i++){
		cin>>a>>b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
 
	dfs(1, 0);
 
	int res = -2;
	for(int i=1;i<=n;i++){
		res = max(res, ans[i]);
	}
 
	cout<<res;
}

//Ques-3 Rerooting a tree
#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> adj[200001];    // our tree
int sum[200001], cnt[200001], ans[200001];

void dfs1(int src, int parent){
	sum[src] = 0;
	cnt[src] = 1;

	for(auto child:adj[src]){
		if(child==parent)continue;
		dfs1(child, src);
		cnt[src]+=cnt[child];

		sum[src] += sum[child]+cnt[child];

	}

}

void dfs2(int src, int parent){
	int s1 = cnt[src];
	int t1 = sum[src];
	ans[src] = sum[src];
	for(auto child:adj[src]){
		if(child==parent)continue;

		int s2 = cnt[child];
		int t2 = sum[child];

		//Transferrinf node from src to child
		cnt[src] -= cnt[child];
		sum[src] -=(sum[child]+cnt[child]);
		cnt[child] +=cnt[src];
		sum[child] += (sum[src]+cnt[src]);

		
		dfs2(child, src);

		cnt[src] = s1;
		sum[src] = t1;
		cnt[child] = s2;
		sum[child] = t2;
	}
}

signed main(){
	int n;
	cin>>n;
	int a,b;
	int m = n-1;
	while(m--){
		cin>>a>>b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs1(1, 0);
	dfs2(1, 0);
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
}