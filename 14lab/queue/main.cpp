#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
    
    Queue<int> stack;
    cout<<"1-push."<<endl<<"2-pop."<<endl<<"3-size."<<endl<<"4-front."<<endl<<"5-isEmpty."<<endl<<"6-exit."<<endl;
    int action;
    bool isEnd=0;
    while (!isEnd)
    {
        cin>>action;
        switch(action)
        {
            case 1:
            {
                cout<<"Enter a value ";
                int value;
                cin>> value;
                stack.push(value);
                cout<<"added"<<endl;
                break;
            }
            case 2:
                if (stack.empty()) cout<<"stack is empty"<<endl;
                else  {stack.pop(); cout<<"deleted"<<endl;}
                break;
            case 3:
                cout<<stack.size()<<endl;
                break;
            case 4:
                if (stack.empty()) cout<<"stack is empty"<<endl;
                else cout<<"Front is "<<stack.front()<<endl;
                break;
            case 5:
                if (stack.empty()) cout<<"stack is empty"<<endl;
                else cout<<"stack is not empty"<<endl;
                break;
            case 6: isEnd=1;
        }
    }

    return 0;
}

