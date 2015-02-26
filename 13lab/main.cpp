#include <vector>
#include <iostream>
#include <list>
#include <deque>
#include <map>
using namespace std;

template <class T>
typename T::value_type sum(const T& cont)
{
    typename T::value_type a=0;
    for(auto it:cont) a+=it;
    return a;
}


template <class S, class C>
typename map<S, C>::mapped_type sum(const map<S, C>& cont)
{
    typename map<S, C>::mapped_type a=0;
    for(auto it:cont) a+=((&it)->second);
    return a;
}



int main(int argc, const char * argv[])
{
    vector<int> container1(10, 4);
    list<double> container2(5, 3.5);
    deque<int> cont3(5, 2);
    map<char, int> cont4{{'a',6},
                            {'b',7}};
    int res3=sum(cont3);
    int result1 = sum(container1);    // =40
    double result2 = sum(container2); // =17.5
    auto res4=sum(cont4);
    cout<<result1<<" "<<result2<<" "<<res3<<" "<<res4;
    return 0;
}

