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
int vetor_primos[max_num];
unsigned int contagem_primos=0;

void *primo(void* arg) {
    //Sao variaveis auxiliares
    int *N = (int*)arg;
    int M = (*N);
    int aux=1;

    for (int p=0 ; p<max_num ; p++) {
    //Verifica qual thread vai trabalhar no que com base no resto da div por 4
    //Tambem ignora os casos 0 e 1
        if ((M == 0) && (vetor_primos[p] != 0) && (vetor_primos[p]!=1) && (p%4==0)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vetor_primos[p] / 2; ++i) {
                        if (vetor_primos[p] % i == 0) {
                            aux =0;
                        }
                    }
                    if (aux!=0) {
                        contagem_primos = contagem_primos + 1;
                    }
                    aux=1;
                    pthread_mutex_unlock(&trava);
        }
        if ((M == 1) && (vetor_primos[p]) != 0 && (vetor_primos[p]!=1) && (p%4==1)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vetor_primos[p] / 2; ++i) {
                        if (vetor_primos[p] % i == 0) {
                            aux = 0;
                        }
                    }
                    if (aux!=0) {
                        contagem_primos = contagem_primos + 1;
                    }
                    aux=1;
                    pthread_mutex_unlock(&trava);
        }
        if ((M == 2) && (vetor_primos[p] != 0) && (vetor_primos[p]!=1) && (p%4==2)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vetor_primos[p] / 2; ++i) {
                        if (vetor_primos[p] % i == 0) {
                            aux=0;
                        }
                    }
                    if (aux!=0) {
                        contagem_primos = contagem_primos + 1;
                    }
                    aux=1;
                    pthread_mutex_unlock(&trava);
        }
        if ((M == 3) && (vetor_primos[p] != 0) && (vetor_primos[p]!=1) && (p%4==3)) {
                    pthread_mutex_lock(&trava);
                    for (int i = 2; i <= vetor_primos[p] / 2; ++i) {
                        if (vetor_primos[p] % i == 0) {
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
    //variaveis auxiliares
    int n,i=0;
    char c;

    //variaveis envolvendo os ids das threads e pthread
    pthread_t threads[max_threads];
    int threads_id[max_threads];

    //Recebe os dados do usuario
	do {
		scanf("%d", &n);
		vetor_primos[i] = n;
		i++;
	} while (c = getchar() != '\n');

    for (int y=i ; y<max_num +1; y++){
        vetor_primos[y] = 0;
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
