#include "esp8266_transport_internal.h"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

static WiFiUDP* p_wifi_udp;
static const char* agent_address;
static uint16_t agent_port;

bool initUDPESP8266(void *udp_instance, const char *ip, uint16_t port)
{
  bool rv = false;

  if (udp_instance == nullptr)
  {
    return false;
  }

  p_wifi_udp = ((WiFiUDP *)(udp_instance));
  p_wifi_udp->begin(port);
  agent_address = ip;
  agent_port = port;

  rv = true;

  // printf("Initialising UDP\n");

  return rv;
}

bool closeUDPESP8266()
{
  // printf("Closing UDP\n");
  p_wifi_udp->stop();

  return true;
}

size_t writeUDPESP8266(const uint8_t *buf, size_t len)
{
  size_t tx_len = 0;

  p_wifi_udp->beginPacket(agent_address, agent_port);
  tx_len = p_wifi_udp->write(buf, len);
  p_wifi_udp->endPacket();
  
  // printf("Writing UDP Data\n");

  return tx_len;
}

size_t readUDPESP8266(uint8_t *buf, size_t len, int timeout)
{
  size_t rv = 0;
  uint32_t pre_time = millis();

  while (rv <= 0 && (millis() - pre_time < (uint32_t)timeout))
  {
    p_wifi_udp->parsePacket();
    rv = p_wifi_udp->available();
  }

  if (rv > len)
  {
    rv = len;
  }

  if (0 < rv)
  {
    p_wifi_udp->read(buf, len);
    // printf("Reading UDP Data\n");
  }


  return rv;
}