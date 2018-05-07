/*
 *Twesha Mitra
 *Project 1
 *Image Transformation
 *This program takes an image and an argument to either invert or turn the image into grayscale
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#pragma pack(1)

struct Header{
    char format_identifier[2];
    int file_size;
    short reserved_value1;
    short reserved_value2;
    int offset_pixel_array;
};

struct DIBHeader{
    int size;
    int width; //number of pixels per row
    int height; //number of rows 
    short num_color_panes;
    short num_bits_per_pixel;
    int compression_scheme;
    int image_size;
    int vertical_resolution;
    int horizontal_resolution;
    int num_colors_palette;
    int num_important_colors;
};

struct Pixel{
    unsigned char blue_intensity;
    unsigned char green_intensity;
    unsigned char red_intensity;
};

int main(int argc, char *argv[]){
    FILE *f;
    struct Header header;
    struct DIBHeader DIB_Header;
    struct Pixel pixel_array;
    int padding_bytes = 0;
    int bytes_per_row = 0;
    unsigned char pixel_inverted[3];
    float pixel_greyscale_float[3];
    unsigned char pixel_greyscale_char[3];
    int num_pixels_read = 0;
    float y;
    float check_value = 0.0031308;
    if(argv[1] == NULL){
        printf("Usage:  <-invert/-grayscale> <file name>\n");
        exit(1);
    }
    if(argv[2]==NULL){
        printf("File not found\n");
        exit(1);
    }
    f = fopen(argv[2], "r+b");
    
    fread(&header, sizeof(header), 1, f);
    if((strncmp((header.format_identifier), "BM",2)!=0)){
        printf("File type not supported\n");
        exit(1);
    }
    fread(&DIB_Header, sizeof(DIB_Header), 1, f);
    if(DIB_Header.size != 40){
        printf("File type not supported\n");
        exit(1);
    }
    if(DIB_Header.num_bits_per_pixel!=24){
        printf("File type not supported\n");
        exit(1);
    }

    //calculate padding for row
    bytes_per_row = (DIB_Header.width) * 3;
    while(bytes_per_row % 4 != 0 ){
        bytes_per_row++;
        padding_bytes++;
    }
    fseek(f, header.offset_pixel_array, SEEK_SET);
        if(strcasecmp(argv[1], "-invert")==0){
            while(fread(&pixel_array, sizeof(pixel_array),1,f)==1){
                pixel_inverted[0] = ~(pixel_array.blue_intensity);
                pixel_inverted[1] = ~(pixel_array.green_intensity);
                pixel_inverted[2] = ~(pixel_array.red_intensity);
                fseek(f, -3L, SEEK_CUR);
                fwrite(pixel_inverted, 3, 1, f);
                num_pixels_read++;
                if(num_pixels_read == DIB_Header.width){
                    num_pixels_read = 0;
                    fseek(f,padding_bytes,SEEK_CUR);
                }  
            }
        }
        else if(strcasecmp(argv[1], "-grayscale") ==0) {
            while(fread(&pixel_array, sizeof(pixel_array), 1, f) ==1){
                    pixel_greyscale_float[0] = (float)((pixel_array.blue_intensity)/255.0);
                    pixel_greyscale_float[1] = (float)((pixel_array.green_intensity)/255.0);
                    pixel_greyscale_float[2] = (float)((pixel_array.red_intensity)/255.0);
                    y = (0.2126 * pixel_greyscale_float[2]) + (0.7152 * pixel_greyscale_float[1]) + (0.0722 * pixel_greyscale_float[0]);
                
                    if( y <= check_value){
                        pixel_greyscale_float[0] =  12.92 * y;
                        pixel_greyscale_float[1] =  12.92 * y;
                        pixel_greyscale_float[2] =  12.92 * y;
                    }
                    else if(y > check_value){
                        pixel_greyscale_float[0] = (((1.055* pow(y, (1/2.4))) - 0.055) * 255);
                        pixel_greyscale_float[1] = (((1.055* pow(y, (1/2.4))) - 0.055) * 255);
                        pixel_greyscale_float[2] = (((1.055* pow(y, (1/2.4))) - 0.055) * 255);    
                    }
                    pixel_greyscale_char[0] = (char) pixel_greyscale_float[0];                    
                    pixel_greyscale_char[1] = (char) pixel_greyscale_float[0];
                    pixel_greyscale_char[2] = (char) pixel_greyscale_float[0];
                    fseek(f,-3L, SEEK_CUR);
                   fwrite(pixel_greyscale_char, 3,1,f);
                    num_pixels_read++;
                    if(num_pixels_read == DIB_Header.width){
                        num_pixels_read = 0;
                        fseek(f,padding_bytes,SEEK_CUR);
                    }  
            }
        }
        else {
            printf("Only invert and grayscale are supported\n");
            exit(1);
        }
}

