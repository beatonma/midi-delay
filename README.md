# MIDI delay

Written for an Arduino Uno with MIDI IN, MIDI OUT, MIDI THRU.

Delays incoming MIDI messages before sending them onward to MIDI OUT.

Original messages pass untouched via MIDI THRU, so two different devices receive the same MIDI messages
with a short delay in between.
