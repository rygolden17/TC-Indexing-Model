# TC-Indexing-Model

Repository for the Thalamocortical model used in the paper "Interleaved Replay of Novel and Familiar Memory Traces During Slow-Wave Sleep Prevents Catastrophic Forgetting."

---

## 1. System Requirements

### Software Dependencies
- **C++ compiler**: g++ (GCC) with OpenMP support — tested on GCC 13.3.0
- **OpenMP**: Required for multi-core parallelism; included with GCC by default
- **GNU Make** On Ubuntu: `sudo apt install build-essential`; https://www.gnu.org/software/make/
- **Operating System**: Linux — tested on Ubuntu 24.04.4 LTS

### Non-Standard Hardware
A multi-core CPU is strongly recommended. The default configuration uses 30 OpenMP threads (`num_mp_threads` in `params.txt`). The simulation can be run on fewer cores by reducing this value, but runtime will increase substantially.

---

## 2. Installation Guide

### Instructions
1. Clone or download the repository.
2. Navigate to the `rand2` subdirectory:
   ```bash
   cd rand2
   ```
3. Compile the main simulation executable:
   ```bash
   make mindcurrent
   ```
   This produces the executable `mindcurrent`.
4. Make a subdirectory named `out` to log simulation output
   ```bash
   mkdir out
   ```

**Typical install time**: Compilation takes under one minute on a standard desktop computer.

---

## 3. Demo

The `rand2` subdirectory is pre-configured to replicate the results of the manuscript when Down-to-Up transition (DUt) indexing is applied during slow-wave sleep (SWS). The pre-generated network connectivity used in the manuscript is provided in `rand2/connection_info2`.

### Running the Demo

From within the `rand2` subdirectory, run:

```bash
make run
```

This executes the full simulation paradigm:

| Stage                    | Duration      |
|--------------------------|---------------|
| Baseline                 | 12 s          |
| Baseline Test (×2)       | 50 s each     |
| Train Sequence 1         | 250 s         |
| Post-Train Test (×2)     | 50 s each     |
| SWS w/ DUt Indexing      | 2000 s        |
| Post-SWS Test (×2)       | 50 s each     |

### Expected Output

Output files are written to the `out/` folder. The primary files used in analyses are:

- **`spike_time`**: All spike events during the simulation. Organized as an S×4 matrix, where S is the total number of spikes. Each row represents one spike: column 1 is the spike time in milliseconds, column 2 is the neuron's type ID, column 3 is the neuron's x-coordinate, and column 4 is the neuron's y-coordinate (not utilized in this simulation). Type IDs are listed as comments in `network.cfg`: RE = reticular interneuron, TC = thalamocortical neuron, CX = cortical pyramidal neuron, IN = cortical inhibitory interneuron.

- **`time_cx`**: Membrane voltage of cortical pyramidal neurons. Organized as a T×(N+2) matrix, where T is the total number of timesteps in milliseconds and N is the total number of pyramidal neurons. Column 1 lists the current timestep; the last column lists the arithmetic mean across all pyramidal neurons at that timestep.

- **`conn_index_cx_cx_G`**: Written once at simulation start. Encodes the static connectivity of all CX→CX AMPA synapses as a single row of 2K values, alternating source and target neuron indices (`source₀ target₀ source₁ target₁ ...`), where K is the total number of CX→CX connections. Indices are 0-based x-coordinates.

- **`time_G_AMPA0_CX_CX`**: Records the AMPA synaptic conductance (`g_AMPA0`) of all CX→CX connections, sampled once every second of simulated time. Organized as a T×2K matrix (T ≈ 2562 rows), where each row alternates target neuron index and conductance value (`target₀ g₀ target₁ g₁ ...`). The K connections appear in the same order as in `conn_index_cx_cx_G`, so the two files can be used together to reconstruct the full time-varying N×N synaptic weight matrix: `conn_index_cx_cx_G` provides the fixed source/target index pairs that define where each conductance value belongs in the matrix, while each row of `time_G_AMPA0_CX_CX` provides the corresponding conductance values at that timepoint.

### Expected Run Time

On a 32-core desktop, the full simulation (~2562 s of simulated time) takes approximately 40 hours. Runtime scales with the number of available CPU threads, which is set via `num_mp_threads` in `params.txt`.

---

## 4. Instructions for Use

### Network Connectivity

The `connection_info2` file in `rand2` contains the pre-generated network connectivity used in the manuscript. To generate a new instantiation of the network with the same statistical properties, navigate to `rand2` and run:

```bash
make network
```

This compiles `generate_network.cpp` into the `generate_network` executable and writes a new `connection_info2` file based on the architecture defined in `network.cfg`.

### Running the Simulation

From within any seeded subdirectory (e.g., `rand2`):

```bash
make run
```

### Running Multiple Iterations

To generate multiple seeded iterations of the simulation (rand3–rand7), first generate the network connectivity as described above, then from the root project directory run:

```bash
./make_sims.sh
```

This creates subdirectories `rand3` through `rand7`, each identical to `rand2` but compiled with a unique random seed. The seed is controlled by the `time2()` macro in `currents.h`, which `make_sims.sh` patches to the directory number for each copy.

To run all iterations in serial, use:

```bash
./submitRuns1.sh
```

This runs the simulation sequentially in `rand2` through `rand7`.

### Simulating Alternative Indexing Protocols

In order to run the model with different indexing protocols, please adjust the following variables in `main.cpp`:

- DUt: `stimType = 1` and `dtime = 0`
- Mid-UP: `stimType = 1` and `dtime = 200`
- UDt: `stimType = 2` and `dtime = 0`


