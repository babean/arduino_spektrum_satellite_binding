# Port of miracoli binding code

# Particle_spektrum_satellite_binding
Enable binding mode for spektrum compatible satellite receives using a Particle.io Photon

This is a little arduino sketch to enable binding mode for spektrum compatible satellite receivers using a sequence of low pulses on startup.

## Usage
Sat gnd -> gnd
Sat TX  -> D1
Sat Vcc -> 3V3

Power up Photon. D7 LED will light when bind process is armed. This is your cue to quickly plug the satellite in (mainly providing power to Sat Vcc).

If all goes well D7 LED will turn off and the satellite led should start rapid blinking to indicate satellite is in bind mode.
