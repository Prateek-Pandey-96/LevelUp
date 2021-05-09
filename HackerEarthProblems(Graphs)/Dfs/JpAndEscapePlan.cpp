#include<bits/stdc++.h>
using namespace std;
#define int long long

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void printSolution(vector<pair<int,int>>& result){
	for(auto r: result){
		cout<<r.first<<" "<<r.second<<'\n';
	}	
}

bool isSafe(int x, int y, vector<vector<int>>& grid, vector<vector<bool>>& visited ){
	if(x<=0 or x>grid.size() or y<=0 or y>grid[0].size())
		return false;
	if(visited[x][y])
		return false;
	return true;
}
bool dfs(int x, int y, vector<vector<int>>& grid, vector<vector<bool>>& visited, vector<pair<int,int>>& result, int& jump ){
	visited[x][y] = true;
	result.push_back({x, y});
	if(x==1 or y==1){
		return true;
	}
	for(int i=0;i<4;i++){
		int newX = x+dx[i];
		int newY = y+dy[i];
		if(isSafe(newX, newY, grid, visited) and grid[newX][newY]<=grid[x][y] and grid[newX][newY] >= grid[x][y] - jump ){
			bool isPossible = dfs(newX, newY, grid, visited, result, jump);
			if(isPossible)
				return true;
		}
	}
	result.pop_back();
	return false;
}

signed main(){
	int n, m, startx, starty, jump;
	cin>>n>>m;

	vector<vector<int>> grid(n+1, vector<int>(m+1, 0));
	vector<vector<bool>> visited(n+1, vector<bool>(m+1, false));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>grid[i][j];
		}
	}

	cin>>startx>>starty>>jump;
	vector<pair<int,int>> result;
	if(dfs(startx, starty, grid, visited, result, jump))
	{
		cout<<"YES"<<'\n';
		printSolution(result);
	}
	else
	{
		cout<<"NO";
	}
}