/*
 * Ref : cJSON/cJSON/README.md
 */

/* Config this file */
#define USING_LIB_DRAMALIFE	1

/* Headers */
#ifdef USING_LIB_DRAMALIFE
#include "lib_dramalife.h"
#else
#include "cJSON.h"
#endif


/* Macros */
#define FINAL_SHOW	\
	"*********************************\n " \
	"{\n "\
	"    \"name\": \"Awesome 4K\",\n "\
	"    \"resolutions\": [\n "\
	"        {\n "\
	"            \"width\": 1280,\n "\
	"            \"height\": 720\n "\
	"        },\n "\
	"        {\n "\
	"            \"width\": 1920,\n "\
	"            \"height\": 1080\n "\
	"        },\n "\
	"        {\n "\
	"            \"width\": 3840,\n "\
	"            \"height\": 2160\n "\
	"        }\n "\
	"    ]\n "\
	"}\n"\
	"*********************************\n"
#if 0
*********************************
* {
*     "name": "Awesome 4K",
*     "resolutions": [
*         {
*             "width": 1280,
*             "height": 720
*         },
*         {
*             "width": 1920,
*             "height": 1080
*         },
*         {
*             "width": 3840,
*             "height": 2160
*         }
*     ]
* }
*********************************
#endif



char *add_info_to_object(cJSON *argm)
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char *string = NULL;
    cJSON *name = NULL;
    cJSON *resolutions = NULL;
    cJSON *resolution = NULL;
    cJSON *width = NULL;
    cJSON *height = NULL;
    size_t index = 0;

    if (argm == NULL)
    {
        goto end;
    }

    name = cJSON_CreateString("Awesome 4K");
    if (name == NULL)
    {
        goto end;
    }

    cJSON_AddItemToObject(argm, "name", name);

    resolutions = cJSON_CreateArray();
    if (resolutions == NULL)
    {
        goto end;
    }
    cJSON_AddItemToObject(argm, "resolutions", resolutions);

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
        resolution = cJSON_CreateObject();
        if (resolution == NULL)
        {
            goto end;
        }
        cJSON_AddItemToArray(resolutions, resolution);

        width = cJSON_CreateNumber(resolution_numbers[index][0]);
        if (width == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "width", width);

        height = cJSON_CreateNumber(resolution_numbers[index][1]);
        if (height == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "height", height);
    }


end:
    return string;
}

void dl_cjson_print(cJSON *argm)
{
	char *string = cJSON_Print(argm);
	printf("********\n%s\n********\n", string?string:"null");
	free(string); // !!!
}

int main(void)//int argc, char **argv)
{
	printf("%s\n", FINAL_SHOW);

	// Init
	cJSON *monitor = cJSON_CreateObject();

	// Add
	add_info_to_object(monitor);

	// Print
	dl_cjson_print(monitor);

	// Parse
	#if 1
	cJSON * test_json;
	char *string = cJSON_Print(monitor);
	printf("********\n%s\n********\n", string?string:"null");
	test_json=cJSON_Parse(string);
	cJSON * testitem_json=cJSON_GetObjectItem(test_json,"name");
	while (testitem_json->next!=NULL)
	{
		printf("%s,%s\n",testitem_json->string, testitem_json->valuestring);
		testitem_json=testitem_json->next;
	}

	free(string); // !!!
	#endif
	#if 1
	const char *str2parse="{\"type\":\"tttttt\",\"data\":{\"item\":\"111111\"}}";
	cJSON *json = cJSON_Parse(str2parse);
	cJSON *loop = cJSON_GetObjectItem(json, "type");
	while(loop){
	    printf("Item: %s,%s\n",loop->string, loop->valuestring);
	    loop=loop->next;
	}
	#endif

	// Clean
	cJSON_Delete(monitor);

	return 0;
}

