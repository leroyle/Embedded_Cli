
LeroyLe   4/26/2022

19-Aug-2022
  Add PlatformIO update files for Adafruit "packages/framework-arduinoadafruitnrf52" and "platforms/nordicnrf52" files.

18-Aug-2022
  Only in the funbiscuit_Cli example
     Add support for Seeed Xiao BLE, just a platformio.ini entry
     Add support to exhaust stack and heap from within app.

An Embedded CLI implementation. 

For an article comparing 5 different CLI implemtations see:
https://dojofive.com/blog/embedded-command-line-interfaces-and-why-you-need-them/

The implmentation this example was based upon can be found at: 
	https://github.com/funbiscuit/embedded-cli




Update PlatformIO files:
This set of examples requires an updated version of PlatformIO "packages" and "platforms" support files.

The following will install a set of defaults then instruct how to add files
needed to support Rak Wireless Wisblock and Seeed Studio Xiao BLE (Sense).

1. Install VS Code and the PlatformIO extension
2. Install a new platform, "NRF52" via the VSCode PIOHome tab, platforms subtab 
   - this will install the necessary "platforms/nordicnrf52" files
3. in the PIOHome tab, create a new project
   in the name field, enter any name
   - for Board selection: "Adafruit Feather nRF52840 Express"
   - for framework: select "Arduino"
   - Click "Finish" to create the project
- when the project has been created, build it. This will result in the download
of the base Adafruit "packages/framework-arduinoadafruitnrf52" files.

Once the project has been build, unzip the update files into your PlatformIO
installation area, by default within your user home directory

For Linux that would be
- download this repo, locate the assets/*.zip files
#> cd ~/.platformio
#> unzip "DOWNLOAD_DIR"/assets/platforms.zip
#> unzip "DOWNLOAD_DIR"/assets/framework.zip

You should now be able to create a new project targeting either Wisblock or Seeed Xiao BLE.
