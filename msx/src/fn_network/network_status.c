#include <msx.h>
#include <stdio.h>

// This helper function tries to read a byte from a specific slot/subslot
// It uses the MSX BIOS "RDSLT" (Read Slot) function at 0x000C
unsigned char read_from_slot(unsigned char slot, unsigned int address) {
    // z88dk provides rdslt: rdslt(slot_id, address)
    // slot_id format: F000SSPP (F=Expanded flag, SS=Subslot, PP=Primary)
    return rdslt(slot, address);
}

// Function to write to the device once found
void write_to_device(unsigned char slot_id, unsigned int address, unsigned char value) {
    // wrslt(slot_id, address, value)
    // This safely switches the slot, writes the byte, and switches back.
    wrslt(slot_id, address, value);
}

uint8_t network_status(const char *devicespec, uint16_t *bw, uint8_t *c, uint8_t *err)
{
    struct _ns
    {
        unsigned short bw;
        bool connected;
        unsigned char err;
    } ns;
    
    unsigned char found_slot = 0;
    
    printf("Probing slots for device...\n");

    for (uint8_t p = 0; p < 4; p++) {
        // We check if slot is expanded (simplified check)
        for (int s = 0; s < 4; s++) {
            unsigned char slot_id = 0x80 | (s << 2) | p; // Construct Slot ID
            
            // Look for MSX ROM Header signature 'AB' at 0x4000
            if (read_from_slot(slot_id, 0x4000) == 0x41 && 
                read_from_slot(slot_id, 0x4001) == 0x42) {
                
                printf("Found ROM in Slot %d-%d\n", p, s);
                
                // Here you would check a specific address for your device ID
                // Example: If your device puts 'X' at 0x4010
                if (read_from_slot(slot_id, 0x4010) == 'X') {
                    found_slot = slot_id;
                    break;
                }
            }
        }
        if (found_slot) break;
    }
    
    // Usage in your main:
    if (found_slot) {
        printf("Writing to device at 0x7000...\n");
        write_to_device(found_slot, 0x7000, 0xFF); 
    }
}
