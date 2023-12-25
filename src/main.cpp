extern "C" {
    #include <esp_event.h>
    #include <esp_log.h>
    #include <esp_system.h>
    #include <nvs_flash.h>
    #include <sys/param.h>
    #include "esp_netif.h"
    // #include "esp_eth.h"
    // #include "esp_wifi.h"
    // #include "protocol_examples_common.h"
    // #include "lwip/sockets.h"
    // #include <esp_https_server.h>
    #include "sdkconfig.h"
    #include <esp_err.h>
    #include "esp_mac.h"
}

#include <Arduino.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <config.h>

extern "C" {
    #include "keep_alive.h"
    #include "wss_server.h"
}

int dist = 0;
void lidarTaskCode( void * pvParameters ){
  printf("lidar task running on core ");
  printf(""+xPortGetCoreID());

  for(;;){
    dist = lidar_distance(true, LIDARLITE_ADDR_DEFAULT);
    printf("lidar %d\n", dist);

    wifi_sta_list_t wifi_sta_list;
    tcpip_adapter_sta_list_t adapter_sta_list;
    memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));
    memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));
    esp_wifi_ap_get_sta_list(&wifi_sta_list);
    tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);
    printf("#STA %d\n", adapter_sta_list.num);

    delay(LIDAR_PERIOD);
  } 
}
extern "C" void app_main(void)
{
    initArduino();
    lidar_begin(0, true, LIDARLITE_ADDR_DEFAULT);
    lidar_configure(3, LIDARLITE_ADDR_DEFAULT);
    TaskHandle_t lidarTask;
    xTaskCreatePinnedToCore(
                    lidarTaskCode,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &lidarTask,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */ 

    static httpd_handle_t server = NULL;

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* Register event handlers to start server when Wi-Fi or Ethernet is connected,
     * and stop server when disconnection happens.
     */

// #ifdef CONFIG_EXAMPLE_CONNECT_WIFI
//     ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
//     ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));
// #endif // CONFIG_EXAMPLE_CONNECT_WIFI
// #ifdef CONFIG_EXAMPLE_CONNECT_ETHERNET
//     ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, &connect_handler, &server));
//     ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ETHERNET_EVENT_DISCONNECTED, &disconnect_handler, &server));
// #endif // CONFIG_EXAMPLE_CONNECT_ETHERNET

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    //ESP_ERROR_CHECK(example_connect());
    ESP_ERROR_CHECK(wifi_init_softap());

    /* This function demonstrates periodic sending Websocket messages
     * to all connected clients to this server
     */
    //wss_server_send_messages(start_wss_echo_server());
    server = start_wss_echo_server();
    wss_server_send_messages(&server);
}