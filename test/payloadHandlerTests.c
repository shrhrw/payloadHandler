#define MUNIT_ENABLE_ASSERT_ALIASES

#include "payloadHandler.h"
#include "ccsds.h"
#include "../munit/munit.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static char * valid_apid_params[] = {
    "0", "1", "2", "256", "257", "258", "512", "513", "514", NULL
};

static char * valid_command_code_params[] = {
    "0", "256", "257", NULL
};

static char * valid_register_id_params[] = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", NULL
};

static char * valid_stream_id_params[] = {
    "24", "56", "88", "8216", "8248", "8280", "32792", "32824", "32856", NULL
};

static MunitParameterEnum test_params_valid[] = {
    { "APID",        valid_apid_params },
    { "CommandCode", valid_command_code_params },
    { "RegisterID",  valid_register_id_params },
    { "StreamID",    valid_stream_id_params },
    { NULL, NULL }
};

static MunitResult test_validate_inputs_valid( const MunitParameter params[], void* user_data ) 
{
    uint16_t apid         = atoi(munit_parameters_get( params, "APID" ));
    uint16_t command_code = atoi(munit_parameters_get( params, "CommandCode" ));
    uint16_t register_id  = atoi(munit_parameters_get( params, "RegisterID" ));
    (void) user_data;

    setAPID( apid );
    setCommandCode( command_code );
    setRegisterId( register_id );

    if ( (validateAPID() != 0) ||
         (validateCommandCodeId() != 0) ||
         (validateRegisterId() != 0) )
    {
        return MUNIT_FAIL;
    }
    else
    {
        return MUNIT_OK;
    }

}

static char * invalid_apid_params[] = {
    "3", NULL
};

static char * invalid_command_code_params[] = {
    "1", NULL
};

static char * invalid_register_id_params[] = {
    "16", NULL
};

static MunitParameterEnum test_params_invalid[] = {
    { "APID",        invalid_apid_params },
    { "CommandCode", invalid_command_code_params },
    { "RegisterID",  invalid_register_id_params },
    { NULL, NULL }
};

static MunitResult test_validate_inputs_invalid( const MunitParameter params[], void* user_data ) 
{
    uint16_t apid         = atoi(munit_parameters_get( params, "APID" ));
    uint16_t command_code = atoi(munit_parameters_get( params, "CommandCode" ));
    uint16_t register_id  = atoi(munit_parameters_get( params, "RegisterID" ));
    (void) user_data;

    setAPID(apid);
    setCommandCode(command_code);
    setRegisterId(register_id);

    if ( ( validateAPID() != 1 ) ||
         ( validateCommandCodeId() != 2 ) ||
         ( validateRegisterId() != 3 ) )
    {
        return MUNIT_FAIL;
    }
    else
    {
        return MUNIT_OK;
    }
}

static MunitParameterEnum test_params_parse_packet_valid[] = {
    { "CommandCode", valid_command_code_params },
    { "RegisterID",  valid_register_id_params },
    { "StreamID",    valid_stream_id_params },
    { NULL, NULL }
};

static MunitResult test_parse_packet( const MunitParameter params[], void* user_data )
{
    uint16_t stream_id    = atoi(munit_parameters_get( params, "StreamID" ));
    uint16_t sequence     = 3;
    uint16_t length       = 16;
    uint16_t command_code = atoi(munit_parameters_get( params, "CommandCode" ));
    uint16_t register_id  = atoi(munit_parameters_get( params, "RegisterID" ));
    uint16_t value        = 42;
    (void)user_data;

    CCSDS_PayloadHandlerPacket_t packet;
    memcpy( &packet.primaryHeader.StreamId,      &stream_id,    sizeof( packet.primaryHeader.StreamId ) );
    memcpy( &packet.primaryHeader.Sequence,      &sequence,     sizeof( packet.primaryHeader.Sequence ) );
    memcpy( &packet.primaryHeader.Length,        &length,       sizeof( packet.primaryHeader.Length ) );
    memcpy( &packet.secondaryHeader.CommandCode, &command_code, sizeof( packet.secondaryHeader.CommandCode ) );
    memcpy( &packet.secondaryHeader.RegisterId,  &register_id,  sizeof( packet.secondaryHeader.RegisterId ) );
    memcpy( &packet.secondaryHeader.Value,       &value,        sizeof( packet.secondaryHeader.Value ) );

    uint8_t returnValue = parsePacket( packet );

    return returnValue;
}

static MunitTest test_suite_tests[] = {
    { (char*) "/test_validate_inputs_valid", test_validate_inputs_valid, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params_valid },
    { (char*) "/test_validate_inputs_invalid", test_validate_inputs_invalid, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params_invalid },
    { (char*) "/test_parse_packet", test_parse_packet, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params_parse_packet_valid },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    (char*) "",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main( int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)] ) {
    return munit_suite_main( &test_suite, (void*) "munit", argc, argv );
}