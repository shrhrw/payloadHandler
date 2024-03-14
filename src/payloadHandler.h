#ifndef __PAYLOAD_HANDLER_H__
#define __PAYLOAD_HANDLER_H__

#include <stdint.h>
#include <stdio.h>

// Create enumeration that represents all valid register ids. 
// To be used to validate the packet request.
enum registerIds {
    REGISTER_0  = 0,
    REGISTER_1  = 1,
    REGISTER_2  = 2,
    REGISTER_3  = 3,
    REGISTER_4  = 4,
    REGISTER_5  = 5,
    REGISTER_6  = 6,
    REGISTER_7  = 7,
    REGISTER_8  = 8,
    REGISTER_9  = 9,
    REGISTER_10 = 10,
    REGISTER_11 = 11,
    REGISTER_12 = 12,
    REGISTER_13 = 13,
    REGISTER_14 = 14,
    REGISTER_15 = 15,
    NUMBER_OF_REGISTERS
};

// Create an enumeration that represents all valid APIDs. 
// To be used to validate the packet request.
enum APIDs {
    APID_0   = 0,
    APID_1   = 1,
    APID_2   = 2,
    APID_256 = 256,
    APID_257 = 257,
    APID_258 = 258,
    APID_512 = 512,
    APID_513 = 513,
    APID_514 = 514
};

// Create an enumeration that represents all valid Command Code IDs. 
// To be used to validate the packet request.
enum commandCodeIds {
    NO_OP          = 0,
    READ_REGISTER  = 256,
    WRITE_REGISTER = 257
};

// Create an enumeration that represents all Error Code IDs.
// To be used to return an success/error value when performing packet parse command.
enum errorCodeIds {
    SUCCESS              = 0,
    INVALID_APID         = 1,
    INVALID_COMMAND_CODE = 2,
    INVALID_REGISTER     = 3
};

// Data struct that holds packet request information, and register values.
typedef struct
{
    uint16_t apid;
    uint16_t commandCode;
    uint16_t registerId;
    uint8_t  registers[ NUMBER_OF_REGISTERS ];

} PayloadHandler_t;

// Function that validates the APID request.
uint8_t validateAPID();

// Function that validates the Register ID request.
uint8_t validateRegisterId();

// Function that validates the Command Code ID request.
uint8_t validateCommandCodeId();

// Function that parses the incoming packet.
uint8_t parsePacket();

#endif // __PAYLOAD_HANDLER_H__