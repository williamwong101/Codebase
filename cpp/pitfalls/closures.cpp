#include <vector>
#include <algorithm>
#include <stdio.h>

int main() {
    std::vector<int> vec;
    for (int i = 1; i<15; i++){
        vec.push_back(i);
    }
    bool asc = false;
    auto show = [](int i){printf("num: %d ", i);};
    auto cmp = [&asc](int first, int second){return (!asc)?first>second:first<=second;};
    std::for_each(vec.begin(), vec.end(), show);

    printf("\n");
    std::sort(vec.begin(), vec.end(), cmp);
    std::for_each(vec.begin(), vec.end(), show);

}