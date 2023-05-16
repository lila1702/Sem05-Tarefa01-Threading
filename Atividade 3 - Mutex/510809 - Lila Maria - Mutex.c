/*
Aluna: Lila Maria Salvador Frazão
Matrícula: 510809

Atividade 3 - Mutex
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 8

pthread_t minhas_threads[NUM_THREADS];

pthread_mutex_t mutex_saldo = PTHREAD_MUTEX_INITIALIZER;

double saldo = 0; // O saldo inicia zerado

void saque(){
    double saldo_velho;
	double saldo_novo;

    sleep(1);

    for(int num_saques = 0; num_saques < 10; num_saques++) {
		pthread_mutex_lock(&mutex_saldo);	
		saldo_velho = saldo;
		if(saldo < 20){
            saldo_novo = 0;
        }
        else{
            saldo_novo = saldo_velho - 20;
        }
		printf("Saldo passou de %0.2lf para o valor de %0.2lf\n", saldo_velho, saldo_novo);
		saldo = saldo_novo;
		pthread_mutex_unlock(&mutex_saldo);	
	}
}

void deposito(){
    double saldo_velho;
	double saldo_novo;

    sleep(1);

    for(int num_depositos = 0; num_depositos < 10; num_depositos++) {
		pthread_mutex_lock(&mutex_saldo);
		saldo_velho = saldo;
		saldo_novo = saldo_velho + 20;
		printf("Saldo passou de %0.2lf para o valor de %0.2lf\n", saldo_velho, saldo_novo);
		saldo = saldo_novo;
		pthread_mutex_unlock(&mutex_saldo);	
	}
}

int main(){
    
    printf("INICIOU-SE\n");

    printf("Saldo Inicial %0.2lf\n", saldo);

    // Cria todas as threads
	for(int i = 0; i < NUM_THREADS; i++){
		if(i < 4){
            pthread_create(&minhas_threads[i], NULL, (void *)deposito, NULL);
        }
        else{
            pthread_create(&minhas_threads[i], NULL, (void *)saque, NULL);
        }
    }

	// Espera por todas as threads
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(minhas_threads[i], NULL);
    }

    printf("Saldo final ficou %0.2lf\n", saldo);

    printf("ACABOU\n");
    
    return 0;
}