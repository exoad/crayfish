#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "public.h"

#define BUFFER_SIZE (512)

U0 skipWhiteSpace(I8** ptr)
{
    while(isspace((U8) **ptr) && **ptr != '\0')
    {
        (*ptr)++;
    }
}

WorldMap* readMapFromFile(const I8* file)
{
    FILE* fileObj = fopen(file, "r");
    if(!fileObj)
    {
        printerr("%s", "Unable to open map file");
        return null;
    }
    WorldMap* map = malloc(sizeof(WorldMap));
    if(map == null)
    {
        printerr("Failed to malloc memory for world map object with file %s", file);
        fclose(fileObj);
        return null;
    }
    map->data = null;
    map->width = -1;
    map->height = -1;
    I8 buffer[BUFFER_SIZE];
    I32 lineNum = 1;
    while(fgets(buffer, sizeof(buffer), fileObj))
    {
        I8* line = buffer;
        skipWhiteSpace(&line);
        if(*line != '#' && *line != '\n')
        {
            I8 commandBuffer[32];
            if(sscanf(line, "%31s", commandBuffer) == 1)
            {
                line += strlen(commandBuffer);
                skipWhiteSpace(&line);
                if(strcmp(commandBuffer, "MapHeight") == 0)
                {
                    map->height = strtol(line, null, 10);
                }
                else if(strcmp(commandBuffer, "MapWidth") == 0)
                {
                    map->width = strtol(line, null, 10);
                }
            }
        }
        lineNum++;
    }
    return map;
}
