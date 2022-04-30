#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
/**
 * Code based on:
 * https://github.com/funbiscuit/embedded-cli
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

#include "embedded_cli.h"
#include "cli.h"

EmbeddedCli * appCli = NULL;
#define appVersion "funbiscuit_Cli V0.3"

void setup() {
    Serial.begin(115200);

    appCli = cliSetup(appVersion);
    if (appCli == NULL) {
        Serial.println(F("Cli was not created. Check sizes!"));
        return;
    }
    Serial.println(F("appCli has started. Enter your commands."));

}

void loop() {

    if (appCli == NULL)
        return;

    // provide all chars to cli
    while (Serial.available() > 0) {
        if (appCli != NULL)
        {
            embeddedCliReceiveChar(appCli, Serial.read());
        }
    }

    if (appCli != NULL)
    {
        embeddedCliProcess(appCli);
    }
}

