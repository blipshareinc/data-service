#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace data_service
{
class UserDTO : public oatpp::DTO
{
    DTO_INIT(UserDTO, DTO)

    DTO_FIELD(String, id,   "id");
    DTO_FIELD(String, name, "name");
};
}

#include OATPP_CODEGEN_END(DTO)