//Name :Radhika Neupane
//UNI ID: 2227097(L5C510)
//TASK 4



//including necesaary libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lodepng.h"

// Variables to store the processed image and original image data.
unsigned char *finalImage;
unsigned char *originalImage;
unsigned  imgWidth, imgHeight;

// Structure to store range of iteration
struct IterationRange
{
// Starting index of iteration
unsigned int startIndex;
// Ending index of iteration
unsigned int endIndex;
};

// Function to perform Gaussian blur on a portion of the image
void *Gauss_Blur(void *args)
{
    // Initialize variables for the for loop indices
    int i, j;
    // Initialize a counter variable
    int n = 0;
     // Cast the argument to the appropriate struct type
    struct IterationRange *value = (struct IterationRange *)args;
    
     // Store the starting and ending index limit
    unsigned int startIndexLimit = value->startIndex;
    unsigned int endIndexLimit = value->endIndex;
    
    
    // Calculate the value of a pixel based on the values of its surrounding pixels
    for (i = startIndexLimit; i < endIndexLimit; i += 4)
    {
        // to the left edge of the image
        if ((i % ( imgWidth * 4)) == 0)
        {

            // to top left corner of the image
            if (i == 0)
            {
                n = 4;
                for (j = 0; j < 3; j++)
                {
                    *(finalImage + i + j) = (originalImage[i + j] + originalImage[i + 4 + j] + originalImage[4 *  imgWidth + j] + originalImage[4 *  imgWidth + 4 + j]) / n;
                }
                *(finalImage + i + 3) = originalImage[i + 3];
            }

            // to bottom left corner of the image
            else if (i == ( imgWidth * 4 * (imgHeight - 1)))
            {
                n = 4;
                for (j = 0; j < 3; j++)
                {
                    *(finalImage + i + j) = (originalImage[i + j] + originalImage[i + 4 + j] + originalImage[i - (4 *  imgWidth) + j] + originalImage[i - (4 *  imgWidth) + 4 + j]) / n;
                }
                *(finalImage + i + 3) = originalImage[i + 3];
            }

            // to Pure left of the image
            else
            {
                n = 6;
                for (j = 0; j < 3; j++)
                {
                    *(finalImage + i + j) = (originalImage[i + j] + originalImage[i + 4 + j] + originalImage[(4 *  imgWidth) + i + j] + originalImage[(4 *  imgWidth) + i + 4 + j] + originalImage[i - (4 *  imgWidth) + j] + originalImage[i - (4 *  imgWidth) + 4 + j]) / n;
                }
                *(finalImage + i + 3) = originalImage[i + 3];
            }
        }

        // to right edge of the image
        else if ((i % ( imgWidth * 4)) == ( imgWidth * 4) - 4)
        {

            // to top right corner of the image
            if (i == (( imgWidth * 4) - 4))
            {
                n = 4;
                for (j = 0; j < 3; j++)
                {
                    *(finalImage + i + j) = (originalImage[i + j] + originalImage[i - 4 + j] + originalImage[(4 *  imgWidth) + i + j] + originalImage[(4 *  imgWidth) + i - 4 + j]) / n;
                }
                *(finalImage + i + 3) = originalImage[i + 3];
            }

            // to bottom right corner of the image
            else if (i == (( imgWidth * imgHeight * 4) - 4))
            {
                n = 4;
                for (j = 0; j < 3; j++)
                {
                    *(finalImage + i + j) = (originalImage[i + j] + originalImage[i - 4 + j] + originalImage[i - (4 *  imgWidth) + j] +originalImage[i - (4 *  imgWidth) - 4 + j]) / n;
                }
                *(finalImage + i + 3) = originalImage[i + 3];
            }

            // to Pure right of the image
            else
            {
                n = 6;
                for (j = 0; j < 3; j++)
                {
                    *(finalImage + i + j) = (originalImage[i + j] + originalImage[i - 4 + j] + originalImage[(4 *  imgWidth) + i + j] + originalImage[(4 *  imgWidth) + i - 4 + j] + originalImage[i - (4 *  imgWidth) + j] + originalImage[i - (4 *  imgWidth) - 4] + j) / n;
                }
                *(finalImage + i + 3) = originalImage[i + 3];
            }
        }

        // to top of the image
        else if (i > 0 && i < (( imgWidth * 4) - 4))
        {
            n = 6;
            for (j = 0; j < 3; j++)
            {
                *(finalImage + i + j) = (originalImage[i + j] + originalImage[i - 4 + j] + originalImage[i + 4 + j] + originalImage[(4 *  imgWidth) + i + j] + originalImage[(4 *  imgWidth) + i + 4 + j] + originalImage[(4 *  imgWidth) + i - 4 + j]) / n;
            }
            *(finalImage + i + 3) = originalImage[i + 3];
        }

        // to bottom of the image
        else if (i > ( imgWidth * 4 * (imgHeight - 1)) && i < (( imgWidth * imgHeight * 4) - 4))
        {
            n = 6;
            for (j = 0; j < 3; j++)
            {
                *(finalImage + i + j) = (originalImage[i + j] + originalImage[i - 4 + j] + originalImage[i + 4 + j] + originalImage[i - (4 *  imgWidth) + j] + originalImage[i - (4 *  imgWidth) + 4 + j] + originalImage[i - (4 *  imgWidth) - 4 + j]) / n;
            }
            *(finalImage + i + 3) = originalImage[i + 3];
        }

        // to middle of the image
        else
        {
            n = 9;
            for (j = 0; j < 3; j++)
            {
                *(finalImage + i + j) = (originalImage[i + j] + originalImage[i + 4 + j] + originalImage[i - 4 + j] + originalImage[(4 *  imgWidth) + i + j] + originalImage[(4 *  imgWidth) + i + 4 + j] + originalImage[(4 *  imgWidth) + i - 4 + j] + originalImage[i - (4 *  imgWidth) + j] + originalImage[i - (4 *  imgWidth) + 4 + j] + originalImage[i - (4 *  imgWidth) - 4 + j]) / n;
            }
            *(finalImage + i + 3) = originalImage[i + 3];
        }
    }
}

// Start of main Function
void main()
{
    int i, j;
    unsigned blunder;
    // Allocate memory for the filename string
    char filename[200];
    char finalImageFile[200];
    
    // Prompt the user to input the file name and read the user input and store it in the filename string
    printf("Enter the file name you want to blur (Must Be In PNG Form): ");
    scanf("%s", filename);

    blunder = lodepng_decode32_file(&originalImage, & imgWidth, &imgHeight, filename);
    // Checking for errors in decoding the PNG file
    if (blunder)
    {
        printf("Error decoding image %u : %s\n", blunder, lodepng_error_text(blunder));
    }
    else
    {
        printf("Height of image is: %d pixels and width of image is: %d pixels.\n\n", imgHeight,  imgWidth);
    }

    printf("Enter the file name for export (With .png): ");
    scanf("%s", filename);

    finalImage= (char *)malloc( imgWidth * imgHeight * 4 * sizeof(char));

    // Calculate the number of iterations needed based on the image size
    long iterations =  imgWidth * imgHeight * 4;
    
    // Get the number of threads from the user
    int threads;
    printf("Enter the number of threads: ");
    scanf("%d", &threads);

    // Create an array to store the number of iterations each thread will perform
    int sliceList[threads];
    int remainder = iterations % threads;

    // Divide the total number of iterations equally among the threads
    for (i = 0; i < threads; i++)
    {
        sliceList[i] = iterations / threads;
    }

    for (j = 0; j < remainder; j++)
    {
        sliceList[j] += 1;
    }
    
    int  startIndexList[threads];
    int  endIndexList[threads];

    // Loop through the number of threads
    int l;
    for (l = 0; l < threads; l++)
    {
    // For the first thread
    if (l == 0)
        // The start index is 0
        startIndexList[l] = 0;
    else
        // For all other threads, the start index is the end index of the previous thread plus 1
        startIndexList[l] = endIndexList[l - 1] + 1;

    // The end index for each thread is the sum of the start index and slice size minus 1
    endIndexList[l] = startIndexList[l] + sliceList[l] - 1;
}

    // Initializing an array of IterationRange structs to store the start and end indices for each thread 
    struct IterationRange arr1[threads];

    int k;
    for (k = 0; k < threads; k++)
    {
        arr1[k].startIndex = startIndexList[k];
        arr1[k].endIndex = endIndexList[k];
    }
    
    // Create an array of pthread_t variables to store the thread IDs created by pthread_create()
    pthread_t threadId[threads];

   // Creating threads with Gauss_Blur function and passing array of IterationRange structure as argument
    int m;
    for (m = 0; m < threads; m++)
    {
        pthread_create(&threadId[m], NULL, Gauss_Blur, &arr1[m]);
    }
    // Waiting for threads to join back and completing the execution
    int n;
    for (n = 0; n < threads; n++)
    {
        pthread_join(threadId[n], NULL);
    }

     // Allocating memory to store the encoded image
    unsigned char *png;
    size_t pngsize;

    // Encoding the finalImage data into PNG format using lodepng_encode32() function
    blunder = lodepng_encode32(&png, &pngsize, finalImage , imgWidth, imgHeight);

    // Checking for any errors in encoding
    if (!blunder)
   {
    // Saving the encoded image data to a file
    lodepng_save_file(png, pngsize, filename);
    printf("Encoding successful!\nThe image is saved in the same directory.");
    }

    // Freeing the memory allocated by the finalImage array
    free(finalImage);

}

/**In Command Prompt
D:\Assigment>gcc Assignment4.c -pthread lodepng.c
D:\Assigment>a
Enter the file name you want to blur (Must Be In PNG Form): demo.png
Height of image is: 2000 pixels and width of image is: 2000 pixels.
Enter the file name for export (With .png): demo.png
Enter the number of threads: 2
Encoding successful!
The image is saved in the same directory.**/
