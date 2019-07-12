This is an implementation and test of two small boolean circuit snarks with libsnark, based on the [libsnark-tutorial](https://github.com/christianlundkvist/libsnark-tutorial) by Christian Lundkvist and Sam Mayo, which was in turn based on [libsnark-tutorial](https://github.com/howardwu/libsnark-tutorial) by Howard Wu.

## Introduction

`libsnark` is a library used to create zkSNARKs from computations expressed as either boolean or arithmetic circuits. Statebox is exploring using boolean circuit-based zkSNARKs to verify computations. 

## Boolean circuits in `libsnark`

Libsnark can create zkSNARKs from boolean circuits. The boolean circuits used by `libsnark` are Two Input Boolean Circuits, in which each boolean gate has two inputs. There are 16 such gates. Each gate outputs either 1 or 0 for each of 4 inputs: (0, 0), (1, 0), (0, 1), (1, 1).

An XOR gate would return 0 1 1 0 respectively on these four inputs. The gates are enumerated by the base-2 number describing their behavior. An XOR is gate type 6 while NAND is gate type 14.

`libsnark` can provide a proof of a satisfying assignment to a boolean circuit. For `libsnark`, a satisfying assignment is one where:

- Each gate is *consistent*
- Each *circuit output* gate outputs 0

A gate is *consistent* if its output matches the behavior expected of the gate. A gate has left, right, and output assignments: (l, r, o). For an XOR gate assignments (1,0,1) and (1,1,0) would be considered consistent. Note that the output is not required to be anything in particular.

A *circuit output* gate, however, must output 0.


## div_by_3.cpp

This boolean circuit is used to test whether a 3-bit number is divisible by 3. The only 3-bit numbers that are divisible by 3 are 110 and 011.

By examining the bits of the two target numbers, we can see that the 3-bit numbers that are divisible by 3 are exactly those whose first and third bits are opposites and whose second bit is a 1. We can implement this circuit with just two gates. An XOR gate will return 1 if its two inputs are different, and then we can make sure the output of the XOR and the middle bit are both 1 with AND.

`libsnark` regards wire 0 as having the constant value 1.

Unfortunately, `libsnark` expects the output gates to have output 0. So we will change the final gate to a gate that is 0 only if both inputs are 1 (NAND).

A diagram of our circuit:

```
    w0      w1         w2        w3
             \          |   _____/
              \   ______|__/
               \ /      |
               XOR      /
                 \     /
                  w4  /
                   \ /
                   NAND
                    |
                    w5
                    |
```

Each of the three input wires (w1, w2, w3), the internal wires (w4), and the output wires (w5) must be correctly assigned in order to satisfy the circuit. There are two correct satisfying assignments:

|  w1 |  w2 |  w3 |  w4 |  w5 |
|:---:|:---:|:---:|:---:|:---:|
|   1 |   1 |   0 |  1  |   0 |
|   0 |   1 |   1 |  1  |   0 |

The assignments are enumerated as big-endian base-2 numbers. The correct assignments above are assignments 11 and 14, respectively.

The program `div_by_3.cpp` creates this boolean circuit using `libsnark` and generates proving and verifying keys (the "Trusted Setup") for the circuit.

Then a proof is generated for each of the 32 possible assignments to the circuit and the verifier is run. The verifier rejects all but two of the proofs--the proofs corresponding to the two correct satisfying assignments.

## prime_under_16.cpp

This circuit picks out the 4-bit numbers that are prime: 0100, 1100, 1010, 1110, 1101 and 1011.

This circuit works by using a pair of gates for a pair of primes. 0100 and 1100 are selected by using two gates: Gate 1 is used to show that the second bit is a 1, and Gate 2 shows that both the third and fourth bits are 0. Then an AND gate is used on the outputs of these two gates. In this way we can build a circuit whose first two levels contain nine gates--three for each pair of primes. The three resulting AND gates are then ORed with each other with two OR gates. This circuit will output 1 if the input is prime, but `libsnark` wants circuit output gates to be 0, so we append a NOT gate to the end of the circuit. This brings the total to twelve gates in all.

I will not show all twelve gates of the circuit, but here are the gates selecting 0100 and 1100:

```
    w0      w1      w2      w3      w4
    ||   ___________/       / _______/
    |\  /                  / /
    | AND                 NOR
    |  \                  /
    |   \_w5__      _w6__/
    |         \    /
    |          \  /
    |           \/
    \           AND
     \           \      /
      \           w11  w12
       \           \  /
        \           OR
         \           \
          \         w13  w14
           \          \  /
            \          OR
             \          |
              \        w15
               \        |
               X AND NOT Y
                    |
                    w16
                    |
```

## Building and running

### Install dependencies

- On Ubuntu 16.04 LTS:

      $ sudo apt-get install build-essential cmake git libgmp3-dev libprocps4-dev python-markdown libboost-all-dev libssl-dev

- On Ubuntu 14.04 LTS:

      $ sudo apt-get install build-essential cmake git libgmp3-dev libprocps3-dev python-markdown libboost-all-dev libssl-dev

- On Fedora 21 through 23:

      $ sudo yum install gcc-c++ cmake make git gmp-devel procps-ng-devel python2-markdown

- On Fedora 20:

      $ sudo yum install gcc-c++ cmake make git gmp-devel procps-ng-devel python-markdown

### Add libsnark 

$ cd depends

$ git submodule add https://github.com/scipr-lab/libsnark.git libsnark

$ cd ..

### Fetch all dependencies

$ git submodule update --init --recursive

### Build

$ mkdir build && cd build

#### Building on Windows using Cygwin

Install Cygwin using the graphical installer, including the g++, libgmp, cmake, and git packages. Then disable the dependencies not easily supported under CygWin, using:

$ cmake -DWITH_PROCPS=OFF ..

$ make
#### Building on Mac OS X

On Mac OS X, install GMP from MacPorts (port install gmp). Then disable the dependencies not easily supported under OS X, using:

$ cmake -DWITH_PROCPS=OFF ..

$ make

#### Building on Linux

$ cmake ..

$ make

### Run examples

#### div_by_3

$ ./src/div\_by\_3

This will create and and attempt to verify 32 proofs. Since the output is massive you may want to run this instead:

$ ./src/div\_by\_3 | grep "Proof accepted"

#### prime_under_16

$./src/prime\_under\_16


