#ifndef __Transport__File__
#define __Transport__File__
#include <map>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;



class Transport
{
    list<string> emptyStops;
    list<int> selectedRoutes;
    map<string, map<int, list<string> > > routes;
    map<string, list<pair<string, int> > > stops;
public:
    void addRoute(int, string, pair<list<string>::iterator, list<string>::iterator>);
    void deleteRoute(int, string);
    void addStop(string);
    void deleteStop(string);
    int numberOfRoutes();
    long numberOfStops();
    pair<list<pair<string, int>>::iterator, list<pair<string, int>>::iterator> listOfRoutes(string);
    pair<list<int>::iterator, list<int>::iterator> listOfRoutes (string, int, int);
    pair<list<string>::iterator, list<string>::iterator> emptyStop();
    string popularStop ();
};





#endif