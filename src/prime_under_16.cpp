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
    tbcs_circuit prime_under_16;

    // This circuit will test whether a 4 bit number is prime.
    // This will require 12 two-input boolean gates 
    // Each bit is an input to the circuit and we will regard each of them as private.

    // Set the circuit size
    prime_under_16.primary_input_size = 0; // this is the number of PUBLIC inputs
    prime_under_16.auxiliary_input_size = 4; // this is the number of PRIVATE inputs

    // Initialize our 12 gates
    tbcs_gate g1;
    tbcs_gate g2;
    tbcs_gate g3;
    tbcs_gate g4;
    tbcs_gate g5;
    tbcs_gate g6;
    tbcs_gate g7;
    tbcs_gate g8;
    tbcs_gate g9;
    tbcs_gate g10;
    tbcs_gate g11;
    tbcs_gate g12;

    /* 
        This circuit was written in the "normal" way, that is, it was written to 
        output 1 if the number is prime, and 0 if not. However since libsnark
        expects all circuit outputs to be 0, a NOT gate has been added at the end
        of the circuit.

    */
       

    //  0 AND 2
        g1.left_wire = 0;
        g1.right_wire = 2;
        g1.type = tbcs_gate_type(1); 
        g1.output = 5;
        g1.is_circuit_output = false;

    //  3 NOR 4
        g2.left_wire = 3;
        g2.right_wire = 4;
        g2.type = tbcs_gate_type(8); 
        g2.output = 6;
        g2.is_circuit_output = false;

    //  0 AND 1
        g3.left_wire = 0;
        g3.right_wire = 1;
        g3.type = tbcs_gate_type(1);
        g3.output = 7;
        g3.is_circuit_output = false;

    //  3 AND NOT 4
        g4.left_wire = 3;
        g4.right_wire = 4;
        g4.type = tbcs_gate_type(4);
        g4.output = 8;
        g4.is_circuit_output = false;

    //  1 AND 4
        g5.left_wire = 1;
        g5.right_wire = 4;
        g5.type = tbcs_gate_type(1);
        g5.output = 9;
        g5.is_circuit_output = false;

    //  2 XOR 3
        g6.left_wire = 2;
        g6.right_wire = 3;
        g6.type = tbcs_gate_type(6);
        g6.output = 10;
        g6.is_circuit_output = false;

    //  5 AND 6
        g7.left_wire = 5;
        g7.right_wire = 6;
        g7.type = tbcs_gate_type(1);
        g7.output = 11;
        g7.is_circuit_output = false;

    //  7 AND 8
        g8.left_wire = 7;
        g8.right_wire = 8;
        g8.type = tbcs_gate_type(1);
        g8.output = 12;
        g8.is_circuit_output = false;

    //  9 AND 10
        g9.left_wire = 9;
        g9.right_wire = 10;
        g9.type = tbcs_gate_type(1);
        g9.output = 13;
        g9.is_circuit_output = false;

    //  11 OR 12
        g10.left_wire = 11;
        g10.right_wire = 12;
        g10.type = tbcs_gate_type(7);
        g10.output = 14;
        g10.is_circuit_output = false;

    //  14 OR 13
        g11.left_wire = 14;
        g11.right_wire = 13;
        g11.type = tbcs_gate_type(7);
        g11.output = 15;
        g11.is_circuit_output = false;


    //  This functions as a NOT gate ensuring the final output is 0
    //  0 AND NOT 15
        g12.left_wire = 0;
        g12.right_wire = 15;
        g12.type = tbcs_gate_type(4);
        g12.output = 16;
        g12.is_circuit_output = true;


    // To add the gates to our circuit object:
    prime_under_16.add_gate(g1);
    prime_under_16.add_gate(g2);
    prime_under_16.add_gate(g3);
    prime_under_16.add_gate(g4);
    prime_under_16.add_gate(g5);
    prime_under_16.add_gate(g6);
    prime_under_16.add_gate(g7);
    prime_under_16.add_gate(g8);
    prime_under_16.add_gate(g9);
    prime_under_16.add_gate(g10);
    prime_under_16.add_gate(g11);
    prime_under_16.add_gate(g12);


    // Print the circuit so we can inspect it:
    prime_under_16.print();

    // Make sure our circuit is valid:
    printf("%d\n", prime_under_16.is_valid());

    // Generate keypair (proving key, verifying key) from the constraint system (this is the "Trusted Setup"):
    const tbcs_ppzksnark_keypair<default_tbcs_ppzksnark_pp> keypair = tbcs_ppzksnark_generator<default_tbcs_ppzksnark_pp>(prime_under_16);

    // public input is empty
    tbcs_primary_input pi = {};

    // assignment for 13
    tbcs_auxiliary_input ai = {1,0,1,1,0,0,1,0,1,1,0,0,1,0,1,0}; //13

    // generate the proof
    tbcs_ppzksnark_proof<default_tbcs_ppzksnark_pp> proof = tbcs_ppzksnark_prover<default_tbcs_ppzksnark_pp>(keypair.pk, pi, ai);
    
    // verify the proof
    bool verified = tbcs_ppzksnark_verifier_strong_IC<default_tbcs_ppzksnark_pp>(keypair.vk, pi, proof);

    printf("%s\n", verified ? "Proof accepted" : "Proof false");

    return 0;

}
