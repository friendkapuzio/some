#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;


template <class T>
void mergeSort(T &cont)
{
    if(cont.size()<2)return;
    T Sort1, Sort2;
    auto it=cont.begin();
    for(int i=0; i<cont.size();++i)
    {
        if(i<(cont.size()/2)) Sort1.push_back(*it);
        else Sort2.push_back(*it);
        ++it;
    }
    mergeSort(Sort1);
    mergeSort(Sort2);
    merge(Sort1.begin(), Sort1.end(), Sort2.begin(), Sort2.end(), cont.begin());
}



int main()
{
    list<int> l;
    l.push_back(5);
    l.push_back(1);
    l.push_back(-2);
    l.push_back(0);
    mergeSort(l);
    for(auto it:l) cout<<it<<" ";
    return 0;
}