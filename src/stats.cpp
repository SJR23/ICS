#include "stats.h"
#include "hashtable.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

Stats::Stats(string name, const vector<int> & chain_lengths) : name(name){
    entries = chain_lengths.size();
    chains = chain_lengths.size();
    load_factor = (double)entries/chains;
    if(entries > 0){
        min = compute_min(chain_lengths);
        max = compute_max(chain_lengths);
        span = 0;
        mean = compute_mean(chain_lengths);
        stddev = compute_stddev(chain_lengths);
        for(int i : chain_lengths){
            histogram[i]++;
        }
    }
}