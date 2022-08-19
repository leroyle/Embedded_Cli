
 18-Aug-2022
  Only in the funbiscuit_Cli example
     Add support for Seeed Xiao BLE, just a platformio.ini entry
     Add support to exhaust stack and heap from within app. 
 19-Aug-2022
  Only in the funbiscuit_Cli example
     Add PlatformIO update files to support Rak Wireless Wisblock/
     Seeed Studio Xiao BLE. See README.md in that directory for more info


 A collection of examples demonstrating the use of Embedded CLI
 - these are platformio apps targeting RakWireless Wisblock devices
 - after building/uploading the app
 - start a termial debug session (putty, etc..)
 - type Help in the terminal window to get a list of commands
 - there are two implemtations of CLI represented here

 FreeRTos based and an implementation named funbiscuit

 - For an article comparing various CLI implementations
  https://dojofive.com/blog/embedded-command-line-interfaces-and-why-you-need-them/

   These examples are based on the following repos, code has been refactored however.
 - funbiscuit repo:
   https://github.com/funbiscuit/embedded-cli
   - funbiscuit_Cli:  this base implementation should be platform agnostic as 
     the cli is run from within the super loop.
   - funbiscuit_Embed_Cli: this was refactored to run the cli from within a 
     separate RTOS task

 - FreeRtos repo:
   - FreeRTOS_Cli:   based on, but refactored from
    https://github.com/iotexpert/PSoC-FileSystem/blob/master/RTC-Example-CLI.cydsn
