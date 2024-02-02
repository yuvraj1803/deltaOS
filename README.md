# deltaOS
deltaOS is a kernel written for microcontrollers with ARMv8-A processors. 
This kernel is written to experiment with deltaSSE. Hence we never jump to EL0 and run the shell in EL1 directly to avoid over complication.
 # Shell Commands
   + sse - this command wont run on baremetal OS. Only supported when running under deltaV or any other hypervisor that supports deltaSSE.
   + ocom - this command is used to communicate with the Omega Secure Monitor. It will only work if the OS is running under Omega(in EL3). Methods to store certain pages of memory in an isolated storage is provided by the secure monitor.
 # deltaV + deltaSSE Integration
   <img width="868" alt="Screenshot 2023-11-03 at 3 53 53 PM" src="https://github.com/yuvraj1803/deltaOS/assets/37622719/3d7583ab-0a9e-4155-8ed8-f667ee402213">
  <img width="1233" alt="Screenshot 2023-11-03 at 4 04 10 PM" src="https://github.com/yuvraj1803/deltaOS/assets/37622719/502f0016-93bd-4881-93d1-31ea75cddb58">


  
 # Build Dependencies
    + make
    + qemu-system-aarch64
    + gcc-aarch64-linux-gnu
 # Debug Dependencies
    + gdb-multiarch
 # How to use?
    + make run
 # How to Debug?
    + make debug
    + (Another Terminal) gdb-multiarch ./deltaOS.elf
    + (gdb) target remote localhost:1234
