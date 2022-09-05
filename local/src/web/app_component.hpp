#pragma once

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp-sqlite/orm.hpp>

#include <oatpp-swagger/Model.hpp>
#include <oatpp-swagger/Resources.hpp>

#include <fmt/core.h>

#include "db/sqlite3_client.hpp"

namespace data_service
{

/**
 * @brief Creates and holds the various application components (like swagger, database) etc
 * 
 */
class AppComponent
{
public:
    /**
     * @brief Create connection provider
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, conn_provider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared(
            { SERVER_NAME, SERVER_PORT, oatpp::network::Address::IP_4 }
        );
    }());

    /**
     * @brief Create router component
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, http_router)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    /**
     * @brief Create connection handler
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, conn_handler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    /**
     * @brief Create object mapper
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, obj_mapper)([]{
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

    /**
     * @brief Create database connection provider component
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider)([] {
        /* Create database-specific ConnectionProvider */
        auto connection_provider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);

        /* Create database-specific ConnectionPool */
        return oatpp::sqlite::ConnectionPool::createShared(connection_provider,
                                                           10 /* max-connections */,
                                                           std::chrono::seconds(5) /* connection TTL */);
    }());

    /**
     * @brief Create Database client
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<data_service::db::sqlite3_client>, database_client)([] {

        // get database connection provider
        OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connection_provider);

        // create database specific executor
        auto executor = std::make_shared<oatpp::sqlite::Executor>(connection_provider);

        // create database client
        return std::make_shared<data_service::db::sqlite3_client>(executor);
    }());

    /**
     * @brief Create Swagger API docs info
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swagger_doc_info)([] {
        oatpp::swagger::DocumentInfo::Builder builder;

        builder
            .setTitle("Available Endpoints")
            .setDescription("APIs with swagger docs")
            .setVersion("1.0")
            .setContactName("BLIPShare")
            .setContactUrl("https://www.blipshare.com")
            .setLicenseName("Apache License, Version 2.0")
            .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")
            .addServer(fmt::format("{}:{}", SERVER_ADDRESS, SERVER_PORT), "server on localhost");

        return builder.build();
    }());

    /**
     * @brief Swagger Resources
     * 
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swagger_resources)([] {
        // set the oatpp-swagger resources path
        return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    }());
};
    
} // namespace data_service

