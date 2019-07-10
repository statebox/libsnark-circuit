This is an implementation and test of two small boolean circuit snarks with libsnark, based on the [libsnark-tutorial](https://github.com/christianlundkvist/libsnark-tutorial) by Christian Lundkvist and Sam Mayo.

## Introduction

Libsnark can create zkSNARKs from boolean circuits. The boolean circuits used by libsnark are Two Input Boolean Circuits, in which each boolean gate has two inputs. There are 16 such gates. Each gate outputs either 1 or 0 for each of 4 inputs: (0, 0), (1, 0), (0, 1), (1, 1).

An XOR gate would return 0 1 1 0 respectively on these four inputs. The gates are enumerated by the big-endian base-2 number describing their behavior. So XOR is gate type 6 while NAND is gate type 14.

Libsnark can provide a proof of a satisfying assignment to a boolean circuit. For libsnark, a satisfying assignment is one where:

- Each gate is *consistent*
- Each *circuit output* gate outputs 0

A gate is *consistent* if its output matches the behavior expected of the gate. A gate has left, right, and output assignments, (l, r, o). For an XOR gate assignments (1,0,1) and (1,1,0) would be considered consistent. Note that the output is not required to be anything in particular.

A *circuit output* gate, however, must output 0.


## div_by_3.cpp

This boolean circuit is used to test whether a 3-bit number is divisible by 3. The only 3-bit numbers that are divisible by 3 are 110 and 011.

By examining the bits of the two target numbers, we can see that the 3-bit numbers that are divisible by 3 are exactly those whose first and third bits are opposites and whose second bit is a 1. We can implement this circuit with just two gates. An XOR gate will return 1 if its two inputs are different, and then we can make sure the output of the XOR and the middle bit are both 1 with AND.

Unfortunately, libsnark expects the output gates to have output 0. So we will change to a gate that is 0 only if both inputs are 1 (NAND).

A diagram of our circuit:

```
        w1         w2        w3
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


The program `div_by_3.cpp` creates this boolean circuit using libsnark and generates proving and verifying keys (the "Trusted Setup") for the circuit.

Then a proof is generated for each of the 32 possible assignments to the circuit and the verifier is run. The verifier rejects all but two of the proofs--the proofs corresponding to the two correct satisfying assignments.

## prime_below_16.cpp
