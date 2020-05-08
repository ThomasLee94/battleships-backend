#ifndef SRC_BATTLESHIP_UNARY_SERVICE_IMPL_H
#define SRC_BATTLESHIP_UNARY_SERVICE_IMPL_H

#include "grpc++/grpc++.h"

#include "src/battleship_service/proto/services.grpc.pb.h"

namespace battleshipservice {

class BattleShipServiceImpl final : public ::battleshipservice::BoardService {
    grpc::Status PlaceShipVert(
        grpc::ServerContext* context,
        const ::battleshipservice::PlaceShipVertRequest* request,
        ::battleshipservice::PlaceShipVertResponse* response) override;

    grpc::Status PlaceShipHor(
        grpc::ServerContext* context,
        const ::battleshipservice::PlaceShipVertRequest* request,
        ::battleshipservice::PlaceShipVertResponse* response) override;

    grpc::Status FireMissile(
        grpc::ServerContext* context,
        const ::battleshipservice::FireMissileRequest* request,
        ::battleshipservice::FireMissileResponse* response) override;

}

}  // namespace battleshipservice

#endif
