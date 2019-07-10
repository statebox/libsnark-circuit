#include "libff/algebra/fields/field_utils.hpp"
#include "libsnark/zk_proof_systems/ppzksnark/tbcs_ppzksnark/tbcs_ppzksnark.hpp"
#include "libsnark/common/default_types/tbcs_ppzksnark_pp.hpp"

using namespace libsnark;
using namespace std;

int main()
{
    // SETUP
    // choose the field we are working in
    typedef libff::Fr<default_tbcs_ppzksnark_pp> FieldT;
    default_tbcs_ppzksnark_pp::init_public_params();

    // To initialize the circuit:
    tbcs_circuit div_by_3;

    // This circuit will test whether a 3 bit number [0...7] is divisible by 3.
    // This will require 2 two-input boolean gates 
    // Each bit is an input to the circuit and we will regard each of them as private.

    // Set the circuit size
    div_by_3.primary_input_size = 0; // this is the number of PUBLIC inputs
    div_by_3.auxiliary_input_size = 3; // this is the number of PRIVATE inputs

    // Initialize our 2 gates
    tbcs_gate g1;
    tbcs_gate g2;

    /*
        Libsnark can ignore internal wires and will only check that gates marked as 
        "circuit outputs" are satisfied. A circuit output gate is satisfied when the 
        value on its outwire is 0. Gates which are not circuit outputs are checked 
        that the gate itself is consistent. For instance, an AND gate should have a 
        value of 1 on its outwire when (1,1) is an input. But the outwire of these 
        internal gates are not required to be 0.


        The 2 acceptable assignments for input wires are (0,1,1) or (1,1,0). (That's 3
        or 6, repectively.) Our circuit will check that the first and last bits are 
        opposites and that the middle bit is 1. 

        There are 16 gate types enumerated by the output column of its truth table. 
        For instance, gate type NOR is gate 8:

            | left | right | out |
            |------|-------|-----|
            |  0   |   0   |  1  |
            |  1   |   0   |  0  |
            |  0   |   1   |  0  |
            |  1   |   1   |  0  |
    */


    //  wire 1 XOR wire 3 checks that the first and last bits are opposites
    g1.left_wire = 1;
    g1.right_wire = 3;
    g1.type = tbcs_gate_type(6); // X XOR Y
    g1.output = 4;
    g1.is_circuit_output = false; 

    /*

        For a 5-wire circuit there are 2^5 possible assignments. Each gate 
        narrows the number of satisfying assignments down.

        The first gate is not marked as a "circuit output", so its outwire 
        (Wire 4) is not required to be 0. Because this gate is not subject
        to that additional constraint, the gate is satisfied by any 
        assignment that is consistent with the gate's operation. That is, 
        if wires 1 and 3 are opposites, the value on wire 4 should be 1. 
        If wires 1 and 3 are not opposites, the value on wire 4 is 0. The 
        assignments that will satisfy the first gate only are therefore:

            (0,0,0,0,0)
            (0,1,0,0,0)
            (1,0,1,0,0)
            (1,1,1,0,0)
            (1,0,0,1,0)
            (1,1,0,1,0)
            (0,0,1,1,0)
            (0,1,1,1,0)
            (0,0,0,0,1)
            (0,1,0,0,1)
            (1,0,1,0,1)
            (1,1,1,0,1)
            (1,0,0,1,1)
            (1,1,0,1,1)
            (0,0,1,1,1)
            (0,1,1,1,1)
            

        The second gate is marked as a "circuit output", and so its outwire
        (Wire 5) must be 0. Since we want the outwire of Gate 1 above to be 1, 
        and the value of wire 2 to also be 1, we need to choose a gate that
        outputs 0 for (1,1) and 1 for everything else (NAND). The satisfying
        assignments to the entire circuit is the subset of the above 
        assignments that also satisfy Gate 2. These are:

            (1,1,0,1,0)
            (0,1,1,1,0)

        These correspond to the circuit assignments for 3 and 6. The first three
        bits are for the input wires, the fourth bit is an internal wire, and the
        fifth bit is the output wire.
       
    */
  
    //  wire 4 NAND wire 2
    g2.left_wire = 4;
    g2.right_wire = 2;
    g2.type = tbcs_gate_type(14); // X NAND Y
    g2.output = 5;
    g2.is_circuit_output = true;


    // To add the gates to our circuit object:
    div_by_3.add_gate(g1);
    div_by_3.add_gate(g2);


    // Print the circuit so we can inspect it:
    div_by_3.print();


    // Make sure our circuit is valid:
    printf("%d\n", div_by_3.is_valid());

    // Generate keypair (proving key, verifying key) from the constraint system (this is the "Trusted Setup"):
        const tbcs_ppzksnark_keypair<default_tbcs_ppzksnark_pp> keypair = tbcs_ppzksnark_generator<default_tbcs_ppzksnark_pp>(div_by_3);

    /* 
        As a sanity test, we will try to prove every single combination of inputs is satisfactory. 
        If our proof system is sound, the proofs of false statements ought to be rejected by the verifier. 
        This circuit has 4 relevant inputs, which are the 3 input bits as well as the value of 
        wire 4. Wire 5, as a circuit output, must be 0.

        The only accepted inputs ought to be (1,1,0,1,0) and (0,1,1,1,0) which are inputs 11 and 14.
    */

    vector<vector<bool>> input_array_32 = {
        {0,0,0,0,0},
        {1,0,0,0,0},
        {0,1,0,0,0},
        {1,1,0,0,0},
        {0,0,1,0,0},
        {1,0,1,0,0},
        {0,1,1,0,0},
        {1,1,1,0,0},
        {0,0,0,1,0},
        {1,0,0,1,0},
        {0,1,0,1,0},
        {1,1,0,1,0},
        {0,0,1,1,0},
        {1,0,1,1,0},
        {0,1,1,1,0},
        {1,1,1,1,0},
        {0,0,0,0,1},
        {1,0,0,0,1},
        {0,1,0,0,1},
        {1,1,0,0,1},
        {0,0,1,0,1},
        {1,0,1,0,1},
        {0,1,1,0,1},
        {1,1,1,0,1},
        {0,0,0,1,1},
        {1,0,0,1,1},
        {0,1,0,1,1},
        {1,1,0,1,1},
        {0,0,1,1,1},
        {1,0,1,1,1},
        {0,1,1,1,1},
        {1,1,1,1,1},

    };


    // Here we generate a proof for each of 16 possible assignments and attempt to verify the proof.

    for (size_t i = 0; i < 32; ++i) {

        // public input is empty
        tbcs_primary_input pi = {};

        // private input is one of 16 possible assignments
        tbcs_auxiliary_input ai = input_array_32[i];

        // generate the proof
        tbcs_ppzksnark_proof<default_tbcs_ppzksnark_pp> proof = tbcs_ppzksnark_prover<default_tbcs_ppzksnark_pp>(keypair.pk, pi, ai);
        // verify the proof
        bool verified = tbcs_ppzksnark_verifier_strong_IC<default_tbcs_ppzksnark_pp>(keypair.vk, pi, proof);

        printf("%s for %d\n", verified ? "Proof accepted" : "Proof false", i);

    }

    return 0;

}
