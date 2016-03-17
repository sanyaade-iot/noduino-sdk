/*
 *  Copyright (c) 2015 - 2025 MaiKe Labs
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/
#include "noduino.h"
#include "mjyun.h"

#define	DEBUG	1

irom void mjyun_stated_cb(mjyun_state_t state)
{
    if (mjyun_state() != state)
        serial_printf("Platform: mjyun_state error \r\n");

    switch (state)
    {
        case WIFI_IDLE:
            serial_printf("Platform: WIFI_IDLE\r\n");
            break;
        case WIFI_SMARTLINK_LINKING:
            serial_printf("Platform: WIFI_SMARTLINK_LINKING\r\n");
            break;
        case WIFI_SMARTLINK_FINDING:
            serial_printf("Platform: WIFI_SMARTLINK_FINDING\r\n");
            break;
        case WIFI_SMARTLINK_TIMEOUT:
            serial_printf("Platform: WIFI_SMARTLINK_TIMEOUT\r\n");
            break;
        case WIFI_SMARTLINK_GETTING:
            serial_printf("Platform: WIFI_SMARTLINK_GETTING\r\n");
            break;
        case WIFI_SMARTLINK_OK:
            serial_printf("Platform: WIFI_SMARTLINK_OK\r\n");
            break;
        case WIFI_AP_OK:
            serial_printf("Platform: WIFI_AP_OK\r\n");
            break;
        case WIFI_AP_ERROR:
            serial_printf("Platform: WIFI_AP_ERROR\r\n");
            break;
        case WIFI_AP_STATION_OK:
            serial_printf("Platform: WIFI_AP_STATION_OK\r\n");
            break;
        case WIFI_AP_STATION_ERROR:
            serial_printf("Platform: WIFI_AP_STATION_ERROR\r\n");
            break;
        case WIFI_STATION_OK:
            serial_printf("Platform: WIFI_STATION_OK\r\n");
            break;
        case WIFI_STATION_ERROR:
            serial_printf("Platform: WIFI_STATION_ERROR\r\n");
            break;
        case MJYUN_CONNECTING:
            serial_printf("Platform: MJYUN_CONNECTING\r\n");
            break;
        case MJYUN_CONNECTING_ERROR:
            serial_printf("Platform: MJYUN_CONNECTING_ERROR\r\n");
            break;
        case MJYUN_CONNECTED:
            serial_printf("Platform: MJYUN_CONNECTED \r\n");
			digitalWrite(2, LOW);
            break;
        case MJYUN_DISCONNECTED:
            serial_printf("Platform: MJYUN_DISCONNECTED\r\n");
			digitalWrite(2, HIGH);
            break;
        default:
            break;
    }
}

irom void mjyun_receive(const char *event_name, const char *event_data)
{
	serial_printf("RECEIVED: key:value [%s]:[%s]", event_name, event_data);
	// Publish back
	mjyun_publish(event_name, event_data);
}

void mjyun_connected()
{
    mjyun_publishstatus("device status save");
    digitalWrite(2, LOW);
}

void mjyun_disconnected()
{
    digitalWrite(2, HIGH);
}

/*
 * 3707 --> 摩羯插座
 * 3708 --> 摩羯灯
 */
const mjyun_config_t mjyun_conf = {
	//"WotP0123456789",		/* 产品id [必填] */
	"gh_51111441aa63",		/* 产品id [必填] */
	"3707",					/* 产品子id (一般用于微信设备) [选填]*/
	"Hi, I'm coming!!!",	/* 设备上线时，给app发送 online 消息中的附加数据，[选填] */
	"I will come back!!!"	/* 设备掉线时，给app发送 offline 消息中的附加数据，[选填] */
};

void init_yun()
{
	mjyun_statechanged(mjyun_stated_cb);
	mjyun_ondata(mjyun_receive);
	mjyun_onconnected(mjyun_connected);
	mjyun_ondisconnected(mjyun_disconnected);

	mjyun_run(&mjyun_conf);
}

irom void setup()
{
	serial_begin(115200);
	pinMode(2, OUTPUT);

	init_yun();
}

irom void loop()
{
	serial_printf("MJYUN device heart beat!\r\n");
	delay(2000);
}
