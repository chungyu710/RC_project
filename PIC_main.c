// code for interfacing with nRF24L01 with PIC microcontroller
// sample code from https://circuitdigest.com/microcontroller-projects/interfacing-nrf24l01-rf-module-with-pic-microcontroller

// these libraries require an Arduino library ported over for PIC18F622K microcontroller
#include "mcc_generated_files/mcc.h"
#include "nrf24_lib.h"
#include <string.h>

#define NRF24L01_TX_EX  0
#define NRF24L01_RX_EX  !NRF24L01_TX_EX

void blink_led() {
    LED_Toggle();
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    TMR0_SetInterruptHandler(blink_led);
    TMR0_StartTimer();

    #if NRF24L01_TX_EX
    ret = nrf24_rf_init(TX_MODE, 115); // Tx mode with 2400+115 Ghz RF frq
    #elif NRF24L01_RX_EX
    ret = nrf24_rf_init(RX_MODE, 115); // Rx mode with 2400+115 Ghz RF frq
    #endif
    if (ret == NRF24_INIT_OK) {
        printf("###############################################################\r\n");
        printf("NRF24L01 Initialize successful\r\n");
        nrf24_printf_rf_config();
        printf("###############################################################\r\n");

    #if NRF24L01_TX_EX
        static char val = 0;
        sprintf(bufferTX, "Sending: %d", val);
        nrf24_send_rf_data(bufferTX);
        val++;
        __delay_ms(100);

    #elif NRF24L01_RX_EX
        while (nrf24_is_rf_data_available()) {
        }
        nrf24_read_rf_data(bufferRX);
        printf("RX data %s\r\n", bufferRX);
        __delay_ms(10);
    #endif