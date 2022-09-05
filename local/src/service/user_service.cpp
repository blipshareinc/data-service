#include "user_service.h"

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
    std::cout << db_result->isSuccess() << std::endl;
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());

    auto items = db_result->fetch<oatpp::Vector<oatpp::Object<UserDTO>>>();

    auto page = PageDTO<oatpp::Object<UserDTO>>::createShared();
    page->offset = offset;
    page->limit = count_to_fetch;
    page->count = items->size();
    page->items = items;

    return page;
}

}
}