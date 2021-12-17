//=========================================================================================================
// file_to_cpp - Converts any file into a compilable CPP data file
//=========================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//=========================================================================================================
// read_file() - Reads in the entire file and returns
//=========================================================================================================
unsigned char* read_file(const char* filename, uint32_t* p_file_size)
{
    FILE* ifile;

    // Open the input file for reading, and if we can't, complain to the user
    if (fopen_s(&ifile, filename, "rb") != 0)
    {
        fprintf(stderr, "Can't open input file %s\n", filename);
        exit(1);
    }

    // Find out how many bytes this file is
    fseek(ifile, 0, SEEK_END);
    *p_file_size = ftell(ifile);
    fseek(ifile, 0, SEEK_SET);

    // Create a buffer that size
    unsigned char* buffer = new unsigned char[*p_file_size];

    // Read in the entire file and close it
    fread(buffer, 1, *p_file_size, ifile);
    fclose(ifile);

    // Hand the pointer to the caller
    return buffer;
}
//=========================================================================================================





//=========================================================================================================
// main() - Takes a filename as an argument
//=========================================================================================================
int main(int argc, const char** argv)
{
    uint32_t length;

    // If the user didn't provide a filename, fail silently
    if (argc < 2) exit(0);

    // Fetch the name of the file we're going to process
    const char* filename = argv[1];

    // Read the file into memory
    const unsigned char* ptr = read_file(filename, &length);

    // This will count the bytes we output
    uint32_t counter = 0;

    printf("const unsigned char data[] =\n{");

    while (length--)
    {
        if ((counter++ % 16) == 0) printf("\n    ");
        printf("0x%02X", *ptr++);
        if (length) printf(", ");
    }

    printf("\n};\n");
}
//=========================================================================================================
