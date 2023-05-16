/*
Aluna: Lila Maria Salvador Frazão
Matrícula: 510809

Atividade 2 - Criando Threads
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define NUM_THREADS 5

pthread_t minhas_threads[NUM_THREADS];

int erro_th = 666;
int sucesso_th = 777;

struct par_thread {
	int num_sec;		// Numero de segundos
	char *nome_thread;		// Nome da thread
};

/** Espera passar 10 segundos, de segundo em segundo */
void *dormir(struct par_thread *param){
	for(int sec = 1; sec <= param->num_sec; sec++){
		sleep(1);
        printf("%s: passaram %d segundos\n", param->nome_thread, sec);
	}

    // Retorna o código 777 se o nome da thread iniciar com a letra maiúscula
    if(isupper(param->nome_thread[0]) != 0){
        return((void *)&sucesso_th);
    }
    // Retorna o código 666 caso o contrário
    else{
        return((void *)&erro_th);
    }
}

int main(){
    struct par_thread param_threads[NUM_THREADS];
    int *codigos_termino[NUM_THREADS];
    
    char possiveis_nomes[10][15] = {"alberto", "Jose Bezerra", "Eugene", "caio cesar", "Nero", "Dante", "Viviane", "sherlock", "anemona", "Lara Croft"};

    printf("INICIOU-SE\n");

    srand((unsigned)time(NULL)); // (Pra fazer os números aleatórios depois)

    // Prepara os parâmetros das threads
    for(int i = 0; i < NUM_THREADS; i++){
        param_threads[i].num_sec = 10;
        // Escolhe um nome aleatório para a thread da lista de nomes possíveis
        param_threads[i].nome_thread = possiveis_nomes[rand() % 10];
        //printf("\nNumero teste aleatorio: %d\n", rand() % 10);
    }
    
    // Cria as threads
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_create(&minhas_threads[i], NULL, (void *)dormir, (void *)&param_threads[i]);
    }

    // Espera as threads
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(minhas_threads[i], (void **)&codigos_termino[i]);
        printf("Thread %d de nome %s retornou %d\n", i+1, param_threads[i].nome_thread, *codigos_termino[i]);
    }

    printf("ACABOU\n");

    return 0;
}