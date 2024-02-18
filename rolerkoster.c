#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BROJ_PUTNIKA 10
#define BROJ_SEDISTA 4

int putniciKojiSeUkrcavaju, putniciKojiSeIskrcavaju;
sem_t mutex1, mutex2;
sem_t redZaUkrcavanje, redZaIskrcavanje;
sem_t punRolerkoster, prazanRolerkoster;

int brojGotovihPutnika = 0;

void *putnik (void) {

    sem_wait(&redZaUkrcavanje);

    printf("Putnik se ukrcava\n");

    sem_wait(&mutex1);

    putniciKojiSeUkrcavaju++;

    if (putniciKojiSeUkrcavaju == BROJ_SEDISTA 
        || putniciKojiSeUkrcavaju+brojGotovihPutnika == BROJ_PUTNIKA) {
        sem_post(&punRolerkoster);
        putniciKojiSeUkrcavaju = 0;
    }

    sem_post(&mutex1);

    sem_wait(&redZaIskrcavanje);

    printf("Putnik se iskrcava\n");

    sem_wait(&mutex2);
    putniciKojiSeIskrcavaju++;

    if (putniciKojiSeIskrcavaju == BROJ_SEDISTA || brojGotovihPutnika == BROJ_PUTNIKA-1 
        || brojGotovihPutnika+putniciKojiSeIskrcavaju == BROJ_PUTNIKA) {
        sem_post(&prazanRolerkoster);
        putniciKojiSeIskrcavaju = 0;
    }

    sem_post(&mutex2);
    brojGotovihPutnika++;

    pthread_exit(NULL);

}

void *rolerkoster (void) {

    while(brojGotovihPutnika<BROJ_PUTNIKA) {

        printf ("Putnici se ukrcavaju!\n");

        for (int i = 0; i < BROJ_SEDISTA; i++)
            sem_post(&redZaUkrcavanje);

        sem_wait(&punRolerkoster);
        sleep(2);
        printf("Rolerkoster je pun!\n");

        printf("\nRolerkoster se krece po svojoj putanji\n");
        sleep(4);
        printf("Rolerkoster je zavrsio svoju voznju\n");

        printf("\nPutnici se iskrcavaju\n");
        sleep(3);

        for(int i = 0; i < BROJ_SEDISTA; i++)
            sem_post(&redZaIskrcavanje);

        sem_wait(&prazanRolerkoster);

    }

    printf ("\nVoznja je gotova za danas!\n");
    pthread_exit(NULL);

}

int main (void) {

    pthread_t putnici[BROJ_PUTNIKA];
    pthread_t roler_koster;

    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&redZaUkrcavanje, 0, 0);
    sem_init(&redZaIskrcavanje, 0, 0);
    sem_init(&punRolerkoster, 0, 0);
    sem_init(&prazanRolerkoster, 0, 0);

    pthread_create(&roler_koster, NULL, rolerkoster, NULL);

    for (int i = 0; i < BROJ_PUTNIKA; i++) 
        pthread_create(&putnici[i], NULL, putnik, NULL);

    pthread_join(roler_koster, NULL);

    return 0;

}