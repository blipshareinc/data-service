#pragma once

#include <oatpp-sqlite/orm.hpp>
#include <fmt/core.h>

#include "web/dto/notification_dto.hpp"

namespace data_service
{
namespace db
{

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class notification_client: public oatpp::orm::DbClient
{
public:
notification_client(const std::shared_ptr<oatpp::sqlite::Executor>& executor) :
    oatpp::orm::DbClient(executor)
{
      fmt::print("Sqlite3 Client for Notification initialized...\n");
}

QUERY(getAllData,
      "SELECT * FROM notification LIMIT :limit OFFSET :offset;",
      PARAM(oatpp::UInt32, offset),
      PARAM(oatpp::UInt32, limit))

QUERY(getDataById,
      "SELECT * FROM notification where id=:id;",
      PARAM(oatpp::UInt32, id))

QUERY(create,
      "INSERT INTO notification (data_id, app_type)"
      "VALUES (:dto.data_id, :dto.app_type);",
      PARAM(oatpp::Object<NotificationDTO>, dto))

QUERY(deleteById,
      "DELETE FROM notification where id=:id;",
      PARAM(oatpp::UInt32, id))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

}
}