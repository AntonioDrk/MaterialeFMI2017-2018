#include <iostream>
#include <vector>

using namespace std;

void insSort(vector<int>&v){
    for(int i=2; i<v.size(); i++){
        int j= i+1;
        while(j>0 && v[i] < v[j]){
            swap(v[i],v[j]);
            j--;
        }
    }
}

int main()
{
    int n,tmp;
    vector<int> v;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> tmp;
        v.push_back(tmp);
    }
    insSort(v);
    for(int i=0;i<n;i++){
        cout << v[i] << " ";
    }
    return 0;
}
