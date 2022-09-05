#pragma once

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "web/dto/user_dto.hpp"
#include "web/dto/page_dto.hpp"
#include "web/dto/status_dto.hpp"
#include "db/sqlite3_client.hpp"

namespace data_service
{
namespace service
{
class UserService
{
public:
    oatpp::Object<PageDTO<oatpp::Object<UserDTO>>> getAllUsers(
        const oatpp::UInt32& offset,
        const oatpp::UInt32& limit
    );
private:
    typedef oatpp::web::protocol::http::Status Status;
    OATPP_COMPONENT(std::shared_ptr<db::sqlite3_client>, db_client_);
};
}
}