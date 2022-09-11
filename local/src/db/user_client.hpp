#pragma once

#include <oatpp-sqlite/orm.hpp>
#include <fmt/core.h>

#include "web/dto/user_dto.hpp"

namespace data_service
{
namespace db
{

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class user_client: public oatpp::orm::DbClient
{
public:
user_client(const std::shared_ptr<oatpp::sqlite::Executor>& executor) :
    oatpp::orm::DbClient(executor)
{
      fmt::print("Sqlite3 Client for User initialized...\n");
}

QUERY(getAllUsers,
      "SELECT * FROM user LIMIT :limit OFFSET :offset;",
      PARAM(oatpp::UInt32, offset),
      PARAM(oatpp::UInt32, limit))

QUERY(getUserById,
      "SELECT * FROM user where user_id=:id;",
      PARAM(oatpp::UInt32, id))

QUERY(createUser,
      "INSERT INTO user (email, first_name, last_name, role_type)"
      "VALUES (:userDTO.email, :userDTO.first_name, :userDTO.last_name, :userDTO.role_type);",
      PARAM(oatpp::Object<UserDTO>, userDTO));

QUERY(deleteUserById,
      "DELETE FROM user where user_id=:id;",
      PARAM(oatpp::UInt32, id))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

}
}