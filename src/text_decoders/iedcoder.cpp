/*  Copyright (C) 2014-2017 FastoGT. All right reserved.

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

#include <common/text_decoders/iedcoder.h>

namespace common {

const char* const edecoder_types[ENCODER_DECODER_NUM_TYPES] = {"Base64", "GZip",    "Snappy",
                                                               "Hex",    "MsgPack", "HtmlEscape"};
COMPILE_ASSERT(ENCODER_DECODER_NUM_TYPES == arraysize(edecoder_types), "Incorrect number of edecoder_types");

std::string ConvertToString(EDType ed_type) {
  if (ed_type >= 0 && ed_type < ENCODER_DECODER_NUM_TYPES) {
    return edecoder_types[ed_type];
  }

  DNOTREACHED();
  return "UNKNOWN";
}

bool ConvertFromString(const std::string& from, EDType* out) {
  if (!out) {
    return false;
  }

  for (size_t i = 0; i < ENCODER_DECODER_NUM_TYPES; ++i) {
    if (from == edecoder_types[i]) {
      *out = static_cast<EDType>(i);
      return true;
    }
  }

  return false;
}

IEDcoder::~IEDcoder() {}

IEDcoder::IEDcoder(EDType type) : type_(type) {}

Error IEDcoder::Encode(const StringPiece& data, std::string* out) {
  if (data.empty()) {
    return make_inval_error_value(ErrorValue::E_ERROR);
  }

  return EncodeImpl(data, out);
}

Error IEDcoder::Decode(const StringPiece& data, std::string* out) {
  if (data.empty()) {
    return make_inval_error_value(ErrorValue::E_ERROR);
  }

  return DecodeImpl(data, out);
}

EDType IEDcoder::GetType() const {
  return type_;
}

}  // namespace common
