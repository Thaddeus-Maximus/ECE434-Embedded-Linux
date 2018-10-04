1. Where does Julia Cartwright work?

National Instruments

2. What is PREEMT_RT? Hint: Google it.

A patch that turns the linux kernel into a real-time operating system.

3. What is mixed criticality?

The ability to run programs with different criticalities; separating programs into different priority levels and scheduling them appropriately

4. How can drivers misbehave?

5. What is Δ in Figure 1?
The time from the event that should trigger something to the time that the code responding to it executes

6. What is Cyclictest[2]?

A utility that measures the time between a thread setting a timer and when it expires. It takes a time before waiting, takes time after finishing, and 

7. What is plotted in Figure 2?

This is a distribution of latencies (Δ's) for a real-time linux (teal) and a normal linux (purple).

8. What is dispatch latency? Scheduling latency?

Scheduling latency is the time taken for the OS scheduler to select a process. Dispatch latency is the time taken to switch contexts, switch user/root mode, and jump to the proper location in the new process.

9. What is mainline?

Mainline kernels are vanilla, unmodified kernels.

10. What is keeping the External event in Figure 3 from starting?

The interrupt request handler must finish before the scheduler is reinvoked.

11. Why can the External event in Figure 4 start sooner?

IRQs are much smaller and jump back to main routines; therefore the "body" of an IRQ can be interrupted to handle a higher-priority interrupt.
