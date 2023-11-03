/* ShiftyEMA.h
 *
 * ShiftyEMA is a lightweight, efficient library for calculating the Exponential Moving Average (EMA)
 * on Arduino-based microcontrollers. The name reflects its use of bitwise shift operations to perform
 * fast, efficient computations without relying on floating-point arithmetic.
 *
 * By using integer math and logical bit shifts, ShiftyEMA can perform EMA calculations with reduced
 * computational overhead, making it particularly suitable for resource-constrained environments and
 * real-time applications where performance is essential.
 *
 * The library defines a set of smoothing factors as powers of two, allowing for quick left and right
 * bitwise shifts to multiply and divide by two respectively, which drastically speeds up the calculation
 * process compared to traditional methods.
 *
 * Usage:
 * 1. Include the ShiftyEMA.h in your Arduino sketch.
 * 2. Instantiate a ShiftyEMA object with the desired smoothing exponent.
 * 3. Use the updateEMA method to input new data points and receive the smoothed EMA value in return.
 * 4. The reset method can be called at any time to reinitialize the EMA calculation.
 *
 * Example:
 * ```
 * #include <ShiftyEMA.h>
 *
 * ShiftyEMA emaFilter(ShiftyEMA::SMOOTHING_VALUE_4);
 *
 * void setup() {
 *   Serial.begin(9600);
 * }
 *
 * void loop() {
 *   int newData = random(0, 1000);
 *   int emaValue = emaFilter.updateEMA(newData);
 *   Serial.print("New Data: ");
 *   Serial.print(newData);
 *   Serial.print(" EMA: ");
 *   Serial.println(emaValue);
 *   delay(1000);
 * }
 * ```
 *
 * ShiftyEMA offers a balance between efficiency and functionality, providing a tool that is both
 * simple to use and highly optimized for the Arduino platform.
 *
 * Created by [Your Name or GitHub username]
 * Released into the public domain for open use and modification as desired.
 */
#ifndef ShiftyEMA_h
#define ShiftyEMA_h

#include "Arduino.h"

class ShiftyEMA
{
public:
  enum SmoothingExponent
  {
    SMOOTHING_VALUE_1 = 0,
    SMOOTHING_VALUE_2,
    SMOOTHING_VALUE_4,
    SMOOTHING_VALUE_8,
    SMOOTHING_VALUE_16,
    SMOOTHING_VALUE_32,
    SMOOTHING_VALUE_64,
    SMOOTHING_VALUE_128,
    SMOOTHING_VALUE_256,
    SMOOTHING_VALUE_512 = 9
  };

  // Constructor that allows setting the scale factor
  explicit ShiftyEMA(SmoothingExponent smoothing, int scale = 4)
  : _smoothingExponent(smoothing), _scale(scale), _firstUpdate(true), _currentEMA(0) 
  {
  }

  int updateEMA(int newValue)
  {
    if (_firstUpdate)
    {
      _currentEMA = newValue; // Initialize _currentEMA with newValue
      _firstUpdate = false;
    }
    else
    {
      int32_t big = (_currentEMA << _scale) - ((_currentEMA << _scale) >> _smoothingExponent) + ((newValue << _scale) >> _smoothingExponent);
      //_currentEMA = big >> _scale; // Scale back down by dividing by 2^_scale
      _currentEMA = (big + (1 << (_scale - 1))) >> _scale; // Scale back down by dividing by 2^_scale with rounding
    }
    return _currentEMA;
  }

  void reset()
  {
    _firstUpdate = true;
    _currentEMA = 0;
  }

private:
  int _currentEMA;
  const SmoothingExponent _smoothingExponent;
  bool _firstUpdate;
  const int _scale; // Scale factor as a power of 2
};

#endif /* ShiftyEMA_h */
