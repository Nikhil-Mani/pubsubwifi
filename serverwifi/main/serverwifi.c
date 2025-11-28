#include "serverwifi.h"
#include "esp_crc.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include "esp_now.h"
#include "esp_random.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "nvs_flash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ESPNOW_MAXDELAY 512

#define ESPNOW_CHANNEL 1 // add kconfig later

static QueueHandle_t espnow_queue = NULL;

static const char *TAG = "espserver";
void read_mac() {
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
}
static void wifi_init(void) {
  esp_netif_init();
  esp_event_loop_create_default();
  wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&config);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(ESPNOW_WIFI_MODE);

  esp_wifi_start();

  esp_wifi_set_channel(CONFIG_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE)
}
static void espnow_send_cb(const esp_now_send_info_t *tx_info,
                           esp_now_send_status_t status) {
  espnow_event_t event;
  espnow_event_send_cb_t *callback = &event.info.send_cb;

  if (tx_info == NULL) {
    ESP_LOGE(TAG, "Error with wifi config thing");
  }

  event.id = ESPNOW_SEND_CB;

  memcpy(callback->mac_addr, tx_info->des_addr, ESP_NOW_ETH_ALEN);

  callback->status = status;

  xQueueSend(espnow_queue, &event, ESPNOW_MAXDELAY);
}

esp_err_t init() { esp_now_init(); }

void app_main(void) {}
