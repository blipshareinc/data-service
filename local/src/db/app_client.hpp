#pragma once

#include <oatpp-sqlite/orm.hpp>
#include <fmt/core.h>

#include "web/dto/app_dto.hpp"

namespace data_service
{
namespace db
{

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class app_client: public oatpp::orm::DbClient
{
public:
app_client(const std::shared_ptr<oatpp::sqlite::Executor>& executor) :
    oatpp::orm::DbClient(executor)
{
      fmt::print("Sqlite3 Client for App initialized...\n");
}

QUERY(getAllData,
      "SELECT * FROM app LIMIT :limit OFFSET :offset;",
      PARAM(oatpp::UInt32, offset),
      PARAM(oatpp::UInt32, limit))

QUERY(getById,
      "SELECT * FROM app where id=:id;",
      PARAM(oatpp::UInt8, id))

QUERY(create,
      "INSERT INTO app (id, name, enabled, url)"
      "VALUES (:dto.id, :dto.text, :dto.enabled, :dto.url);",
      PARAM(oatpp::Object<AppDTO>, dto))

QUERY(deleteById,
      "DELETE FROM app where id=:id;",
      PARAM(oatpp::UInt8, id))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

}
}