#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// Definition of a pair structure.
typedef struct pair_t
{
    int first;
    int second;
} pair_t;


// Definition of a pair vector structure.
typedef struct pairvec_t
{
    pair_t  *t;
    int     len;
    int     size;
    int     block;
} pairvec_t;


// Definition of an integer vector structure.
typedef struct intvec_t
{
    int  *p;
    int  len;
    int  size;
    int  block;
} intvec_t;


// Allocate and initialize a ndw pair_vec_t
pairvec_t * new_pairvec(int initialSize, int block)
{
    pairvec_t *pv;
    
    pv = malloc(sizeof(pairvec_t));
    
    if (!pv)
    {
        fprintf(stderr, "ERROR: Insufficient memory in new_pairvec\n");
        exit(1);
    }

    pv->t = malloc(initialSize * sizeof(pair_t));
    if(!pv->t)
    {
        fprintf(stderr, "ERROR: Insufficient memory.");
        exit(1);
    }
    pv->len = 0;
    pv->size = initialSize;
    pv->block = block;

    return pv;
}


// Deallocate a pairvec_t structure.
void free_pairvec(pairvec_t **ppv)
{
    if (!ppv)
    {
        fprintf(stderr, "ERROR: Invalid pointer passed to free_pairvec\n");
        exit(1);
    }
    
    pairvec_t *pv = *ppv;
    
    if(pv->t)
    {
        free(pv->t);
    }
    
    free(*ppv);
}


// Add a new pair_t to the pairvec_t vector.
void add_pair_to_pairvec(pairvec_t *pv, int key, int value)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid pairvec_t pointer passed to add_pair_to_pairvec");
        exit(1);
    }
    
    if(!pv->t) {
        fprintf( stderr, "ERROR: pairvec data pointer is null in add_pair_to_pairvec\n");
        exit(1);
    }
    
    // Sanity check.
    if(pv->len > pv->size)
    {
        fprintf(stderr, "ERROR: len > size in add_pair_to_pairvec\n");
        exit(1);
    }

    if(pv->len == pv->size)
    {
        // Add room for quanta element(s).
        pair_t *p = malloc( (pv->size + pv->block) * sizeof(pair_t));
        if(!p)
        {
            fprintf(stderr, "ERROR: Insufficient memory.");
            exit(1);
        }
        pv->size += pv->block;
        memcpy(p, pv->t, (pv->len * sizeof(pair_t)));
        free(pv->t);
        pv->t = p;
    }

    pv->t[pv->len].first = key;
    pv->t[pv->len].second = value;
    pv->len += 1;
}


// Increment the value of an elemnt in the pair vector by key.
// Adds it and initializes the value to 1 if not already present.
int increment_value_in_pairvec_by_key(pairvec_t *pv, int key)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid pairvec_t pointer passed to increment_value_in_pairvec_by_key");
        exit(1);
    }

    if(!pv->t) {
        fprintf( stderr, "ERROR: pairvec data pointer is null in increment_value_in_pairvec_by_key\n");
        exit(1);
    }

    for(int i = 0; i < pv->len; i++)
    {
        if (pv->t[i].first == key)
        {
            pv->t[i].second += 1;
            return pv->t[i].second;
        }
    }

    // If we get here, the key is not yet in the vec. Add it now.
    add_pair_to_pairvec(pv, key, 1);
    return 1;
}

// Comparison function for the qsort call in sort_pairvec_by_value function.
int compare(const void *a, const void *b)
{
    pair_t *t1 = (pair_t *) a;
    pair_t *t2 = (pair_t *) b;
    
    return t2->second - t1->second;
}


// Sort the pair_t structures in the pair vector by value (second).
void sort_pairvec_by_value(pairvec_t *pv)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid pairvec_t pointer passed to sort_pairvec_by_value");
        exit(1);
    }
    
    qsort(pv->t, pv->len, sizeof(pair_t), compare);
}


// Allocate and initialize a new integer vector.
intvec_t * new_intvec(int initialSize, int block)
{
    intvec_t *pv = malloc(sizeof(intvec_t));
    
    if(!pv)
    {
        fprintf(stderr, "ERRRO: Insufficient memory in new_intvec\n");
        exit(1);
    }
    
    pv->p = malloc(initialSize * sizeof(int));
    if(!pv->p)
    {
        fprintf(stderr, "ERROR: Insufficient memory.");
        exit(1);
    }
    pv->len = 0;
    pv->size = initialSize;
    pv->block = block;

    return pv;
}


// Adds an integer to the integer vector. Grows the vector if necessary.
void add_int_to_intvec(intvec_t *pv, int value)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid intvec_t pointer passed to add_int_to_intvec");
        exit(1);
    }
    
    if(!pv->p) {
        fprintf( stderr, "ERROR: intvec data pointer is null in increment_value_in_pairvec_by_key\n");
        exit(1);
    }
    
    // Sanity check.
    if(pv->len > pv->size)
    {
        fprintf(stderr, "ERROR: len > size in add_int_to_intvec\n");
        exit(1);
    }

    if(pv->len == pv->size)
    {
        // Add room for quanta int(s).
        int *p = malloc( (pv->size + pv->block) * sizeof(int));
        if(!p)
        {
            fprintf(stderr, "ERROR: Insufficient memory.");
            exit(1);
        }
        pv->size += pv->block;
        memcpy(p, pv->p, (pv->len * sizeof(int)));
        free(pv->p);
        pv->p = p;
    }

    pv->p[pv->len] = value;
    pv->len += 1;
}


// Deallocate an integer vector.
void free_intvec(intvec_t **ppv)
{
    if (!ppv)
        {
            fprintf(stderr, "ERROR: Invalid pointer passed to free_intvec\n");
            exit(1);
        }
    
    intvec_t *pv = *ppv;
    
    if(pv->p)
        {
            free(pv->p);
        }
    
    free(*ppv);
}


// Print the contents of an integer array.
void print_int_array(const char *title, int *nums, int n)
{
    if(!title)
    {
        fprintf(stderr, "ERROR: Null title passed to print_int_array\n");
        exit(1);
    }

    if(!nums) 
    {
        fprintf(stderr, "ERROR: Null nums passed to print_int_array\n");
        exit(1);
    }
    
    const int no_truncate_arrays = getenv("NO_TRUNCATE_ARRAYS") != 0 ? 1 : 0;

    printf("%s[ ", title);
    for(int i = 0; i < n; i++) 
    {
        if(!no_truncate_arrays && i >= 30)
        {
            printf("...");
            break;
        }
        printf("%d ", nums[i]);
    }
    printf("]\n");
}


// Print the contents of an integer vector.
void print_intvec(const char *title, const intvec_t *piv)
{
    if(!title) 
    {
        fprintf(stderr, "ERROR: Null title passed to print_intvec\n");
        exit(1);
    }
    
    if(!piv)
    {
        fprintf(stderr, "ERROR: Null intvec_t pointer passed to print_int_array\n");
        exit(1);
    }

    const int no_truncate_arrays = getenv("NO_TRUNCATE_ARRAYS") != 0 ? 1 : 0;
    
    printf("%s[ ", title);
    for(int i = 0; i < piv->len; i++)
    {
        if(!no_truncate_arrays && i >= 30)
        {
            printf("...");
            break;
        }
        printf("%d ", piv->p[i]);
    }
    printf("]\n");
}


// This is where we actually do the work of find the most frequent numbers.
intvec_t * get_most_frequent_numbers(int *nums, int n, int k)
{
    const int size = n / 2 > 0 ? n / 2 : 20;
    intvec_t *result = 0;
    pairvec_t *pv = new_pairvec(size, size);
    
    
    // Record the number of occurrences of each value in the pairvec.
    for(int i = 0; i < n; i++)
    {
        increment_value_in_pairvec_by_key(pv, nums[i]);
    }
    
    // Sort the pairvec by number of occurrences.
    sort_pairvec_by_value(pv);
    
    result = new_intvec(k, k);
    
    // Copy the top k most frequent numbers from the pair vector into an int vector.
    for(int i = 0; i < k; i++)
    {
        result->p[i] = pv->t[i].first;
        result->len++;
    }
    
    free_pairvec(&pv);
    
    return result;
}


// Runs a test on get_most_frequent_numbers using an array of random integers.
void run_random_inputs_test(int num_data_points, int max_value, int num_most_frequent)
{
    int *nums = malloc(num_data_points * sizeof(int));
    int k = num_most_frequent;
    intvec_t *r;
    srand(time(0));
    for(int i = 0; i < num_data_points; i++)
    {
        nums[i] = rand() % max_value;
    }
    r = get_most_frequent_numbers(nums, num_data_points, k);
    print_int_array("  nums: ", nums, num_data_points);
    printf("     k: %d\n", k);
    print_intvec("result: ", r);
    free(nums);
    free_intvec(&r);
}


// Entry point.
int main(int argc, char *argv[])
{
    intvec_t *r;
    int nums[] = {9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1};
    int n = sizeof(nums) / sizeof(int);
    int k = 4;
    
    r = get_most_frequent_numbers(nums, n, k);
    
    print_int_array("  nums: ", nums, n);
    printf("     k: %d\n", k);
    print_intvec("result: ", r);
    
    free_intvec(&r);

    if (argc > 3)
    {
        int num_data_points = atoi(argv[1]);
        int max_value = atoi(argv[2]);
        int num_most_frequent = atoi(argv[3]);
        run_random_inputs_test(num_data_points, max_value, num_most_frequent);
    }
    
    return 0;
}





