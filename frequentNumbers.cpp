#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;


// Comparison function to sort a vector of pairs by the second value in the pair.
bool compare(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second > p2.second;
}

vector<int> getMostFrequentNumbers(vector<int>& nums, int k)
{
    // Build up a map where the keys are each unique value from the input 'nums'
    // and the value is the number of times it appears in the input array.
    map<int, int> m;
    for (int i : nums)
    {
        m[i]++;
    }
    
    // Store the pairs of values from the map in the vector a
    vector<pair<int, int> > a(m.begin(), m.end());
    
    // Sort the vector 'a' by the value (the second part of the pair).
    sort(a.begin(), a.end(), compare);

    // Build up a vector containing the top k elements
    vector<int> r;
    for (int i = 0; i < k; i++)
    {
        r.push_back(a[i].first);
    }
    
    return r;
}


void print_vec(const string s, const vector<int>& v)
{
    cout << s;
    
    for (int n :v)
    {
        cout << n << " ";
    }
    
    cout << endl;
}


int main(int argc, char *argv[])
{
    vector<int> nums{9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1};
    int k(4);
    vector<int> v;
    
    v = getMostFrequentNumbers(nums, k);
    
    print_vec("The most frequent numbers are: ", v);
    
    return 0;
}



