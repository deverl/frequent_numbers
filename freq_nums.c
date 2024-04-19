#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct pair_t
{
    int first;
    int second;
} pair_t;


typedef struct pairvec_t
{
    pair_t  *t;
    int     len;
    int     size;
    int     block;
} pairvec_t;


typedef struct intvec_t
{
    int  *p;
    int  len;
    int  size;
    int  block;
} intvec_t;


void init_pairvec(pairvec_t *pv, int initialSize, int block)
{
    if(pv)
    {
        pv->t = malloc(initialSize * sizeof(pair_t));
        if(!pv->t)
        {
            fprintf(stderr, "ERROR: Insufficient memory.");
            exit(1);
        }
        pv->len = 0;
        pv->size = initialSize;
        pv->block = block;
    }
    else {
        fprintf(stderr, "ERROR: invalid pairvec_t pointer passed to init_pairvec");
        exit(1);
    }
}

void add_pair_to_pairvec(pairvec_t *pv, int key, int value)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid pairvec_t pointer passed to add_pair_to_pairvec");
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


int increment_value_in_pairvec_by_key(pairvec_t *pv, int key)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid pairvec_t pointer passed to increment_value_in_pairvec_by_key");
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


int compare(const void *a, const void *b)
{
    pair_t *t1 = (pair_t *) a;
    pair_t *t2 = (pair_t *) b;
    
    return t2->second - t1->second;
}


void sort_pairvec_by_value(pairvec_t *pv)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid pairvec_t pointer passed to sort_pairvec_by_value");
        exit(1);
    }
    
    qsort((void *)pv->t, pv->len, sizeof(pair_t), compare);
}


void init_intvec(intvec_t *pv, int initialSize, int block)
{
    if(pv)
    {
        pv->p = malloc(initialSize * sizeof(int));
        if(!pv->p)
        {
            fprintf(stderr, "ERROR: Insufficient memory.");
            exit(1);
        }
        pv->len = 0;
        pv->size = initialSize;
        pv->block = block;
    }
    else {
        fprintf(stderr, "ERROR: invalid intvec_t pointer passed to init_intvec");
        exit(1);
    }
}

void add_int_to_intvec(intvec_t *pv, int value)
{
    if(!pv)
    {
        fprintf(stderr, "ERROR: invalid intvec_t pointer passed to add_int_to_intvec");
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

void print_int_array(const char *title, int *nums, int n)
{
    printf("%s[ ", title);
    for(int i = 0; i < n; i++) 
    {
        printf("%d ", nums[i]);
    }
    printf("]\n");
}

void print_intvec(const char *title, const intvec_t *piv)
{
    printf("%s[ ", title);
    for(int i = 0; i < piv->len; i++)
    {
        printf("%d ", piv->p[i]);
    }
    printf("]\n");
}




intvec_t get_most_frequent_numbers(int *nums, int n, int k)
{
    intvec_t result;
    pairvec_t pv;
    
    const int size = n / 2 > 0 ? n / 2 : 20;
    
    init_pairvec(&pv, size, size);
    
    // Record the number of occurrences of each value in the pairvec.
    for(int i = 0; i < n; i++)
    {
        increment_value_in_pairvec_by_key(&pv, nums[i]);
    }
    
    // Sort the pairvec by number of occurrences.
    sort_pairvec_by_value(&pv);
    
    init_intvec(&result, k, k);
    
    for(int i = 0; i < k; i++)
    {
        result.p[i] = pv.t[i].first;
        result.len++;
    }
    
    free(pv.t);
    
    return result;
}



void run_random_inputs_test(int num_data_points, int max_value, int num_most_frequent)
{
    int *nums = malloc(num_data_points * sizeof(int));
    int k = num_most_frequent;
    intvec_t r;
    srand(time(0));
    for(int i = 0; i < num_data_points; i++)
    {
        nums[i] = rand() % max_value;
    }
    r = get_most_frequent_numbers(nums, num_data_points, k);
    print_int_array("  nums: ", nums, num_data_points);
    printf("     k: %d\n", k);
    print_intvec("result: ", &r);
    free(nums);
    free(r.p);
}




int main(int argc, char *argv[])
{
    intvec_t r;
    int nums[] = {9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1};
    int n = sizeof(nums) / sizeof(int);
    int k = 4;
    
    r = get_most_frequent_numbers(nums, n, k);
    
    print_int_array("  nums: ", nums, n);
    printf("     k: %d\n", k);
    print_intvec("result: ", &r);
    
    free(r.p);

    if (argc > 3)
    {
        int num_data_points = atoi(argv[1]);
        int max_value = atoi(argv[2]);
        int num_most_frequent = atoi(argv[3]);
        run_random_inputs_test(num_data_points, max_value, num_most_frequent);
    }
    
    return 0;
}





