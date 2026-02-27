#include <stdio.h>
#include "fujinet-network-msx.h"

uint8_t network_status(const char *devicespec, uint16_t *bw, uint8_t *c, uint8_t *err)
{
	// if we do a read on the nw_status_cmd channel, we get the status for the specified devicespec, but we have to tell FN which device we want the status for first
	const char *after;
	uint8_t status[4];
    uint16_t temp_bw = 0;
    uint8_t temp_c = 0;
	uint8_t temp_err = 0;
	char *ptr;

	uint8_t unit = network_unit(devicespec);

	struct _s
    {
        uint8_t opcode;
        uint8_t unit;
        uint8_t cmd;
        uint8_t aux1;
        uint8_t aux2;
    } s;

	unsigned char device_id = 0x71; // I'm assuming Fujinet's Device ID will be 0x71
    unsigned char data_to_write = 1;
    
    // 1. Select the device by writing its ID to Port $40
    outp(0x40, device_id);

    // 2. Verify device existence by reading back from Port $40
    // (Should return the bitwise complement of the ID)
    unsigned char check = inp(0x40);
    if (check != (unsigned char)(~device_id)) {
        return FN_ERR_IO_ERROR;
    }

	outp(0x41, data_to_write);

	unsigned char rec = (unsigned char)inp(0x41);

	if (bw) {
        *bw = (uint16_t)(status[1] << 8) | status[0]; // Combine the first two bytes for bw
    }
    if (c) {
        *c = status[2]; // The third byte is directly assigned to c
    }
    if (err) {
        *err = status[3]; // The fourth byte is directly assigned to err
    }

	return FN_ERR_OK;
}
