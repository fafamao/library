#include <sys/socket.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>

namespace http
{
    constexpr int MAX_CONNECTION_THREAD = 10;
    constexpr int BUFFER_SIZE = 30720;

    typedef struct
    {
        short sin_family;
        unsigned short sin_port;
        in_addr in_addr;
    } sock_addr;

    class tcp_server
    {
    public:
        tcp_server(std::string ip_address, int port);
        ~tcp_server();

        void start_server();
        void close_server();
        void start_listen();
        void acceptConnection();
        void sendResponse();
        std::string buildResponse();
        void log(const std::string &message)
        {
            std::cout << message << std::endl;
        };
        void exitWithError(const std::string &errorMessage)
        {
            log("ERROR: " + errorMessage);
            exit(1);
        };

    private:
        int _socket;
        int _new_socket;
        std::string _ip;
        std::string serverMsg;
        int _port;
        char buffer[BUFFER_SIZE] = {0};
        unsigned int socketAddressLength;
        sock_addr socketAddress;
    };
}