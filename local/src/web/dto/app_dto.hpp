#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace data_service
{
class AppDTO : public oatpp::DTO
{
    DTO_INIT(AppDTO, DTO)

    DTO_FIELD(UInt8,   id,      "id");
    DTO_FIELD(String,  name,    "name");
    DTO_FIELD(Boolean, enabled, "enabled");
    DTO_FIELD(String,  url,     "url");
};
}

#include OATPP_CODEGEN_END(DTO)