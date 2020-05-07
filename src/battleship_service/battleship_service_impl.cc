#include "src/battleship_service/battleship_service_impl.h"
#include "src/battleship_game/board.h"
#include "src/battleship_game/board.cc"

#include "grpc++/grpc++.h"

#include "src/battleship_service/proto/services.grpc.pb.h"
#include "src/util/status_macros.h"

namespace battleshipservice  {

grpc::Status BattleShipServiceImpl::CreateBoard(
    grpc::ServerContext* context,
    const ::battleshipservice::CreateBoardRequest* request,
    ::battleshipservice::CreateBoardResponse* response) {

     *response->set_message(new battleship::Board(10,10));
     return grpc::Status::OK;
}

}  // namespace battleshipservice