#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace data_service
{
class NotificationDTO : public oatpp::DTO
{
    DTO_INIT(NotificationDTO, DTO)

    DTO_FIELD(UInt32, id,         "id");
    DTO_FIELD(UInt32, data_id,    "data_id");
    DTO_FIELD(UInt8,  app_type,   "app_type");
    DTO_FIELD(String, created_on, "created_on");
};
}

#include OATPP_CODEGEN_END(DTO)