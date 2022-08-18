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

 /**
 * @file main.cpp
 * 
 * @author Leroy Levin
 * @brief 
 * @version 0.1
 * @date 2022-08-18
 * 
 * This app can demo the use of the CLI supporting
 * stackCheck - dump stack statistics
 *  - optional stack exhaustion test, see EAT_HELP ifdefs
 * heapCheck -  dump heap statistics
 *  - optional heap exhaustion test, see EAT_STACK ifdefs
 * appVersion - dump app version
 * help
 * 
 */
#include "embedded_cli.h"
#include "cli.h"

EmbeddedCli *appCli = NULL;
#define appVersion "funbiscuit_Cli V0.5"

// Enable EAT_HEAP if you want to emulate exhaust heap space
// Enable EAT_STACK if you want to emulate exhaust stack space
// #define EAT_HEAP
// #define EAT_STACK
#ifdef EAT_STACK
void eatStack(uint8_t);
static uint8_t cnt = 0;
static uint8_t count = 10;
#endif

#ifdef EAT_HEAP
void eatHeap();
#endif

uint32_t lastTime = 0;
uint32_t waitTime = 3000;

void setup()
{
    Serial.begin(115200);
    // Wait for Serial connection in debug mode
    while (!Serial)
        yield();

    appCli = cliSetup(appVersion);
    if (appCli == NULL)
    {
        Serial.println(F("Cli was not created. Check sizes!"));
        return;
    }
    Serial.println(F("appCli has started. Enter your commands."));

#ifdef EAT_STACK
    Serial.println("\n\tRunning stack exhaustion");
#endif

#ifdef EAT_HEAP
    Serial.println("\n\tRunning heap exhaustion");

#endif
}

void loop()
{

    if (appCli == NULL)
        return;

    // provide all chars to cli
    while (Serial.available() > 0)
    {
        if (appCli != NULL)
        {
            embeddedCliReceiveChar(appCli, Serial.read());
        }
    }

    if (appCli != NULL)
    {
        embeddedCliProcess(appCli);
    }

#if defined(EAT_STACK) || defined(EAT_HEAP)
    uint32_t curTime = millis();

    if (curTime > (lastTime + waitTime))
    {
#ifdef EAT_STACK
        // call eatStack X number of times
        cnt = 0;
        Serial.print("Call eatStack ");
        Serial.print(count);
        Serial.println(" times");
        eatStack(cnt);
        count += 10;
#endif

#ifdef EAT_HEAP
        eatHeap();
#endif
        lastTime = curTime;
    }
#endif  // EAT_STACK || EAT_HEAP
}

#ifdef EAT_STACK
void eatStack(uint8_t cnt)
{
    uint8_t arrSize = 5;
    uint32_t arr[arrSize];

    memset(arr, 0, arrSize);
    if (cnt < count)
    {
        cnt++;
        eatStack(cnt);
    }
}
#endif

#ifdef EAT_HEAP
uint32_t *ptr = 0;
static uint32_t totalMem = 0;
void eatHeap()
{
    uint16_t mallSize = 8192;
    totalMem += mallSize;
    ptr = (uint32_t *)rtos_malloc(mallSize);

    Serial.print("Total Malloc'd: ");
    Serial.println(totalMem);
}
#endif
