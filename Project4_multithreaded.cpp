#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close()

// ClientHandler Class
class ClientHandler
{
public:
    int clientSocket;

    ClientHandler(int socket) : clientSocket(socket) {}

    void handleRequest()
    {
        char buffer[1024];                 // Buffer to hold incoming data
        memset(buffer, 0, sizeof(buffer)); // Clear buffer

        // Read the request data from client
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead > 0)
        {
            std::cout << "Request received:\n"
                      << buffer << std::endl;

            // We can assume the client requests a basic HTML file for simplicity
            std::string requestedFile = "index.html"; // You could parse `buffer` to find the exact file requested

            // Get the content of the HTML file
            std::string fileContent = getFileContent(requestedFile);

            // Send HTTP response back to client
            sendResponse(fileContent);
        }
        else
        {
            std::cerr << "Failed to read request.\n";
        }

        close(clientSocket); // Close the client socket after response
    }

private:
    // Function to read the HTML file content
    std::string getFileContent(const std::string &filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            return "<html><body><h1>404 Not Found</h1></body></html>"; // Basic 404 error if file doesn't exist
        }

        std::stringstream contentStream;
        contentStream << file.rdbuf(); // Read the file content into a string stream
        return contentStream.str();    // Convert stream to string and return
    }

    // Function to send the HTTP response
    void sendResponse(const std::string &html)
    {
        std::string response = "HTTP/1.1 200 OK\r\n"; // Basic HTTP headers
        response += "Content-Type: text/html\r\n";
        response += "Content-Length: " + std::to_string(html.size()) + "\r\n";
        response += "\r\n"; // Empty line between headers and body
        response += html;   // HTML content

        write(clientSocket, response.c_str(), response.size()); // Send the response back to the client
    }
};

// Server Class
class Server
{
private:
    int serverSocket;
    int port;
    std::vector<std::thread> threads; // Vector to hold threads

public:
    Server(int p) : port(p) {}

    void start()
    {
        // Set up socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP
        if (serverSocket == -1)
        {
            std::cerr << "Failed to create socket.\n";
            return;
        }

        // Define server address
        sockaddr_in serverAddress;
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface
        serverAddress.sin_port = htons(port);       // Set port (convert to network byte order)

        // Bind the socket to the IP and port
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Failed to bind to port " << port << ".\n";
            return;
        }

        // Listen for incoming connections
        if (listen(serverSocket, 5) < 0)
        {
            std::cerr << "Failed to listen on socket.\n";
            return;
        }

        std::cout << "Server listening on port " << port << "...\n";

        // Main loop to accept and handle client connections
        while (true)
        {
            int clientSocket = accept(serverSocket, nullptr, nullptr); // Accept incoming connection
            if (clientSocket < 0)
            {
                std::cerr << "Failed to accept client connection.\n";
                continue;
            }

            // Spawn a new thread for each client connection
            threads.emplace_back(&Server::handleClient, this, clientSocket);
        }
    }

    // Function to handle each client connection in a separate thread
    void handleClient(int clientSocket)
    {
        ClientHandler handler(clientSocket); // Create a ClientHandler for each client
        handler.handleRequest();             // Handle the client's request
    }

    ~Server()
    {
        close(serverSocket); // Close the server socket
        for (std::thread &t : threads)
        {
            if (t.joinable())
            {
                t.join(); // Ensure all threads are joined
            }
        }
    }
};

int main()
{
    Server server(8080); // Start the server on port 8080
    server.start();      // Begin listening and handling connections
    return 0;
}
