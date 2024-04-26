#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;


// Helper to get the value of an environment variable as an integer.
int get_env_var_as_int(const char *name, int default_value)
{
    char *p = getenv(name);
    if(p)
    {
        return atoi(p);
    }
    else
    {
        return default_value;
    }
}


// Comparison function to sort a vector of pairs by the second value in the pair.
bool compare(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second > p2.second;
}

vector<int> get_most_frequent_numbers(const vector<int>& nums, int k)
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
    const int no_truncate_arrays(get_env_var_as_int("NO_TRUNCATE_ARRAYS", 0));
    cout << s << "[ ";
    
    for (vector<int>::size_type i = 0; i < v.size(); i++)
    {
        if(!no_truncate_arrays && i >= 30)
        {
            cout << "... ";
            break;
            
        }
        cout << v[i] << " ";
    }
    
    cout << "]" << endl;
}


void run_test(const vector<int>& nums, int k)
{
    vector<int> v;

    v = get_most_frequent_numbers(nums, k);
    
    cout << endl;
    print_vec("  nums: ", nums);
    cout << "     k: " << k << endl;
    print_vec("result: ", v);
}



// Runs a test on get_most_frequent_numbers using a vector of random integers.
void run_random_inputs_test(int num_data_points, int max_value, int num_most_frequent)
{
    vector<int> nums;
    
    srand(time(0));
    for(int i = 0; i < num_data_points; i++)
    {
        int n = rand() % max_value;
        nums.push_back(n);
    }

    run_test(nums, num_most_frequent);
}



int main(int argc, char *argv[])
{
    vector<int> nums1{1,1,1,2,2,3};
    int k1(2);
    run_test(nums1, k1);

    vector<int> nums2{1,4,2,5,7,5,4,4,5,5,5,2,7,2,5,4};
    int k2(3);

    run_test(nums2, k2);    

    vector<int> nums3{9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1};
    int k3(4);

    run_test(nums3, k3);    

    if (argc > 3)
    {
        int num_data_points = atoi(argv[1]);
        int max_value = atoi(argv[2]);
        int num_most_frequent = atoi(argv[3]);
        run_random_inputs_test(num_data_points, max_value, num_most_frequent);
    }


    cout << endl;

    return 0;
}



