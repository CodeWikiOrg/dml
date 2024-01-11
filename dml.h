/**
 * Author(s):           Arda T. Kersu
 * File name:           dml.h
 * Date:                30th November 2023
 *
 * Description: Header file for the library "dml.h" that provides a set of functions to be used
 * 				when working with diluted ML algorithms. This library is dependent on "open_csv.h",
 * 				that is another open source library which allows for easier manipulation and usage
 * 				of ".csv" files, and will not work without it. Although most of the functions in this
 * 				library are just plain mathematics and nothing new, it was a challenge to find a
 * 				C library dedicated for the operations that this library is dedicated to. Hence, 
 * 				"dml.h" was developed during the time of developing diluted ML to help ease as well as
 * 				facilitate the DML development process.
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

#ifndef DML_DML_H
#define DML_DML_H

#include "../open_csv/open_csv.h"

void head(csvData_t *df, int lines);
void tail(csvData_t *df, int lines);
float *randomDataStream(csvData_t *df, int numOfData);
float *createFloatVector(int len);
float mean(csvData_t *df, int col);
int compareVectors(const void *a, const void *b);
float median(csvData_t *df, int col);
float standardDeviation(csvData_t *df, int col);
float *scaleToUnity(float *vector, int vectorLen, float lowerBound, float upperBound);
float *scaleVector(float *vector, int vectorLen, float lowerBound, float upperBound, float newLowBound, float newUpBound);


#endif //DML_DML_H
