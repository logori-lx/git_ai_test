#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> res{1,2,3};
    vector<int> sec{4,5,6};
    res.insert(res.end(), sec.begin(), sec.end());    
}