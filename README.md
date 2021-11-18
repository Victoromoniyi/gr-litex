[![License](https://img.shields.io/badge/License-BSD_2--Clause-orange.svg)](https://opensource.org/licenses/BSD-2-Clause)

# GNULiteX Accelerator Block

-------------

LiteX Accelerator Block for GNU Radio


# Prerequisites

-------------

1. [GNU Radio version 3.9+](https://github.com/gnuradio/gnuradio)
2. [LiteX](https://github.com/enjoy-digital/litex)
3. SRQL Acorn CLE 215+ FPGA


# Quick start guide

-------------

To run, first clone the repo
```
$ git clone https://github.com/Victoromoniyi/GNULiteX.git
```
Go into the /gr-litexgnu directory and run the following:

```
$ mkdir build
$ cd build
```
Once in the build directory, run:
```
$ cmake../
```
After this is completed, run:
```
$ sudo make install
```

To use GNU Radio companion, run
```
$ gnuradio-companion
```
