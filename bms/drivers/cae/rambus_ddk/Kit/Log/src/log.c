/* log.c
 *
 * Log implementation for specific environment
 */

/*****************************************************************************
* Copyright (c) 2008-2020 by Rambus, Inc. and/or its subsidiaries.
* All rights reserved. Unauthorized use (including, without limitation,
* distribution and copying) is strictly prohibited. All use requires,
* and is subject to, explicit written authorization and nondisclosure
* Rambus, Inc. and/or its subsidiaries
*
* For more information or support, please go to our online support system at
* https://sipsupport.rambus.com.
* In case you do not have an account for this system, please send an e-mail
* to sipsupport@rambus.com.
*****************************************************************************/
#include <common.h>
#include <linux/types.h>

//#define LOG_SEVERITY_MAX  LOG_SEVERITY_NO_OUTPUT

// Logging API
#include "log.h"            // the API to implement


/*----------------------------------------------------------------------------
 * Log_HexDump
 *
 * This function logs Hex Dump of a Buffer
 *
 * szPrefix
 *     Prefix to be printed on every row.
 *
 * PrintOffset
 *     Offset value that is printed at the start of every row. Can be used
 *     when the byte printed are located at some offset in another buffer.
 *
 * Buffer_p
 *     Pointer to the start of the array of bytes to hex dump.
 *
 * ByteCount
 *     Number of bytes to include in the hex dump from Buffer_p.
 *
 * Return Value
 *     None.
 */
void
Log_HexDump(
        const char * szPrefix_p,
        const unsigned int PrintOffset,
        const uint8_t * Buffer_p,
        const unsigned int ByteCount)
{
    unsigned int i;
    char Format[] = "%s %08d:";

    for(i = 0; i < ByteCount; i += 16)
    {
        unsigned int j, Limit;

        // if we do not have enough data for a full line
        if (i + 16 > ByteCount)
            Limit = ByteCount - i;
        else
            Limit = 16;

        Log_FormattedMessage(Format, szPrefix_p, PrintOffset + i);

        for (j = 0; j < Limit; j++)
            Log_FormattedMessage(" %02X", Buffer_p[i+j]);

        Log_FormattedMessage("\n");
    } // for
}


/*----------------------------------------------------------------------------
 * Log_HexDump32
 *
 * This function logs Hex Dump of an array of 32-bit words
 *
 * szPrefix
 *     Prefix to be printed on every row.
 *
 * PrintOffset
 *     Offset value that is printed at the start of every row. Can be used
 *     when the byte printed are located at some offset in another buffer.
 *
 * Buffer_p
 *     Pointer to the start of the array of 32-bit words to hex dump.
 *
 * Word32Count
 *     Number of 32-bit words to include in the hex dump from Buffer_p.
 *
 * Return Value
 *     None.
 */
void
Log_HexDump32(
        const char * szPrefix_p,
        const unsigned int PrintOffset,
        const uint32_t * Buffer_p,
        const unsigned int Word32Count)
{
    unsigned int i;
    char Format[] = "%s %08d:";

    for(i = 0; i < Word32Count; i += 4)
    {
        unsigned int j, Limit;

        // if we do not have enough data for a full line
        if (i + 4 > Word32Count)
            Limit = Word32Count - i;
        else
            Limit = 4;

        Log_FormattedMessage(Format, szPrefix_p, PrintOffset + i*4);

        for (j = 0; j < Limit; j++)
            Log_FormattedMessage(" %08X", Buffer_p[i+j]);

        Log_FormattedMessage("\n");
    } // for
}

/* end of file log.c */
