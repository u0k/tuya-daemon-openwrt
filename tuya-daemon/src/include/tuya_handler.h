#pragma once
#include <tuyalink_core.h>

struct device_details {
	char *device_id;
	char *device_secret;
	char *product_id;
	int daemon;
};
int handle_connection(tuya_mqtt_context_t *client, struct device_details *device_details);
