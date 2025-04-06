#include<stdio.h>
#include<curl/curl.h>
#include<string.h>
#include<stdlib.h>

//parsing constants
#define TEMP_LEN 7
#define HUMI_LEN 3
#define TMIN_LEN 7
#define TMAX_LEN 7
#define DATA_OFFSET 2
#define ABS_TEMP 273.15

struct ReturnData {
	char* res;
	size_t size;
};

struct ParsedData {
	float temp;
	float temp_min;
	float temp_max;
	float humidity;
};

static size_t WriteCallback(void* chunk, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct ReturnData *ret = (struct ReturnData *)userp;
	
	//re allocate memory to add the new data chunk
	ret->res = (char*)realloc(ret->res, ret->size + realsize + 1);
	if(ret->res == NULL) {
		printf("Out of memory!\n");
		return 0;
	}
	
	//copy the new data into the struct
	memcpy(&(ret->res[ret->size]), chunk, realsize);
	ret->size += realsize;
	ret->res[ret->size] = 0;
	
	return realsize;
}

struct ParsedData Parser (char* str) {
		struct ParsedData ret;
		
		if (str == NULL) {
			ret.temp = 0.0;
			ret.temp_max = 0.0;
			ret.temp_min = 0.0;
			ret.humidity = 0.0;
			return ret;
		}
		
		char *temp_offset; 
		char temp_str[TEMP_LEN] = {0};
		char temp_min_str[TMIN_LEN] = {0};
		char temp_max_str[TMAX_LEN] = {0};
		char humidity_str[HUMI_LEN] = {0};
		
		temp_offset = strstr(str, "temp") + strlen("temp") + DATA_OFFSET;
		for (int i = 0; i < TEMP_LEN - 1; ++i) {
				if(*(temp_offset + i) == ',') break;
				temp_str[i] = *(temp_offset + i);
		}
		
		temp_offset = strstr(str, "temp_min") + strlen("temp_min") + DATA_OFFSET;
		for (int i = 0; i < TMIN_LEN - 1; ++i) {
				if(*(temp_offset + i) == ',') break;
				temp_min_str[i] = *(temp_offset + i);
		}
		
		temp_offset = strstr(str, "temp_max") + strlen("temp_max") + DATA_OFFSET;
		for (int i = 0; i < TMAX_LEN - 1; ++i) {
				if(*(temp_offset + i) == ',') break;
				temp_max_str[i] = *(temp_offset + i);
		}
		
		temp_offset = strstr(str, "humidity") + strlen("humidity") + DATA_OFFSET;
		for (int i = 0; i < HUMI_LEN - 1; ++i) {
				if(*(temp_offset + i) == ',') break;
				humidity_str[i] = *(temp_offset + i);
		}
		
		ret.temp = atof(temp_str) - ABS_TEMP;
		ret.temp_max = atof(temp_max_str) - ABS_TEMP;
		ret.temp_min = atof(temp_min_str) - ABS_TEMP;
		ret.humidity = atof(humidity_str);
		
		return ret;
}



int main(void) {
	CURL *curl;
	CURLcode res;
	
	struct ReturnData chunk;
	struct ParsedData data;
	
	//memory will be added by the callback
	chunk.res = (char*)malloc(1);
	chunk.size = 0;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "api.openweathermap.org/data/2.5/weather?lat=37&lon=127&appid=f44f4c06e39d29b08955f712c9f8d25b");
		//In case of redirection, follow it
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		//register callback
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
		
		//request
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "Request Failed: %s \n", curl_easy_strerror(res));
		}
		else {
			printf("Returned data:\n %s\n", chunk.res);
			data = Parser(chunk.res);
			printf("Current Temperature: %.2f degrees\n", data.temp);
			printf("Maximum Temperature: %.2f degrees\n", data.temp_max);
			printf("Minimum Temperature: %.2f degrees\n", data.temp_min);
			printf("Humidity: %.2f\n", data.humidity);
		}
		//cleanup
		curl_easy_cleanup(curl);
	}
	
	curl_global_cleanup();
	return 0;
}

