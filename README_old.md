# TC-Indexing-Model
Repository for Thalamocortical model used in the paper entitled "Interleaved Replay of Novel and Familiar Memory Traces During Slow-Wave Sleep Prevents Catastrophic Forgetting" 

# Basic Usage
The code is implemented in C++ and uses OpenMP multi-core parallelism to optimize the code's performance. The model in the **rand2** subdirectory is configured to replicate the results of the above paper when Down-to-Up transition (DUt) indexing is appled during slow-wave sleep (SWS).

The network connectivity is given in the *network.cfg* file. To generate the network connectivity file, navigate to the **rand2** subdirectory and run the following command:
>make network

To compile the code into an executible (*mindcurrent*), use the following command:
>make mindcurrent

To run the simulation, use the following command:
>make run

The code generates several output files in the out folder, including the primary ones used in analyses, the spike times of all neurons (*spike_time*) and the membrane voltage of cortical pyramidal neurons (*time_cx*).

The *time_cx* file is organized as an Tx(N+2) matrix, with T being the total number of timesteps in milliseconds and N being the total number of pyramidal neurons. The first column of the matrix simply lists the current timestep, while the last column lists the arithmetic mean across all pyramidal neurons at a given timestep.

The *spike_time* file is organized as an Sx4 matrix where S is the total number of spike during the simulation, thus each spike is given as a row in the matrix. The first column of each row lists the time of the spike in milliseconds, the second the neuron's type ID, the third the neuron's x-coordinate, and the fourth the neuron's y-coordinate (not utilized in this simulation). The type IDs are listed as comments next to each neuron type in the *network.cfg* file, with RE - reticular interneuron; TC - thalamocortical neuron; CX - cortical pyradmidal neuron; and IN - cortical inhibitory interneuron.

## Simulation Paradigm
  Baseline periond:                  12 s\
  Baseline Test:                     50 s (x2)\
  Train Sequence 1:                  250 s\
  Post-Train Test:                   50 s (x2)\
  SWS w/ DUt Indexing of Seqence 2:  2000 s\
  Post-SWS Test:                     50 s (x2)

## Running multiple iterations
To generate multiple iterations of the simulation, each initialized with a unique seed, first generate the network as describes above, then navigate to the root directory of the project run the *make_sims.sh* file. This will generate addtional subdirectories **randN** where N ranges from 3 to 7, identical to **rand2** except seeded with unique value. To run the simulations, either use the steps given above for each uniquely seeded version, or run the *submitRuns1.sh* file to run them all in serial.

