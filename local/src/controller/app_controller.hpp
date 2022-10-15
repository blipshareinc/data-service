#pragma once

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include "web/dto/status_dto.hpp"
#include "web/dto/app_dto.hpp"
#include "service/app/app_service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace data_service
{
class AppController : public oatpp::web::server::api::ApiController
{
public:
  AppController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
  :
  oatpp::web::server::api::ApiController(object_mapper)
  { }

  ENDPOINT_INFO(getAllData)
  {
      info->summary = "Get All App Data";
      info->addResponse<Object<AppDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET",
      "/app/get_app/offset/{offset}/limit/{limit}",
      getAllData,
      PATH(UInt32, offset),
      PATH(UInt32, limit))
  {
      return createDtoResponse(Status::CODE_200, app_service_.getAllData(offset, limit));
  }

  ENDPOINT_INFO(getById)
  {
      info->summary = "Get App By Id";
      info->addResponse<Object<AppDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET",
      "/app/get_app/{id}",
      getById,
      PATH(UInt8, id))
  {
      return createDtoResponse(Status::CODE_200, app_service_.getById(id));
  }

  ENDPOINT_INFO(create)
  {
      info->summary = "Create New App";
      info->addConsumes<Object<AppDTO>>("application/json");
      info->addResponse<Object<AppDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST",
      "/app/create",
      create,
      BODY_DTO(Object<AppDTO>, dto))
  {
      return createDtoResponse(Status::CODE_200, app_service_.create(dto));
  }

  ENDPOINT_INFO(deleteById)
  {
      info->summary = "Delete Existing App by Id";
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("DELETE",
      "/app/delete/{id}",
      deleteById,
      PATH(UInt8, id))
  {
      return createDtoResponse(Status::CODE_200, app_service_.deleteById(id));
  }

  static std::shared_ptr<AppController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) // Inject objectMapper component here as default parameter
  {
    return std::make_shared<AppController>(objectMapper);
  }
private:
  service::AppService  app_service_;
};

#include OATPP_CODEGEN_END(ApiController)
} // namespace data_service
