#pragma once

#include "user_dto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace data_service
{
template<class T>
class PageDTO : public oatpp::DTO
{
    DTO_INIT(PageDTO, DTO)

    DTO_FIELD(UInt32, offset);
    DTO_FIELD(UInt32, limit);
    DTO_FIELD(UInt32, count);
    DTO_FIELD(Vector<T>, items);
};
}

#include OATPP_CODEGEN_END(DTO)