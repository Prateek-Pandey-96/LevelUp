#include <bits/stdc++.h>
using namespace std;
//Time - O(M) for search
struct TrieNode{
	bool isEndOfWord;
	int count;
	TrieNode* arr[26];

	TrieNode(){
		isEndOfWord = false;
		count = 0;
		for(int i=0;i<26;i++)
			arr[i] = NULL;
	}
};

void addWord(TrieNode* root, string word){
	TrieNode* crawl = root;
	for(int i=0;i<(int)word.length();i++){
		char c = word[i];
		if(crawl->arr[c-'a']==NULL){
			crawl->arr[c-'a']=new TrieNode();
		}
		crawl = crawl->arr[c-'a'];
		crawl->count++;
	}
	crawl->isEndOfWord = true;
}

int findStrings(TrieNode* root, string word){
	TrieNode* crawl = root;
	for(int i=0;i<(int)word.length();i++){
		char c = word[i];
		if(crawl->arr[c-'a']==NULL)
			return 0;
		crawl = crawl->arr[c-'a'];
	}
	return crawl->count;
}

int main(){
	int n;
	cin>>n;
	string opt, word;
	TrieNode* root = new TrieNode();
	while(n--){
		cin>>opt>>word;
		if(opt=="add"){
			addWord(root, word);
		} else {
			cout<<findStrings(root, word)<<endl;
		}
	}
	return 0;
}

