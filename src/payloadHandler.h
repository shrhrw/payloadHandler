#ifndef __PAYLOAD_HANDLER_H__
#define __PAYLOAD_HANDLER_H__

#include <stdint.h>
#include <stdio.h>
#include "ccsds.h"

// Create an enumeration that represents all Error Code IDs.
// To be used to return an success/error value when performing packet parse command.
enum errorCodeIds {
    SUCCESS              = 0,
    INVALID_APID         = 1,
    INVALID_COMMAND_CODE = 2,
    INVALID_REGISTER     = 3,
    INVALID_PACKET       = 4
};

// Data struct that holds packet request information, and register values.
typedef struct
{
    uint16_t apid;
    uint16_t commandCode;
    uint16_t registerId;
    uint16_t value;

    uint8_t  registers[ 16 ];

} PayloadHandler_t;

void setAPID( uint16_t value );

void setCommandCode( uint16_t value );

void setRegisterId( uint16_t value );

// Function that validates the APID request.
uint8_t validateAPID();

// Function that validates the Register ID request.
uint8_t validateRegisterId();

// Function that validates the Command Code ID request.
uint8_t validateCommandCodeId();

// Function that parses the incoming packet.
uint8_t parsePacket();

#endif // __PAYLOAD_HANDLER_H__