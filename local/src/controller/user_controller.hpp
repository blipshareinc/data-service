#pragma once

#include <fmt/core.h>
#include <oatpp/core/macro/component.hpp>

#include "web/dto/user_dto.hpp"
#include "web/dto/status_dto.hpp"
#include "service/user/user_service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace data_service
{
class UserController : public  oatpp::web::server::api::ApiController
{
public:
  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
  :
  oatpp::web::server::api::ApiController(object_mapper)
  { }

  ENDPOINT_INFO(getAllUsers)
  {
      info->summary = "Get All users";
      info->addResponse<Object<UserDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET",
      "users/get_users/offset/{offset}/limit/{limit}",
      getAllUsers,
      PATH(UInt32, offset),
      PATH(UInt32, limit))
  {
      return createDtoResponse(Status::CODE_200, user_service_.getAllUsers(offset, limit));
  }

  ENDPOINT_INFO(getUserById)
  {
      info->summary = "Get User By Id";
      info->addResponse<Object<UserDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET",
      "users/get_user/{id}",
      getUserById,
      PATH(UInt32, id))
  {
      return createDtoResponse(Status::CODE_200, user_service_.getUserById(id));
  }

  ENDPOINT_INFO(createUser)
  {
      info->summary = "Create New User";
      info->addConsumes<Object<UserDTO>>("application/json");
      info->addResponse<Object<UserDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST",
      "users/create_user",
      createUser,
      BODY_DTO(Object<UserDTO>, userDTO))
  {
      return createDtoResponse(Status::CODE_200, user_service_.createUser(userDTO));
  }

  ENDPOINT_INFO(deleteUserById)
  {
      info->summary = "Delete Existing User by Id";
      info->addResponse<Object<UserDTO>>(Status::CODE_200, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_400, "application/json");
      info->addResponse<Object<StatusDTO>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("DELETE",
      "users/delete_user/{id}",
      deleteUserById,
      PATH(UInt32, id))
  {
      return createDtoResponse(Status::CODE_200, user_service_.deleteUserById(id));
  }

  static std::shared_ptr<UserController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) // Inject objectMapper component here as default parameter
  {
    return std::make_shared<UserController>(objectMapper);
  }
private:
  service::UserService user_service_;
};

#include OATPP_CODEGEN_END(ApiController)
} // namespace data_service