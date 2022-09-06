#pragma once

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include "web/dto/status_dto.hpp"
#include "web/dto/tts_dto.hpp"
#include "service/tts/tts_service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace data_service
{
class TtsController : public oatpp::web::server::api::ApiController
{
public:
  TtsController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
  :
  oatpp::web::server::api::ApiController(object_mapper)
  { }

  ENDPOINT_INFO(getAllTtsData)
  {
      info->summary = "Get All TTS Data";
      info->addResponse<Object<TtsDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET",
      "/tts/get_tts/offset/{offset}/limit/{limit}",
      getAllTtsData,
      PATH(UInt32, offset),
      PATH(UInt32, limit))
  {
      return createDtoResponse(Status::CODE_200, tts_service_.getAllTtsData(offset, limit));
  }

  static std::shared_ptr<TtsController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) // Inject objectMapper component here as default parameter
  {
    return std::make_shared<TtsController>(objectMapper);
  }
private:
  service::TtsService  tts_service_;
};

#include OATPP_CODEGEN_END(ApiController)
} // namespace data_service
