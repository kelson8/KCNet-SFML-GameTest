#pragma once

class RandomNumberGenerator
{
public:
    static RandomNumberGenerator &getInstance()
    {
        static RandomNumberGenerator instance; // Guaranteed to be destroyed.
        return instance;
    }


    // Generate a random number with a minimum and maximum value.
    static int GenerateRandomNumber(int min, int max);

    // Generate an array of random numbers.
    int *GenerateRandomNumberArray(int min, int max, int numbersToGenerate);
    
    // Test for running the GenerateRandomNumberArray function and freeing up memory for it.
    void PrintRandomNumberList();

private:
    RandomNumberGenerator();
    // ~RandomNumberGenerator(); // Optional deconstructor
    RandomNumberGenerator(const RandomNumberGenerator &) = delete;            // Prevent copy-construction
    RandomNumberGenerator &operator=(const RandomNumberGenerator &) = delete; // Prevent assignment
};
    