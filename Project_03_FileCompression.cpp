#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to compress the input string using Run-Length Encoding (RLE)
string compress(const string &input)
{
    string compressed = "";
    int n = input.length();

    for (int i = 0; i < n; i++)
    {
        // Count occurrences of the current character
        int count = 1;
        while (i < n - 1 && input[i] == input[i + 1])
        {
            count++;
            i++;
        }
        compressed += input[i] + to_string(count); // Add character and count
    }
    return compressed;
}

// Function to decompress the compressed string
string decompress(const string &compressed)
{
    string decompressed = "";
    int n = compressed.length();

    for (int i = 0; i < n; i++)
    {
        char ch = compressed[i]; // Current character
        i++;
        string countStr = "";
        // Collect all digits that represent the count
        while (i < n && isdigit(compressed[i]))
        {
            countStr += compressed[i];
            i++;
        }
        i--; // Adjust i to point back to the last digit

        int count = stoi(countStr); // Convert count to integer
        // Append the character count times
        for (int j = 0; j < count; j++)
        {
            decompressed += ch;
        }
    }
    return decompressed;
}

// Function to read a file into a string
string readFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Function to write a string to a file
void writeFile(const string &filename, const string &content)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not write to file " << filename << endl;
        exit(1);
    }
    file << content;
    file.close();
    cout << "File written successfully: " << filename << endl;
}

int main()
{
    string inputFilename = "project3.txt", compressedFilename, decompressedFilename;

    // Use a different name for the ofstream object
    ofstream newFile;
    newFile.open(inputFilename);
    newFile << "AAAABBCCCD##EEEEEEEEEEFFFGHHHIIIJJJKKKKLLMNOOPPQQQRRRRSSSSSTTTUUVWWWXXXXYYYYYZZZZZZ\n";
    newFile.close();

    // Read the content of the file
    string fileContent = readFile(inputFilename);

    // Display the original content of the file
    cout << "Original Content of the File: \n"
         << fileContent << endl;

    // Compress the file content
    string compressedContent = compress(fileContent);
    compressedFilename = inputFilename + ".compressed";

    // Write compressed content to a file
    writeFile(compressedFilename, compressedContent);

    // Display the compressed content
    cout << "\nCompressed Content: \n"
         << compressedContent << endl;

    // Decompress the file content
    string decompressedContent = decompress(compressedContent);
    decompressedFilename = inputFilename + ".decompressed";

    // Write decompressed content to another file
    writeFile(decompressedFilename, decompressedContent);

    // Display the decompressed content
    cout << "\nDecompressed Content: \n"
         << decompressedContent << endl;

    cout << "\nCompression and Decompression completed." << endl;
    return 0;
}