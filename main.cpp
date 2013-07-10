/* -------------------------------------------------------------------------------------------------
 * main.cpp
 * Author   : mango
 * Date     : June 2013
 * ------------------------------------------------------------------------------------------------- */

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "image.h"

/* -------------------------------------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------------------------------------- */
Image* radialize( std::vector< RGBPixel* >* pixels, int w, int h );
bool lightnessSorter( RGBPixel* px1, RGBPixel* px2 );
bool valueSorter( RGBPixel* px1, RGBPixel* px2 );

/* -------------------------------------------------------------------------------------------------
 * The main program.
 *
 * Usage: ./ImgGradient <input.jpg> <output.jpg> <lightness or value>
 * This program will only accept jpg files only.
 * Parameter "lightness" will sort the pixels by lightness and "value" will sort
 * the pixels by value.
 * ------------------------------------------------------------------------------------------------- */
int main( int argc, char* argv[] )
{
    // Check the number of arguments, wich should be at least 4. Otherwise, print the command line usage.
    // Exit program on invalid number of parameters.
    if( argc < 4 ) {
        std::cout << "Invalid number of parameters" << std::endl;
        std::cout << "Usage: " << argv[ 0 ] << " <input.jpg> <output.jpg> <lightness|value>" << std::endl;
        return 2;
    }

    // Read the input jpg file into an Image object.
    // WARNING: No runtime check whether the input file is a valid jpg file or not.
    //          Extend this line if necessary.
    Image* im = Image::fromJPG( argv[ 1 ] );

    // "Flatten" pixels in 1-dimensional array and sort them based on lightness or value
    // Depending on the supplied last command line parameter.
    // Exit program if the parameter is not valid.
    std::vector< RGBPixel* >* flatPixels = Image::flatten( im );
    if( std::string( argv[ 3 ] ).compare( "lightness" ) )  {
        std::sort( flatPixels->begin(), flatPixels->end(), lightnessSorter );
    }
    else if( std::string( argv[ 3 ] ).compare( "value" ) ) {
        std::sort( flatPixels->begin(), flatPixels->end(), valueSorter );
    }
    else {
        std::cout << "Unknown sorting parameter: " << argv[ 3 ] << std::endl;
        return 2;
    }

    // "Radialize" pixels and save to jpg.
    // WARNING: Output file name is not checked at all. Extend if necessary.
    Image* rad = radialize( flatPixels, im->width(), im->height() );
    Image::toJPG( rad, argv[ 2 ] );

    // Free up used memory blocks.
    delete im;
    delete flatPixels;
    delete rad;
    return 0;
}

/* -------------------------------------------------------------------------------------------------
 * Walk from the middle of the image to the right, bottom, left, up while coloring
 * each pixel and repeats such movement step until all image pixels are colored.
 *
 * [in] pixels  Input pixel data, which is a 1D RGBPixel array.
 *              Because of the number of components in the RGB colorspace,
 *              the size of this array should be image width * image height * 3.
 * [in] w       Image width.
 * [in] h       Image height.
 *
 * Returns a new image object.
 * ------------------------------------------------------------------------------------------------- */
Image* radialize( std::vector< RGBPixel* >* pixels, int w, int h )
{
    // -------------------------------------------------------------------------------------------------
    // Define the directions first. Basically the radial movement is:
    //                           RIGHT -> DOWN -> LEFT -> UP -> repeat.
    //
    // We define the first direction is RIGHT and the movement step is 0, which will be incremented
    // AFTER each DOWN and UP steps.
    //
    // Movement example (5 x 5) pixels:
    //
    // Empty          0 step         1 step RIGHT   1 step DOWN    2 steps LEFT   2 steps UP     3 steps RIGHT
    // pixels         (step = 0)     (step = 1)     (step = 1)     (step = 2)     (step = 2)     (step = 3)
    // . . . . .      . . . . .      . . . . .      . . . . .      . . . . .      . . . . .      . . . . .
    // . . . . .      . . . . .      . . . . .      . . . . .      . . . . .      . 6 . . .      . 6 7 8 9
    // . . . . .  ->  . . 0 . .  ->  . . 0 1 .  ->  . . 0 1 .  ->  . . 0 1 .  ->  . 5 0 1 .  ->  . 5 0 1 .  ->  and so on..
    // . . . . .      . . . . .      . . . . .      . . . 2 .      . 4 3 2 .      . 4 3 2 .      . 4 3 2 .
    // . . . . .      . . . . .      . . . . .      . . . . .      . . . . .      . . . . .      . . . . .
    //
    // -------------------------------------------------------------------------------------------------
    enum directions { RIGHT, DOWN, LEFT, UP };
    directions dir = RIGHT;
    int steps = 0;

    // Start position is in the middle of the canvas
    Image* im = new Image( w, h );
    int x = (int) floor( w / 2.0 );
    int y = (int) floor( h / 2.0 );

    // Color the first pixel with the first color is pixel std::vector
    im->setPixel( pixels->back(), x, y );
    pixels->pop_back();

    // Begin the radial loop. Loop and color pixels as long as there are
    // still pixels available in the pixel std::vector.
    while( pixels->size() ) {
        // Walk to the directions for n steps
        for( int i = 0 ; i < steps ; i++ ) {
            // Set the x and y position based on the direction.
            if      ( dir == RIGHT  )  x++;
            else if ( dir == DOWN   )  y++;
            else if ( dir == LEFT   )  x--;
            else if ( dir == UP     )  y--;

            // If setPixel returns false, then the (x, y) coordinate is out of bounds.
            // Do not color the pixel if this position is out of bounds.
            // Otherwise, remove the last pixel element from the list because we have
            // used this pixel data to color the pixel in position (x, y).
            if( pixels->size() && im->setPixel( pixels->back(), x, y ) ) {
                pixels->pop_back();
            }
        }

        // If after going down or going up, the number of steps should be incremented.
        if( dir == DOWN || dir == UP ) steps++;

        // Change direction: RIGHT -> DOWN -> LEFT -> UP -> repeat.
        if      ( dir == RIGHT  ) dir = DOWN;
        else if ( dir == DOWN   ) dir = LEFT;
        else if ( dir == LEFT   ) dir = UP;
        else if ( dir == UP     ) dir = RIGHT;
    }

    return im;
}

/* -------------------------------------------------------------------------------------------------
 * A comparison function to sort two RGBPixel objects by lightness component in HSL colorspace.
 * This custom function is used by std::sort() function.
 *
 * [in] px1     First pixel.
 * [in] px2     Second pixel.
 *
 * Returns true if px1's lightness is less than px2's.
 * ------------------------------------------------------------------------------------------------- */
bool lightnessSorter( RGBPixel* px1, RGBPixel* px2 )
{
    return px1->lightness() < px2->lightness();
}

/* -------------------------------------------------------------------------------------------------
 * A comparison function to sort two RGBPixel objects by value component in HSV colorspace.
 * This custom function is used by std::sort() function.
 *
 * [in] px1     First pixel.
 * [in] px2     Second pixel.
 *
 * Returns true if px1's value is less than px2's.
 * ------------------------------------------------------------------------------------------------- */
bool valueSorter( RGBPixel* px1, RGBPixel* px2)
{
    return px1->value() < px2->value();
}

