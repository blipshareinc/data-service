#pragma once

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include "web/dto/user_dto.hpp"
#include "web/dto/status_dto.hpp"
#include "service/user_service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace data_service
{
class RESTApiController : public  oatpp::web::server::api::ApiController
{
public:
  RESTApiController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
  :
  oatpp::web::server::api::ApiController(object_mapper)
  { }

  ENDPOINT_INFO(root)
  {
    const char* html = 
      "<html lang='en'>"
      "  <head>"
      "    <meta charset=utf-8/>"
      "  </head>"
      "  <body>"
      "    <p>Home Automation Project</p>"
      "    <a href='swagger/ui'>API Documentation</a>"
      "  </body>"
      "</html>";
    info->summary = "";
    info->addResponse<Object<StatusDTO>>(
      Status::CODE_200,
      "application/json"
    );
  }
  ENDPOINT("GET", "/", root)
  {
    auto dto = StatusDTO::createShared();
    dto->code = 200;
    dto->message = "Hello World";
    return createDtoResponse(Status::CODE_200, dto);
  }
  ENDPOINT_INFO(getAllUsers)
  {
      info->summary = "Get all users";
      info->addResponse<Object<UserDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET",
      "/get_users/offset/{offset}/limit/{limit}",
      getAllUsers,
      PATH(UInt32, offset),
      PATH(UInt32, limit))
  {
      return createDtoResponse(Status::CODE_200, user_service_.getAllUsers(offset, limit));
  }
private:
  static std::shared_ptr<RESTApiController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) // Inject objectMapper component here as default parameter
  {
    return std::make_shared<RESTApiController>(objectMapper);
  }

  service::UserService user_service_;
};

#include OATPP_CODEGEN_END(ApiController)
} // namespace data_service
