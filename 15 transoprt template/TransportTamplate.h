#ifndef __Transport_template__TransportTamplate__
#define __Transport_template__TransportTamplate__

#include <iostream>



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
    list<string> emptyStops;
    list<T> selectedRoutes;
    map<string, map<T, list<string> > > routes;
    map<string, list<pair<string, T> > > stops;
public:
    void addRoute(T, string, pair<list<string>::iterator, list<string>::iterator>);
    void deleteRoute(T, string);
    void addStop(string);
    void deleteStop(string);
    int numberOfRoutes();
    long numberOfStops();
    pair<typename list<pair<string, T>>::iterator, typename list<pair<string, T>>::iterator> listOfRoutes(string);
    pair<typename list<T>::iterator, typename list<T>::iterator> listOfRoutes (string, T, T);
    pair<list<string>::iterator, list<string>::iterator> emptyStop();
    string popularStop ();
};


template <class T>
void Transport<T>::addRoute(T number, string type, pair<list<string>::iterator, list<string>::iterator> pstops)
{
    pair<string, T> a = make_pair(type, number);
    for(auto it=pstops.first; it!=pstops.second; it++)
    {
        stops[*it].push_back(a);
        routes[type][number].push_back(*it);
    }
}


template <class T>
void Transport<T>::deleteRoute(T number, string type)
{
    for(auto it=routes[type][number].begin(); it!=routes[type][number].end(); ++it)
    {
        stops[*it].erase(find(stops[*it].begin(), stops[*it].end(), make_pair(type, number)));
    }
    routes[type].erase(number);
}




template <class T>
void Transport<T>::addStop(string stop)
{
    stops[stop];
}



template <class T>
void Transport<T>::deleteStop(string stop)
{
    if(stops[stop].size()==0)
    {
        stops.erase(stop);
        return;
    }
    for(auto it=stops[stop].begin(); it!=stops[stop].end(); ++it)
    {
        routes[it->first][it->second].erase(find(routes[it->first][it->second].begin(), routes[it->first][it->second].end(), stop));
        if(routes[it->first][it->second].empty()) routes[it->first].erase(it->second);
    }
    stops.erase(stop);
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
    return make_pair(stops[stop].begin(), stops[stop].end());
}




template <class T>
pair<typename list<T>::iterator, typename list<T>::iterator> Transport<T>::listOfRoutes(string type, T begin, T end)
{
    selectedRoutes.clear();
    for(auto it=routes[type].begin(); it!=routes[type].end(); ++it)
        if(it->first>=begin && it->first<= end) selectedRoutes.push_back(it->first);
    return make_pair(selectedRoutes.begin(), selectedRoutes.end());
}




template <class T>
pair<list<string>::iterator, list<string>::iterator> Transport<T>::emptyStop()
{
    emptyStops.clear();
    for(auto it=stops.begin(); it!=stops.end(); ++it)
        if(it->second.size()==0) emptyStops.push_back(it->first);
    return make_pair(emptyStops.begin(), emptyStops.end());
}




template <class T>
string Transport<T>::popularStop()
{
    auto it=stops.begin();
    if(stops.size()==0) return "";
    string popularStop=it->first;
    long amount=(it->second.size());
    for(; it!=stops.end(); ++it)
        if(it->second.size()>amount)
        {
            popularStop=it->first;
            amount=it->second.size();
        }
    return popularStop;
}




#endif