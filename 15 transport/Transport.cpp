#include "Transport.h"



void Transport::addRoute(int number, string type, pair<list<string>::iterator, list<string>::iterator> pstops)
{
    pair<string, int> a = make_pair(type, number);
    for(auto it=pstops.first; it!=pstops.second; it++)
    {
        stops[*it].push_back(a);
        routes[type][number].push_back(*it);
    }
}



void Transport::deleteRoute(int number, string type)
{
    for(auto it=routes[type][number].begin(); it!=routes[type][number].end(); ++it)
    {
        stops[*it].erase(find(stops[*it].begin(), stops[*it].end(), make_pair(type, number)));
    }
    routes[type].erase(number);
}





void Transport::addStop(string stop)
{
    stops[stop];
}




void Transport::deleteStop(string stop)
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






int Transport::numberOfRoutes()
{
    int amount=0;
    for(auto it=routes.begin(); it!=routes.end(); ++it)
        amount+=(it->second).size();
    return amount;
}






long Transport::numberOfStops()
{
    return stops.size();
}




pair<list<pair<string, int>>::iterator, list<pair<string, int>>::iterator> Transport::listOfRoutes(string stop)
{
    return make_pair(stops[stop].begin(), stops[stop].end());
}





 pair<list<int>::iterator, list<int>::iterator> Transport::listOfRoutes(string type, int begin, int end)
{
    selectedRoutes.clear();
    for(auto it=routes[type].begin(); it!=routes[type].end(); ++it)
        if(it->first>=begin && it->first<= end) selectedRoutes.push_back(it->first);
    return make_pair(selectedRoutes.begin(), selectedRoutes.end());
}





pair<list<string>::iterator, list<string>::iterator> Transport::emptyStop()
{
    emptyStops.clear();
    for(auto it=stops.begin(); it!=stops.end(); ++it)
        if(it->second.size()==0) emptyStops.push_back(it->first);
    return make_pair(emptyStops.begin(), emptyStops.end());
}





string Transport::popularStop()
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







