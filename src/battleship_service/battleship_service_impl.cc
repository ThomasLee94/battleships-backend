#include "src/battleship_service/battleship_service_impl.h"
#include "src/battleship_game/board.h"
#include "src/battleship_game/board.cc"

#include "grpc++/grpc++.h"

#include "src/battleship_service/proto/services.grpc.pb.h"
#include "src/util/status_macros.h"

namespace battleshipservice  {

    board = new Board(10,10);

    // instantiate game, not just board?

grpc::Status BattleShipServiceImpl::PlaceShipVert(
    grpc::ServerContext* context,
    const ::battleshipservice::PlaceShipVertRequest* request,
    ::battleshipservice::PlaceShipVertResponse* response) {

        int row_start = *request->get_row_start();
        int row_end = *request->get_row_end();
        int col = *request->get_col();

        status = board.PlaceShipVertical(row_start, row_end, col);
        response.set_message(status)

        return grpc::Status::OK;
}

grpc::Status BattleShipServiceImpl::PlaceShipHor(
    grpc::ServerContext* context,
    const ::battleshipservice::PlaceShipVertRequest* request,
    ::battleshipservice::PlaceShipVertResponse* response) {

        int col_start = *request->get_col_start();
        int col_end = *request->get_col_end();
        int row = *request->get_row();

        status = board.PlaceShipHorizontal(col_start, col_end, row);
        response.set_message(status);
        return grpc::Status::OK;
    }

grpc::Status BattleShipServiceImpl::FireMissile(
    grpc::ServerContext* context,
    const ::battleshipservice::FireMissileRequest* request,
    ::battleshipservice::FireMissileResponse* response) {

        int col = *request->get_col();
        int row = *request->get_row();

        status = board.FireMissile(col, row);
        response.set_message(status)
        return grpc::Status::OK;
}

}  // namespace battleshipservice