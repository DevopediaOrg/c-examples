/*
Read 24-bit BMP image and output the same as ASCII art.
For BMP format, see https://upload.wikimedia.org/wikipedia/commons/7/75/BMPfileFormat.svg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short type;       // Magic identifier: "BM"
    unsigned int   size;       // File size
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int   offset;     // Offset to point to pixel data
} BMPHeader;

typedef struct {
    unsigned int   size;           // Header size
    int            width;          // Image width
    int            height;         // Image height
    unsigned short planes;
    unsigned short bits_per_pixel; // Should be 24 for RGB
    unsigned int   compression;
    unsigned int   image_size;
    int            x_pixels_per_meter;
    int            y_pixels_per_meter;
    unsigned int   colors_used;
    unsigned int   colors_important;
    // TODO: handle other header fields that follow
} BMPInfoHeader;
#pragma pack(pop)

typedef enum {
    SUCCESS = 0,
    ERR_WRONG_ARGS,
    ERR_INPUT_READ,
    ERR_OUTPUT_WRITE,
    ERR_BAD_HEADER,
    ERR_MALLOC
} ErrCode;

// ASCII palette ordered from darkest visual density to brightest
// This is meant for a device or app set in a dark theme
// The following 15-char set works well but you may
// try other sets or even increase/decrease the number of characters
const char ASCII_PALETTE[] = " .:-=+*xX#%&W@$";
//const char ASCII_PALETTE[] = " .:-=+*#%@";
const int PALETTE_SIZE = strlen(ASCII_PALETTE);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: expecting exactly 1 program argument, the BMP filename to process. Quitting...\n");
        return ERR_WRONG_ARGS;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("Error: Could not open input file %s. Quitting...\n", argv[1]);
        return ERR_INPUT_READ;
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;

    fread(&header, sizeof(BMPHeader), 1, file);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // Verify it's a valid 24-bit uncompressed BMP
    // chars BM = 0x4D42 in ASCII
    if (header.type != 0x4D42 || infoHeader.bits_per_pixel != 24) {
        printf("Error: App appears not to be a valid 24-bit BMP image.\n");
        fclose(file);
        return ERR_BAD_HEADER;
    }

    // Jump straight to where the pixel array begins

    int width = infoHeader.width;
    int height = infoHeader.height;

    // BMP rows are padded to multiples of 4 bytes in memory
    int padding = (4 - (width * 3) % 4) % 4;

    unsigned char *grid = malloc(height * width * sizeof(unsigned char));
    if (!grid) {
        printf("Memory allocation failed!\n");
        return ERR_MALLOC;
    }

    // Read the pixels and convert to
    fseek(file, header.offset, SEEK_SET); // jump to where pixels start
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            unsigned char b = fgetc(file);
            unsigned char g = fgetc(file);
            unsigned char r_val = fgetc(file);

            // Convert RGB to a single grayscale/brightness value
            unsigned char luminance = (0.2126 * r_val) + (0.7152 * g) + (0.0722 * b);
            grid[r*width+c] = luminance;
        }
        // Skip over the row padding bytes
        for (int p = 0; p < padding; p++) {
            fgetc(file);
        }
    }
    fclose(file);

    // Assemble outfile filename: replace .bmp with .txt
    char outfile[255];
    int count = strlen(argv[1]) - 4; // ignore trailing .bmp
    strncpy(outfile, argv[1], count);
    strncpy(outfile + count, ".txt", 4);
    outfile[count+4] = '\0';

    FILE *fp = fopen(outfile, "w");
    if (!fp) {
        printf("Error: Could not open output file %s. Quitting...\n", outfile);
        return ERR_OUTPUT_WRITE;
    }

    // Print the ASCII Art: BMP is stored bottom row first
    for (int r = height-1; r >= 0; r--) {
        for (int c = 0; c < width; c++) {
            unsigned char brightness = grid[r*width+c];
            
            // Map 0-255 scaling down to our 0-9 palette array index
            int palette_index = (brightness * (PALETTE_SIZE - 1)) / 255;
            
            // Print the mapped character twice! 
            // Consoles have tall, skinny fonts. Printing twice keeps the image's aspect ratio squarish.
            fprintf(fp, "%c%c", ASCII_PALETTE[palette_index], ASCII_PALETTE[palette_index]);
        }
        fprintf(fp, "\n");
    }

    // Clean up memory allocation
    free(grid);

    return SUCCESS;
}