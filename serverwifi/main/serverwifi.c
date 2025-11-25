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

static const char *TAG = "espserver";
void read_mac() {
  uint8_t mac = 0;
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  ESP_LOGI(TAG, "Mac addr: %hhu", mac);
}
static void wifi_init(void) {
  esp_netif_init();
  esp_event_loop_create_default();
  wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&config);

  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(ESPNOW_WIFI_MODE);

  esp_wiif_start();

  esp_wifi_set_channel(CONFIG_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE)
}

esp_err_t init() { esp_now_init(); }

void app_main(void) {

  esp_mac_type_t type = ESP_MAC_WIFI_STA;
  uint8_t mac;
  esp_read_mac()
}
