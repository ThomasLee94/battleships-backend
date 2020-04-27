import React from "react";
import { Component } from "react";

const { googleRPC } = require("reactrpc")

const requests = require("../../helloworld_pb.js");
const clients = require("../../helloworld_grpc_web_pb.js");

googleRPC.build(
  requests,
  clients,
  "http://" + window.location.hostname + ":8080"
);

class App extends Component {
  constructor(props) {
    super(props);
    const stream = this.props.Greeter.sayRepeatHello(
      { name: "Josh", count: 5, msgType: "RepeatHelloRequest" },
      {}
    );
    stream.onMessage(res => {
      console.log(res.getMessage());
    });
    console.log(stream);
  }

  render() {
    console.log("This is the props", this.props);
    this.props.Health.check(
      { service: "Greeter", msgType: "HealthCheckRequest" },
      {},
      (err, response) => {
        console.log(response.getStatus());
      }
    );
    return (
      <div>
        <h1>googleRPC</h1>
      </div>
    );
  }
}

export default googleRPC.wrapper(App);
