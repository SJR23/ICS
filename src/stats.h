#ifndef STATS_H
#define STATS_H
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include "hashtable.h"

using namespace std;

struct Stats {
    string name;
    int entries = 0;
    int chains = 0;
    double load_factor = 0;
    int min = 0;
    int max = 0;
    int span = 0;
    double mean = 0;
    double stddev = 0;
    map<int,int> histogram{};
    vector<int> chain_lengths{};

    Stats(string name, const vector<int> & chain_lengths);

    void print_histogram(ostream & out)
    {
        for (auto &e : histogram)
        {
            auto [len,freq] = e;
            if (freq > 0)
                out << "len(" << len << ") = " << freq << endl;
        }
    }
    
    int compute_min(const vector<int> & v){
        return *min_element(v.begin(), v.end());
    }
    
    int compute_max(const vector<int> & v){
        int val = v[0];
        for(auto n : v){
            if(n > val)
                val = n;
        }
        return val;
    }
    
    double compute_mean(const vector<int> & v){
        double s = 0;
        for(auto & i : v)
            s += i;
        return s/v.size();
    }
    
    double compute_stddev(const vector<int> & v){
        double s = 0;
        double ss = 0;
        for(int i : v){
            s += i;
            ss += i * i;
        }
        double m = s / v.size();
        double var = ss/v.size() - m*m;
        return sqrt(var);
    }
    
    
    void print(ostream & out)
    {
        cout << name << endl;
        out << "Entries = " << entries << endl;
        out << "Chains = " << chains << endl;
        out << "Load Factor = " << load_factor << endl;
        out << "Min = " << min << endl;
        out << "Max = " << max << endl;
        out << "Span = " << (max-min) << endl;
        out << "Mean = " << mean << endl;
        out << "StdDev = " << stddev << endl;
        // print_histogram(out);
    }
};

#endif
