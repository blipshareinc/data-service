#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace data_service
{

ENUM(Role_Type, v_int8,
     VALUE(ADMIN, 0, "ROLE_ADMIN"),
     VALUE(USER,  1, "ROLE_USER")
)

class UserDTO : public oatpp::DTO
{
    DTO_INIT(UserDTO, DTO)

    DTO_FIELD(UInt32, user_id,    "user_id");
    DTO_FIELD(String, email,      "email");
    DTO_FIELD(String, first_name, "first_name");
    DTO_FIELD(String, last_name,  "last_name");
    DTO_FIELD(Enum<Role_Type>::AsNumber, role_type,  "role_type");
};
}

#include OATPP_CODEGEN_END(DTO)