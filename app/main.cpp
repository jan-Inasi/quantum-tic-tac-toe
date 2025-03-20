#include <iostream>
#include <restinio/all.hpp>
#include <string>

#include "move_interpreter.hpp"


int main(int argc, char** argv) {

    if(argc < 3) {
        std::cout << "Please provide server IP and port as arguments.\n";
        return 1;
    }

    std::string address = argv[1]; //NOLINT
    int port = atoi(argv[2]); //NOLINT

    MoveInterpreter intr;

    std::cout << "API is running on http://" << address << ':' << port << '\n';

    try{
        restinio::run(
            restinio::on_this_thread().port(port).address(address).request_handler(
                [&](const restinio::request_handle_t& req) {
                    auto path = req->header().path();
                    std::string body = intr.detectMove(static_cast<std::string>(path));
                    std::cout << path << " | " << body << "\n";
                    return req->create_response()
                        .append_header(restinio::http_field::access_control_allow_origin, "*") //CORS
                        .append_header(restinio::http_field::content_type, "application/json; charset=utf-8")
                        .set_body(body)
                        .done();
                }));
    }
    catch(std::exception& e){
        std::cout << "Exception thrown:" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "exiting" << std::endl;
    }
    catch(...){
        std::cout << "Unknown exception thrown." << std::endl;
        std::cout << "exiting" << std::endl;
    }
    
    return 0;
}
