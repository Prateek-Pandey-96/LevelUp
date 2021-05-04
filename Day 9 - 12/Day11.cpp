#include <bits/stdc++.h>

//Ques 1 Sliding Window Maximum

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //Dequeue will be used for sure
    vector<int> result;
    deque<int> q;
    
    q.push_back(0);
    for(int i=1;i<k;i++){
        while(!q.empty() and nums[i]>=nums[q.back()]){
            q.pop_back();
        }
        q.push_back(i);
    }
    
    for(int i=k;i<nums.size();i++){
        result.push_back(nums[q.front()]);
        while(!q.empty() and q.front()<= i-k)
            q.pop_front();
        while(!q.empty() and nums[i]>=nums[q.back()]){
            q.pop_back();
        }
        q.push_back(i);
    }

        result.push_back(nums[q.front()]);

    return result;
    
}

//Merge k sorted lists
ListNode* mergeTwoLists(ListNode* A, ListNode* B)
{
    if(A== NULL)
        return B;
    if(B== NULL)
        return A;
    
    ListNode* result;
    if(A->val <= B->val)
    {   
        ListNode* newNode = new ListNode(A->val);
        newNode->next = mergeTwoLists(A->next, B);
        result = newNode;
    }
    else
    {
        ListNode* newNode = new ListNode(B->val);
        newNode->next = mergeTwoLists(A, B->next);
        result = newNode;
    }
    
    return result;
}

ListNode* merge(vector<ListNode*>& lists, int low, int high){
    if(low>high)
        return NULL;
    if(low==high)
        return lists[low];
    
    if(low+1 == high)
        return mergeTwoLists(lists[low], lists[high]);
    
    int mid = low + (high - low)/2;
    ListNode* left = merge(lists, low, mid);
    ListNode* right = merge(lists, mid+1, high);
    
    return mergeTwoLists(left, right);
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    //Base case        
    if(lists.size()==0)
        return NULL;
    //Normal Case
    
    return merge(lists, 0, lists.size()-1);
}

//Ques -3 Trie
struct TrieNode{
    bool isEndOfWord;
    TrieNode* children[26];
    
};
/** Initialize your data structure here. */
TrieNode* root;
Trie() {
    root = new TrieNode();
}

/** Inserts a word into the trie. */
void insert(string word) {
    TrieNode* crawl = root;
    for(int i=0;i<word.length();i++){
        int index = word[i] - 'a';
        if(crawl->children[index]==NULL)
            crawl->children[index] = new TrieNode();
        crawl = crawl->children[index];
    }
    crawl->isEndOfWord = true;
}

/** Returns if the word is in the trie. */
bool search(string word) {
    TrieNode* crawl = root;
    for(int i=0;i<word.length();i++){
        int index = word[i]-'a';
        if(crawl->children[index]==NULL)
            return false;
        crawl = crawl->children[index];
    }
    return crawl->isEndOfWord;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool startsWith(string prefix) {
    TrieNode* crawl = root;
    for(int i=0;i<prefix.length();i++){
        int index = prefix[i]-'a';
        if(crawl->children[index]==NULL)
            return false;
        crawl = crawl->children[index];
    }
    return true;
}

//Ques-4 Visiting Rooms Leetcode
void dfs(int src, vector<bool>& visited, vector<int> adj[]){
    visited[src] = true;
    for(auto child:adj[src]){
        if(!visited[child])
            dfs(child, visited, adj);
    }
}
bool canVisitAllRooms(vector<vector<int>>& rooms) {
    int n = rooms.size();
    vector<bool> visited(n, false);
    vector<int> adj[n];
    //Directed Graph
    for(int i=0;i<rooms.size();i++){
        for(int j=0;j<rooms[i].size();j++){
            adj[i].push_back(rooms[i][j]);
        }
    }
    //start dfs from 0
    dfs(0, visited, adj);
    
    for(int i=0;i<n;i++){
        if(visited[i]==false)
            return false;
    }
    return true;
}

//Ques-5 Island Perimeter
int islandPerimeter(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int count = 0, sharedBoundary = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]==1)
            {   count++;
                if(i!=0 and grid[i-1][j]==1)
                    sharedBoundary++;
                if(j!=0 and grid[i][j-1]==1)
                    sharedBoundary++;
            }
        }
    }
    return count*4 - sharedBoundary*2;
}

//Ques-6 Trie with a dot
struct TrieNode{
bool isEndOfWord;
TrieNode* children[26];
};
/** Initialize your data structure here. */
TrieNode* root;
WordDictionary() {
    root = new TrieNode();
}

void addWord(string word) {
TrieNode* crawl = root;
for(int i=0;i<word.length();i++){
    int index = word[i] - 'a';
    if(crawl->children[index]==NULL)
        crawl->children[index] = new TrieNode();
    crawl = crawl->children[index];
}
crawl->isEndOfWord = true;
}
bool search(string word, int i, TrieNode* node){
    if(i==word.length())
        return node->isEndOfWord;
    
    if(word[i]=='.'){
        for(int j=0;j<26;j++){
            if(node->children[j]!=NULL and search(word, i+1, node->children[j]))
                return true;
        }
    }
    else{
        if(node->children[word[i]-'a']!=NULL and search(word, i+1, node->children[word[i]-'a']))
            return true;
    }
    return false;
}
bool search(string word) {
    TrieNode* temp = root;
    return search(word, 0, temp);
}

//Ques-7 WildCard Pattern Matching
int dp[201][201];
    
int recursiveSolver(string pattern, string str, int p, int s){
    if(p==-1 and s==-1)
        return 1;
    if(p==-1)
        return false;
    if(s==-1){
        for(int i=0;i<p;i++){
            if(pattern[i]!='*')
                return 0;
        }
        return 1;
    }
    if(dp[p][s]!=-1)
        return dp[p][s];
    if(str[s]==pattern[p] or pattern[p]=='?')
        return dp[p][s]=recursiveSolver(pattern, str, p-1, s-1);
    else if(pattern[p]=='*'){
        int op1 = recursiveSolver(pattern, str, p-1, s);
        int op2 = recursiveSolver(pattern, str, p, s-1);
        return dp[p][s] = op1 or op2;
    }
    return 0;
}
/*You are required to complete this method*/
int wildCard(string pattern,string str)
{
    memset(dp, -1, sizeof dp);
    return recursiveSolver(pattern, str, pattern.length()-1, str.length()-1);
}

//Ques-8 First missing positive
int firstMissingPositive(vector<int>& nums) {
    //Good ques
    int n = nums.size();
    int currentNum ;
    vector<long long> v;
    for(auto num:nums){
        v.push_back(num);
    }
    //Using one based indexing
    for(int i=0;i<n;i++){
        int correctPosition = v[i]-1;
        while( v[i]>= 1 and v[i]<=n and v[i]!=v[correctPosition])
        {
            swap(v[i], v[correctPosition]);
            correctPosition = v[i]-1;
        }
    }
    int i;
    for(i=0;i<n;i++){
        if(v[i]!=i+1)
            return i+1;
    }
    return i+1;
}