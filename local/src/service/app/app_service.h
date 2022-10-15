#pragma once

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "web/dto/app_dto.hpp"
#include "web/dto/page_dto.hpp"
#include "web/dto/status_dto.hpp"
#include "db/app_client.hpp"

namespace data_service
{
namespace service
{
class AppService
{
public:
    oatpp::Object<PageDTO<oatpp::Object<AppDTO>>> getAllData(
        const oatpp::UInt32& offset,
        const oatpp::UInt32& limit
    );

    oatpp::Object<AppDTO> getById(
        oatpp::UInt8 id,
        const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection=nullptr);

    oatpp::Object<AppDTO> create(
        const oatpp::Object<AppDTO>& dto);

    oatpp::Object<StatusDTO> deleteById(
        oatpp::UInt8 id);
private:
    typedef oatpp::web::protocol::http::Status Status;
    OATPP_COMPONENT(std::shared_ptr<db::app_client>, db_client_);
};
}
}