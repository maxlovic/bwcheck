//
// blocking_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };

void server(boost::asio::io_context& io_context, unsigned short port)
{
    udp::socket sock(io_context, udp::endpoint(udp::v4(), port));
    for (;;)
    {
        char data[max_length];
        udp::endpoint sender_endpoint;
        size_t length = sock.receive_from(
            boost::asio::buffer(data, max_length), sender_endpoint);
        sock.send_to(boost::asio::buffer(data, length), sender_endpoint);
    }
}

int udp_server(const std::string& port)
{
    try
    {
        boost::asio::io_context io_context;

        server(io_context, stoi(port));
    }
    catch (std::exception & e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

