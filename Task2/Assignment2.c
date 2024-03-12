//Name :Radhika Neupane
//UNI ID: 2227097(L5C510)
//TASK 2


//including library for input and output operations
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Declaring global variable mutex lock to access in all threads 
pthread_mutex_t mutex_lock;
double total = 0;

// Creading a structure  to split the task into equal parts for each thread
struct  iteration_range
{
    long long starting_point, ending_point;  // start and end point of every iteration in each thread
};


// Creating a function to calculate the exponential value
double Exponential(long long x)
{
    if (x == 0)
    {
        return 1;
    }
    // Recursive calculation of exponential
    return -1 * Exponential(x - 1);
}


// Creating a Function to calculate total of each iteration
void *sum(void *arg)
{ 
// function to be performed by threads
    struct iteration_range *p = (struct  iteration_range *)arg;  // Casting the void pointer to a pointer to the iteration_range structure
    
     // solving the starting and ending points for the range of iterations assigned to this thread
    long long starting_point = p->starting_point;
    long long ending_point = p->ending_point;
    
    // Looping through the assigned range of iterations
    for (long long n = starting_point; n <= ending_point; n++)

    {
    	// Locking the mutex variable to avoid race condition
        pthread_mutex_lock(&mutex_lock);
        
        // Adding the value of each iteration to the total
        total += (Exponential(n)) / ((2 * n) + 1);
        
        // Unlocking the mutex variable after adding the value
        pthread_mutex_unlock(&mutex_lock);
    }
    // Exit the thread
    pthread_exit(0);
}
// End of sum function

// Function to divide the task in to equal half for each thread
struct  iteration_range *DivideTask(int numThreads, long long numIterations)

{
	int iterationCounts[numThreads];  // iterationCounts = number of iterations assigned to each thread
   
    int remainingIterations  = numIterations % numThreads;  // remainingIterations = number of iterations not evenly divided among threads

    for (int i = 0; i < numThreads ; i++)
    {
        iterationCounts[i] = numIterations / numThreads; // Divide the iterations equally among the threads
    }

    for (int i = 0; i < remainingIterations ; i++)
    {
        iterationCounts[i] = iterationCounts[i] + 1; // Add an extra iteration to the first 'remainingIterations' threads
    }

    int starting_pointList[numThreads]; // starting_pointList = starting point for each thread's iteration range
    int ending_pointList[numThreads]; // ending_pointList = ending point for each thread's iteration range

    for (int i = 0; i <numThreads ; i++)
    {
        if (i == 0) // // For the first iteration range
        {
            starting_pointList[i] = 0; // The first iteration range starts at 0
        }
        else // For all other iteration ranges
        {
            starting_pointList[i] = ending_pointList[i - 1] + 1; // Start the current iteration range after the end of the previous one
        }
        ending_pointList[i] = starting_pointList[i] + iterationCounts[i] - 1;  // End the current iteration range after 'iterationCounts[i]' iterations
    }

    // Allocate memory for each thread to store its starting and ending iteration range
    struct  iteration_range *structure = malloc(numThreads * sizeof(struct  iteration_range));

    // Assign the starting and ending iteration range for each thread
    for (int i = 0; i < numThreads; i++)
    {
        structure[i].starting_point = starting_pointList[i];
        structure[i].ending_point = ending_pointList[i];
    }
   // Return the iteration range for each thread
    return structure;
}

// Main function starting point
void main()
{
    long long numIterations; // Number of iterations to be performed
    int numThreads;  // Number of threads to be used

    // Ask the user for the number of iterations to be performed
    printf("Enter number of Iterations you want to perform: ");
    scanf("%lld", &numIterations);

    // Ask the user for the number of threads to be used
    printf("Enter number of threads you want to perform: ");
    scanf("%d", &numThreads);

    // Call the DivideTask function to divide the task into equal parts for each thread
    struct  iteration_range *structure = DivideTask(numThreads, numIterations); // importing the value assigned structures to the new structure
    
    // Create an array of threads
    pthread_t thread[numThreads];

    // Loop to create the threads and assign each thread a portion of the task
        
    for (int i = 0; i < numThreads; i++)
    {
    pthread_create(&thread[i], NULL, sum, &structure[i]);
    }

    // Loop to wait for all the threads to finish their execution
    for (int i = 0; i < numThreads; i++)
    {
    pthread_join(thread[i], NULL);
    }

    // Destroying the mutex lock after all the threads have finished their execution
    pthread_mutex_destroy(&mutex_lock);

    // Printing the final calculated value of PI
    printf("\nThe Value of Pi according to Leibniz formula is %lf.", 4 * total);

    return 0;
}








