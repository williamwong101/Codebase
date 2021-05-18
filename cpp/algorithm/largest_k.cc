#include<iostream>
#include<vector>
#include<queue>

using namespace std;
vector<int> find_largest_k(vector<int> & input_vec, size_t k){
	priority_queue<int> pq;
	for(auto num : input_vec){
		pq.push(num);
	}
	vector<int> ret(k);
	for(size_t i = 0; i<k; i++){
		ret[i] = pq.top();
		pq.pop();
	}
	return ret;	
}

int main(){
	vector<int> input_vec = {1,4,2,456,34,462,45,2,635,3476,52,24,53564,2345,34,23,5,536,675,56};
	vector<int> largest_k = find_largest_k(input_vec, 5);
	for_each(largest_k.begin(), largest_k.end(), [](int &i){ cout<<i<<' '; });
	return 0;

}

