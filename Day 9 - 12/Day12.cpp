#include <bits/stdc++.h>

//Ques -1 Search in a rotated sorted array
int search(vector<int>& nums, int target) {
    //Implementation of binary search
    int low = 0, high = nums.size()-1;
    int mid;
    while(low <= high){
        mid = low+(high-low)/2;
        if(nums[mid]==target)
            return mid;
        //first half sorted
        if(nums[mid] >= nums[low])
        {
            if(target>=nums[low] and target<nums[mid])
                high = mid-1;
            else
                low = mid+1;
        }
        else{
            if(target>nums[mid] and target<=nums[high])
                low = mid+1;
            else
                high = mid-1;
        }
    }
    return -1;
}

//Ques-2 First and last index in a sorted array
vector<int> searchRange(vector<int>& nums, int target) {
    int low=0, high=nums.size()-1;
    int mid;
    int left=-1,right=-1;
    
    while(low<=high){
        mid=low+(high-low)/2;
        if(nums[mid]<target)
            low = mid+1;
        else if(nums[mid]>target)
            high = mid-1;
        else{
            left = mid;
            high = mid-1;
        }
    }
    
    low=0,high=nums.size()-1;
    while(low<=high){
        mid=low+(high-low)/2;
        if(nums[mid]<target)
            low = mid+1;
        else if(nums[mid]>target)
            high = mid-1;
        else{
            right = mid;
            low = mid+1;
        }
    }
    return {left, right};
}

//Ques 3 Majority element
int majorityElement(vector<int>& nums) {
    //Boyre Moore's Voting algo O(N)Time and O(1)Space
    int majority_index = 0;
    int count = 1;
    
    for(int i=1;i<nums.size();i++){
        if(nums[i]==nums[majority_index])
            count++;
        else
            count--;
        if(count == 0){
            majority_index = i;
            count = 1;
        }
    }
    return nums[majority_index];
}

//Ques-4 Majority element 2
vector<int> majorityElement(vector<int>& nums) {
    if(nums.size()==1)
        return {nums[0]};
    int first_element = 0;
    int second_element = 0;
    vector<int> result;
    int c1=0,c2=0;
    for(int i=0;i<nums.size();i++){
        if(first_element== nums[i])
            c1++;
        else if(second_element== nums[i])
            c2++;
        else if(c1 == 0)
            first_element = nums[i], c1++;
        else if(c2 == 0)
            second_element = nums[i], c2++;
        else
            c1--,c2--;
    }
    c1=c2=0;
    for(int i=0;i<nums.size();i++){
        if(nums[i]==first_element)c1++;
        if(nums[i]==second_element)c2++;
    }
    if(c1 > nums.size()/3)
        result.push_back(first_element);
    if(c2 > nums.size()/3)
        result.push_back(second_element);
    if(result.size()==2 and result[0]==result[1])
        result.pop_back();
    return result;
}