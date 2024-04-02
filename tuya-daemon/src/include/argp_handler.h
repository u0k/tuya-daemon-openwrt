#pragma once
#include <argp.h>

struct arguments {
	char *device_id;
	char *device_secret;
	char *product_id;
};

error_t parse_opt(int key, char *arg, struct argp_state *state);