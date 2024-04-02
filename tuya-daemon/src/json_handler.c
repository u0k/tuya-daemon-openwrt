#include <cJSON.h>
#include <stdio.h>
#include "message_handler.h"

/**
 * parse_property_json() - Handle the process of parsing given JSON
 * @arg1: JSON string
 *
 * Tries to parse an integer value (either 0 or 1)
 * 
 * Return: Error code on failure, otherwise parsed value.
 * 
 */
int parse_property_json(char *json_string)
{
	cJSON *json	   = cJSON_Parse(json_string);
	const cJSON *value = NULL;
	int rt		   = -1;
	if (json == NULL) {
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL) {
			log_message(ERROR_JSON_PARSING, json_string);
		}
		goto cleanup;
	}
	value = cJSON_GetObjectItemCaseSensitive(json, "led_capslock");
	if (cJSON_IsNumber(value)) {
		int parsed_value = value->valueint;
		if (parsed_value == 1 || parsed_value == 0)
			rt = parsed_value;
		else {
			rt = -1;
		}
	}
cleanup:
	cJSON_Delete(json);
	return rt;
}