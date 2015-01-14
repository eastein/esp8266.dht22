#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void loop(os_event_t *events);

static void ICACHE_FLASH_ATTR
loop(os_event_t *events)
{
    os_printf("Hello\n\r");
    os_delay_us(10000);
    system_os_post(user_procTaskPrio, 0, 0 );
}

void wifi_init(void){
    char ssid[32] = WIFI_USER;
    char password[64] = WIFI_PASS;
    
    struct station_config stconf;
        
    // station mode
    wifi_set_opmode(0x1);
    
    // this is necessary, see: http://41j.com/blog/2015/01/esp8266-wifi-doesnt-connect/
    stconf.bssid_set = 0;
    
    // yay auth stuff
    os_memcpy((char *)stconf.ssid,ssid, 32);
    os_memcpy((char *)stconf.password,password, 64);
    
    // set config
    wifi_station_set_config(&stconf);
    wifi_station_set_auto_connect(1);
}

//init
void ICACHE_FLASH_ATTR
user_init()
{
    wifi_init();
}