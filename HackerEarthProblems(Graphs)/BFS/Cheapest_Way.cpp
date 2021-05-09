#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> iPair;
typedef pair<int,iPair> iiPair;
 
const int INF = 9e17;
 
signed main(){
	int n, m;
	cin>>n>>m;
	int a, b, c;
	vector<iPair> adj[n+1];
	while(m--){
		cin>>a>>b>>c;
		adj[a].push_back({b,c});
	}
 
	vector<int> dist(n+1, INF);
	vector<int> disc(n+1, INF);
 
	priority_queue<iiPair, vector<iiPair>, greater<iiPair>> pq;    //min heap
 
	pq.push({0,{1,0}});    //0 indicates coupon not used 1 indictes coupon used or you can use vice versa paani barsa
	dist[1] = 0;
	disc[1] = 0;
 
	while(!pq.empty()){
		int u = pq.top().second.first;
		int couponUseKiya = pq.top().second.second;
		int d = pq.top().first;
		pq.pop();
 
		if(couponUseKiya)
			if(disc[u] < d)continue;
 
		if(!couponUseKiya)
			if(dist[u] < d)continue;
 
		for(auto [v,w]:adj[u]){
			if(couponUseKiya){
				if(disc[v] > w+d)
				{
					disc[v] = d+w;
					pq.push({disc[v],{v,couponUseKiya}});
				}
			}
			else{
				if(dist[v] > w+d){
					dist[v] = w+d;
					pq.push({dist[v],{v,couponUseKiya}});
				}
				if(disc[v] > d+0){
					disc[v] = d+0;
					pq.push({disc[v],{v,!couponUseKiya}});
				}
			}
		}
	}
 
	cout<<disc[n];
}
