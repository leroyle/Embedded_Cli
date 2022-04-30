#ifndef __CLI_IMPL_H__
#define __CLI_IMPL_H__

extern "C" {
void xCreateCLITask(const char * appVersionString);
}
// App version
#define VERSION_MAX 50
extern char cliAppVersion [VERSION_MAX];

typedef BaseType_t Peripheral_Descriptor_t;
size_t FreeRTOS_read( Peripheral_Descriptor_t const pxPeripheral, 
                      int8_t * pvBuffer, 
                      const size_t xBytes );
size_t FreeRTOS_write( Peripheral_Descriptor_t const pxPeripheral, 
                       const void *pvBuffer, 
                       const size_t xBytes );

#endif
