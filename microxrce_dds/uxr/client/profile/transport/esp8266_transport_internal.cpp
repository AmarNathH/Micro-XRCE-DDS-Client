#include "esp8266_transport_internal.h"

#include <ESP8266WiFi.h> 
#include <WiFiUdp.h>

static WiFiUDP *p_wifi_udp;

bool initUDPESP8266(void* udp_instance, uint16_t port)
{
  bool rv = false;

  if (udp_instance == nullptr)
  {
    return false;
  }

  p_wifi_udp = (WiFiUDP *)(udp_instance);
  p_wifi_udp->begin(port);

  rv = true;

  return rv;
}

bool closeUDPESP8266()
{
  p_wifi_udp->stop();

  return true;
}

size_t writeUDPESP8266(const uint8_t *buf, size_t len)
{
  size_t tx_len = 0;

  p_wifi_udp->beginPacket(p_wifi_udp->remoteIP(),p_wifi_udp->remotePort());
  tx_len = p_wifi_udp->write(buf, len);
  p_wifi_udp->endPacket();

  return tx_len;
}

size_t readUDPESP8266(uint8_t *buf, size_t len, int timeout)
{
  size_t rv = 0;
  uint32_t pre_time = millis();

  while (rv <= 0 && (millis() - pre_time < (uint32_t)timeout))
  {
    rv = p_wifi_udp->available();
  }

  if (rv > len)
  {
    rv = len;
  }

  if (0 < rv)
  {
    p_wifi_udp->read(buf, len);
  }

  return rv;
}