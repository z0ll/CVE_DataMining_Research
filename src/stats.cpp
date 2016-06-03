#include "JsonHelper.h"
#include "Calculation.h"
#include <fstream>
#include <map>
#include <set>
#include <algorithm>    // std::set_intersection, std::sort
#include <iostream>
#include <algorithm>

using namespace std;

typedef map<string, vector<int> > table;

int NumFiles = 75539;

vector<string> readfilenames()
{
    vector<string> filenames;
    ifstream ifs;
    ifs.open("filelist.txt");
    while (ifs.good())
    {
        string str;
        ifs >> str;
        if (str.length() > 4)
        {
            str = "export/" + str;
            filenames.push_back(str);     
        }
    }
    return filenames;
}

void progressBar(double progress)
{
    std::cout << "[";
    int pos = 70.0 * progress;
    for (int i = 0; i < 70; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << (int)(progress*100) << " %\r";
    std::cout.flush();
}

void printTableStats(table t, string filename)
{
    std::ofstream ofs (filename, std::ofstream::out);
    for (auto kv : t)
    {
        ofs << kv.first << "," << kv.second.size() << "\n";
        ofs.flush();
    }
    ofs.close();
}

void printList(vector<Cell> list, string filename)
{
    std::ofstream ofs (filename, std::ofstream::out);
    for (auto c : list)
    {
        ofs << c.RowName << ",";
        ofs << c.ColName << ",";
        ofs << c.RelationValue << "\n";
        ofs.flush();
    }
    ofs.close();
}

void push(table& t, string key, int val)
{
    if (t.find(key) == t.end())
        t[key] = vector<int>();
    t[key].push_back(val);
}

int main()
{
    JsonHelper helper;
    auto filenames = readfilenames();
    vector<Item*> items;
    table CWEs;
    table CAPECs;
    table Risks;
    table CPEs;
    
    int count = 0;    
    for (auto filename : filenames)
    {
        if (count % 10 == 0) progressBar(count * 1.0 / NumFiles * 0.5);
        auto item = helper.parse(fopen(filename.c_str(), "r"));
        items.push_back(item);
        
        push(CWEs, item->CWE, count);

        for (auto c : item -> CAPEC)
            push(CAPECs, c, count);
        
        push(Risks, item->Risk, count);
            
        for (auto c : item->CPE)
            push(CPEs, c, count);

        count ++;
    }
    
    // CWE table
    printTableStats(CWEs, "data/CWE.csv");
    printTableStats(CAPECs, "data/CAPEC.csv");
    printTableStats(Risks, "data/Risk.csv");
    printTableStats(CPEs, "data/CPE.csv");
    progressBar(0.9);
    
    // double-variable
    vector<Cell> CWE_Risk;
    vector<Cell> CWE_CAPEC;
    vector<Cell> CPE_CWE;
    table CPETop200;
    takeTop(CPEs, CPETop200, 200);
    
    calculateList(CWE_Risk, CWEs, Risks);
    calculateList(CWE_CAPEC, CWEs, CAPECs);
    calculateList(CPE_CWE, CPETop200, CWEs);
    printList(CWE_Risk, "data/CWE_Risk.csv");
    printList(CWE_CAPEC, "data/CWE_CAPEC.csv");
    printList(CPE_CWE, "data/CPE_CWE.csv");
   
   
    progressBar(1);
    cout << endl;
    
  

    

    return 0;
}

