#ifndef COMMAND_H
#define COMMAND_H

#include "Arduino.h"
#include "ArduinoJson.h"

namespace CBlocks{
  struct CommandResponse{
    unsigned int requestID;
    bool success;
    String message;
    String toJSON(DynamicJsonBuffer& buffer);

    static CommandResponse getSuccessCommandResponseFor(unsigned int requestID);
    static CommandResponse getErrorCommandResponseFor(unsigned int requestID, String message);
  };

  typedef CommandResponse (*commandCallback)(JsonObject& json);
}

#endif
