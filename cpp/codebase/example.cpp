#include <string>
#include <vector>
#include <iostream>
#include <boost/format.hpp>

std::string concat(const std::vector<std::string>& vec, char split) {
    std::string result;
    for(auto&& str: vec) {
        result += str(boost::format("%c%s%c" %split %str %split));
    }
    return result;
}

std::vector<std::string> generate_string_from_seed(const std::vector<std::string>& seed_vec, int num){
    std::vector<std::string> candidate{seed_vec.begin(), seed_vec.end()};
    std::vector<std::string> used;
    std::vector<std::string> res;
    used.reserve(seed_vec.size());

    size_t count = 0;

    while(!candidate.empty()){
        auto ins = candidate.back();
        candidate.pop_back();
        used.push_back(ins);

        if (used.size() == seed_vec.size()) {
            res.push_back(concat(used, ' '));
            count++;
            if (count == num) {
                break;
            }
        }
        else {
            for(auto&& seed: seed_vec) {
                candidate.push_back(seed);
            }
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> string_vec;

    std::vector<std::string> seed_vec = {
        "hello",
        "world",
        "cpp",
        "next",
        "string",
        "word",
        "vector",
        "queue"
    };

}