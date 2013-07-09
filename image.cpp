#include "image.h"

/**
 * @brief Image constructor. Constructs a blank image with specified width and height.
 * @param [in]  width   Image width.
 * @param [in]  height  Image height.
 */
Image::Image( int width, int height ) :
    mData( new RGBPixelData ), mWidth( width ), mHeight( height )
{
    int i = 0;
    // Set each pixel data with default RGBPixel objects.
    for( int y = 0 ; y < height ; y++ ) {
        mData->push_back( std::vector<RGBPixel*>() );
        for( int x = 0 ; x < width ; x++ ) {
            mData->at( y ).push_back( new RGBPixel() );
            i++;
        }
    }
}

/**
 * @brief Image constructor. Constructs an image with specified pixel data, width and height.
 * @param [in]  im      Image pixel data.
 * @param [in]  width   Image width.
 * @param [in]  height  Image height.
 */
Image::Image( uint8 *im, int width, int height ) :
    mData( new RGBPixelData ), mWidth( width ), mHeight( height )
{
    int i = 0;
    // Unsigned integer input 1D array holds width * height * 3 pixel data.
    // Put it in this images 2D pixel data array.
    for( int y = 0 ; y < height ; y++ ) {
        mData->push_back( std::vector< RGBPixel* >() );
        for( int x = 0 ; x < width ; x++ ) {
            RGBPixel* px = new RGBPixel( (int) im[ i   ],
                                         (int) im[ i+1 ],
                                         (int) im[ i+2 ] );
            mData->at( y ).push_back( px );
            i += 3;
        }
    }
}

/**
 * @brief Image constructor. Constructs an image with specified pixel data, width and height.
 * @param [in]  im      Image pixel data.
 * @param [in]  width   Image width.
 * @param [in]  height  Image height.
 */
Image::Image( std::vector< RGBPixel* >* im, int width, int height) :
    mData( new RGBPixelData ), mWidth( width ), mHeight( height )
{
    int i = 0;
    // 1D input list holds width * height * 3 pixel data.
    // Put it in this images 2D pixel data array.
    for( int y = 0 ; y < height ; y++ ) {
        mData->push_back( std::vector< RGBPixel* >() );
        for( int x = 0 ; x < width ; x++ ) {
            setPixel( im->at( i ), x, y );
            i++;
        }
    }
}

/* Destructor */
Image::~Image()
{
    // Release memory used by each pixel in this image.
    for( int y = 0 ; y < mHeight ; y++ ) {
        std::vector< RGBPixel* > row = mData->at( y );
        for( int x = 0 ; x < mWidth ; x++ ) {
            RGBPixel* px = row.at( x );
            if( px != 0 ) delete px;
        }
    }
    // Release memory used by the vector which holds the pixels.
    if( mData != 0 ) delete mData;
}

/**
 * @brief Tests whether a point is inside this image.
 * @param [in]  x       Value in x-axis.
 * @param [in]  y       Value in y-axis.
 * @return True if the input point is inside and false if it is outside of this image.
 */
bool Image::isInside( int x, int y )
{
    // A point is inside this image when it is inside this image's boundaries.
    return ( x >= 0 && x < mWidth && y >= 0 && y < mHeight );
}

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
bool Image::setPixel( RGBPixel* px, int x, int y )
{
    if( isInside( x, y ) ) {
        // Get the specified pixel data from this image and set its RGB components.
        RGBPixel* p = getPixel( x, y );
        p->setRGB( px->r(), px->g(), px->b() );
        return true;
    }
    return false;
}

/**
 * @brief Returns the pixel data of a specific position in this image.
 * @param [in]  x       Value in x-axis.
 * @param [in]  y       Value in y-axis.
 * @return Pixel data. If pixel position is invalid. This method will return a null pointer instead.
 * @see Image::isInside()
 * @see Image::setPixel()
 */
RGBPixel* Image::getPixel( int x, int y )
{
    if( isInside( x, y ) ) {
        // Get the specified pixel data from this image.
        RGBPixel* px = mData->at( y ).at( x );
        return px;
    }
    return 0;
}

/**
 * @brief Returns the 2D array of pixel data, which represents all pixels in this image.
 * @return The pixel data.
 */
RGBPixelData* Image::data()
{
    return mData;
}

/**
 * @brief Returns the width of this image.
 * @return The width of this image.
 */
int Image::width()
{
    return mWidth;
}

/**
 * @brief Returns the height of this image.
 * @return The height of this image.
 */
int Image::height()
{
    return mHeight;
}
