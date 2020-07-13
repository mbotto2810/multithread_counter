#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define max_threads 4
#define max_num 100

pthread_mutex_t trava;
int vet[max_num];
unsigned int contagem_primos=0;

void *primo(void* arg) {
    int *N = (int*)arg;
    int M = (*N);
    int aux=1;
    for (int p=0 ; p<max_num ; p++) {
        if ((M == 0) && (vet[p] != 0) && (vet[p]!=1) && (p%4==0)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vet[p] / 2; ++i) {
                        if (vet[p] % i == 0) {
                            aux =0;
                        }
                    }
                    if (aux!=0) {
                        contagem_primos = contagem_primos + 1;
                    }
                    aux=1;
                    pthread_mutex_unlock(&trava);
        }
        if ((M == 1) && (vet[p]) != 0 && (vet[p]!=1) && (p%4==1)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vet[p] / 2; ++i) {
                        if (vet[p] % i == 0) {
                            aux = 0;
                        }
                    }
                    if (aux!=0) {
                        contagem_primos = contagem_primos + 1;
                    }
                    aux=1;
                    pthread_mutex_unlock(&trava);
        }
        if ((M == 2) && (vet[p] != 0) && (vet[p]!=1) && (p%4==2)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vet[p] / 2; ++i) {
                        if (vet[p] % i == 0) {
                            aux=0;
                        }
                    }
                    if (aux!=0) {
                        contagem_primos = contagem_primos + 1;
                    }
                    aux=1;
                    pthread_mutex_unlock(&trava);
        }
        if ((M == 3) && (vet[p] != 0) && (vet[p]!=1) && (p%4==3)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vet[p] / 2; ++i) {
                        if (vet[p] % i == 0) {
                            aux=0;
                        }
                    }
                    if (aux!=0) {
                        contagem_primos = contagem_primos + 1;
                    }
                    aux=1;
                    pthread_mutex_unlock(&trava);
        }

    }
    return NULL;
}

int main() {
    int n,i=0;
    char c;

    pthread_t threads[max_threads];
    int threads_id[max_threads];

    //Recebe os dados do usuario
	do {
		scanf("%d", &n);
		vet[i] = n;
		i++;
	} while (c = getchar() != '\n');

    for (int y=i ; y<max_num +1; y++){
        vet[y] = 0;
    }

    //Dispara threads
    for (int p=0 ; p<max_threads ; p++){
        threads_id[p]=p;
        pthread_create(&(threads[p]),NULL,primo,&(threads_id[p]));
    }

    //Aguarda o encerramento e todas as threads
	for (int x=0; x<max_threads; x++) {
		pthread_join(threads[x],NULL);
    }

    //Imprime o resultado final
	printf("%d\n",contagem_primos);
	return 0;
}
