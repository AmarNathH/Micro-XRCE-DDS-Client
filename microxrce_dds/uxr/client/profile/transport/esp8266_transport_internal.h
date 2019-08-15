#ifndef _SRC_C_PROFILE_TRANSPORT_ESP8266_TRANSPORT_INTERNAL_H_
#define _SRC_C_PROFILE_TRANSPORT_ESP8266_TRANSPORT_INTERNAL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

bool initUDPESP8266(void *udp_instance, const char *ip, uint16_t port);
bool closeUDPESP8266();
size_t writeUDPESP8266(const uint8_t *buf, size_t len);
size_t readUDPESP8266(uint8_t *buf, size_t len, int timeout);

#ifdef __cplusplus
}
#endif

#endif //_SRC_C_PROFILE_TRANSPORT_ARDUINO_TRANSPORT_INTERNAL_H_