#include "answer07.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>

/**
 * Loads a bmp (windows bitmap) image, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Note: This function is written for you and appears in image-bmp.c
 */

/**
 * Loads an ECE264 image file, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
Image * Image_load(const char * filename)
{
  FILE *fptr = fopen(filename, "r"); 
  size_t read;
  ImageHeader header; 
  uint32_t size;
  uint32_t one = 1;
  int err = 0;
  Image * tmp_im;
  Image * image;
  size_t h ;
  size_t w; 
  size_t length;
  if( fptr == NULL) 
    {
      return NULL;  
    }
  
   read =  fread(&header, sizeof(ImageHeader), 1, fptr); 
   size = header.width * header.height;   
   if( read != 1) 
    { 
       fprintf(stderr, "Failed to read header from '%s'\n", filename);
       err = 1;    
       fclose(fptr);
       return NULL;
    } 
   if(header.magic_number != ECE264_IMAGE_MAGIC_NUMBER) 
   {  
      err = 1;
      fclose(fptr);
      return NULL; 
   } 
   if(size == 0 || size > 1000000000) 
   { 
     err = 1;
     fclose(fptr);
     return NULL;
   } 
   if((header.comment_len > 10000000) || (header.comment_len == 0)) 
   { 
     err = 1; 
     fclose(fptr);
     return NULL;
   } 
    if(!err) 
{
    if(!err) { // Allocate Image struct
	tmp_im = malloc(sizeof(Image));			
	if(tmp_im == NULL) {
	  fclose(fptr);
	    fprintf(stderr, "Failed to allocate im structure\n");
	    err = 1;
	} 
    }
     if(!err) 
      { // Init the Image struct
	tmp_im->width = header.width;
	tmp_im->height = header.height;
        tmp_im->comment = malloc(sizeof(char ) * header.comment_len);
        tmp_im->data = malloc(sizeof(uint8_t) * header.height * header.width);
	if((tmp_im -> data == NULL)|| tmp_im -> comment == NULL) 
        { 
	  fclose(fptr);
          Image_free(tmp_im);
            err = 1;
            return NULL; 
        }
        // Handle the comment
        if(!err)
	  {
	    h = header.height; 
	    w = header.width;
	    length = header.comment_len;
	    read = fread(tmp_im->comment, sizeof(char), header.comment_len, fptr);
	    if(read != header.comment_len) 
	      {
		fclose(fptr);
		Image_free(tmp_im);
		err = 1;
		return NULL; 
	      }
	    if(tmp_im->comment[header.comment_len -one] != '\0')
	      { 
		 fclose(fptr);
		 Image_free(tmp_im);
		 err = 1;
		 return NULL; 
	      }
	    if((tmp_im -> comment) == NULL)
	      {
		fclose(fptr);
		 Image_free(tmp_im);
		 err = 1;
		 return NULL; 
	      }
	    // Handle image data
	    read = fread(tmp_im->data,sizeof(uint8_t), header.width*header.height,fptr);
	    if(read != (header.height * header.width)) 
	      {
		fclose(fptr);
		 Image_free(tmp_im);
		 err = 1;
		 return NULL;
	      }
            char * byte;
	    if(fread(&byte,sizeof(uint8_t),1,fptr) != 0)
	      { 
		fclose(fptr);
		 Image_free(tmp_im);
		 err = 1;
		 return NULL;
	      }
	  }
      }
 }
    
    if(err != 1) 
    {
      return tmp_im;
    } 
    Image_free(tmp_im);
    return NULL;
}
/**
 * Save an image to the passed filename, in ECE264 format.
 * Return TRUE if this succeeds, or FALSE if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
int Image_save(const char * filename, Image * image)
{
  FILE *fptr = NULL; 
  fptr = fopen(filename,"w");
  if(fptr == NULL) 
    { 
      return 0; 
    }

  ImageHeader header;
  header.width = image->width; 
  header.height = image ->height; 
  header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
  header.comment_len = strlen(image ->comment) + 1;
  
  
  if(fwrite(&(header),sizeof(ImageHeader),1,fptr) !=1) 
    {
      fclose(fptr);
      return 0; 
    }
   if(fwrite((image->comment),sizeof(char),header.comment_len,fptr) !=header.comment_len) 
    {
      fclose(fptr);
      return 0; 
    }
  if(fwrite(image -> data, sizeof(uint8_t), image->height * image -> width,fptr) != (image->height * image -> width))
    {
      fclose(fptr);
      return 0;
    }
  fclose(fptr);
  return 1; 
}
/**
 * Free memory for an image structure
 *
 * Image_load(...) (above) allocates memory for an image structure. 
 * This function must clean up any allocated resources. If image is 
 * NULL, then it does nothing. (There should be no error message.) If 
 * you do not write this function correctly, then valgrind will 
 * report an error. 
 */
void Image_free(Image * image)
{
  if(image != NULL)
    {
      free(image -> data) ; 
      free(image -> comment); 
      free(image);
    }
}
/**
 * Performs linear normalization, see README
 */
void linearNormalization(int width, int height, uint8_t * intensity)
{

  int min = intensity[0]; 
  int max = intensity[0];
  int pxl;  
 for(pxl = 0; pxl < width * height; pxl++) 
    {  
	  if(intensity[pxl] < min) 
	    min =intensity[pxl];
	  if(intensity[pxl] > max) 
	    max = intensity[pxl];
    }
 pxl = 0; 
 for(pxl = 0; pxl < height*width; pxl++) 
   {
     intensity[pxl] = (intensity[pxl] - min) * 255/ (max-min);
   }  
}