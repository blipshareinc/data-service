//#include <fmt/core.h>
#include <iostream>

#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>

#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp-swagger/Controller.hpp>

#include "web/app_component.hpp"
#include "controller/controller.hpp"
#include "controller/user_controller.hpp"
#include "controller/tts_controller.hpp"
#include "controller/notification_controller.hpp"
#include "controller/app_controller.hpp"

auto run() -> void
{
    // register components
    data_service::AppComponent components;

    // get the router
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    // create swagger document end point controller
    oatpp::web::server::api::Endpoints doc_end_points;

    // create controller and all of its endpoints to router
    auto controller              = std::make_shared<data_service::RESTApiController>();
    auto user_controller         = std::make_shared<data_service::UserController>();
    auto tts_controller          = std::make_shared<data_service::TtsController>();
    auto notification_controller = std::make_shared<data_service::NotificationController>();
    auto app_controller          = std::make_shared<data_service::AppController>();

    doc_end_points.append(router->addController(controller)->getEndpoints());
    doc_end_points.append(router->addController(user_controller)->getEndpoints());
    doc_end_points.append(router->addController(tts_controller)->getEndpoints());
    doc_end_points.append(router->addController(notification_controller)->getEndpoints());
    doc_end_points.append(router->addController(app_controller)->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(doc_end_points));

    // get Http connection handler
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, conn_handler);

    // get TCP connection provider
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, conn_provider);

    // create server which takes provided TCP connections and passes them to Http connection handler
    auto server = oatpp::network::Server(conn_provider, conn_handler);

    // print server info
    OATPP_LOGI("DataService", "Server running on port %s", conn_provider->getProperty("port").getData());

    // run the server
    server.run();
}

/**
 * @brief Starting point of the application
 * 
 * @return int: 0 if successful. Else error code.
 */
int main(int argc, char* argv[])
{
    // initialize oatpp environment
    oatpp::base::Environment::init();

    // run the app
    run();

    // destrop oatpp environment
    oatpp::base::Environment::destroy();

    return 0;
}