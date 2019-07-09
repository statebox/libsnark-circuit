This is some practice with libsnark, based on Christian Lundkvist's libsnark-tutorial.

I am modifying the file /src/test.cpp

So far I have generated a SNARK for the following arithmetic circuit:

    `(c1\*(c2 + c3) - c4)\*c5 = out`

Then generated a proof using:

   - c1 = 26
   - c2 = 11
   - c3 = 15
   - c4 = 3
   - c5 = 3
   - out = 2019

And verified the proof's accuracy. Changing `c2` to `10` caused the proof to be invalid, as expected.

Next I will try to write a boolean circuit.
