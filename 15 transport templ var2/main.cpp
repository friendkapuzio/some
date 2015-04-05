#include <iostream>
#include "TranportTemplVar2.h"







int main()
{
    Transport<string> trp;
    int action;
    bool isEnd=0;
    cout<<"1-addRoute"<<endl<<"2-addStop"<<endl<<"3-deleteRoute"<<endl<<"4-deleteStop"<<endl<<"5-numberOfRoutes"<<endl<<"6-numberOfStops"<<endl<<"7-routes stop"<<endl<<"8-selectRoutes"<<endl<<"9-emptyStops"<<endl<<"10-popularStop"<<endl<<"11-exit"<<endl;
    while (!isEnd)
    {
        cin>>action;
        switch (action) {
            case 1:
            {
                cout<<"type: ";
                string type;
                cin>>type;
                cout<<"number: ";
                string number;
                cin>>number;
                cout<<"stops: ";
                bool stop=1;
                string nameStop;
                list<string> stops;
                while(stop)
                {
                    cin>>nameStop;
                    stops.push_back(nameStop);
                    cout<<"1-add \n0-enough ";
                    cin>>stop;
                }
                trp.addRoute(number, type, make_pair(stops.begin(), stops.end()));
                break;
            }
            case 2:
            {
                cout<<"stop: ";
                string stop;
                cin>>stop;
                trp.addStop(stop);
                cout<<"added"<<endl;
                break;
            }
            case 3:
            {
                cout<<"enter type and number: ";
                string type;
                string number;
                cin>>type>>number;
                trp.deleteRoute(number, type);
                cout<<"deleted"<<endl;
                break;
            }
            case 4:
            {
                cout<<"enter stop: ";
                string stop;
                cin>>stop;
                trp.deleteStop(stop);
                cout<<"deleted"<<endl;
                break;
            }
            case 5:
            {
                cout<<trp.numberOfRoutes()<<endl;
                break;
            }
            case 6:
            {
                cout<<trp.numberOfStops()<<endl;
                break;
            }
            case 7:
            {
                cout<<"enter stop: ";
                string stop;
                cin>>stop;
                pair<list<pair<string, string>>::iterator, list<pair<string, string>>::iterator> a=trp.listOfRoutes(stop);
                for (auto it=a.first; it!=a.second; ++it) cout<<it->first<<" "<<it->second<<endl;
                break;
            }
            case 8:
            {
                cout<<"enter type and range: ";
                string type;
                string begin, end;
                cin>>type>>begin>>end;
                pair<list<string>::iterator, list<string>::iterator> a=trp.listOfRoutes(type, begin, end);
                for (auto it=a.first; it!=a.second; ++it) cout<<*it<<" ";
                break;
            }
            case 9:
            {
                pair<set<string>::iterator, set<string>::iterator> a=trp.emptyStop();
                for(auto it=a.first; it!=a.second; ++it) cout<<*it<<" ";
                break;
            }
            case 10:
            {
                cout<<trp.popularStop()<<endl;
                break;
            }
            case 11:
            {
                isEnd=1;
            }
        }
    }
    return 0;
}