set multiplot layout 4, 1 title "Synapse example" font ",14"
set lmargin 5
set bmargin 3
unset key
set title "Input"
plot "synapse_example.txt" u 4 w l
set title "Pre-synaptic Neuron"
plot "synapse_example.txt" u 1 w l
set title "Synapse"
plot "synapse_example.txt" u 3 w l
set title "Post-synaptic Neuron"
plot "synapse_example.txt" u 2 w l
unset multiplot

set multiplot layout 4, 1 title "Synapse example" font ",14"
set lmargin 5
set bmargin 3
unset key
set title "Input"
plot "synapse2_example.txt" u 4 w l
set title "Pre-synaptic Neuron"
plot "synapse2_example.txt" u 1 w l
set title "Synapse"
plot "synapse2_example.txt" u 3 w l
set title "Post-synaptic Neuron"
plot "synapse2_example.txt" u 2 w l
unset multiplot

