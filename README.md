# Diluted Machine Learning - From The DML Project.

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

The DML project is an effort to fit ML algorithms in devices with scarce hardware resources, typically like a device with 32 kB EEPROM and 1.6 kB RAM. The project also includes effort to try and find ways to have supervised ML algorithms run on these devices, that would require large datasets, which could not possibly fit in such a small device memory. This particular library, which is still being developed and is a shared library among multiple branches of the DML project, includes some all-purpose functions that are very common in the field of ML.


## Features

- Head/tail functions.
- Create a random stream of data from the elements of a dataset.
- Allocate a memory block for an initially empty vector.
- Mean/median/standard dev. calculations.
- Comparison of two vectors for sorting purposes.
- Scale vectors to unity.
- Scale vectors to a range of choice.

## Installation and Usage

To use DML in your project, follow these steps:

1. Clone this repository to your local machine:

     https://github.com/CodeWikiOrg/dml

2. Include the 'dml.h' header file in your C source files.

3. Build your project with 'dml.c' as part of your source files.
 
## Contributing
Contributions are welcome! If you encounter a bug or have ideas for improvements, please open an issue or submit a pull request.

## License
DML is released under the MIT License. See the LICENSE file for full licensing details.
