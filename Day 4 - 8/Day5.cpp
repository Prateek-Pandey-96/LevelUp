#include <bits/stdc++.h>

//Ques - 1 Generate and print all ways you can select k distinct characters out of a word
void printSelections(string s, int lettersSelected, int k, int index, string asf){
    if(index == s.length())
    {
        if(lettersSelected == k){
            cout<<asf<<'\n';
        }
        return;
    }
    
    char c = s[index];
    string charSelected = asf;
    charSelected.push_back(c);
    printSelections(s, lettersSelected+1, k, index+1, charSelected);
    printSelections(s, lettersSelected, k, index+1, asf);
    
}

int main(){
    string str;
    cin>>str;
    int k;
    cin>>k;
    string unique;
    unordered_set<char> hashSet;
    for(int i=0;i<str.size();i++){
        if(hashSet.find(str[i])==hashSet.end())
        {
            hashSet.insert(str[i]);
            unique.push_back(str[i]);
        }
    }
    printSelections(unique, 0, k, 0, "");
   
}

//Ques-2 First non repeating character in a string
char nonrepeatingCharacter(string S)
{
   int n = S.size();
   int hashMap[26];
   memset(hashMap, 0, sizeof hashMap);
   for(int i=0;i<n;i++){
        hashMap[S[i]-'a']++;    
   }
   //cout<<hashMap[7];
   for(int i=0;i<n;i++){
        if(hashMap[S[i]-'a']==1)
            return S[i];
   }
   return '$';
}

//Ques-3 Longest array with equal number of zeroes and ones 
int GetLongestLength(vector<int>& arr){
    unordered_map<int, int> hashMap;
    int sum = 0;
    int size = 0;
    for(int i =0;i<arr.size();i++){
        sum+=arr[i];
        if(sum == 0){
            size = max(size, i+1);
        }
        
        if(hashMap.find(sum)!=hashMap.end()){
            size = max(size, i - hashMap[sum]);
        }
        else{
            hashMap[sum] = i;
        }
    }
    return size;
}
int main(){
    vector<int> arr;
    int n, x;
    cin>>n;
    
    for(int i=0;i<n;i++){
        cin>>x;
        if(x==0)
            x=-1;
        arr.push_back(x);
    }
    
    cout<<GetLongestLength(arr);
}

//Ques- 4 Count of subarrays with equal number of zeroes and ones 
int GetSubArrayCounts(vector<int>& arr){
    unordered_map<int, int> hashMap;
    hashMap[0] = 1;
    int sum  = 0;
    int count = 0;
    for(int i =0;i<arr.size();i++){
       sum += arr[i];
       if(hashMap.find(sum)!=hashMap.end()){
           count += hashMap[sum];
       }
       hashMap[sum] += 1;
    }
    return count;
}
int main(){
    vector<int> arr;
    int n, x;
    cin>>n;
    
    for(int i=0;i<n;i++){
        cin>>x;
        if(x==0)
            x=-1;
        arr.push_back(x);
    }
    
    cout<<GetSubArrayCounts(arr);
}

//Ques - 5 Count of subarrays with equal number of 0, 1 and 2
int countSubArrays(vector<int>& arr){
    map<pair<int,int>, int> hashMap;
    int count0=0, count1=0, count2=0, count = 0;
    //put count0-count1 and count1-count2 in hashMap
    hashMap[{0,0}]++;
    for(int i=0;i<arr.size();i++){
        if(arr[i]==0)
            count0++;
        else if(arr[i]==1)
            count1++;
        else
            count2++;
            
        pair<int,int> p = {count0-count1 , count1-count2};
        
        if(hashMap.find(p) != hashMap.end()){
            count += hashMap[p];
        }
        hashMap[p]++;
    }
    return count;
}
int main(){
    int n, x;
    cin>>n;
    
    vector<int> arr;
    
    for(int i=0;i<n;i++){
        cin>>x;
        arr.push_back(x);
    }
    
    cout<<countSubArrays(arr);
}

//Ques-6  Length of longest subarray with equal number of 0, 1 and 2
int LongestSubArrayLength(vector<int>& arr){
    map<pair<int,int>, int> hashMap;
    int count0=0, count1=0, count2=0;
    int len = 0;
    //put count0-count1 and count1-count2 in hashMap
    hashMap[{0,0}]++;
    for(int i=0;i<arr.size();i++){
        if(arr[i]==0)
            count0++;
        else if(arr[i]==1)
            count1++;
        else
            count2++;
            
        pair<int,int> p = {count0-count1 , count1-count2};
        if(p.first == 0 and p.second==0){
            len = max(len, i+1);
        }
        if(hashMap.find(p) != hashMap.end()){
            len = max(len, i-hashMap[p]);
        }
        else
        {
            hashMap[p] = i;
        }
    }
    return len;
}
int main(){
    int n, x;
    cin>>n;
    
    vector<int> arr;
    
    for(int i=0;i<n;i++){
        cin>>x;
        arr.push_back(x);
    }
    
    cout<<LongestSubArrayLength(arr);
}

//Ques 7 Gold Miner-2
bool isSafe(int i, int j, vector<vector<int>>& arr){
    int m = arr.size();
    int n = arr[0].size();
    
    if(i<0 or i>=m or j<0 or j>=n)
        return false;
    if(arr[i][j]==0)
        return false;
    return true;
}

void dfs(int i, int j,  vector<vector<int>>& arr, int& count){
    count+=arr[i][j];
    arr[i][j]=0;
    
    int dy[4] ={-1,1,0,0} ;
    int dx[4] ={0,0,1,-1} ;
    for(int k = 0; k< 4;k++){
        int newX = i + dx[k];
        int newY = j + dy[k];
        if(isSafe(newX,newY,arr))
            dfs(newX, newY, arr, count);
    }
    return;
}

int main(){
    int n, m;
    cin>>n>>m;
    vector<vector<int>> arr(n, vector<int>(m, 0));
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            arr[i][j] = 0;
            cin>>arr[i][j];
        }
    }
    
    //We have to find the connected component with most gold
    int ans =0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int count = 0;
            if(arr[i][j]!=0)
                dfs(i, j, arr, count),ans = max(ans, count);
        }
    }
    
    cout<<ans;
}

//Ques 8 Coin Combination to form a given sum

//Either we will take the coin or leave it
void printCombinations(int coins[], int n,int index, int ssf, int amt, string asf){
    if(index == n){
        if(ssf == amt)
            cout<<asf<<"."<<'\n';
        return;
    }
    int coin = coins[index];
    
    printCombinations(coins, n, index+1, ssf+coin, amt, asf+to_string(coin)+"-");
    printCombinations(coins, n, index+1, ssf, amt, asf);
 }

int main(){
    int n, amt;
    cin>>n;
    int coins[n];
    for(int i=0;i<n;i++){
        coins[i]=0;
        cin>>coins[i];
    }
    cin>>amt;
    printCombinations(coins, n, 0, 0, amt, "");
}