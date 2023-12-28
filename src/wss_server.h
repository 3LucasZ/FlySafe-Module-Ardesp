#ifndef WSS_SERVER_H
#define WSS_SERVER_H

// #include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
// #include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "esp_eth.h"
#include "esp_wifi.h"
#include "protocol_examples_common.h"
#include "lwip/sockets.h"
#include <esp_https_server.h>
#include "keep_alive.h"
#include "sdkconfig.h"
#include <esp_err.h>
#include "esp_mac.h"
#include "config.h"


#if !CONFIG_HTTPD_WS_SUPPORT
#error This example cannot be used unless HTTPD_WS_SUPPORT is enabled in esp-http-server component configuration
#endif


struct async_resp_arg {
    httpd_handle_t hd;
    int fd;
};

extern const char *TAG;
const size_t max_clients = MAX_WS_CONN;

esp_err_t root_get_handler(httpd_req_t *req);

esp_err_t reboot_get_handler(httpd_req_t *req);

esp_err_t ws_handler(httpd_req_t *req);

esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd);

void wss_close_fd(httpd_handle_t hd, int sockfd);

void send_dist(void *arg);

void send_ping(void *arg);

bool client_not_alive_cb(wss_keep_alive_t h, int fd);

bool check_client_alive_cb(wss_keep_alive_t h, int fd);

httpd_handle_t start_wss_echo_server(void);

esp_err_t stop_wss_echo_server(httpd_handle_t server);

void disconnect_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data);

void connect_handler(void* arg, esp_event_base_t event_base,
                            int32_t event_id, void* event_data);

// Get all clients and send async message
void wss_server_send_messages(httpd_handle_t* server);

//*** CUSTOM AP & ROUTE
void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);

esp_err_t wifi_init_softap(void);

const httpd_uri_t ws = {
        .uri        = "/ws",
        .method     = HTTP_GET,
        .handler    = ws_handler,
        .user_ctx   = NULL,
        .is_websocket = true,
        .handle_ws_control_frames = true,
        .supported_subprotocol = "soap",
};

const httpd_uri_t root = {
        .uri        = "/",
        .method     = HTTP_GET,
        .handler    = root_get_handler,
        .user_ctx   = NULL,
        .is_websocket = false,
        .handle_ws_control_frames = false,
        .supported_subprotocol = "soap",
};

const httpd_uri_t reboot = {
        .uri        = "/reboot",
        .method     = HTTP_POST,
        .handler    = reboot_get_handler,
        .user_ctx   = NULL,
        .is_websocket = false,
        .handle_ws_control_frames = false,
        .supported_subprotocol = "soap",
};

//***
#endif