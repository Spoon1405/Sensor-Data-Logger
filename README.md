# Sensor-Data-Logger
I want to build an embedded system that can read sensors on a fixed time interval and store those readings in a ring buffer, logs it, and includes a Serial command interface.

Building a small embedded system on the Arduino Mega 2560 that reads the environmental data from a BME280 sensor on a fixed interval, stores the recent readings in a ring buffer, and then exposes a Serial CLI for status or configuration.

## Goals
- Practice embedded fundamentals: periodic sampling, non-blocking timing, memory-bound storage, I/O/
- Produce a project with clear documentation and a reproducible setup.
- Build something that can be demoed.


## Features (current goal / Future planned) checklist
### Current
- [x] Read BME280 temperature, humidity, and pressure over I2C.
- [x] Sample at a configurable interval
- [ ] Store last N readings in a fixed size ring buffer.
- [x] Serial output in structured format (CSV)

### Serial CLI
- [ ] 'help' - list commands
- [ ] 'status' - uptime, sample rate, error counts, buffer usage
- [ ] 'latest' - print most recent reading
- [ ] 'dump' - print buffer contents
- [ ] 'set rate <ms> - change the sample interval
- [ ] 'start' / 'stop' - enable/disable sampling

### Possible extensions (for future)
- [ ] microSD CSV logging ('log start', 'log stop')
- [ ] RTC timestamps (DS3231)
- [ ] basic reliability features (sanity checks, error counters, watchdog)

## Hardware
- Arduino Mega 2560
- BME280 breakout module (I2C)
- (optional) microSD module
- (optional) DS3231 RTC module
- Jumper wires + breadboard

## Wiring (Arduino Mega 2560, I2C)
> useful note: Mega I2C pins are SDA = 20, SCL 21

  | BME280 Pins | Arduino Mega |
  |-------------|--------------|
  | VCC / VIN   | 5V or 3.3V   |    (Depends on your BME280)
  | GND         | GND          |
  | SDA         | SDA (pin 20) |
  | SCL         | SCL (pin 21) |
  | CS          | disable (3.3V) |
  | ADDR        | GND (Address 0x76 |

## Software
- Arduino IDE
- Library: (TBD) 'Adafruit BME280' (or any others)

## Build & Run
1. Install Adafruit BME280, Adafruit BusIO, Adafruit Unified Sensor via the Library manager in the Arduino IDE
2. Set ADDR pin to GND for the address to be 0x76
3. Open the Serial monitor at 115200 baud

## Architecture
- 'main': initialises peripherals and runs the main loop
- sampler: periodic task using 'millis()' (non-blocking)
- ring buffer: fixed-size storage for last N reading
- cli: parses serial input and runs commands
- (optional) storafe: microSD logging module

## Project status
This repo is under active development alongside my university coursework.
Milestone 1 Complete

## Roadmap
-  [x] Milestone 1: I2C sensor read + periodic print
-  [ ] Milestone 2: Ring buffer + 'latest' + 'dump'
-  [ ] Milestone 3: CLI config ('set rate', 'start/stop')
-  [ ] Milestone 4: (optional): microSD logging + robustness polish

## Design decisions and tradeoff (to be expanded)
- Use a ring buffer for predictable memory usage on a microcontroller.
- Use a non-blocking timing ('millis()') to keep the system responsive to CLI inputs.
- Prefer I2C for simplicity and fewer pins.

## Demo
- (TBD) Video or GIF link
- (TBD) photos would be provided in /docs
