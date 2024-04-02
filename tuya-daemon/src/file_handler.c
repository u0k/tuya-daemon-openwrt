#include <errno.h>
#include <string.h>
#include "file_handler.h"
#include <stdlib.h>
#include "message_handler.h"

/**
 * toggle_led() - Handle the process of writing to 'brightness' file.
 * @arg1: Status of the LED 1 = ON, 0 = 0FF
 *
 * Return: Error code on failure, otherwise 0.
 */
int toggle_led(int status)
{
	int rt		      = 0;
	FILE *brightness_file = NULL;
	brightness_file	      = fopen("/sys/class/leds/input6::capslock/brightness", "w");

	if (brightness_file == NULL) {
		return ERROR_FILE_OPEN;
	} else {
		fprintf(brightness_file, "%d", status);
		rt = fclose(brightness_file);
		if (rt != 0) {
			return ERROR_FILE_CLOSE;
		}
	}
	return rt;
}

/**
 * read_memory() - Handle the process of reading free memory from 'meminfo' file.
 * @arg1: File path
 *
 * Return: Error code on failure, otherwise free memory as an integer.
 */
int read_memory(char *path)
{
	int mem_free = 0;
	char line[400];
	char *token;
	int file_rt;
	FILE *meminfo_file = NULL;
	meminfo_file	   = fopen(path, "r");
	while (fgets(line, sizeof(line), meminfo_file)) {
		char *ptr = strstr(line, "MemFree");
		if (ptr != NULL) {
			token	 = strtok(ptr, ":");
			token	 = strtok(NULL, " ");
			mem_free = strtol(token, NULL, 10);
			file_rt	 = fclose(meminfo_file);
			if (file_rt != 0) {
				log_message(ERROR_FILE_CLOSE, path);
			}
			return mem_free;
		}
	}
	file_rt = fclose(meminfo_file);
	if (file_rt != 0) {
		log_message(ERROR_FILE_CLOSE, path);
	}
	return mem_free;
}