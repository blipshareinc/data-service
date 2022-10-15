#include "app_service.h"

#include <iostream>

namespace data_service
{
namespace service
{
oatpp::Object<PageDTO<oatpp::Object<AppDTO>>> AppService::getAllData(
    const oatpp::UInt32& offset,
    const oatpp::UInt32& limit)
{
    oatpp::UInt32 count_to_fetch = limit;
    if (count_to_fetch > 10)
    {
        count_to_fetch = 10;
    }

    auto db_result = db_client_->getAllData(offset, count_to_fetch); 
    std::cout << db_result->isSuccess() << std::endl;
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());

    auto items = db_result->fetch<oatpp::Vector<oatpp::Object<AppDTO>>>();

    auto page = PageDTO<oatpp::Object<AppDTO>>::createShared();
    page->offset = offset;
    page->limit = count_to_fetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<AppDTO> AppService::getById(
    oatpp::UInt8 id,
    const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection)
{
    auto db_result = db_client_->getById(id, connection);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());
    OATPP_ASSERT_HTTP(db_result->hasMoreToFetch(), Status::CODE_404, "App not found");

    auto items = db_result->fetch<oatpp::Vector<oatpp::Object<AppDTO>>>();
    OATPP_ASSERT_HTTP(items->size() == 1, Status::CODE_500, "Unknown error");

    return items[0];
}

oatpp::Object<AppDTO> AppService::create(
    const oatpp::Object<AppDTO>& dto)
{
    auto db_result = db_client_->create(dto);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());

    auto row_id = oatpp::sqlite::Utils::getLastInsertRowId(db_result->getConnection());
    OATPP_ASSERT_HTTP(row_id != 0, Status::CODE_500, "Could not create new app.");
    return getById(row_id);
}

oatpp::Object<StatusDTO> AppService::deleteById(
    oatpp::UInt8 id)
{
    auto db_result = db_client_->deleteById(id);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());
    std::cout << "Success: " << db_result->isSuccess() << std::endl;

    auto status = StatusDTO::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = fmt::format("App with id '{}' was successfully deleted.", id);
    return status;
}
}
}