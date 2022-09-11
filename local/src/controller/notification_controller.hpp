#pragma once

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include "web/dto/status_dto.hpp"
#include "web/dto/notification_dto.hpp"
#include "service/notification/notification_service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace data_service
{
class NotificationController : public oatpp::web::server::api::ApiController
{
public:
  NotificationController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
  :
  oatpp::web::server::api::ApiController(object_mapper)
  { }

  ENDPOINT_INFO(getAllData)
  {
      info->summary = "Get All Notification Data";
      info->addResponse<Object<NotificationDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET",
      "/notification/get_notification/offset/{offset}/limit/{limit}",
      getAllData,
      PATH(UInt32, offset),
      PATH(UInt32, limit))
  {
      return createDtoResponse(Status::CODE_200, notification_service_.getAllData(offset, limit));
  }

  ENDPOINT_INFO(getDataById)
  {
      info->summary = "Get Notification By Id";
      info->addResponse<Object<NotificationDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET",
      "notification/get_notification/{id}",
      getDataById,
      PATH(UInt32, id))
  {
      return createDtoResponse(Status::CODE_200, notification_service_.getDataById(id));
  }

  ENDPOINT_INFO(create)
  {
      info->summary = "Create New Notification";
      info->addConsumes<Object<NotificationDTO>>("application/json");
      info->addResponse<Object<NotificationDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST",
      "notification/create",
      create,
      BODY_DTO(Object<NotificationDTO>, dto))
  {
      return createDtoResponse(Status::CODE_200, notification_service_.create(dto));
  }

  ENDPOINT_INFO(deleteById)
  {
      info->summary = "Delete Existing Notification by Id";
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("DELETE",
      "notification/delete/{id}",
      deleteById,
      PATH(UInt32, id))
  {
      return createDtoResponse(Status::CODE_200, notification_service_.deleteById(id));
  }

  static std::shared_ptr<NotificationController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) // Inject objectMapper component here as default parameter
  {
    return std::make_shared<NotificationController>(objectMapper);
  }
private:
  service::NotificationService  notification_service_;
};

#include OATPP_CODEGEN_END(ApiController)
} // namespace data_service
