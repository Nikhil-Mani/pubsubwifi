#include "esp_now.h"
#include "esp_wifi.h"
#include "freertos/queue.h"
#include <stdint.h>

#ifndef SERVER_WIFI_H
#define SERVER_WIFI_H

#if CONFIG_ESPNOW_WIFI_MODE_STATION
#define ESPNOW_WIFI_MODE WIFI_MODE_STA
#define ESPNOW_WIFI_IF WIFI_IF_STA
#else
#define ESPNOW_WIFI_MODE WIFI_MODE_AP
#define ESPNOW_WIFI_IF WIFI_IF_AP
#endif

#define ESPNOW_QUEUE_SIZE 6

#define ESP_NOW_ETH_ALEN 6

typedef enum {
  ESPNOW_SEND_CB,
  ESPNOW_RECV_CB,
} espnow_event_id_t;

typedef struct {
  uint8_t mac_addr[ESP_NOW_ETH_ALEN];
  esp_now_send_status_t status;
} espnow_event_send_cb_t;

typedef struct {
  uint8_t mac_addr[ESP_NOW_ETH_ALEN];
  uint8_t *data;
  int data_len;
} espnow_event_recv_cb_t;

typedef union {
  espnow_event_send_cb_t send_cb;
  espnow_event_recv_cb_t recv_cb;
} espnow_event_info_t;

typedef struct {
  espnow_event_id_t id;
  espnow_event_info_t info;
} espnow_event_t;

#endif