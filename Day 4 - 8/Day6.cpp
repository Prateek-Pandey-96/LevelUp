#include<bits/stdc++.h>

//Ques 1 Kosaraju
vector<int> adj[100001];
vector<int> tAdj[100001];
bool visited[100001];

void dfs1(int src, stack<int>& s){
    visited[src] = true;
    
    for(auto child : adj[src]){
        if(!visited[child]){
            dfs1(child, s);
        }
    }
    
    s.push(src);
}

void dfs2(int src){
    visited[src] = true;
    
    for(auto child: tAdj[src]){
        if(!visited[child]){
            dfs2(child);
        }
    }
}

int main(){
    int n, m, a, b;
    cin>>n>>m;
    memset(visited, false, sizeof visited);
    while(m--){
        cin>>a>>b;
        adj[a].push_back(b);       //Graph
        tAdj[b].push_back(a);      //Transpose Graph
    }
    
    stack<int> s;
    for(int i=1;i<=n;i++){
        if(visited[i]==false)
            dfs1(i, s);
    }
    
    memset(visited, false, sizeof visited);
    
    int count =0;
    while(!s.empty()){
        if(!visited[s.top()]){
            count++;
            dfs2(s.top());
        }
        s.pop();
    }
    
    cout<<count;
}

//Ques 2 Level Order Traversal Tree
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if(root == NULL)
        return result;
    queue<TreeNode*> q;
    vector<int> v;
    
    q.push(root);
    
    while(!q.empty()){
        int n = q.size();
        for(int i=0;i<n;i++){
            TreeNode* temp = q.front();
            q.pop();
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
            v.push_back(temp->val);
        }
        result.push_back(v);
        v.clear();
    }
    
    return result;
}