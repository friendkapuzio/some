#ifndef __Transport__File__
#define __Transport__File__
#include <map>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;


template <class T>
class Transport
{
    list<pair<string, T>> listRoutes;
    set<string> emptyStops;
    list<T> selectedRoutes;
    map<string, map<T, list<string> > > routes;
    set<string> stops;
public:
    void addRoute(T, string, pair<list<string>::iterator, list<string>::iterator>);
    void deleteRoute(T, string);
    void addStop(string);
    void deleteStop(string);
    int numberOfRoutes();
    long numberOfStops();
    pair<typename list<pair<string, T>>::iterator, typename list<pair<string, T>>::iterator> listOfRoutes(string);
    pair<typename list<T>::iterator, typename list<T>::iterator> listOfRoutes (string, T, T);
    pair<set<string>::iterator, set<string>::iterator> emptyStop();
    string popularStop ();
};



template <class T>
void Transport<T>::addRoute(T number, string type, pair<list<string>::iterator, list<string>::iterator> pstops)
{
    for(auto it=pstops.first; it!=pstops.second; ++it)
    {
        stops.insert(*it);
        routes[type][number].push_back(*it);
    }
}


template <class T>
void Transport<T>::deleteRoute(T number, string type)
{
    if(routes.find(type)!=routes.end())
    {
        if(routes[type].find(number)!=routes[type].end())
            routes[type].erase(number);
    }
}



template <class T>
void Transport<T>::addStop(string stop)
{
    stops.insert(stop);
}



template <class T>
void Transport<T>::deleteStop(string stop)
{
    if (stops.find(stop)!=stops.end()) stops.erase(stop);
    else return;
    for(auto it=routes.begin(); it!=routes.end(); ++it)
    {
        for(auto iter=it->second.begin(); iter!=it->second.end(); ++iter)
        {
            auto delet = find(iter->second.begin(), iter->second.end(), stop);
            if(delet != iter->second.end())
                iter->second.erase(delet);
            if(iter->second.empty() /*&& ++iter==it->second.end()*/) {/*--iter;*/ it->second.erase(iter->first); break;}
        }
    }
}





template <class T>
int Transport<T>::numberOfRoutes()
{
    int amount=0;
    for(auto it=routes.begin(); it!=routes.end(); ++it)
        amount+=(it->second).size();
    return amount;
}





template <class T>
long Transport<T>::numberOfStops()
{
    return stops.size();
}



template <class T>
pair<typename list<pair<string, T>>::iterator, typename list<pair<string, T>>::iterator> Transport<T>::listOfRoutes(string stop)
{
    listRoutes.clear();
    for(auto it=routes.begin(); it!=routes.end(); ++it)
    {
        for(auto iter=routes[it->first].begin(); iter!=routes[it->first].end(); ++iter)
        {
            if(find(routes[it->first][iter->first].begin(), routes[it->first][iter->first].end(), stop)!=routes[it->first][iter->first].end())
                listRoutes.push_back(make_pair (it->first, iter->first));
        }
    }
    return make_pair(listRoutes.begin(), listRoutes.end());
}




template <class T>
pair<typename list<T>::iterator, typename list<T>::iterator> Transport<T>::listOfRoutes(string type, T begin, T end)
{
    selectedRoutes.clear();
    if(routes.find(type)!=routes.end())
    {
        auto ends=routes[type].upper_bound(end);
        for(auto it=routes[type].lower_bound(begin); it!=ends; ++it)
            selectedRoutes.push_back(it->first);
    }
    return make_pair(selectedRoutes.begin(), selectedRoutes.end());
}




template <class T>
pair<set<string>::iterator, set<string>::iterator> Transport<T>::emptyStop()
{
    emptyStops.clear();
    for(auto it=stops.begin(); it!=stops.end(); ++it)
        emptyStops.insert(*it);
    for(auto it=routes.begin(); it!=routes.end(); ++it)
    {
        for(auto iter=routes[it->first].begin(); iter!=routes[it->first].end(); ++iter)
        {
            for(auto iterat:routes[it->first][iter->first])
                emptyStops.erase(iterat);
        }
    }
    return make_pair(emptyStops.begin(), emptyStops.end());
}




template <class T>
string Transport<T>::popularStop()
{
    if (stops.empty()) return "";
    map<string, int> allStops;
    for(auto it:stops) allStops[it];
    for(auto it:routes)
    {
        for (auto iter:routes[(&it)->first])
        {
            for(auto iterat:(&iter)->second)
                allStops[iterat]+=1;
        }
    }
    auto it=allStops.begin();
    string popularStop=it->first;
    for(; it!=allStops.end(); ++it)
    {
        if(it->second>allStops[popularStop])
            popularStop=it->first;
    }
    return popularStop;
}



#endif