/* ShiftyEMA.h
 *
 * ShiftyEMA is a specialized library designed for efficient calculation of the 
 * Exponential Moving Average (EMA) on Arduino platforms. It takes advantage of 
 * bitwise shift operations to optimize performance, which is especially useful 
 * for systems with limited computational capabilities.
 *
 * Key Advantages:
 * - Utilizes integer arithmetic to avoid the computational expense of floating-point operations.
 * - Employs logical bit shifts for multiplications and divisions by powers of two,
 *   significantly accelerating the EMA computation process over traditional methods.
 *
 * How to Use:
 * 1. Include ShiftyEMA.h in your Arduino project.
 * 2. Create a ShiftyEMA object with a specified smoothing factor.
 * 3. Use the getCurrentEMA method to add new data points and obtain the EMA value.
 * 4. Use the reset method to clear the current EMA state, if necessary.
 *
 * Example Sketch:
 * 
 * #include <ShiftyEMA.h>
 *
 * ShiftyEMA ema(ShiftyEMA::SMOOTHING_VALUE_4);
 *
 * void setup() {
 *   Serial.begin(9600);
 * }
 *
 * void loop() {
 *   int sensorReading = analogRead(A0);
 *   int emaValue = ema.getCurrentEMA(sensorReading);
 *   Serial.print("Sensor Reading: ");
 *   Serial.print(sensorReading);
 *   Serial.print(" | EMA: ");
 *   Serial.println(emaValue);
 *   delay(1000);
 * }
 * 
 *
 * Methods Description:
 * - ShiftyEMA(SmoothingExponent smoothing, int16_t scale = 4): Constructor that initializes the filter with a specified smoothing factor.
 * - void updateEMA(int16_t newValue): Internally updates the EMA with a new data value without returning it.
 * - int16_t getCurrentEMA(int16_t newValue): Updates the EMA with a new value and returns the updated EMA value.
 * - int16_t getCurrentEMA() const: Returns the current EMA value without updating it with a new data point.
 * - int32_t getScaledEMA() const: Returns the scaled internal EMA value for more precise calculations.
 * - void reset(): Resets the EMA calculation to its initial state as if no data points had been provided.
 *
 * ShiftyEMA offers a perfect balance between simplicity and efficiency, making it an 
 * ideal tool for EMA computations in embedded systems using the Arduino framework.
 *
 * Author: mackelec
 * License: Released into the public domain for unrestricted use and adaptation.
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
  explicit ShiftyEMA(SmoothingExponent smoothing, int16_t scale = 4)
  : smoothingExponent(smoothing), scale(scale), firstUpdate(true), scaledEMA(0), rounding(1 << (scale - 1)) 
  {
  }

  void updateEMA(int16_t newValue)
  {
    if (firstUpdate)
    {
      scaledEMA = newValue << scale; // Store the scaled up value of the first data point
      firstUpdate = false;
    }
    else
    {
      // Apply the EMA formula on the scaled value
      scaledEMA = scaledEMA - (scaledEMA >> smoothingExponent) + ((newValue << scale) >> smoothingExponent);
    }
  }

  // Update EMA with a new value and return the current EMA
  int16_t getCurrentEMA(int16_t newValue)
  {
    updateEMA(newValue); // Update the scaled EMA
    return getCurrentEMA(); // Return the scaled-down current EMA
  }

  // Get the current EMA without updating it
  int16_t getCurrentEMA() const
  {
    return (scaledEMA + rounding) >> scale; // Scale the EMA back down and round to nearest integer
  }

  int32_t getScaledEMA() const
  {
    return scaledEMA;
  }

  void reset()
  {
    firstUpdate = true;
    scaledEMA = 0;
  }

private:
  int32_t scaledEMA; // Scaled EMA value to avoid recalculations
  const   SmoothingExponent smoothingExponent;
  bool    firstUpdate;
  const int16_t scale; // Scale factor as a power of 2
  const int32_t rounding; // Value for rounding result to nearest integer
};

#endif /* ShiftyEMA_h */
