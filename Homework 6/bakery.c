// bakery.c is a program which simulates a bakery in action
// It was written by Matthew Nykamp for Calvin College CS 232
//
// 3-27-18

#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

// Declare constants and global variables
int MAX_CUSTOMERS = 5;
int customers = 0;
int CUSTOMERS_TOTAL = 10;
int loaves = 0;
int customer_ids = 0;

// Declare our semaphores
sem_t baker_semaphore;
sem_t entering_semaphore;
sem_t transaction_semaphore;
sem_t loaf_semaphore;
sem_t payment_semaphore;
sem_t receipt_semaphore;

// This site was helpful in understanding how pthreads work
// https://www.cs.nmsu.edu/~jcook/Tools/pthreads/library.html


// cashier_work is the job that the cashier (baker) does
void* cashier_work() {
	// Continue checking until all customers leave
	while (customers > 0 || customer_ids == 0)
	{
		// Wait until a customer grabs a loaf
		sem_wait(&loaf_semaphore);
		fprintf(stderr, "Cashier: Has noticed that a customer has grabbed a loaf.\n");
		
		// Restrict baker to one task
		sem_wait(&baker_semaphore);

		// Wait for payment
		sem_wait(&payment_semaphore);
		fprintf(stderr, "Cashier: Payment received.\n");

		// Process payment
		usleep(1000000);

		// Give back receipt
		fprintf(stderr, "Cashier: Handing back receipt\n");
		sem_post(&receipt_semaphore);
		usleep(1000000);

		// Allow the baker to switch tasks
		sem_post(&baker_semaphore);
	}
}

// baker_work is the job that the baker thread does
void* baker_work() {
	// Bake 10 loaves in total
	for(int i = 0; i < 10; i++)
	{
		// Restrict baker to one task
		sem_wait(&baker_semaphore);

		// Loaf has completed
		fprintf(stderr, "Bread Baking: Loaf completed!\n");
		loaves++;

		// Signal
		sem_post(&baker_semaphore);
		// Wait before baking another bread
		usleep(1000000);
	}

	fprintf(stderr, "Bread Baking: All loaves completed!\n");
}


// customer_work is the job that the customer does
void* customer_work() {
	int customer_num = 0;
	while (customer_num == 0) {
		// Mutex so multiple threads don't enter the if statement
		sem_wait(&entering_semaphore);

		// Ensure that only five customers enter at a time
		if (customers < MAX_CUSTOMERS)
		{
			customers++;
			customer_ids++;
			customer_num = customer_ids;

			fprintf(stderr, "Customer #%d has entered the store.\n", customer_num);
		}

		// Signal
		sem_post(&entering_semaphore);
	}

	// Only one customer should be doing a transaction at a time
	sem_wait(&transaction_semaphore);

	// Wait until there are loaves to buy
	while (loaves < 1) {
		;
	}

	// Take the loaf
	loaves--;
	fprintf(stderr, "Customer #%d has obtained a loaf of bread; %d loaves remaining\n", customer_num, loaves);
	sem_post(&loaf_semaphore);
	usleep(1000000);

	// Pay
	sem_post(&payment_semaphore);
	fprintf(stderr, "Customer #%d has paid, waiting for receipt...\n", customer_num);

	// Wait for the receipt to be given
	sem_wait(&receipt_semaphore);

	fprintf(stderr, "Customer #%d has received a receipt.\n", customer_num);

	// Allow a different transaction to take place
	sem_post(&transaction_semaphore);

	// Leave
	fprintf(stderr, "Customer #%d has left the store.\n", customer_num);
	customers--;

}

int main() {
	fprintf(stderr, "Welcome to the bakery!\n");

	// Initialize the semaphores
	sem_init(&baker_semaphore, 1, 1);
	sem_init(&entering_semaphore, 1, 1);
	sem_init(&transaction_semaphore, 1, 1);
	sem_init(&payment_semaphore, 1, 0);
	sem_init(&receipt_semaphore, 1, 0);
	sem_init(&loaf_semaphore, 1, 0);

	// Create the baker threads, 0 is the baker, 1 is the cashier
	pthread_t baker_thread[2];
	pthread_create(&baker_thread[0], NULL, cashier_work, NULL);
	pthread_create(&baker_thread[1], NULL, baker_work, NULL);

	// Create the ten customer threads
	pthread_t customer_thread[CUSTOMERS_TOTAL];
	for (int i = 0; i < CUSTOMERS_TOTAL; i++) {
		pthread_create(&customer_thread[i], NULL, customer_work, NULL);
	}

	// Close the semaphores
	sem_close(&baker_semaphore);
	sem_close(&entering_semaphore);
	sem_close(&transaction_semaphore);
	sem_close(&payment_semaphore);
	sem_close(&receipt_semaphore);
	sem_close(&loaf_semaphore);

	pthread_exit(NULL);
}

