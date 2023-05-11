#include "stats.h"
#include "hashtable.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

Stats::Stats(string name, const vector<int> & chain_lengths) : name(name), chain_lengths(chain_lengths){
    entries = NWORDS;
    chains = chain_lengths.size();
    load_factor = (double)entries/chains;
    min = calc_min(chain_lengths);
    max = calc_max(chain_lengths);
    span = max - min;
    mean = calc_mean(chain_lengths);
    stddev = calc_stddev(chain_lengths);
    for(int i : chain_lengths){
        histogram[i]++;
    }
}