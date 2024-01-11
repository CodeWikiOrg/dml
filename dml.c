/**
 * Author(s):           Arda T. Kersu
 * File name:           dml.c
 * Date:                30th November 2023
 *
 * Description: Source code for the library "dml.h" that provides a set of functions to be used
 *              when working with diluted ML algorithms. This library is dependent on "open_csv.h",
 *              that is another open source library which allows for easier manipulation and usage
 *              of ".csv" files, and will not work without it. See inline comments for further details
 *              regarding any specific function of interest.
 *
 * Disclaimer: This open-source project is provided "as is" without any warranty, expressed or implied.
 *             The contributors and maintainers disclaim any an all unintended consequences or issues
 *             that may arise from its use. Users are encouraged to review and understand the software's
 *             characteristics before implementation.
 *
 *
 * Copyright @ [Arda T. Kersu]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dml.h"


/**
 * @brief Display the top rows of a '.csv' file.
 *
 * This function displays the top rows of the provided tabular data structure in 'df'.
 *
 * @param df        A pointer to the '.csv' file data structure.
 * @param lines     The number of rows to display from the top of the data.
 *
 * @note            The 'df' itself is not the tabular structure, it is 'df->dataFrame'.
                    'df' is a more complex structure that stores the number of rows
                    and columns, as well as the size of the data frame 'df->dataFrame'.

 *
 * @code
 *   // Example usage:
 *   csvData_t data = loadCsv(FILE); // Assuming the file has been loaded successfully.
 *   head(&data, 5); // Display the top 5 rows of 'data'.
 * @endcode
 */
void head(csvData_t *df, int lines)
{
    printf("*** ================ TOP %d ROWS ================ ***\n", lines);
    for(int row=0; row<lines; row++)
    {
        for(int col=0; col<df->cols; col++)
        {
            printf("%10.3f\t", df->dataFrame[row][col]);
        }
        puts(" ");
    }
    printf("*** ============================================= ***\n");
}

/**
 * @brief Display the bottom rows of a '.csv' file.
 *
 * This function displays the bottom rows of the provided tabular data structure 'df'.
 *
 * @param df        A pointer to the '.csv' file data structure.
 * @param lines     The number of rows to display from the top of the data.
 *
 * @note            The 'df' itself is not the tabular structure, it is 'df->dataFrame'.
                    'df' is a more complex structure that stores the number of rows
                    and columns, as well as the size of the data frame 'df->dataFrame'.
 *
 * @code
 *   // Example usage:
 *   csvData_t data = loadCsv(FILE); // Assuming the file has been loaded successfully.
 *   tail(&data, 5); // Display the bottom 5 rows of 'data'.
 * @endcode
 */
void tail(csvData_t *df, int lines)
{
    printf("*** ================ BOTTOM %d ROWS ================ ***\n", lines);
    for(int row=df->rows-1; row>df->rows-lines-1; row--)
    {
        for(int col=0; col<df->cols; col++)
        {
            printf("%10.2f ", df->dataFrame[row][col]);
        }
        puts(" ");
    }
    printf("*** ========================================== ***\n");
}

/**
 * @brief Generate a random data stream from a '.csv' file.
 *
 * This function generates a random data stream by sampling 'numOfData' values
 * from the provided '.csv' file. The sampled values are stored in a dynamically
 * allocated float array.
 *
 * @param df        A pointer to the '.csv' file data structure.
 * @param numOfData The number of data points to sample.
 *
 * @return A pointer to a dynamically allocated float array containing the
 *         sampled data points. The caller is responsible for freeing the memory
 *         allocated for the array when it is no longer needed.
 *
 * @note The '.csv' file should contain numerical data accessible via 'dataFrame'.
 *       The function uses the 'rand' function to select random indices within the
 *       dimensions of the data structure to sample values.
 *
 * @warning The caller is responsible for freeing the memory allocated for the
 *          returned array using the 'free' function to prevent memory leaks.
 *
 * @code
 *   // Example usage:
 *   csvData_t data = loadCsv(FILE); // Assuming the file has been loaded successfully.
 *   int numOfDataPoints = 10;
 *   float *dataStream = randomDataStream(&data, numOfDataPoints);
 *   // Use the dataStream...
 *   free(dataStream); // Free the allocated memory when done.
 * @endcode
 */
float *randomDataStream(csvData_t *df, int numOfData)
{
    float *stream = (float *)malloc(sizeof(float) * numOfData);

    srand(time(NULL));

    for(int num=0; num<numOfData; num++)
    {
        int xIndex = rand() % df->rows;
        int yIndex = rand() % df->cols;

        *(stream + num) = df->dataFrame[xIndex][yIndex];
    }

    return stream;
}

/**
 * @brief Create a dynamically allocated float vector.
 *
 * This function allocates memory for a float vector of the specified length 'len'
 * and returns a pointer to the allocated memory. The caller is responsible for
 * freeing the memory when it is no longer needed.
 *
 * @param len The length of the float vector to create.
 *
 * @return A pointer to the dynamically allocated float vector.
 *
 * @warning The caller must free the memory allocated for the vector using the 'free' function
 *          to prevent memory leaks when it is no longer needed.
 *
 * @code
 *   // Example usage:
 *   int vectorLength = 10;
 *   float *dataVector = createFloatVector(vectorLength);
 *   // Use the 'dataVector'...
 *   free(dataVector); // Free the allocated memory when done.
 * @endcode
 */
float *createFloatVector(int len)
{
    float *vector = (float *)malloc(sizeof(float) * len);

    return vector;
}

/**
 * @brief Calculate the mean of a specific column in a '.csv' file.
 *
 * This function calculates the mean of the values in the specified
 * column of the provided '.csv' file data structure 'df->dataFrame'.
 *
 * @param df  A pointer to the '.csv' file data structure.
 * @param col The column index for which to calculate the mean.
 *
 * @return The mean value of the specified column.
 *
 * @note The '.csv' file should contain numerical data accessible via 'dataFrame'.
 *       The function iterates through all rows of the column and computes the mean.
 *
 * @code
 *   // Example usage:
 *   csvData_t data = loadCsv(FILE); // Assuming the file has been loaded successfully.
 *   int targetColumn = 2; // The column for which to calculate the mean.
 *   float columnMean = mean(&data, targetColumn);
 *   // Use the 'columnMean'...
 * @endcode
 */
float mean(csvData_t *df, int col)
{
    float sum = 0;

    for(int row=0; row<df->rows; row++)
    {
        sum += df->dataFrame[row][col];
    }

    return (sum / (float)df->rows);
}

/**
 * @brief Compare two float values for sorting purposes.
 *
 * This function is used as a comparison function for sorting float values in ascending order.
 * It compares two float values pointed to by 'a' and 'b'.
 *
 * @param a A pointer to the first float value to compare.
 * @param b A pointer to the second float value to compare.
 *
 * @return An integer value:
 *         - Less than 0 if the value pointed to by 'a' is less than the value pointed to by 'b'.
 *         - 0 if the values are equal.
 *         - Greater than 0 if the value pointed to by 'a' is greater than the value pointed to by 'b'.
 *
 * @note This function is designed to be used with sorting functions like 'qsort'.
 *       It allows sorting an array of float values in ascending order.
 *
 * @code
 *   // Example usage with qsort:
 *   float values[] = {3.5, 1.2, 2.8, 0.9};
 *   int numValues = sizeof(values) / sizeof(values[0]);
 *   qsort(values, numValues, sizeof(float), compareVectors);
 *   // 'values' will be sorted in ascending order.
 * @endcode
 */
int compareVectors(const void *a, const void *b)
{
    return (*(float *)a > *(float *)b) - (*(float *)a < *(float *)b);
}

/**
 * @brief Calculate the median of a specific column in a '.csv' file.
 *
 * This function calculates the median of the values in the specified column
 * of the provided '.csv' file data structure 'df->dataFrame'.
 *
 * @param df  A pointer to the '.csv' file data structure.
 * @param col The column index for which to calculate the median.
 *
 * @return The median value of the specified column.
 *
 * @note The '.csv' file should contain numerical data accessible via 'dataFrame'.
 *       The function creates a sorted copy of the column's values, calculates the
 *       median, and returns it.
 *
 * @code
 *   // Example usage:
 *   csvData_t data = loadCsv(FILE); // Assuming the file has been loaded successfully.
 *   int targetColumn = 2; // The column for which to calculate the median.
 *   float columnMedian = median(&data, targetColumn);
 *   // Use the 'columnMedian'...
 * @endcode
 */
float median(csvData_t *df, int col)
{
    float medianVal = 0;
    float *sortedFeature = createFloatVector(df->rows);

    for(int index=0; index<df->rows; index++)
        *(sortedFeature + index) = df->dataFrame[index][col];

    qsort(sortedFeature, df->rows, sizeof(float), compareVectors);

    medianVal = (df->rows % 2 == 1) ?
                (df->dataFrame[(df->rows-1)/2][col])
                                    :
                ((df->dataFrame[df->rows/2][col] + df->dataFrame[df->rows/2 - 1][col]) / 2);

    free(sortedFeature);

    return medianVal;
}

/**
 * @brief Calculate the standard deviation of a specific column in a '.csv' file.
 *
 * This function calculates the standard deviation of the values in the specified
 * column of the provided '.csv' file data structure 'df'.
 *
 * @param df  A pointer to the '.csv' file data structure.
 * @param col The column index for which to calculate the standard deviation.
 *
 * @return The standard deviation of the specified column.
 *
 * @note The '.csv' file should contain numerical data accessible via 'dataFrame'.
 *       The function first calculates the mean of the column, then computes the
 *       variance by summing the squared differences between each value and the mean,
 *       and finally returns the square root of the variance as the standard deviation.
 *
 * @code
 *   // Example usage:
 *   csvData_t data = loadCsv(FILE); // Assuming the file has been loaded successfully.
 *   int targetColumn = 2; // The column for which to calculate the standard deviation.
 *   float columnStdDev = standardDeviation(&data, targetColumn);
 *   // Use the 'columnStdDev'...
 * @endcode
 */
float standardDeviation(csvData_t *df, int col)
{
    float sum = 0;
    float meanVal = mean(df, col);

    for(int row=0; row<df->rows; row++)
    {
        float distance = df->dataFrame[row][col] - meanVal;
        sum += distance * distance;
    }

    return (sum / (float)df->rows);
}

/**
 * @brief Scale a float vector to the range [0, 1] (unity) given custom bounds.
 *
 * This function scales each element of the input float vector 'vector' to the
 * range [0, 1] (unity) based on the specified 'lowerBound' and 'upperBound'.
 * The scaled values are stored in a dynamically allocated float array.
 *
 * @param vector      A pointer to the input float vector to be scaled.
 * @param vectorLen   The length of the input vector.
 * @param lowerBound  The lower bound of the desired range.
 * @param upperBound  The upper bound of the desired range.
 *
 * @return A pointer to a dynamically allocated float array containing the scaled values.
 *         The caller is responsible for freeing the memory allocated for the array
 *         when it is no longer needed.
 *
 * @warning The caller must free the memory allocated for the returned array using
 *          the 'free' function to prevent memory leaks when it is no longer needed.
 *
 * @note The function scales each element of 'vector' individually based on the provided
 *       'lowerBound' and 'upperBound' values.
 *
 * @code
 *   // Example usage:
 *   int vectorLength = 5;
 *   float originalVector[] = {1.0, 2.0, 3.0, 4.0, 5.0};
 *   float lowerBound = 1.0;
 *   float upperBound = 5.0;
 *   float *scaledVector = scaleToUnity(originalVector, vectorLength, lowerBound, upperBound);
 *   // Use the 'scaledVector'...
 *   free(scaledVector); // Free the allocated memory when done.
 * @endcode
 */
float *scaleToUnity(float *vector, int vectorLen, float lowerBound, float upperBound)
{
    float *unity = (float *)malloc(sizeof(float) * vectorLen);

    for(int loop=0; loop<vectorLen; loop++)
    {
        *(unity + loop) = *(vector + loop) / (upperBound - lowerBound);
    }

    return unity;
}

/**
 * @brief Scale a float vector from one range to another given custom bounds.
 *
 * This function scales each element of the input float vector 'vector' from the
 * range defined by 'lowerBound' and 'upperBound' to a new range defined by
 * 'newLowBound' and 'newUpBound'. The scaled values are stored in a dynamically
 * allocated float array.
 *
 * @param vector      A pointer to the input float vector to be scaled.
 * @param vectorLen   The length of the input vector.
 * @param lowerBound  The lower bound of the original range.
 * @param upperBound  The upper bound of the original range.
 * @param newLowBound The lower bound of the new range.
 * @param newUpBound  The upper bound of the new range.
 *
 * @return A pointer to a dynamically allocated float array containing the scaled values.
 *         The caller is responsible for freeing the memory allocated for the array
 *         when it is no longer needed.
 *
 * @warning The caller must free the memory allocated for the returned array using
 *          the 'free' function to prevent memory leaks when it is no longer needed.
 *
 * @note The function scales each element of 'vector' individually based on the provided
 *       bounds and computes the scaled values according to the new range.
 *
 * @code
 *   // Example usage:
 *   int vectorLength = 5;
 *   float originalVector[] = {1.0, 2.0, 3.0, 4.0, 5.0};
 *   float lowerBound = 1.0;
 *   float upperBound = 5.0;
 *   float newLowerBound = 0.0;
 *   float newUpperBound = 1.0;
 *   float *scaledVector = scaleVector(originalVector, vectorLength, lowerBound, upperBound, newLowerBound, newUpperBound);
 *   // Use the 'scaledVector'...
 *   free(scaledVector); // Free the allocated memory when done.
 * @endcode
 */
float *scaleVector(float *vector, int vectorLen, float lowerBound, float upperBound, float newLowBound, float newUpBound)
{
    float *scaledDownVector = (float *)malloc(sizeof(float) * vectorLen);

    float scale = (newUpBound - newLowBound) / (upperBound - lowerBound);
    float offset = newLowBound - (scale * lowerBound);

    for(int loop=0; loop<vectorLen; loop++)
    {
        *(scaledDownVector + loop) = *(vector + loop) * scale + offset;
    }

    return scaledDownVector;
}
