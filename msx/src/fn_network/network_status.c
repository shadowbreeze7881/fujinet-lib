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
