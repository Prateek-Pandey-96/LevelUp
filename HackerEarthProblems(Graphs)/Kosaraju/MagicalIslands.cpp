//Kosaraju - length of longest scc
#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100001];
vector<int> tAdj[100001];
bool visited[100001];
stack<int> s;

void dfs1(int src){
	visited[src] = true;

	for(auto child:adj[src]){
		if(!visited[child]){
			dfs1(child);
		}
	}

	s.push(src);
}

void dfs2(int src, int& size){
	visited[src] = true;
	size++;
	for(auto child:tAdj[src]){
		if(!visited[child]){
			dfs2(child, size);
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
	memset(visited, false, sizeof visited);
	for(int i=1;i<=n;i++){
		if(!visited[i])
			dfs1(i);
	}
	memset(visited, false, sizeof visited);
	int size = 0;
	int mx = 0;
	while(!s.empty()){
		int curr = s.top();
		s.pop();
		if(visited[curr]==false)
		{	size = 0;
			dfs2(curr, size);
			mx = max(mx, size);
		}
	}
	cout<<mx<<endl;
}