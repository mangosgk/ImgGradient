#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include "jpgd.h"
#include "jpge.h"
#include "rgbpixel.h"

/**
 * @brief RGBPixelData is a 2D array of RGBPixels. It represents pixels collection of an image.
 */
typedef std::vector< std::vector< RGBPixel* > > RGBPixelData;

/**
 * @brief uint8 is another alias for unsigned char.
 */
typedef unsigned char uint8;

/**
 * @brief The Image class represents an image which contains pixel data.
 * @author Mango
 * @date June 2013
 */
class Image
{
public: /* methods */
    /**
     * @brief Image constructor. Constructs a blank image with specified width and height.
     * @param [in]  width   Image width.
     * @param [in]  height  Image height.
     */
    Image( int width, int height );

    /**
     * @brief Image constructor. Constructs an image with specified pixel data, width and height.
     * @param [in]  im      Image pixel data.
     * @param [in]  width   Image width.
     * @param [in]  height  Image height.
     */
    Image( uint8 *im, int width, int height );

    /**
     * @brief Image constructor. Constructs an image with specified pixel data, width and height.
     * @param [in]  im      Image pixel data.
     * @param [in]  width   Image width.
     * @param [in]  height  Image height.
     */
    Image( std::vector< RGBPixel* > *im, int width, int height );

    /* Destructor */
    ~Image();

    /**
     * @brief Tests whether a point is inside this image.
     * @param [in]  x       Value in x-axis.
     * @param [in]  y       Value in y-axis.
     * @return True if the input point is inside and false if it is outside of this image.
     */
    bool isInside( int x, int y );

    /**
     * @brief Sets the pixel of a specific position in this image.
     * @param [in]  px      Image pixel data.
     * @param [in]  x       Value in x-axis.
     * @param [in]  y       Value in y-axis.
     * @return If specified pixel position is not ouf of bounds and the input pixel data is valid,
     *         this method will return true. Otherwise false.
     * @see Image::isInside()
     * @see Image::getPixel()
     */
    bool setPixel( RGBPixel *px, int x, int y );

    /**
     * @brief Returns the pixel data of a specific position in this image.
     * @param [in]  x       Value in x-axis.
     * @param [in]  y       Value in y-axis.
     * @return Pixel data. If pixel position is invalid. This method will return a null pointer instead.
     * @see Image::isInside()
     * @see Image::setPixel()
     */
    RGBPixel *getPixel( int x, int y );

    /**
     * @brief Returns the 2D array of pixel data, which represents all pixels in this image.
     * @return The pixel data.
     */
    RGBPixelData *data();

    /**
     * @brief Returns the width of this image.
     * @return The width of this image.
     */
    int width();

    /**
     * @brief Returns the height of this image.
     * @return The height of this image.
     */
    int height();

public: /* static methods */
    /**
     * @brief Reads a jpg file and returns a new image object.
     * @param [in]  filename    The jpg filename.
     * @return An image object containing pixel data.
     * @see Image::toJPG()
     */
    static Image* fromJPG( char* filename )
    {
        int w, h, comp;
        uint8* out = jpgd::decompress_jpeg_image_from_file( filename, &w, &h, &comp, 3 );
        return new Image( out, w, h );
    }

    /**
     * @brief Writes a jpg file from an image object.
     * @param [in]  im          The image object.
     * @param [out] filename    Output filename.
     * @return True on write success, otherwise false.
     * @see Image::fromJPG()
     */
    static bool toJPG( Image* im, char* filename )
    {
        int w = im->width();
        int h = im->height();
        int i = 0;

        // Loops each columns and rows of an image and put the pixel data into a
        // 1D unsigned integer array. The size of the array is width * height * 3
        // because each pixel holds 3 color components (RGB).
        uint8* in = new uint8[ w * h * 3 ];
        for( int y = 0 ; y < h ; y++ ) {
            for( int x = 0 ; x < w ; x++ ) {
                RGBPixel* px = im->getPixel( x, y );
                in[ i   ] = px->r();
                in[ i+1 ] = px->g();
                in[ i+2 ] = px->b();
                i += 3;
            }
        }
        return jpge::compress_image_to_jpeg_file( filename, w, h, 3, in );
    }

private: /* member variables */
    /**
     * @brief Image width.
     */
    int mWidth;

    /**
     * @brief Image Height.
     */
    int mHeight;

    /**
     * @brief Image pixel data.
     */
    RGBPixelData *mData;
};

#endif // IMAGE_H
