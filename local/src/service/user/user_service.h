#pragma once

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "web/dto/user_dto.hpp"
#include "web/dto/page_dto.hpp"
#include "web/dto/status_dto.hpp"
#include "db/user_client.hpp"

namespace data_service
{
namespace service
{
class UserService
{
public:
    oatpp::Object<PageDTO<oatpp::Object<UserDTO>>> getAllUsers(
        const oatpp::UInt32& offset,
        const oatpp::UInt32& limit);

    oatpp::Object<UserDTO> getUserById(
        oatpp::UInt32 id,
        const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection=nullptr);

    oatpp::Object<UserDTO> createUser(
        const oatpp::Object<UserDTO>& userDTO);

    oatpp::Object<StatusDTO> deleteUserById(
        oatpp::UInt32 id);
private:
    typedef oatpp::web::protocol::http::Status Status;
    OATPP_COMPONENT(std::shared_ptr<db::user_client>, db_client_);
};
}
}