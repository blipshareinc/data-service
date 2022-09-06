#include "user_service.h"

#include <fmt/core.h>

#include <iostream>

namespace data_service
{
namespace service
{
oatpp::Object<PageDTO<oatpp::Object<UserDTO>>> UserService::getAllUsers(
    const oatpp::UInt32& offset,
    const oatpp::UInt32& limit)
{
    oatpp::UInt32 count_to_fetch = limit;
    if (count_to_fetch > 10)
    {
        count_to_fetch = 10;
    }

    auto db_result = db_client_->getAllUsers(offset, count_to_fetch); 
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());

    auto items = db_result->fetch<oatpp::Vector<oatpp::Object<UserDTO>>>();

    auto page = PageDTO<oatpp::Object<UserDTO>>::createShared();
    page->offset = offset;
    page->limit = count_to_fetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<UserDTO> UserService::getUserById(
    oatpp::UInt32 id,
    const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection)
{
    auto db_result = db_client_->getUserById(id, connection);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());
    OATPP_ASSERT_HTTP(db_result->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto items = db_result->fetch<oatpp::Vector<oatpp::Object<UserDTO>>>();
    OATPP_ASSERT_HTTP(items->size() == 1, Status::CODE_500, "Unknown error");

    return items[0];
}

oatpp::Object<UserDTO> UserService::createUser(
    const oatpp::Object<UserDTO>& userDTO)
{
    auto db_result = db_client_->createUser(userDTO);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());

    auto row_id = oatpp::sqlite::Utils::getLastInsertRowId(db_result->getConnection());
    OATPP_ASSERT_HTTP(row_id != 0, Status::CODE_500, "Could not create new user.");
    return getUserById(row_id);
}

oatpp::Object<StatusDTO> UserService::deleteUserById(
    oatpp::UInt32 id)
{
    auto db_result = db_client_->deleteUserById(id);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());
    std::cout << "Success: " << db_result->isSuccess() << std::endl;

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = fmt::format("User with email '{}' was successfully deleted.", id);
    return status;
}

}
}