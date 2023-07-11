#include <http_server.h>

namespace http
{
    tcp_server::tcp_server(std::string ip_address, int port) : _ip(ip_address), _port(port)
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
}