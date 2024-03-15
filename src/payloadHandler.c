#include "payloadHandler.h"

PayloadHandler_t PayloadHandler_Data;

void setAPID( uint16_t value )
{
    PayloadHandler_Data.apid = value;
}

void setCommandCode( uint16_t value )
{
    PayloadHandler_Data.commandCode = value;
}

void setRegisterId( uint16_t value )
{
    PayloadHandler_Data.registerId = value;
}

uint8_t maskBits( uint8_t numBits, uint8_t startBit )
{
    return ( ( 1 << numBits ) - 1 ) << startBit;
}

uint8_t validateAPID()
{
    if ( ( PayloadHandler_Data.apid == 0 )   ||
         ( PayloadHandler_Data.apid == 1 )   ||
         ( PayloadHandler_Data.apid == 2 )   ||
         ( PayloadHandler_Data.apid == 256 ) ||
         ( PayloadHandler_Data.apid == 257 ) ||
         ( PayloadHandler_Data.apid == 258 ) ||
         ( PayloadHandler_Data.apid == 512 ) ||
         ( PayloadHandler_Data.apid == 513 ) ||
         ( PayloadHandler_Data.apid == 514 ) )
    {
        return SUCCESS;
    }
    else 
    {
        return INVALID_APID;
    }
}

uint8_t validateCommandCodeId()
{
    if ( ( PayloadHandler_Data.commandCode == 0 ) ||
         ( PayloadHandler_Data.commandCode == 256 ) ||
         ( PayloadHandler_Data.commandCode == 257 )  )
    {
        return SUCCESS;
    }
    else
    {
        return INVALID_COMMAND_CODE;
    }
}

uint8_t validateRegisterId()
{
    if ( ( PayloadHandler_Data.registerId >= 0 ) &&
         ( PayloadHandler_Data.registerId < 16 ) )
    {
        return SUCCESS;
    }
    else
    {
        return INVALID_REGISTER;
    }
}

uint8_t parsePacket( CCSDS_PayloadHandlerPacket_t packet )
{
    PayloadHandler_Data.apid        = (packet.primaryHeader.StreamId >> 5) & ((1 << 11) - 1 );
    PayloadHandler_Data.commandCode = packet.secondaryHeader.CommandCode;
    PayloadHandler_Data.registerId  = packet.secondaryHeader.RegisterId;
    PayloadHandler_Data.value       = packet.secondaryHeader.Value;

    if ( INVALID_APID == validateAPID() )
    {
        return INVALID_PACKET; 
    }

    if ( INVALID_COMMAND_CODE == validateCommandCodeId() )
    {
        return INVALID_PACKET; 
    }

    if ( INVALID_REGISTER == validateRegisterId() )
    {
        return INVALID_PACKET; 
    }

    PayloadHandler_Data.registers[ PayloadHandler_Data.registerId ] = PayloadHandler_Data.value;

    if ( PayloadHandler_Data.commandCode == 257 )
    {
        printf( "\nthe register %u of the payload %u is set to %u.\n",
                PayloadHandler_Data.registerId,
                PayloadHandler_Data.apid,
                PayloadHandler_Data.registers[ PayloadHandler_Data.registerId ]);
    }

    if ( PayloadHandler_Data.commandCode == 256 )
    {
        printf( "\nthe register %u of the payload %u is read.\n",
                PayloadHandler_Data.registerId,
                PayloadHandler_Data.apid );
    }

    if ( PayloadHandler_Data.commandCode == 0 )
    {
        printf( "\nthe payload %u receives NOOP.\n",
                PayloadHandler_Data.apid );
    }

    return SUCCESS;
}