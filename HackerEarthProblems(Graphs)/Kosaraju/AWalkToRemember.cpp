//Kosasraju - Number of cycles
//Time - O(V+E)
#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100001];
vector<int> tAdj[100001];
bool visited[100001];
stack<int> s;
vector<int> scc;
int ans[100001];

void dfs1(int src){
	visited[src] = true;

	for(auto child:adj[src]){
		if(!visited[child]){
			dfs1(child);
		}
	}

	s.push(src);
}

void dfs2(int src){
	visited[src] = true;
	scc.push_back(src);
	for(auto child:tAdj[src]){
		if(!visited[child]){
			dfs2(child);
		}
	}
}

void updateAns(){
	if(scc.size()>1)
	{
		for(auto node : scc){
			ans[node]=1;
		}
	}
}

int main(){
	int n, m, a, b;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		adj[a].push_back(b);     //Graph
		tAdj[b].push_back(a);	 //Transposed Graph
	}
	memset(ans, 0, sizeof ans);
	memset(visited, false, sizeof visited);
	for(int i=1;i<=n;i++){
		if(!visited[i])
			dfs1(i);
	}
	memset(visited, false, sizeof visited);
	while(!s.empty()){
		int curr = s.top();
		s.pop();
		if(visited[curr]==false)
		{
			scc.clear();
			dfs2(curr);
			updateAns();
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
}