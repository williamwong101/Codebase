#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;
void quick_sort(vector<int> & input,size_t left, size_t right);
size_t partition(vector<int> &input, size_t left, size_t right, size_t pivot);
int main()	{
	vector<int> input_vec = {5,73,4,7,2,4,9,1,23,65};
	
	quick_sort(input_vec, 0, input_vec.size()-1);

	for(auto i: input_vec){
		cout<<i<<" ";
	}
}
void quick_sort(vector<int> & input,size_t left, size_t right){
	if(left>=right) return;
	size_t pivot = partition(input, left, right, right);
	if(left<pivot) quick_sort(input, left, pivot-1);
	if(pivot<right) quick_sort(input, pivot+1, right);	
}


size_t partition(vector<int> &input, size_t left, size_t right, size_t pivot){
	while(left < right){
		while(left < right && input[left] <= input[pivot]) left++;
		while(left < right && input[right] >= input[pivot]) right--;
		if (left < right) swap(input[left], input[right]);
	}
	swap(input[left], input[pivot]);
	return left;
}


