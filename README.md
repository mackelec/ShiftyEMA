# ShiftyEMA

A fast, efficient, and lightweight library for calculating Exponential Moving Averages (EMA) on Arduino platforms using integer arithmetic and bitwise operations for optimal performance.

## Features

- **Efficient Calculations**: Uses bitwise shifting for fast EMA updates.
- **Integer Math**: Avoids floating-point computations for increased speed.
- **Simple Interface**: Easy to use with minimal setup.
- **Flexible Smoothing**: Supports multiple smoothing factors for fine control over the averaging process.

## Usage

To use ShiftyEMA in your project, include the `ShiftyEMA.h` header file and follow these steps:

1. Create an instance of the `ShiftyEMA` class.
2. Call the `updateEMA` method with new data.
3. Use the `reset` method to reinitialize the EMA calculation if needed.

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
  int emaValue = emaFilter.updateEMA(newData);
  
  Serial.print("New Data: ");
  Serial.print(newData);
  Serial.print(" EMA: ");
  Serial.println(emaValue);
  
  delay(1000);
}
```

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

Don't forget to give the project a star! Thanks again!

## License

Distributed under the MIT License. See `LICENSE` for more information.


