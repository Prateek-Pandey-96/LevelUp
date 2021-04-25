#include <bits/stdc++.h>

//Ques-1
int maxLen(int A[], int n)
{
    unordered_map<int, int> hashMap;
    int sum = 0;
    int ans = 0;
    for(int i=0;i<n;i++){a
        sum += A[i];
        if(sum==0){
            ans = max(ans, i+1);
        }
        else{
            if(hashMap.find(sum)!=hashMap.end()){
                ans = max(ans, i-hashMap[sum]);
            }
            else
                hashMap[sum] = i;
        }
    }
    return ans;
}

//Ques-2
int findSubarray(vector<int> arr, int n ) {
        unordered_map<int, int> hashMap;
        int sum = 0;
        int count = 0;
        
        for(int i=0;i<n;i++){
            sum += arr[i];
            if(sum==0)
                count++;
            if(hashMap.find(sum)!=hashMap.end()){
                count+=hashMap[sum];
            }
            hashMap[sum] += 1;                    //Importaant to note that there is no else here
        }
        return count;
    }

//Ques-3
vector<int> Solution::Nums(vector<int> &A, int B) {
    unordered_map<int,int> m;
    int dist =0;
    for(int i=0;i<B;i++){
        if(m[A[i]]==0)
            dist++;
        m[A[i]]+=1;
    }
    vector<int> result;
    result.push_back(dist);
    for(int i=B;i<A.size();i++)
    {
        if(m[A[i-B]]==1)
            dist--;
        m[A[i-B]]-=1;
        
        if(m[A[i]]==0)
            dist++;
        m[A[i]]+=1;
        result.push_back(dist);
    }
    return result;
}

//Ques-4
int longestUniqueSubsttr(string s){
    if(s.length()==0)
        return 0;
    unordered_map<char, int> hashMap;
    int i=0;
    int j=0;
    int ans = INT_MIN;
    while(j<s.length()){
        hashMap[s[j]]++;
        while(hashMap[s[j]]>1){
            hashMap[s[i++]]--;
        }
        ans = max(ans,j-i+1);
        j++;
    }
    return ans;
}

//Ques-5
int longestOnes(vector<int>& nums, int k) {
    int n = nums.size();
    int i=0,j=0;
    int count = 0;
    int ans = 0;
    while(j<n){
        if(nums[j]==0)
            count++;
        
        while(count > k){
            if(nums[i]==0)
                count--;
            i++;
        }
        
        ans = max(ans, j-i+1);
        j++;
    }
    return ans;
}

//Ques-6
bool isIsomorphic(string s, string t) {
    if(s.length()!=t.length())
        return false;
    
    unordered_map<char, char> hashMap;
    unordered_map<char, bool> m;
    
    for(int i=0;i<s.size();i++){
        if(hashMap.find(s[i])!=hashMap.end()){
            if(hashMap[s[i]]!=t[i])
                return false;
        }
        else{
            if(m[t[i]]==true)
                return false;
            else{
                hashMap[s[i]] = t[i];
                m[t[i]] = true;
            }
        }
    }
    
    return true;
}

//Ques-7
int longestKSubstr(string s, int k) {
    int size = -1;
    int l = s.length();
    unordered_map<char, int> hashMap;
    int dist = 0;
    int i=0,j=0;
    
    while(j<l){
        if(hashMap[s[j]]==0)
            dist++;
        hashMap[s[j]]++;
        
        if(dist < k)
            j++;
        else if(dist==k){
            size = max(size, j-i+1);j++;
        }
        else{
            while(dist>k){
                if(hashMap[s[i]]==1)
                    dist--;
                hashMap[s[i]]--;
                i++;
            }
            j++;
        }
            
    }
    return size;
}

//Ques-8
long long int helper(string s, int k){
    long long int m[26]={0};           //using ordered and unordered_map gives tle so i formed a map of my own
    long long int i=0,j=0;
    long long int count = 0;
    long long int dist = 0;
    while(j<s.length()){
        if(m[s[j]-'a']==0)
            dist++;
         m[s[j]-'a']++;
        
        while(dist>k){
            if(m[s[i]-'a']==1)
                dist--;
            m[s[i]-'a']--;
            i++;
        }
        
        count += j-i+1;
        j++;
    }
    return count;
}

long long int substrCount (string s, int k)
{
    //K!=0 given in question
    return helper(s, k)-helper(s, k-1);	
}