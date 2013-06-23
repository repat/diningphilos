/**
 * \file diningphilos.h
 * \brief all the includes, constants, macros, variables and declarations
 * \author repat, repat@repat.de
 * 
 * \note All comments for doxygen
 */
//all the includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

//!Number of philosophers
#define NPHILO 5
//!Helps to cope with ASCII
#define ASCII 48
//!Used for the think-loop in think() as a really large number
#define THINK_LOOP 100000000
//!Used for the eat-loop in eat() as a really large number
#define EAT_LOOP 500000000
//!For Keyboard-Input
#define KEYKOMBO 3

//!this is how the stick IDs match the philosophers on the right side
#define RIGHT(philoID) ((philoID+1)%NPHILO)
//!this is how the stick IDs match the philosophers on the left side
#define LEFT(philoID) philoID

//!this is how neighbours are defined at a round table - right side
#define RIGHTNEIGHB(philoID) ((philoID == NPHILO-1)? 0 : philoID+1)
//!this is how neighbours are defined at a round table - left side
#define LEFTNEIGHB(philoID) ((philoID == 0)? NPHILO-1 : philoID-1)

//!boolean variables true and false
typedef enum {
    FALSE = 0,
    TRUE = 1
} Bool;

//!definition of the states of the philosophers
typedef enum {
    THINK = 0,
    HUNGRY = 1,
    EAT = 2
} State;

//!definition of the states of the sticks
typedef enum {
    FREE = 0,
    IN_USE = 1
} Sticks;

//!states of the N philosophers
State philoStates[NPHILO];
//!states of the N sticks
Sticks stickStates[NPHILO];

//!mutual exclusion with pthreads
pthread_mutex_t mutex;
//!condition variables with pthreads - one for every philosopher
pthread_cond_t cond[NPHILO];
//!semaphors with pthreads - one for every philosopher
sem_t semaphore[NPHILO];
//!philoIDs
int tmp[NPHILO];               

//!For keyboard input
char keyinput[KEYKOMBO];
//!For transmitting b, u or p to the philosophers
char listen[NPHILO];

// declaration to get an overview
void *philo(void *arg);
void think(int philoID);
void eat(int philoID);
void get_sticks(int philoID);
void put_sticks(int philoID);
void disp_philo_states();
char convertStates(State philoState);
void checkForB(int philoID);
