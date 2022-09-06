#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace data_service
{
class TtsDTO : public oatpp::DTO
{
    DTO_INIT(TtsDTO, DTO)

    DTO_FIELD(UInt32, tts_id,           "tts_id");
    DTO_FIELD(UInt32, user_id,          "user_id");
    DTO_FIELD(String, text,             "text");
    DTO_FIELD(String, audio_file_name,  "audio_file_name");
};
}

#include OATPP_CODEGEN_END(DTO)