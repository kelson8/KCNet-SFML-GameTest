#include "random_number_generator.h"

#include <iostream>

// Originally from my KCNet-Library project.

// For random number generator
#include <random>

RandomNumberGenerator::RandomNumberGenerator()
{

}

/**
 * Generate a list of random numbers with a minimum and maximum value in an array.
 * 
 * https://www.geeksforgeeks.org/cpp/how-to-return-a-local-array-from-a-cpp-function/
 * 
 * @param min The minimum number for the generator.
 * @param max The maximum number for the generator.
 * @param numbersToGenerate The amount of random numbers to generate with this function.
 * 
 * @return Return an array list of random numbers generated.
 */
int *RandomNumberGenerator::GenerateRandomNumberArray(int min, int max, int numbersToGenerate)
{
    // int *arr = new int[5];
    int *arr = new int[numbersToGenerate];

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    // Generate random number in the range [min, max]
    int randomValue = distrib(gen);

    // For debug logging
    // std::cout << "Random number between " << min << " and "
        //  << max << " is " << randomValue << std::endl;

    // std::cout << "Random numbers list between " << min << " and " 
            // << max << ":" << std::endl;
    //

    for(int i = 0; i < numbersToGenerate; i++)
    {
        int randomValue = distrib(gen);
        arr[i] = randomValue;
        // std::cout << randomValue << std::endl;
    }

    return arr;
}

/**
 * Print the array of random numbers as a test.
 * 
 * This works! I wasn't expecting this to work.
 * 
 * I now have this function to run to display the numbers on the menu:
 * 
 * MenuSystem::GenerateRandomNumArray(WINDOW *win, int xPos)
 * 
 */
void RandomNumberGenerator::PrintRandomNumberList()
{
    int min = 1;
    int max = 500;
    int numbersToGenerate = 5;
    int* randomNumArray = GenerateRandomNumberArray(min, max, numbersToGenerate);

    // Print the array of numbers
    for(int i = 0; i < numbersToGenerate; i++)
    {
        std::cout << randomNumArray[i] << " ";
    }

    // allocated memory must be deleted
    delete[] randomNumArray;

    // Extra check to null the pointer.
    // https://stackoverflow.com/questions/1931126/is-it-good-practice-to-null-a-pointer-after-deleting-it
    randomNumArray = NULL;
}

// https://www.geeksforgeeks.org/cpp/how-to-return-a-local-array-from-a-cpp

/**
 * Generate a random number with a minimum and maximum value.
 * 
 * 
 * @param min The minimum number for the generator.
 * @param max The maximum number for the generator.
 * @return Return the random number generated, I set this up to be just one for now.
 */
int RandomNumberGenerator::GenerateRandomNumber(int min, int max)
{
    // https://www.geeksforgeeks.org/cpp/how-to-generate-random-number-in-range-in-cpp/

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    // Generate random number in the range [min, max]
    int randomValue = distrib(gen);

    return randomValue;
}