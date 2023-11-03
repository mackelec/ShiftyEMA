# ShiftyEMA

A fast, efficient, and lightweight library for calculating Exponential Moving Averages (EMA) on Arduino platforms using integer arithmetic and bitwise operations for optimal performance.

## Features

- **Efficient Calculations**: Uses bitwise shifting for fast EMA updates.
- **Integer Math**: Avoids floating-point computations for increased speed.
- **Simple Interface**: Easy to use with minimal setup.
- **Flexible Smoothing**: Supports multiple smoothing factors for fine control over the averaging process.

## Methods

The ShiftyEMA library provides several methods for EMA calculation and management:

- `ShiftyEMA(SmoothingExponent smoothing)`: Constructor to initialize the EMA filter with a specified smoothing factor.
- `updateEMA(int16_t newValue)`: Accepts a new data point and updates the EMA value accordingly. This method should be called with each new data point before calling `getCurrentEMA` to get the updated EMA value.
- `getCurrentEMA(int16_t newValue)`: Combines the action of updating the EMA with the new data point and returning the updated EMA value. This is a convenience method that calls `updateEMA` internally.
- `getCurrentEMA()`: Returns the current EMA value without updating it with a new data point, allowing you to retrieve the last calculated EMA without altering its state.
- `getScaledEMA()`: Provides access to the scaled EMA value used internally, which might be useful for advanced calculations or for debugging purposes.
- `reset()`: Resets the EMA calculation to its initial state, effectively starting the calculation over. This is useful when the data stream has been interrupted or when a new type of data is being processed.

These methods facilitate a flexible and straightforward approach to applying an EMA filter in your Arduino projects.

## Usage

To use ShiftyEMA in your project, include the `ShiftyEMA.h` header file and follow these steps:

1. Create an instance of the `ShiftyEMA` class.
2. Call the `updateEMA` method with new data.
3. Call getCurrentEMA() to retrieve the current EMA value.
4. Call getCurrentEMA(newData) to update the EMA with newData and retrieve EMA value.
5. Use the `reset` method to reinitialize the EMA calculation if needed.

Here is a simple example to get you started:

```
#include <ShiftyEMA.h>

// Create an EMA filter with a smoothing factor equivalent to 16
ShiftyEMA emaFilter(ShiftyEMA::SMOOTHING_VALUE_16);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int newData = random(0, 1000);
  int emaValue = emaFilter.getCurrentEMA(newData);
  
  Serial.print("New Data: ");
  Serial.print(newData);
  Serial.print(" EMA: ");
  Serial.println(emaValue);
  
  delay(1000);
}
```


## License

Distributed under the MIT License. See `LICENSE` for more information.


