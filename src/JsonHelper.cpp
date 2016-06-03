#include "JsonHelper.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include <iostream>


using namespace std;
using namespace rapidjson;

Item* JsonHelper::parse(FILE* file)
{
    char readBuffer[65536];
    FileReadStream is(file, readBuffer, sizeof(readBuffer));
    
    Document d;
    d.ParseStream(is);
    
    Value& info  = d["Information"];
    Value& CWE   = info["CWE"];
    Value& CAPEC = info["CAPEC"];
    Value& CPE   = info["CPE"];
    Value& Risk  = d["Risk"];

    Item* item = new Item;
    getCWE(item->CWE, CWE);
    getCAPEC(item->CAPEC, CAPEC);
    getRisk(item->Risk, Risk);
    getCPE(item->CPE, CPE);
    fclose (file);
    return item;
}

string JsonHelper::CPEStringSimplify(string cpe)
{
    int start = 7;
    int end   = cpe.find(":", 8);
    end = cpe.find(":", end + 1);
    return cpe.substr(start, end - start);
}

string JsonHelper::CAPECStringfy(int val)
{
    string str = "CAPEC-"+to_string(val);
    return str;
}

void JsonHelper::getCWE(string& CWEstr, Value& CWE)
{
    CWEstr = (CWE.IsNull()) ? "Null" : CWE[0]["id"].GetString();
}

void JsonHelper::getCAPEC(set<string> & CAPECList, Value& CAPEC)
{
    if (CAPEC.IsNull() || !CAPEC.IsArray()) return;
    for (SizeType i = 0; i < CAPEC.Size(); ++i)
    {
        CAPECList.insert(CAPECStringfy(CAPEC[i]["id"].GetInt()));
    }
    
}

void JsonHelper::getRisk(string& Riskstr, Value& Risk)
{
    Riskstr = (Risk.IsNull()) ? "Null" : Risk[0]["severity"].GetString();
}

void JsonHelper::getCPE(set<string> & CPEList, Value& CPE) 
{
    if (CPE.IsNull() || !CPE.IsArray()) return;
    for (SizeType i = 0; i < CPE.Size(); ++i)
    {
        CPEList.insert(CPEStringSimplify(CPE[i]["id"].GetString()));
    }
}

