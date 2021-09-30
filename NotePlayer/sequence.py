import os
import time

music_files = os.listdir('music')

for file in music_files:
    try:
        os.unlink("melody.h")
    except:
        pass
    os.symlink("music/" + file, "melody.h")
    os.system("SKETCH=NotePlayer && arduino-cli compile --fqbn arduino:avr:uno $SKETCH && arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno $SKETCH")
    time.sleep(45)

