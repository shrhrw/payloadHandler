#include "payloadHandler.h"

PayloadHandler_t PayloadHandler_Data;

uint8_t validateAPID()
{
    if ( PayloadHandler_Data.apid != APID_0   ||
         PayloadHandler_Data.apid != APID_1   ||
         PayloadHandler_Data.apid != APID_2   ||
         PayloadHandler_Data.apid != APID_256 ||
         PayloadHandler_Data.apid != APID_257 ||
         PayloadHandler_Data.apid != APID_258 ||
         PayloadHandler_Data.apid != APID_512 ||
         PayloadHandler_Data.apid != APID_513 ||
         PayloadHandler_Data.apid != APID_514 )
    {
        printf("Error %u: Invalid APID received.\n ", INVALID_APID );
        return INVALID_APID;
    }

    return SUCCESS;
}

uint8_t validateCommandCodeId()
{
    if ( PayloadHandler_Data.commandCode != NO_OP || 
         PayloadHandler_Data.commandCode != READ_REGISTER || 
         PayloadHandler_Data.commandCode != WRITE_REGISTER  )
    {
        printf("Error %u: Invalid COMMAND_CODE_ID received.\n ", INVALID_COMMAND_CODE );
        return INVALID_COMMAND_CODE;
    }

    return SUCCESS;
}

uint8_t validateRegisterId()
{
    if ( PayloadHandler_Data.registerId < REGISTER_0 || 
         PayloadHandler_Data.registerId >= NUMBER_OF_REGISTERS )
    {
        printf("Error %u: Invalid REGISTER_ID received.\n ", INVALID_REGISTER );
        return INVALID_REGISTER;
    }

    return SUCCESS;
}

uint8_t parsePacket()
{
    // parse packet
}