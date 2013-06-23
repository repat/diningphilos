/**
 * \file diningphilos.c
 * \brief Problem of dining philosophers using monitor-concept with pthreads-
 * mutex and pthreads-condvars
 * \author repat, <repat@repat.de>
 *
 * \note All comments for doxygen
*/

#include "diningphilos.h"

/**
 * \brief Main function that starts threads and listens for keyboard
 * input
 * \return 0 if programm exits normally
 */
int
main(void)
{
    pthread_t philoThreadIDs[NPHILO];
    int i;
    int err;
    int res[NPHILO];

//init stuff
    for(i = 0; i < NPHILO; i++) {
        philoStates[i] = THINK;
        stickStates[i] = FREE;
        err = pthread_cond_init(&cond[i], NULL);
        assert(!err);
        sem_init(&semaphore[i], 0, 0);
    }
    pthread_mutex_init(&mutex, NULL);

// start threads
    for(i = 0; i < NPHILO; i++) {
        res[i] =
            pthread_create(&philoThreadIDs[i], NULL, philo, &tmp[i]);
        tmp[i] = i;

        if(res[i] != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

// keyboard input
    while(TRUE) {
        fgets(keyinput, KEYKOMBO, stdin);

        if(keyinput[0] == 'q' || keyinput[0] == 'Q') {

        printf("Quitting...\n");
	    
	    printf("Unblocking all philos\n");
	    for(i = 0; i < NPHILO; i++) {
	      listen[i] = 'q';
	      sem_post(&semaphore[keyinput[0]-ASCII]);
	    }
        for(i = 0; i < NPHILO; i++) {
        	printf("Thread %d joined\n", i);
			pthread_cond_signal(&cond[i]);
            pthread_join(philoThreadIDs[i], NULL);
            }
            
        printf("Destroying the rest...\n");
        for(i = 0; i < NPHILO; i++) {
			pthread_cond_destroy(&cond[i]);
            sem_destroy(&semaphore[i]);
	    }
        pthread_mutex_destroy(&mutex);
        
	    printf("Exiting...\n");
        pthread_exit(NULL);
        exit(EXIT_FAILURE);    // programm stops here
        }
        else if(keyinput[0] >= '0' && keyinput[0] < NPHILO + ASCII) {
            if(keyinput[1] == 'b') {
                printf("Blocking Philo Nr. %d\n", keyinput[0] - ASCII);
                listen[keyinput[0] - ASCII] = keyinput[1];
            }
            else if(keyinput[1] == 'u') {
                printf("Unblocking Philo Nr. %d\n", keyinput[0] - ASCII);
                listen[keyinput[0] - ASCII] = 'u';
                sem_post(&semaphore[keyinput[0] - ASCII]);
            }
            else if(keyinput[1] == 'p') {
                printf("Proceeding Philo Nr. %d\n", keyinput[0] - ASCII);
                listen[keyinput[0] - ASCII] = 'p';
            }
        }
    }

    return 0;
}       // main

/**
 * \brief The main philosopher function
 * \param pID philosoher ID from thread creation
 * \return nothing
 */
void *
philo(void *pID)
{

    int *philoID = pID;
    int running = 1;            // init

    printf("philospher %d just awoke\n", *philoID);

    while(running) {

        checkForB(*philoID);

        think(*philoID);

        checkForB(*philoID);

        get_sticks(*philoID);

        eat(*philoID);

        checkForB(*philoID);

        put_sticks(*philoID);

        if(listen[*philoID] == 'q' || listen[*philoID] == 'Q') {
            running = 0;
        }
    }
    return NULL;
}



/**
 * \brief Simulates thinking by going through an empty loop
 * \param philoID philosoher ID from thread creation
 * \return nothing
 */
void
think(int philoID)
{
    int i;

    for(i = 0; i < THINK_LOOP; i++) {
        if(listen[philoID] == 'p') {
            listen[philoID] = 'd';
            break;
        }
    }
}

/**
 * \brief Simulates eating by going through an empty loop
 * \param philoID philosoher ID from thread creation
 * \return nothing
 */
void
eat(int philoID)
{
    int i;
    for(i = 0; i < EAT_LOOP; i++) {
        if(listen[philoID] == 'p') {
            listen[philoID] = 'd';
            break;
        }
    }
}

/**
 * \brief Checks if Thread is blocked
 * \param philoID philosoher ID from thread creation
 * \return nothing
 */
void
checkForB(int philoID)
{
    if(listen[philoID] == 'b') {
        sem_wait(&semaphore[philoID]);
    }
}
