#ifndef RGBPIXEL_H
#define RGBPIXEL_H

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
    RGBPixel( int r, int g, int b );

    /**
     * @brief Sets the R, G and B components of this object.
     * @param [in]  r   The R color component (0-255).
     * @param [in]  g   The G color component (0-255).
     * @param [in]  b   The B color component (0-255).
     */
    void setRGB( int r, int g, int b );

    /**
     * @brief Getter for the R color component (0-255).
     * @return
     */
    int r();

    /**
     * @brief Getter for the G color component (0-255).
     * @return
     */
    int g();

    /**
     * @brief Getter for the B color component (0-255).
     * @return
     */
    int b();

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
    int mR;

    /**
     * @brief The G (green) component.
     */
    int mG;

    /**
     * @brief The B (blue) component.
     */
    int mB;
};

#endif // RGBPIXEL_H
