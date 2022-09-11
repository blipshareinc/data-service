#pragma once

#include <oatpp-sqlite/orm.hpp>
#include <fmt/core.h>

#include "web/dto/tts_dto.hpp"

namespace data_service
{
namespace db
{

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

class tts_client: public oatpp::orm::DbClient
{
public:
tts_client(const std::shared_ptr<oatpp::sqlite::Executor>& executor) :
    oatpp::orm::DbClient(executor)
{
      fmt::print("Sqlite3 Client for TTS initialized...\n");
}

QUERY(getAllTtsData,
      "SELECT * FROM tts LIMIT :limit OFFSET :offset;",
      PARAM(oatpp::UInt32, offset),
      PARAM(oatpp::UInt32, limit))

QUERY(getTtsById,
      "SELECT * FROM tts where tts_id=:id;",
      PARAM(oatpp::UInt32, id))

QUERY(createTts,
      "INSERT INTO tts (user_id, text, audio_file_name)"
      "VALUES (:dto.user_id, :dto.text, :dto.audio_file_name);",
      PARAM(oatpp::Object<TtsDTO>, dto))

QUERY(deleteTtsById,
      "DELETE FROM tts where tts_id=:id;",
      PARAM(oatpp::UInt32, id))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

}
}