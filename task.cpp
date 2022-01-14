#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <unordered_map>
using namespace std;

void func()
{
    map<string, string> months_map = {
        {"01", "January"},
        {"02", "February"},
        {"03", "March"},
        {"04", "April"},
        {"05", "May"},
        {"06", "June"},
        {"07", "July"},
        {"08", "August"},
        {"09", "September"},
        {"10", "October"},
        {"11", "November"},
        {"12", "December"}};
    unordered_map<string, unordered_map<string, unordered_map<string, int>>> name_umap;
    unordered_map<string, unordered_map<string, int>> year_umap;
    unordered_map<string, int> month_umap;

    string fname = "input.csv";

    string line, word, name, year, month, date;
    int hours, value;

    bool res_uname = name_umap.find(name) == name_umap.end();
    bool res_uyear = name_umap[name].find(year) == name_umap[name].end();
    bool res_umonth = name_umap[name][year].find(month) == name_umap[name][year].end();
    vector<string> row;
    vector<string> names;
    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);

            while (getline(str, word, ';'))
                row.push_back(word);

            name = row[0];
            if (name == "Alex")
                throw "Alex is not a real name";
            date = row[6];
            unsigned first = date.find("-");
            unsigned last = date.find_last_of("-");
            month = months_map[date.substr(first + 1, last - first - 1)];
            year = date.substr(0, 4);
            hours = stoi(row[7]);

            res_uname = name_umap.find(name) == name_umap.end();
            res_uyear = name_umap[name].find(year) == name_umap[name].end();
            res_umonth = name_umap[name][year].find(month) == name_umap[name][year].end();
            if (res_uname)
            {
                name_umap[name] = {};
            }
            if (res_uyear)
            {
                name_umap[name][year] = {};
            }
            if (res_umonth)
            {
                name_umap[name][year][month] = hours;
            }
            if (!res_uyear)
            {
                if (!res_umonth)
                {
                    name_umap[name][year][month] += hours;
                }
            }
        }
        int i = 0, j = 0;
        std::ofstream myFile("result.csv");
        myFile << "Name   Year    Month   Hours \n";
        unordered_map<string, unordered_map<string, unordered_map<string, int>>>::iterator itr1;
        for (itr1 = name_umap.begin(); itr1 != name_umap.end(); itr1++)
        {
            myFile << itr1->first << "    ";

            unordered_map<string, unordered_map<string, int>>::iterator itr2;
            for (itr2 = itr1->second.begin(); itr2 != year_umap.end(); itr2++)
            {
                if (i != 0)
                {
                    myFile << itr1->first << "    ";
                }
                myFile << itr2->first << "    ";

                unordered_map<string, int>::iterator itr3;
                for (itr3 = itr2->second.begin(); itr3 != month_umap.end(); itr3++)
                {
                    if (j != 0)
                    {
                        myFile << itr1->first << "    ";
                        myFile << itr2->first << "    ";
                    }
                    myFile << itr3->first << "    " << itr3->second << "\n";

                    j++;
                }
                j = 0;
                i++;
            }
            i = j = 0;
        }
    }
}

int main()
{
    func();
    return 0;
}