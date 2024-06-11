#include <systemc.h>

SC_MODULE(simple_module) {
    sc_in<bool> input_signal;   // Input signal
    sc_in_clk clock;            // Clock signal
    sc_out<bool> output_signal; // Output signal

    // Method to handle logic whenever the input_signal changes or on the positive clock edge
    void process_logic() {
        output_signal.write(input_signal.read()); // Mirror the input to the output
        std::cout << "At time " << sc_time_stamp() << ", output_signal = " 
                  << output_signal.read() << std::endl;
    }

    // Constructor
    SC_CTOR(simple_module) {
        SC_METHOD(process_logic);      // Register the process_logic method with the kernel
        sensitive << input_signal;     // Make process_logic sensitive to changes in input_signal
        sensitive << clock.pos();      // Make process_logic sensitive to the positive edge of the clock
    }
};

// Stimulus process for the input_signal
SC_MODULE(stimulus) {
    sc_out<bool> signal_out;
    
    void run_test() {
        signal_out.write(false);
        for (int i = 0; i < 5; ++i) {
            wait(15, SC_NS); // Wait for 15ns
            signal_out.write(!signal_out.read()); // Toggle the signal
        }
    }
    
    SC_CTOR(stimulus) {
        SC_THREAD(run_test);
    }
};

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_signal<bool> input;
    sc_clock clk("clock", 10, SC_NS);  // Clock with a period of 10ns
    sc_signal<bool> output;

    // Instantiate the module
    simple_module mod("simple_module");
    mod.input_signal(input); // Connect the input
    mod.clock(clk);          // Connect the clock
    mod.output_signal(output); // Connect the output

	// Instantiate the stimulus module

    stimulus stim("stimulus");
    stim.signal_out(input);

    // Start the simulation
    sc_start(100, SC_NS); // Run for 100 nanoseconds

}