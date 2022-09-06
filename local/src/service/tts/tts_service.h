#pragma once

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "web/dto/tts_dto.hpp"
#include "web/dto/page_dto.hpp"
#include "web/dto/status_dto.hpp"
#include "db/tts_client.hpp"

namespace data_service
{
namespace service
{
class TtsService
{
public:
    oatpp::Object<PageDTO<oatpp::Object<TtsDTO>>> getAllTtsData(
        const oatpp::UInt32& offset,
        const oatpp::UInt32& limit
    );
private:
    typedef oatpp::web::protocol::http::Status Status;
    OATPP_COMPONENT(std::shared_ptr<db::tts_client>, db_client_);
};
}
}