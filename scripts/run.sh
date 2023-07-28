#loads the sink and loopback
sink_index=$(pactl load-module module-null-sink sink_name=spectral sink_properties=device.description="spectral") 
monitor_index=$(pactl load-module module-loopback sink=spectral)

#starts the main program
./bin/main

#unloads the loopback and sink 
pactl unload-module $monitor_index 
pactl unload-module $sink_index
