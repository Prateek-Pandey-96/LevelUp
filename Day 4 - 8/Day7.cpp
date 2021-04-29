#include <bits/stdc++.h>

//Ques-1 All paths with max gold
struct node{
    int i;
    int j;
    string psf = "";
    
    node(int x, int y, string s):i(x), j(y), psf(s){}
};
int main(){
    int n, m;
    cin>>n>>m;
    int board[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
        }
    }
    int dp[n][m];
    //Lets form the dp table first-----------
    for(int i=0;i<n;i++){
        dp[i][m-1]=board[i][m-1];
    }
    
    for(int j=m-2;j>=0;j--){
        for(int i=0;i<n;i++){
            if(i==0){
                dp[i][j] = board[i][j] + max(dp[i][j+1], dp[i+1][j+1]);
            } else if(i==n-1){
                dp[i][j] = board[i][j] + max(dp[i-1][j+1], dp[i][j+1]);
            }else
            {
                dp[i][j] = board[i][j] + max(dp[i+1][j+1],max(dp[i-1][j+1], dp[i][j+1]));
            }
        }
    }
    //----------------------------------------
    //Time to do bfs--------------------------
    int m_ = -5;
    int count =0;
    for(int i=0;i<n;i++){
        m_ = max(m_, dp[i][0]);
    }
    cout<<m_<<endl;
    queue<node> q;
    for(int i=0;i<n;i++){
        if(dp[i][0]==m_)
        {
            node newnode(i, 0 ,to_string(i) + " ") ;
            q.push(newnode);
        }
    }
    
    while(!q.empty()){
        node curr = q.front();
        q.pop();
        int nextNode;
        if(curr.j==m-1)
            cout<<curr.psf<<endl;
        else if(curr.i == 0)
        {
            nextNode = max(dp[curr.i+1][curr.j+1], dp[curr.i][curr.j+1]);
            if(nextNode == dp[curr.i][curr.j+1]){
                q.push(node(curr.i, curr.j+1, curr.psf + "d2 "));
            }
            if(nextNode == dp[curr.i+1][curr.j+1]){
                q.push(node(curr.i+1, curr.j+1, curr.psf + "d3 "));
            }
        }
        else if(curr.i == n-1)
        {
            nextNode = max(dp[curr.i-1][curr.j+1], dp[curr.i][curr.j+1]);
            if(nextNode == dp[curr.i-1][curr.j+1]){
                q.push(node(curr.i-1, curr.j+1, curr.psf + "d1 "));
            }
            if(nextNode == dp[curr.i][curr.j+1]){
                q.push(node(curr.i, curr.j+1, curr.psf + "d2 "));
            }
        }
        else
        {
            nextNode = max(dp[curr.i][curr.j+1], max(dp[curr.i+1][curr.j+1], dp[curr.i-1][curr.j+1]));
            if(nextNode == dp[curr.i-1][curr.j+1]){
                q.push(node(curr.i-1, curr.j+1, curr.psf + "d1 "));
            }
            if(nextNode == dp[curr.i][curr.j+1]){
                q.push(node(curr.i, curr.j+1, curr.psf + "d2 "));
            }
            if(nextNode == dp[curr.i+1][curr.j+1]){
                q.push(node(curr.i+1, curr.j+1, curr.psf + "d3 "));
            }
        }

    }

}
//Ques-2 Top view
void topView(Node* root) {
    //map will be needed
    map<int, vector<int>> m;
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    
    while(!q.empty()){
        Node* curr = q.front().first;
        int d = q.front().second;
        q.pop();
        m[d].push_back(curr->data);
        if(curr->right){
            q.push({curr->right, d+1});
        }
        if(curr->left){
            q.push({curr->left, d-1});
        }
    }
    
    for(auto v:m){
        cout<<v.second[0]<<" ";
    }
}

//Ques 3 Rabbits leetcode
int numRabbits(vector<int>& answers) {
    int n = answers.size();
    unordered_map<int, int> hashMap;
    
    for(int i=0;i<n;i++){
        hashMap[answers[i]]++;
    }
    //ceil(a, b) = ( a + b - 1)/2
    int rabbits=0;
    int grps;
    for(auto i:hashMap){
        grps = (i.second + i.first)/(i.first+1);
        rabbits+=grps*((i.first)+1);
    }
    return rabbits;
}

//Ques 4
vector<int> findAnagrams(string s, string p) {
    int p_length = p.length();
    int s_length = s.length();
    
    unordered_map<char, int> m1, m2;
    
    for(int i=0;i < p_length;i++){
        m1[p[i]]++;
        m2[s[i]]++;
    }
    
    vector<int> result;
    for(int i=p_length;i<s_length;i++){
        if(m1 == m2)
            result.push_back(i-p_length);
        m2[s[i]]++;
        if(m2[s[i-p_length]]==1)
            m2.erase(s[i-p_length]);           //Important
        else
           m2[s[i-p_length]]--;
    }
    if(m1 == m2)
        result.push_back(s_length-p_length);
    
    return result;
}

//Ques-5 All permutations
void generateSubsets(vector<vector<int>>& result, vector<int>& A, int index, vector<int>& temp){
    if(index==A.size())
    {
        return;
    }
    
    temp.push_back(A[index]);
    result.push_back(temp);
    generateSubsets(result,A,index+1,temp);
    temp.pop_back();
    generateSubsets(result,A,index+1,temp);
}

vector<vector<int> > Solution::subsets(vector<int> &A) {
    vector<vector<int>> result;
    vector<int> temp;
    result.push_back(temp);
    sort(A.begin(),A.end());
    generateSubsets(result, A , 0, temp);
    sort(result.begin(),result.end());
    return result;
}

//Ques-6 Longest Common Subsequence
int main(){
    string x, y;
    cin>>x>>y;
    
    int dp[x.size()+1][y.size()+1];
    
    for(int i=0;i<=x.size();i++){
        for(int j=0;j<=y.size();j++){
            if(i==0||j==0){
                dp[i][j]=0;
            }
            else if(x[i-1]==y[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    cout<<dp[x.size()][y.size()];
}

//Ques-7 Longest Pallindromic subsequence
int main(){
    string x, y;
    cin>>y;
    x = y;
    reverse(y.begin(), y.end());
    int dp[x.size()+1][y.size()+1];
    
    for(int i=0;i<=x.size();i++){
        for(int j=0;j<=y.size();j++){
            if(i==0||j==0){
                dp[i][j]=0;
            }
            else if(x[i-1]==y[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    cout<<dp[x.size()][y.size()];
}

//Ques 8 Longest Pallindromic Substring
int main(){
    string x, y;
    cin>>y;
    x = y;
    reverse(y.begin(), y.end());
    int dp[x.size()+1][y.size()+1];
    
    for(int i=0;i<=x.size();i++){
        for(int j=0;j<=y.size();j++){
            if(i==0||j==0){
                dp[i][j]=0;
            }
            else if(x[i-1]==y[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }
    int result = -1;
    for(int i=1;i<=x.size();i++){
        for(int j=1;j<=y.size();j++){
            result = max(result, dp[i][j]);
        }
    }
    
    cout<<result<<endl;
}

//Ques-9 All min jump paths
struct node{
    int i;
    string psf="";
    
    node(int x, string s):i(x), psf(s){};
};

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int dp[n];
    memset(dp, INT_MAX-1, sizeof dp);
    dp[n-1] = 0;
    int m;
    for(int i=n-2;i>=0; i--){
        int steps = arr[i];
        m = INT_MAX-1;
        for(int j=1;j<=steps and i+j<=n-1;j++){
            if(dp[i+j]!=INT_MAX-1)                  //To avoid overflow
              m = min(m, dp[i+j]+1);
        } 
        if(m!=INT_MAX-1);
            dp[i] = m;
    }
    cout<<dp[0]<<'\n';
    
    queue<node> q;
    q.push(node(0, "0"));
    
    while(!q.empty()){
        node curr = q.front();
        int x = curr.i;
        string path = curr.psf;
        q.pop();
        if(x==n-1){
            cout<<path+" ."<<endl;
        }
        else{
            int i = x;
            int m =INT_MAX;
            for(int j=1;j<=arr[x] and (i+j)<n;j++){
                m = min(dp[i+j], m);
            }
            for(int j=1;j<=arr[x] and (i+j)<n;j++){
                if(dp[i+j]==m)
                    q.push(node(i+j, path+" -> "+to_string(i+j)));
            }
        }
    }
}