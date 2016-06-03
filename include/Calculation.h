#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

typedef map<string, vector<int> > table;

class Cell
{
public:
    double RelationValue = 0;
    string RowName;
    string ColName;
    
    Cell (double _RelationValue, string _RowName, string _ColName) 
    {
        RelationValue = _RelationValue;
        RowName = _RowName;
        ColName = _ColName;
    }
    
    bool operator==(const Cell other) const { return RelationValue == other.RelationValue; }
    bool operator< (const Cell other) const { return RelationValue >  other.RelationValue; }
    bool operator> (const Cell other) const { return RelationValue <  other.RelationValue; }
    bool operator<=(const Cell other) const { return RelationValue >= other.RelationValue; }
    bool operator>=(const Cell other) const { return RelationValue <= other.RelationValue; }
    bool operator!=(const Cell other) const { return RelationValue != other.RelationValue; }
};

int numberIntersection(vector<int> v1, vector<int> v2)
{
    vector<int> v (v1.size());
    auto it=std::set_intersection (v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
    v.resize(it-v.begin());  
    return v.size();
}

void calculateList(vector <Cell> &TopList, table &Row, table &Column)
{
    for (auto row : Row)
    {        
        if (row.first == "Null") continue;
        int sum = 0;
        vector<Cell> thisrow;
        for (auto col : Column)
        {
            Cell c = Cell(
                numberIntersection(row.second, col.second),
                row.first,
                col.first);

            sum += c.RelationValue;
            if (col.first != "Null") thisrow.push_back(c);
        }
        
        for (auto &n : thisrow)
        {
            if (sum != 0)
                n.RelationValue /= sum;
            TopList.push_back(n);
        }
    }
    
    std::sort(TopList.begin(), TopList.end());
}

bool sortFromLarge (pair<string, vector<int> > i, pair <string, vector<int> > j) { return (i.second.size() > j.second.size()); }

void takeTop(table &full, table& top, int number)
{
    vector < pair <string, vector <int> > > list;
    for (auto &n : full)
    {
        list.push_back(n);
    }
    std::sort(list.begin(), list.end(), sortFromLarge);
    for (int i = 0; i < number; ++i)
    {
        top.insert(list[i]);
    }
}