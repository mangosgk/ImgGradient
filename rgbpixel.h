#ifndef RGBPIXEL_H
#define RGBPIXEL_H

#include <vector>

/**
 * @brief uint8 is another alias for unsigned char.
 */
typedef unsigned char uint8;

/**
 * @brief The RGBPixel class represents a pixel data of an image.
 *        As the name suggests, the colorspace used by this class is RGB.
 * @author Mango
 * @date June 2013
 */
class RGBPixel
{
public: /* methods */
    /**
     * @brief RGBPixel constructor. Constructs a white RGB pixel (255, 255, 255).
     */
    RGBPixel();

    /**
     * @brief RGBPixel constructor. Constructs an RGB pixel with specified component values.
     * @param [in]  r   The R color component (0-255).
     * @param [in]  g   The G color component (0-255).
     * @param [in]  b   The B color component (0-255).
     */
    RGBPixel( uint8 r, uint8 g, uint8 b );

    /**
     * @brief Sets the R, G and B components of this object.
     * @param [in]  r   The R color component (0-255).
     * @param [in]  g   The G color component (0-255).
     * @param [in]  b   The B color component (0-255).
     */
    void setRGB( uint8 r, uint8 g, uint8 b );

    /**
     * @brief Getter for the R color component (0-255).
     * @return
     */
    uint8 r();

    /**
     * @brief Getter for the G color component (0-255).
     * @return
     */
    uint8 g();

    /**
     * @brief Getter for the B color component (0-255).
     * @return
     */
    uint8 b();

    /**
     * @brief Converts the RGB colorspace to HSV and returns only the "lightness" component.
     * @return The "lightness" component in HSV colorspace.
     */
    double lightness();

    /**
     * @brief Converts the RGB colorspace to HSV and returns only the "value" component.
     * @return The "value" component in HSV colorspace.
     */
    double value();

private: /* member variables */
    /**
     * @brief The R (red) component.
     */
    uint8 mR;

    /**
     * @brief The G (green) component.
     */
    uint8 mG;

    /**
     * @brief The B (blue) component.
     */
    uint8 mB;
};

#endif // RGBPIXEL_H
