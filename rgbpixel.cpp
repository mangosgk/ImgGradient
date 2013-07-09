#include "rgbpixel.h"

/**
 * @brief RGBPixel constructor. Constructs a white RGB pixel (255, 255, 255).
 */
RGBPixel::RGBPixel() :
    mR( 255 ), mG( 255 ), mB( 255 )
{
}

/**
 * @brief RGBPixel constructor. Constructs an RGB pixel with specified component values.
 * @param [in]  r   The R color component (0-255).
 * @param [in]  g   The G color component (0-255).
 * @param [in]  b   The B color component (0-255).
 */
RGBPixel::RGBPixel(int r, int g, int b) :
    mR( r ), mG( g ), mB( b )
{
}

/**
 * @brief Sets the R, G and B components of this object.
 * @param [in]  r   The R color component (0-255).
 * @param [in]  g   The G color component (0-255).
 * @param [in]  b   The B color component (0-255).
 */
void RGBPixel::setRGB( int r, int g, int b )
{
    mR = r;
    mG = g;
    mB = b;
}

/**
 * @brief Converts the RGB colorspace to HSV and returns only the "lightness" component.
 * @return The "lightness" component in HSV colorspace.
 */
double RGBPixel::lightness()
{
    // L = 1/2 * (M+m), whereas:
    // M = max(R, G, B) and
    // m = min(R, G, B)
    int M = mR;
    if( mR >= mG && mR >= mB ) M = mR;
    if( mG >= mR && mG >= mB ) M = mG;
    if( mB >= mR && mB >= mG ) M = mB;

    int m = mR;
    if( mR <= mG && mR <= mB ) m = mR;
    if( mG <= mR && mG <= mB ) m = mG;
    if( mB <= mR && mB <= mG ) m = mB;

    double L = 0.5 * ( M + m );
    return L;
}

/**
 * @brief Converts the RGB colorspace to HSV and returns only the "value" component.
 * @return The "value" component in HSV colorspace.
 */
double RGBPixel::value()
{
    // V = M, whereas:
    // M = max(R, G, B)
    int M = mR;
    if( mR >= mG && mR >= mB ) M = mR;
    if( mG >= mR && mG >= mB ) M = mG;
    if( mB >= mR && mB >= mG ) M = mB;
    return M;
}

/**
 * @brief Getter for the R color component (0-255).
 * @return
 */
int RGBPixel::r()
{
    return mR;
}

/**
 * @brief Getter for the G color component (0-255).
 * @return
 */
int RGBPixel::g()
{
    return mG;
}

/**
 * @brief Getter for the B color component (0-255).
 * @return
 */
int RGBPixel::b()
{
    return mB;
}
