#ifndef queueTwoStacks_Header_h
#define queueTwoStacks_Header_h
#include <stack>

template<class T, class C=std::stack<T>> class Queue
{
    C up;
    C down;
public:
    void push(T);
    void pop();
    bool empty();
    long size();
    T& front();
};






template<class T, class C>
T& Queue<T,C>::front()
{
    if(down.empty())
    {
        for(long i=up.size();i>0;--i)
        {
            down.push(up.top());
            up.pop();
        }
    }
    return down.top();
}







template<class T, class C>
void Queue<T,C>::push(T n)
{
    up.push(n);
}





template<class T, class C>
void Queue<T, C>::pop()
{
    if(empty()) return;
    if(down.empty())
    {
        for(long i=up.size();i>1;--i)
        {
            down.push(up.top());
            up.pop();
        }
    up.pop();
    }
    else down.pop();
}




template<class T, class C>
bool Queue<T, C>::empty()
{
    if(up.empty() && down.empty()) return true;
    else return false;
}




template<class T, class C>
long Queue<T, C>::size()
{
    return up.size()+down.size();
}




#endif
