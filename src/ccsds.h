#ifndef __CCSDS_HEADER_H__
#define __CCSDS_HEADER_H__

typedef struct CCSDS_PrimaryHeader
{
    uint16_t StreamId; /**< \brief packet identifier word (stream ID) */
                       /*  bits  shift   ------------ description ---------------- */
                       /* 0x07FF    0  : application ID                            */
                       /* 0x0800   11  : secondary header: 0 = absent, 1 = present */
                       /* 0x1000   12  : packet type:      0 = TLM, 1 = CMD        */
                       /* 0xE000   13  : CCSDS version:    0 = ver 1, 1 = ver 2    */

    uint16_t Sequence; /**< \brief packet sequence word */
                       /*  bits  shift   ------------ description ---------------- */
                       /* 0x3FFF    0  : sequence count                            */
                       /* 0xC000   14  : segmentation flags:  3 = complete packet  */

    uint16_t Length; /**< \brief packet length word */
                     /*  bits  shift   ------------ description ---------------- */
                     /* 0xFFFF    0  : (total packet length) - 7                 */
} CCSDS_PrimaryHeader_t;

typedef struct
{
    uint16_t CommandCode;
    uint8_t  RegisterId;
    uint16_t Value;
} CCSDS_SecondaryHeader_t;

// CCSDS Payload Handler Packet to be sent to payloadHandler application.
typedef struct CCSDS_PayloadHandlerPacket_t
{
    CCSDS_PrimaryHeader_t primaryHeader;
    CCSDS_SecondaryHeader_t secondaryHeader;
} CCSDS_PayloadHandlerPacket_t;

#endif // __CCSDS_HEADER_H__