#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    BYTE buffer[512];
    int BLOCK_SIZE = 512;
    int jpg_counter = 0;
    if (argc != 2)
    {
        printf("Provide one forensic image\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }
    char* filename = malloc(8);
    // read 512 bytes into a buffer
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If First JPEG
            sprintf(filename, "%03i.jpg", jpg_counter);
            FILE *img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, img);
            fclose(img);
            jpg_counter ++;
        }
        // If not start of JPEG
        else
        {
            sprintf(filename, "%03i.jpg", (jpg_counter - 1));
            FILE *img = fopen(filename, "a");
            fwrite(buffer, sizeof(BYTE), 512, img);
            fclose(img);
        }
    }
    //Close any remaining files and free memory
    free(filename);
    fclose(raw_file);
    return 0;
}
