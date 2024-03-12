//Name :Radhika Neupane
//UNI ID: 2227097(L5CG10)
//TASK 1

//including library for input and output operations
#include <stdio.h>
void main()
{
    int n = 0;
    double y_intercept, slope, input_x, predict_y, x[600], y[600], sumOfX = 0, sumOfY = 0, sumOfX2 = 0, sumOfY2 = 0, sumOfXY = 0;


    //creating 4 pointer array to read the four file which are given 
    FILE *fof[4];
    
   //opening and reading the files
    fof[0] = fopen("datasetLR1.txt", "r");  //for first file
    fof[1] = fopen("datasetLR2.txt", "r");  //for second file 
    fof[2] = fopen("datasetLR3.txt", "r");  //for third file 
    fof[3] = fopen("datasetLR4.txt", "r");  //for fourth file 

    //Reading the file after opening them in read mode 
    for (int i = 0; i < 4; i++)
    {
        while (fscanf(fof[i], "%lf,%lf", &x[n], &y[n]) != EOF) // Scanning till end of the file
        {
            n++;
        }

        // Closing the file when it reach to the end
        fclose(fof[i]);
    }

    //Using for loop to store the values of x and y in the arrays to calculate the slope and intercept of the best-fit line for the data
    for (int i = 0; i < n; i++)
    {
        sumOfX += x[i];
        sumOfY += y[i];
        sumOfX2 += x[i] * x[i];
        sumOfY2 += y[i] * y[i];
        sumOfXY += x[i] * y[i];
    }

    /*calculating the slope and y-intercept of the line for the given dataset 
	and printing the best fit line on the basis of result*/
    y_intercept= ((sumOfY * sumOfX2) - (sumOfX * sumOfXY)) / ((n * sumOfX2) - (sumOfX * sumOfX)); 
    slope = ((n * sumOfXY) - (sumOfX * sumOfY)) / ((n * sumOfX2) - (sumOfX * sumOfX));     
    printf("The best-fit line equation is y = %lf * x + %lf. \n", slope, y_intercept);

    //Asking users for a input 
    printf("Enter value of x: ");
    scanf("%lf", &input_x);

    // Predicting the y according to the user input i.e. x
    predict_y = slope * input_x + y_intercept;

    //Printing the final predicted value 
    printf("\nThe Predicted value of y for %lf is %lf.", input_x, predict_y);
    
}
