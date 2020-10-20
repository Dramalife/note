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



//create a monitor with a list of supported resolutions
//NOTE: Returns a heap allocated string, you are required to free it after use.
char *create_monitor(void)
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

    cJSON *monitor = cJSON_CreateObject();
    if (monitor == NULL)
    {
        goto end;
    }

    name = cJSON_CreateString("Awesome 4K");
    if (name == NULL)
    {
        goto end;
    }
    /* after creation was successful, immediately add it to the monitor,
     * thereby transferring ownership of the pointer to it */
    cJSON_AddItemToObject(monitor, "name", name);

    resolutions = cJSON_CreateArray();
    if (resolutions == NULL)
    {
        goto end;
    }
    cJSON_AddItemToObject(monitor, "resolutions", resolutions);

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

    string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
    return string;
}

int main(void)//int argc, char **argv)
{
	printf("%s\n", FINAL_SHOW);

	// Add & Print
	printf("%s \n", create_monitor());

	return 0;
}

