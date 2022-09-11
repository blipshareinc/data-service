#pragma once

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "web/dto/notification_dto.hpp"
#include "web/dto/page_dto.hpp"
#include "web/dto/status_dto.hpp"
#include "db/notification_client.hpp"

namespace data_service
{
namespace service
{
class NotificationService
{
public:
    oatpp::Object<PageDTO<oatpp::Object<NotificationDTO>>> getAllData(
        const oatpp::UInt32& offset,
        const oatpp::UInt32& limit
    );

    oatpp::Object<NotificationDTO> getDataById(
        oatpp::UInt32 id,
        const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection=nullptr);

    oatpp::Object<NotificationDTO> create(
        const oatpp::Object<NotificationDTO>& dto);

    oatpp::Object<StatusDTO> deleteById(
        oatpp::UInt32 id);
private:
    typedef oatpp::web::protocol::http::Status Status;
    OATPP_COMPONENT(std::shared_ptr<db::notification_client>, db_client_);
};
}
}