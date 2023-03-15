#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/resource.h>
#include <string.h>

#define DEFAULT_THREADS 1
#define DEFAULT_POOL_ADDRESS "stratum+tcp://btc.pool.com:3333"
#define MEGABYTE 1024*1024
#define MIN_VIRTUAL_MEMORY (20 * 1024 * 1024)
#define MAX_VIRTUAL_MEMORY (40 * 1024 * 1024)

void print_help() {
    printf("Uso: b1tc01n_m!n3r [OPZIONI]\n");
    printf("Opzioni disponibili:\n");
    printf("  -h, --help                      Visualizza l'aiuto del programma e termina.\n");
    printf("  -t, --threads=<num_threads>     Specifica il numero di thread da utilizzare per il mining di Bitcoin. Il valore predefinito è 1.\n");
    printf("  -p, --pool=<pool_address>       Specifica l'indirizzo del pool di mining a cui il programma si connetterà.\n");
    printf("  -e, --exec=<command>            Esegue il comando specificato e termina il programma.\n");
}

int main(int argc, char *argv[]) {
    int threads = DEFAULT_THREADS;
    char *pool_address = DEFAULT_POOL_ADDRESS;
    char *command = NULL;

    int opt;
    struct option longopts[] = {
        { "help", no_argument, NULL, 'h' },
        { "threads", required_argument, NULL, 't' },
        { "pool", required_argument, NULL, 'p' },
        { "exec", required_argument, NULL, 'e' },
        { NULL, 0, NULL, 0 }
    };

    while ((opt = getopt_long(argc, argv, "ht:p:e:", longopts, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 't':
                threads = atoi(optarg);
                break;
            case 'p':
                pool_address = optarg;
                break;
            case 'e':
                command = optarg;
                break;
            default:
                fprintf(stderr, "Opzione non valida. Usa l'opzione -h o --help per visualizzare l'aiuto.\n");
                return 1;
        }
    }
    

    // Imposta il limite minimo e massimo alla quantità di memoria virtuale utilizzata dal processo
    struct rlimit memory_limit = {
        .rlim_cur = MIN_VIRTUAL_MEMORY,
        .rlim_max = MAX_VIRTUAL_MEMORY
    };
    if (setrlimit(RLIMIT_AS, &memory_limit) != 0) {
        fprintf(stderr, "Impossibile impostare il limite di memoria virtuale.\n");
        return 1;
    }

    if (command != NULL) {
        system(command);
        return 0;
    }
    else{
        sleep(20);
    }

    return 0;
}
