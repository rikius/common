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

#include <common/qt/logger.h>

#include <QMetaType>

#include <common/convert2string.h>
#include <common/logger.h>
#include <common/qt/convert2string.h>

namespace common {
namespace qt {

Logger::Logger() {
  qRegisterMetaType<common::logging::LEVEL_LOG>("common::logging::LEVEL_LOG");
}

void Logger::print(const char* mess, logging::LEVEL_LOG level, bool notify) {
  RUNTIME_LOG(level) << mess;
  if (notify) {
    QString qmess;
    bool res = ConvertFromString(std::string(mess), &qmess);
    UNUSED(res);
    emit printed(qmess, level);
  }
}

void Logger::print(const QString& mess, logging::LEVEL_LOG level, bool notify) {
  const std::string smess = ConvertToString(mess);
  RUNTIME_LOG(level) << smess;
  if (notify) {
    emit printed(mess, level);
  }
}

void Logger::print(const std::string& mess, logging::LEVEL_LOG level, bool notify) {
  RUNTIME_LOG(level) << mess;
  if (notify) {
    QString qmess;
    bool res = ConvertFromString(mess, &qmess);
    UNUSED(res);
    emit printed(qmess, level);
  }
}

}  // namespace qt
}  // namespace common
