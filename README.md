# Stickerbox

This bit of code controls LEDs on a Stickerbox.

The Stickerbox has some LED-Stripes taped to it on which some animations are
shown. Each animation is shown for 1000 frames after which a new animation is chosen from the available ones.

## Contribute

Aside from bug fixing or creating new features, which would be possible everywhere,
one way to contribute is to add new animations. Before doing so some info might
be relevant.

### Relevant Data Structures

Some stuff you probably should know.

#### The RGB-Struct
All colors are stored using a Struct called RGB which looks like this

```c++
struct RGB {
  byte r;
  byte g;
  byte b;
};
```

#### Useful Constants

The **modeutil.h** file sets a bunch of useful constants such as the number of
led-strips, the number of leds per stripe, the number of frames per animation
and a lot more.

All these are avaliable to your animation-function.

#### Utility function

There are a bunch of utility functions in the **modeutil.h** which any animation
can use.

##### Setting a Color
```c++
void setcolor(int ledStripeNumber, RGB c)
```
will set the LED-Stripe with the Number *ledStripeNumber* to the specified color.  *c*. LED-Stripes are numbered from top to bottom staring with 0 to *number_of_stripes*

##### Reset
```c++
reset(int ledStripeNumber)
```
This function will reset all LEDs of The LED-Stripe with the number *ledStripeNumber* to BLACK. LED-Stripes are numbered from top to bottom staring with 0 to *number_of_stripes*

```c++
reset()
```
will reset all LEDs to BLACK

##### Walking
```c++
void walkForwards(int ledStripeNumber)
```
This function will move all values from one LED to the LED with the next higher number in the LED-Stripe with the Number *ledStripeNumber*. The value from the last LED will be set into the first LED. LED-Stripes are numbered from top to bottom staring with 0 to *number_of_stripes*
```c++
void walkForwards()
```
The same with all stripes.
```c++
void walkBackwards(int ledStripeNumber)
```
Same. Just the opposite direction.
```c++
void walkBackwards()
```
yeah.
##### Init Functions
Some functions provide the initial colors for patterns like the pride colors.

### How to add a new animation

Any animation is displayed for a number of frames (for example 1000, the number is set in the constant *frames_per_mode*). After that a new animation is
chosen at random.

To add a new animation at a new function into the **modes.h** file, and add the
function to the modes-array. Your function must take one int parameter. If
your function is chosen at random it is called 1000 times with the frame
number as a parameter.

Your function must set the array "leds" in the way the LED-Strips ought to be
displayed in the next frame. The array is of the size

leds[number_of_stripes][number_of_leds_per_stripe] and the elements are each of
the type *RGB*.

Be aware that not all LEDS may be actually visible in any setup. For example in the 36C6 Stickerbox setup the first 12 and the last 13
leds of each stripe are not.

Please do not call delay in your function or use other things to make stall the execution of the main loop.
