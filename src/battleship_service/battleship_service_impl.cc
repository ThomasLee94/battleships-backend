#include "src/battleship_service/battleship_service_impl.h"
#include "src/battleship_game/board.h"
#include "src/battleship_game/board.cc"

#include "grpc++/grpc++.h"

#include "src/battleship_service/proto/services.grpc.pb.h"
#include "src/util/status_macros.h"

namespace battleshipservice  {

    board = new Board(10,10);

grpc::Status BattleShipServiceImpl::PlaceShipVert(
    grpc::ServerContext* context,
    const ::battleshipservice::PlaceShipVertRequest* request,
    ::battleshipservice::PlaceShipVertResponse* response) {

     *request->get_message() = row_start, row_end, col;
     status = board.PlaceShipVertical(row_start, row_end, col);
     *response->set_message(status)
     return grpc::Status::OK;
}

grpc::Status BattleShipServiceImpl::PlaceShipHor(
    grpc::ServerContext* context,
    const ::battleshipservice::PlaceShipVertRequest* request,
    ::battleshipservice::PlaceShipVertResponse* response) {

     *request->get_message() = col_start, col_end, row;
     status = board.PlaceShipVertical(col_start, col_end, row);
     *response->set_message(status)
     return grpc::Status::OK;
}

}  // namespace battleshipservice