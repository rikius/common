/*  Copyright (C) 2014-2018 FastoGT. All right reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

        * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following disclaimer
    in the documentation and/or other materials provided with the
    distribution.
        * Neither the name of FastoGT. nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <string>

#include <common/optional.h>
#include <common/protocols/json_rpc/json_rpc_types.h>

namespace common {
namespace protocols {
namespace json_rpc {

// Json RPC error
enum JsonRPCErrorCode : int {
  JSON_RPC_PARSE_ERROR = -32700,       // Parse error
  JSON_RPC_INVALID_REQUEST = -32600,   // Invalid Request
  JSON_RPC_METHOD_NOT_FOUND = -32601,  // Method not found
  JSON_RPC_INVALID_PARAMS = -32602,    // Invalid params
  JSON_RPC_INTERNAL_ERROR = -32603,    // Internal error
  JSON_RPC_SERVER_ERROR = -32000,      // to -32099 Server error
  JSON_RPC_NOT_RFC_ERROR = -32001
};

struct JsonRPCError {
  std::string message;
  JsonRPCErrorCode code;
};

struct JsonRPCMessage {
  std::string result;
};

typedef Optional<JsonRPCMessage> json_rpc_message;
typedef Optional<JsonRPCError> json_rpc_error;

// should be message or error
struct JsonRPCResponce {
  JsonRPCResponce();

  static JsonRPCResponce MakeError(json_rpc_id jid, JsonRPCError error);
  static JsonRPCResponce MakeMessage(json_rpc_id jid, JsonRPCMessage msg);

  bool IsError() const;
  bool IsMessage() const;
  bool IsValid() const;

  json_rpc_id id;
  json_rpc_message message;
  json_rpc_error error;
};

}  // namespace json_rpc
}  // namespace protocols
}  // namespace common
