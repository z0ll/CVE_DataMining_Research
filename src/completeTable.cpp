#include "JsonHelper.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace rapidjson;

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
            str = "rawdata/" + str;
            filenames.push_back(str);     
        }
    }
    return filenames;
}

int main()
{
    auto filenames = readfilenames();
    JsonHelper jsonHelper();
    std::ofstream ofs (filename, std::ofstream::out);

    ofs << "CVE_ID, Published_Time, Lastest_Modification_Time, " 
        << "CAPEC_IDs, CWE_IDs, CPE_IDs, Risk_Severity\n";

    for (auto &f : filenames)
    {
        auto d = jsonHelper.parse(fopen(filename.c_str(), "r"));

        if (d["Information"]["CVE"] != null)
        {
            auto CVEId = d["Information"]["CVE"][0]["id"];
            ofs << CVEId.GetInt();
        }

        ofs << ",";
        if (d["Information"]["CVE"]["published"] != null)
        {
            auto PublishedTime= d["Information"]["CVE"]["published"];
            ofs << PublishedTime.GetString();
        }

        ofs << ",";
        if (d["Information"]["CVE"]["modified"] != null)
        {
            auto LatestModTime= d["Information"]["CVE"]["modified"];
            ofs << LatestModTime.GetString();
        }

        ofs << ",";
        if (d["Information"]["CAPEC"] != null)
        {
            auto CAPEC = d["Information"]["CAPEC"];
            for (SizeType i = 0; i < CAPEC.Size(); ++i) ofs << CAPEC[i]["id"].GetInt() << "|";
        }

        ofs << ",";
        if (d["Information"]["CWE"] != null)
        {
            auto CWE = d["Information"]["CWE"];
            ofs << CWE[0]["id"] << " : " << CWE["title"];
        }

        ofs << ",";
        if (d["Information"]["CPE"] != null)
        {
            auto CPE = d["Information"]["CPE"];
            for (SizeType i = 0; i < CPE.Size(); ++i) ofs << jsonHelper.CPEStringSimplify(CPE[i]["id"].GetString()) << "|";
        }

        ofs << ",";
        if (d["Risk"]["severity"] != null)
        {
            auto RiskSeverity= d["Risk"]["severity"];
            ofs << RiskSeverity.GetString();
        }



    }

    ofs.close();
    return 0;
}