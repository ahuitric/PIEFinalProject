import mido

mid = mido.MidiFile('Queen - Bohemian Rhapsody.mid', clip=True)
#print(mid.tracks)

for m in mid.tracks[1][:20]:
    print(m)
