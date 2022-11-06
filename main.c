#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*
    Example:
    rand --size 10000 --lower-limit -10 --upper-limit 10
*/

typedef struct {
    long long int lenght_result;
    int only_positives;
    int min;
    int max;
} Config;

void print_vector(int vector_size, int* vector)
{
    for (int i = 0; i < vector_size; i++)  {
        printf("%d", vector[i]);
        if (i != vector_size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

Config read_config_from_stdin(int argc, char** argv)
{
    Config config;
    config.lenght_result = 1;
    config.only_positives = 1;
    config.min = 0;
    config.max = INT_MAX;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (!strcmp("-s", argv[i]) || !strcmp("--size", argv[i])) {
                config.lenght_result = atoll(argv[i + 1]);
            } else if (!strcmp(argv[i], "-n") || !strcmp("--allow-negatives", argv[i])) {
                config.only_positives = 0;
            } else if (!strcmp(argv[i], "-ll") || !strcmp("--lower-limit", argv[i])) {
                config.min = atoi(argv[i + 1]);
                if (config.min < 0)
                    config.only_positives = 0;
            } else if (!strcmp(argv[i], "-ul") || !strcmp("--upper-limit", argv[i])) {
                config.max = atoi(argv[i + 1]);
            }
        }
    }
    return config;
}

int *vector(Config config) 
{
    return (int *) malloc(sizeof(long long int) * config.lenght_result);
}

int *random_numbers(Config config)
{
    int *v = vector(config);
    srand(time(NULL));
    for(int i = 0; i < config.lenght_result; i++)
    {
        int n = rand();
        if (!config.only_positives && i % 2) {
            n = -n;
        }
        n += config.min;
        n = n % config.max;
        v[i] = n;
    }
    return v;
}

int main(int argc, char** argv)
{
    Config config = read_config_from_stdin(argc, argv);
    int *v = random_numbers(config);
    print_vector(config.lenght_result, v);
    free(v);
    return EXIT_SUCCESS;
}
