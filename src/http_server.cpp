#include <http_server.h>

namespace http
{
    tcp_server::tcp_server(std::string ip_address, int port) : _ip(ip_address), _port(port), serverMsg(buildResponse())
    {
        start_server();
    };
    tcp_server::~tcp_server()
    {
        if (_socket > 0)
        {
            close_server();
        }
    };

    void tcp_server::start_server()
    {
        socketAddress.in_addr.s_addr = inet_addr(_ip.c_str());
        socketAddress.sin_family = AF_UNIX;
        socketAddress.sin_port = htons(_port);
        socketAddressLength = sizeof(socketAddress);

        _socket = socket(AF_UNIX, SOCK_STREAM, 0);
        if (_socket < 0)
        {
            exitWithError("Failed to create socket!\n");
        }
        else
        {
            log("Socket created!\n");
        }

        if (bind(_socket, (sockaddr *)&socketAddress, socketAddressLength) < 0)
        {
            exitWithError("Cannot connect socket to address\n");
        }
    }

    void tcp_server::close_server()
    {
        int idx = close(_socket);
        if (_socket < 0)
        {
            exitWithError("Failed to close socket!\n");
        }
        else
        {
            log("Socket closed!\n");
        }
    }

    void tcp_server::start_listen()
    {
        if (listen(_socket, MAX_CONNECTION_THREAD) < 0)
        {
            exitWithError("Socket listen failed\n");
        }
        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: "
           << inet_ntoa(socketAddress.in_addr)
           << " PORT: " << ntohs(socketAddress.sin_port)
           << " ***\n\n";
        log(ss.str());

        int bytesReceived;
        while (true)
        {
            log("====== Waiting for a new connection ======\n\n\n");
            acceptConnection();

            bytesReceived = read(_new_socket, buffer, BUFFER_SIZE);
            if (bytesReceived < 0)
            {
                exitWithError("Failed to read bytes from client socket connection");
            }

            std::ostringstream ss;
            ss << "------ Received Request from client ------\n\n";
            log(ss.str());

            sendResponse();

            close(_new_socket);
        }
    }

    void tcp_server::acceptConnection()
    {
        _new_socket = accept(_socket, (sockaddr *)&socketAddress,
                             &socketAddressLength);
        if (_new_socket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: "
               << inet_ntoa(socketAddress.in_addr) << "; PORT: "
               << ntohs(socketAddress.sin_port);
            exitWithError(ss.str());
        }
    }

    void tcp_server::sendResponse()
    {
    }

    std::string tcp_server::buildResponse()
    {
        long bytesSent;

        bytesSent = write(_new_socket, serverMsg.c_str(), serverMsg.size());

        if (bytesSent == serverMsg.size())
        {
            log("------ Server Response sent to client ------\n\n");
        }
        else
        {
            log("Error sending response to client");
        }
    }
}