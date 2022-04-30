#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
/**
 * Code based on the following repo, however it 
 * has been refactored to move all of the CLI 
 * setup and processing out of main.cpp:
 * https://github.com/funbiscuit/embedded-cli
 * 
 * 
 * Simple example of using embedded-cli in arduino.
 * To compile copy embedded-cli.h and embedded-cli.c to sketch directory.
 *
 * With specified settings:
 * 32 bytes for cmd buffer, 16 for RX buffer,
 * 32 bytes for history,
 * 3 binding functions and no dynamic allocation
 * Total size of firmware is 7538 bytes, 654 bytes of RAM are used.
 * Not everything is used by library, some memory is used by Serial, for
 * example.
 * Most of RAM space is taken up by char arrays so size can be reduced if
 * messages are discarded.
 * For example, by removing code inside onHelp and onUnknown functions inside
 * library (and replacing help strings in bindings by nullptr's) size of FW is
 * reduced by 688 bytes of ROM and 190 bytes of RAM. Total usage is then
 * 6850 of ROM and 464 of RAM.
 */
// the CLI interface
#include "cli.h"

#define _AppVersion "funbiscuit_Embed_Cli V0.3"

void setup() {
    Serial.begin(115200);

    // init the CLI interface
    uint8_t cliRc = cliSetup(_AppVersion);
    if (cliRc == 0)
    {
        Serial.println(F("Cli has started. Enter your commands."));
    } else {
        Serial.println(F("<====== ERROR: Cli startup failed. ======"));
    }
 }

uint32_t lastTime=0;
uint32_t cycleTime = 5000;

void loop() {
    uint32_t currTime = millis();
    if(currTime - lastTime > cycleTime)
    {
        lastTime = currTime;
        Serial.println("In main loop");
    }

    // custom loop code
}

