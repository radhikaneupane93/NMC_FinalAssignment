//Name :Radhika Neupane
//UNI ID: 2227097(L5C510)
//TASK 3

//including necesaary libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global Variable Declaration
pthread_mutex_t mutex_lock; // Starting mutex lock variable
int *inputData, *prime_numbers, prime_count = 0; // Global resource (variable to store prime numbers and count of them)

// Creating structure named itter for spliting the task upon each threads
struct task_division
{
    long long starting_point, ending_point; // Stores start and end point of the each threads
};

// Function to count prime numbers
void *PrimeNumbers(void *arg) // start of PrimeNumbers function
{   
    // Accessing the task division for each thread and getting start & end points
    struct task_division *p = (struct task_division *)arg;
    long long starting_point = p->starting_point;
    long long  ending_point = p-> ending_point;

    // loop through the interval defined by starting_point and ending_point
    for (long long x = starting_point; x  <=  ending_point; x++)
    {   
        // initialize check to 1, means the number may be prime
        int check = 1;
        // if the number is 0 or 1, it is not prime
        if (inputData[x] == 0 || inputData[x] == 1)
        {
        	// set check to 0, means the number is not prime
            check = 0;
        }
        // loop through numbers from 2 to inputData[x]-1
        for (int i = 2; i < inputData[x]; i++)
        {
        	// if inputData[x] is divisible by i, it is not prime
            if (inputData[x] % i == 0)
            {
            	// set check to 0, means the number is not prime
                check = 0;
                // breaking the inner loop as we have found a factor
                break;
            }
        }
        // if the number is prime
        if (check == 1)
        {   
            // lock the mutex to access shared resources
            pthread_mutex_lock(& mutex_lock);
            // add the prime number to the prime_numbers array
            prime_numbers[prime_count] = inputData[x];
            // increment the prime_count variable
            prime_count++;
            // release the mutex lock
            pthread_mutex_unlock(& mutex_lock);
        }
    }
    pthread_exit(0);
} // end of PrimeNumbers function

// allocate memory for the inputData array
void M_Alloc(int TotalData) // start of M_Alloc function
{
    // allocate memory for TotalData elements of type int
    inputData = malloc(TotalData * sizeof(int));
    
    // check if memory allocation was successful
    if (inputData == NULL)
    {
    	// if not, print error message and exit
        printf("Couldn't allocate memory. Insufficient storage.");
        exit(0);
    }

   // allocate memory for prime_numbers array
    prime_numbers = malloc(TotalData * sizeof(int));
    
    // check if memory allocation was successful
    if (prime_numbers == NULL)
    {
    	// if not, print error message and exit
        printf("Couldn't allocate memory. Insufficient storage.");
        exit(0);
    }
}


// count total number of data in the file
int PrimeDataCounter()
{
    int TotalData = 0, exceptionthrow;

    // create an array of 3 FILE pointers
    FILE *fo[3];
    // open the first file for reading
    fo[0] = fopen("PrimeData1.txt", "r");
    // open the second file for reading
    fo[1] = fopen("PrimeData2.txt", "r");
    // open the third file for reading
    fo[2] = fopen("PrimeData3.txt", "r");

    // for each file
    for (int i = 0; i < 3; i++)
    {
        // read integers from the file until end of file
        while (fscanf(fo[i], "%d", &exceptionthrow) != EOF)
        {
            // increment TotalData counter
            TotalData++;
        }
        // close the file
        fclose(fo[i]);
    }
    // return the total number of data
    return TotalData;
}


//Function to interate equally
struct task_division *Data(int TotalThreads, int TotalData)
{
    int List[TotalThreads];
    int remaining = TotalData % TotalThreads;
    for (int i = 0; i < TotalThreads; i++) // Divide iterations equally for each thread
    {
        List[i] = TotalData / TotalThreads;
    }

    for (int i = 0; i < remaining; i++) // Add the remaining iterations to the first few threads
    {
        List[i] = List[i] + 1;
    }
    int starting_pointList[TotalThreads]; // starting point for every thread
    int  ending_pointList[TotalThreads]; // ending point for every thread

    for (int i = 0; i < TotalThreads; i++) // Calculate starting and ending points for each thread
    {
        if (i == 0)
        {
            starting_pointList[i] = 0; // assigning first iteration as the starting point for first thread
        }
        else
        {
         starting_pointList[i] =  ending_pointList[i - 1] + 1; // start after the end of the previous thread
        }
         ending_pointList[i] = starting_pointList[i] + List[i] - 1; // end at the allotted iterations
    }



    // Allocate memory for `TotalThreads` number of `task_division` structures
struct task_division *structures = malloc(TotalThreads * sizeof(struct task_division));

// For each thread, store the starting and ending points in the corresponding structure
for (int i = 0; i < TotalThreads; i++)
{
    structures[i].starting_point = starting_pointList[i]; // Store starting point
    structures[i].ending_point =  ending_pointList[i]; // Store ending point
}

// Return the array of structures
return structures;
}

// FUNCTION TO READ FILES AND IMPORT DATA
void ReadFiles()
{
   int j = 0; // counter to store data in the inputData array
   FILE *fo[3]; // array of file pointers to store 3 file names
   fo[0] = fopen("PrimeData1.txt", "r"); // open the first file
   fo[1] = fopen("PrimeData2.txt", "r"); // open the second file
   fo[2] = fopen("PrimeData3.txt", "r"); // open the third file


for (int i = 0; i < 3; i++) // for each file
{
    while (fscanf(fo[i], "%d", &inputData[j]) != EOF) // scan every data and store it to data list
    {
        j++;
    }
    fclose(fo[i]); // close the current file after reading it
}


} 

// Function to write the prime numbers to a file
void write()
{
    // If there are prime numbers found
    if (prime_count > 0)
    {
        // Open a file named "OutputFiles.txt" in write mode
        FILE *p = fopen("OutputFiles.txt", "w");
        
        // Write the total count of prime numbers found to the file
        fprintf(p, "Total prime numbers: %d.\n\n", prime_count);
        
        // Loop through all the prime numbers found
        for (int i = 0; i < prime_count; i++)
        {
            // Write each prime number to the file
            fprintf(p, "%d\n", prime_numbers[i]); 
        }

        // Close the file
        fclose(p); 

        // Notify the user to check the output file
        printf("Please check the 'OutputFile.txt' file to see all the prime numbers found.");
    }
}


// Start of main function
void main()
{
    int TotalThreads, TotalData;

    // Prompt the user for the number of threads to use
    printf("Enter number of threads you want: ");
    scanf("%d", &TotalThreads);

    // Get the total number of data to be processed
    TotalData = PrimeDataCounter();

    // Allocate memory for the input data
    M_Alloc(TotalData);

    // Read data from the input file
    ReadFiles();

    // Divide the data into tasks to be assigned to each thread
    struct task_division *structures = Data(TotalThreads, TotalData);

    // Create an array of pthreads
    pthread_t thread[TotalThreads];

    // Start each thread to process its assigned task
    for (int i = 0; i < TotalThreads; i++)
    {
        pthread_create(&thread[i], NULL, PrimeNumbers, &structures[i]);
    }

    // Wait for each thread to finish
    for (int i = 0; i < TotalThreads; i++)
    {
        pthread_join(thread[i], NULL);
    }

    // Destroy the mutex lock variable after all threads have completed
    pthread_mutex_destroy(& mutex_lock); 

    // Print the total number of prime numbers found
    printf("\n%d total prime numbers found.\n", prime_count);

    // Write the prime numbers to a file
    write();

    // Free the memory allocated for the input data and prime numbers
    free(inputData);
    free(prime_numbers);
}

