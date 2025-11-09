### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

GPIO Pin: CS/UD/INC GPIO22/GPIO17/GPIO27.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(x9cxx REQUIRED)
```

### 3. X9CXX

#### 3.1 Command Instruction

1. Show x9cxx chip and driver information.

   ```shell
   x9cxx (-i | --information)
   ```

2. Show x9cxx help.

   ```shell
   x9cxx (-h | --help)
   ```

3. Show x9cxx pin connections of the current board.

   ```shell
   x9cxx (-p | --port)
   ```

4. Run x9cxx output test, number is the test times.

   ```shell
   x9cxx (-t output | --test=output) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--times=<number>]
   ```

5. Run x9cxx max function.

   ```shell
   x9cxx (-e max | --example=max) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>]
   ```

6. Run x9cxx min function.

   ```shell
   x9cxx (-e min | --example=min) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>]
   ```

7. Run x9cxx inc function, number means the step counter.

   ```shell
   x9cxx (-e inc | --example=inc) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]
   ```

8. Run x9cxx dec function, number means the step counter.

   ```shell
   x9cxx (-e dec | --example=dec) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]
   ```

9. Run x9cxx step function, number means the step counter.

   ```shell
   x9cxx (-e step | --example=step) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]
   ```

10. Run x9cxx resistor function, ohm means the resistor value in ohm.

    ```shell
    x9cxx (-e res | --example=res) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--resistor=<ohm>]
    ```

#### 3.2 Command Example

```shell
./x9cxx -i

x9cxx: chip is Renesas X9CXX.
x9cxx: manufacturer is Renesas.
x9cxx: interface is GPIO.
x9cxx: driver version is 1.0.
x9cxx: min supply voltage is 4.5V.
x9cxx: max supply voltage is 5.5V.
x9cxx: max current is 3.00mA.
x9cxx: max temperature is 85.0C.
x9cxx: min temperature is -40.0C.
```

```shell
./x9cxx -p

x9cxx: CS connected to GPIO22(BCM).
x9cxx: UD connected to GPIO17(BCM).
x9cxx: INC connected to GPIO27(BCM).
```

```shell
./x9cxx -t output --type=X9C104 --times=3

x9cxx: chip is Renesas X9CXX.
x9cxx: manufacturer is Renesas.
x9cxx: interface is GPIO.
x9cxx: driver version is 1.0.
x9cxx: min supply voltage is 4.5V.
x9cxx: max supply voltage is 5.5V.
x9cxx: max current is 3.00mA.
x9cxx: max temperature is 85.0C.
x9cxx: min temperature is -40.0C.
x9cxx: start output test.
x9cxx: increment and current step counter is 1.
x9cxx: increment and current step counter is 2.
x9cxx: increment and current step counter is 3.
x9cxx: decrement and current step counter is 98.
x9cxx: decrement and current step counter is 97.
x9cxx: decrement and current step counter is 96.
x9cxx: set absolute step counter 68.
x9cxx: ohm is 66.70 and converted ohm is 0.00.
x9cxx: finish output test.
```

```shell
./x9cxx -e max --type=X9C104 --save=false

x9cxx: reset to max.
x9cxx: step is 99.
x9cxx: resistor is 100000.00ohm.
```

```shell
./x9cxx -e min --type=X9C104 --save=false

x9cxx: reset to min.
x9cxx: step is 0.
x9cxx: resistor is 0.00ohm.
```

```shell
./x9cxx -e inc --type=X9C104 --save=false --step=10

x9cxx: increment 10 step.
x9cxx: step is 10.
x9cxx: resistor is 10101.01ohm.
```

```shell
./x9cxx -e dec --type=X9C104 --save=false --step=10

x9cxx: decrement 10 step.
x9cxx: step is 89.
x9cxx: resistor is 89898.99ohm.
```

```shell
./x9cxx -e step --type=X9C104 --save=false --step=50

x9cxx: set absolute step 49.
x9cxx: step is 49.
x9cxx: resistor is 49494.95ohm.
```

```shell
./x9cxx -e res --type=X9C104 --save=false --resistor=500.0

x9cxx: set absolute resistor 1020.00ohm.
x9cxx: step is 1.
x9cxx: resistor is 1010.10ohm.
```

```shell
./x9cxx -h

Usage:
  x9cxx (-i | --information)
  x9cxx (-h | --help)
  x9cxx (-p | --port)
  x9cxx (-t output | --test=output) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--times=<number>]
  x9cxx (-e max | --example=max) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>]
  x9cxx (-e min | --example=min) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>]
  x9cxx (-e inc | --example=inc) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]
  x9cxx (-e dec | --example=dec) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]
  x9cxx (-e step | --example=step) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]
  x9cxx (-e res | --example=res) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--resistor=<ohm>]

Options:
  -e <max | min | inc | dec | step | res>, --example=<max | min | inc | dec | step | res>
                          Run the driver example.
  -h, --help              Show the help.
  -i, --information       Show the chip information.
  -p, --port              Display the pin connections of the current board.
      --resistor=<ohm>    Set the resistor value.([default: 1000.0])
      --save=<true | false>
                          Save the settings to eeprom.([default: false])
      --step=<number>     Set the chip step.([default: 1])
  -t <output>, --test=<output>
                          Run the driver test.
      --times=<number>    Set the test times.([default: 3])
      --type=<X9C102 | X9C103 | X9C503 | X9C104>
                          Set the chip type.([default: X9C102])
```
