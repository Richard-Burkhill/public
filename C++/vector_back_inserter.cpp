#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char** argv){
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::fill_n(std::back_inserter(v), 3, -1);
    
    vector<int> v1;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v1), [] (int x) { return x % 2; });
    vector<int> v2;
    std::copy(v.begin(), v.end(), std::back_inserter(v2));
}
