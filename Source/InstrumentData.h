/*
  ==============================================================================

    InstrumentData.h
    Created: 5 Apr 2024 6:49:24pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//Violin
constexpr auto violinRange = "G3 - A7";
constexpr auto violinTransposition = "-";
const StringArray violinQualities = {"G3 - thickest, and most sonorous", "D4: least distinctive, yet can exude warmth and lyricism", "A4 : -", "E5 : most brilliant, gets a mysterious qualities at low dynamics"};
const StringArray violinRoles = { "Violin 1 : Melody", "Violin 2: Supporting Harmony or doubling the 1st Violins in octaves" };

//Viola
constexpr auto violaRange = "C3 - E6";
constexpr auto violaTransposition = "-";
const StringArray violaQualities = { "C3 - most characteristic viola sound; somber, austere, sometimes a bit forbidding", 
"G3: dark", "D4 : dark ", "A4 : piercing and nasal; combines beautifully with woodwinds (in some cases also with soft trumpet and trombones)" };
const StringArray violaRoles = { "Often used to double the bassline or fill the harmony in the center (often coupling 2nd Violins)" };

// Violoncello
constexpr auto celloRange = "C2 - C6";
constexpr auto celloTransposition = "-";
const StringArray celloQualities = { "C2 : richly, sonorous bass", "G2 : least strong, carries less well than the others",
"D3 : The most musically captivating, exuding warm and lyrical quality", "A4 : Most brilliant and piercing" };
const StringArray celloRoles = { "Often doubled with: Bassoon, Contrabass, Horns, Clarinet, Trombone, Tuba or pizzicato Cello with Timpani" };

// Contrabass
constexpr auto contrabassRange = "E2 - C5";
constexpr auto contrabassTransposition = "One octave lower : E1 - C4";
const StringArray contrabassQualities = { "E2 : Weighty, dark, powerful -> sonorous fundamental bass", 
"A2 : Sonorous timbre, clearer and more precise", "D3 : Shares Cellos range, but fuller, more powerful and darker",
"G3 : Shares Cello range, but fuller, more powerful and darker" };
const StringArray contrabassRoles = { "Often identical to Cello part (especially mid 18th century)" };

//French Horn
constexpr auto frenchHornRange = "F#2 - C6";
constexpr auto frenchHornTransposition = "F: Perfect 5th lower : B1 - F5";
const StringArray frenchHornQualities = { "C3 - G3 : dark, a bit unfocused", "G3 - C4 : deep and solid",
"C4 - G5 : bright and heroic", "G5 - C6 : brilliant and loud" };
const StringArray frenchHornRoles = { "Can play chromatically with walves", "Creates a feeling of heroism (since the 18th century)", "2 Horns = 1 Trumpet in power" };

//Trumpet
constexpr auto trumpetRange = "F#3 - B3";
constexpr auto trumpetTransposition = "C : as written; Bb : Maj2nd lower (E3 - C6)";
const StringArray trumpetQualities = { "F#3 - B3 : rather dull", "C4 - A5 : clear, bright and most articulate", "B5 - D6 : brilliant, but shrill" };
const StringArray trumpetRoles = { "Most agile of the brass choir", " Creates an aura of anticipation and excitement", "Often doubled in Oboe and Timpani" };

//Tenor Trombone
constexpr auto tenorTromboneRange = "E2 - A#4";
constexpr auto tenorTromboneTransposition = "-";
const StringArray tenorTromboneQualities = { "E2 - G2 : dark, less strong", "A2 - F4 : firm and powerful", "G4 - A#4 : very intense" };
const StringArray tenorTromboneRoles = { "Notes below G#3 are only available in 1st position -> fast changing positions are difficult, if the positions are extreme", "Can play glissandi very well", "great for harmony, contrapuntal lines or doubling" };

//Bass Trombone
constexpr auto bassTromboneRange = "A#1 - A#4";
constexpr auto bassTromboneTransposition = "-";
const StringArray bassTromboneQualities = { "A#1 - F2 : Heavy and quite strong", "G2 - G3 : Deep and solid", "A3 - A#4 : Very powerful" };
const StringArray bassTromboneRoles = { "Can be light and delicate, or hard and menacing", "Pedal tones (lowest harmonic) are easier than on the tenor trombone", "Contrabass Trombone is hard to play and today its parts are mostly assigned to the Tuba" };

//Cimbasso
constexpr auto cimbassoRange = "F1 - F4";
constexpr auto cimbassoTransposition = "-";
const StringArray cimbassoQualities = { "F1 - G2 : Full, clear and concise", "G#2 - G3 : Soft, round and bright", "G#3 - F4 : Softer and brighter" };
const StringArray cimbassoRoles = { "Similar to the Tuba and Bass Trombone, yet not as metallic as the Bass Trombone and not as sluggish as the Tuba",
"Mixes nicely with Trombones and Trumpets, Horns, Tuba and the Contrabassoon" };

//Tuba
constexpr auto tubaRange = "D1 - G4";
constexpr auto tubaTransposition = "-";
const StringArray tubaQualities = { "D1 - A#1 : Deep and heavy", "B2 - E3 : Very strong", "F3 - G4 : Getting weaker, but quite intense" };
const StringArray tubaRoles = { "Can play lyrical soft lines as well", "Sometimes 2 Tubas to compensate for the oversized Horn/Trumpet sections",
"Mixes nicely with Trumpets and Horns", "Sluggish in the lows, but very agile in the middle and up" };


//Piccolo
constexpr auto piccoloRange = "D4 - C7";
constexpr auto picooloTransposition = "One octave higher : D5 - C8";
const StringArray piccoloQualities = { "D4 - G4 : Quiet, hauntingly hallow", "A4 - G5 : Soft and mallow", "A5 - G6 : Bright and clear",
"A6 - C7 : Shrill, edgy" };
const StringArray piccoloRoles = { "--" };

//Flute
constexpr auto fluteRange = "C4 - D7";
constexpr auto fluteTransposition = "-";
const StringArray fluteQualities = { "C4 - G4 : Weak, but lucious", "A4 - G5 : Sweet, but little power", "A5 - G6 : Clear, brilliant", "A6 - D7 : a bit shrill" };
const StringArray fluteRoles = { "--" };

//Oboe
constexpr auto oboeRange = "A#3 - A6";
constexpr auto oboeTransposition = "-";
const StringArray oboeQualities = { "A#3 - F4 : Thick, heavy", "G4 - A5 : Warm, prominent, reedy, poignant", "B5 - E6 : Thin, but clear", "F6 - A6 : Pinched and effective" };
const StringArray oboeRoles = { "Avoid ppp / pp in very low or high registers", "Can hold longer notes, but not very fast repeating staccato notes" };

//Cor Anglais
constexpr auto corAnglaisRange = "B3 - G6";
constexpr auto corAnglaisTransposition = "Perfect 5th lower : E2 - C6";
const StringArray corAnglaisQualities = { "B3 - G4 : Deep, rich, intense", "A4 - A5 : Mellow, reedy, sonorous", "A6 - G6 : Thin, pinched" };
const StringArray corAnglaisRoles = { "Melancholic touch, most used for sadness", "Much more mellow than the Oboe -> does not cut through as easily as the Oboe" };

//Clarinet
constexpr auto clarinetRange = "E3 - C7";
constexpr auto clarinetTransposition = "Bb : Maj2nd lower (D3 - B6) ; A: min3rd lower (C#3 - A#6)";
const StringArray clarinetQualities = { "E3 - F#4 : Chalumau Register: deep and rich", "G4 - A#4 : Throat Tones: rather pale", "B4 - C6 : Clarino Register: bright, incisive, expressive", "D6 - C7 : Shrill, piercing" };
const StringArray clarinetRoles = { "Homogenous accross all pitches-dynamics", "Fingering break between A#4 - B4", "Clarinet in A is better for sharp keys", "Clarinet in Bb is better for flat keys", "Known as the nightingale of the orchestra" };

//Bass Clarinet
constexpr auto bassClarinetRange = "D#3 - G6";
constexpr auto bassClarinetTransposition = "Treble Clef: Maj9th lower (C#2 - E5) -> most common ; Bass Clef: Maj2nd lower (D3 - F6)";
const StringArray bassClarinetQualities = { "D#3 - G3 : Chalumeau Register, mysterious, shadowy, sinister", "A3 - G4 : Clarino Register", "A4 - G6 : Thin, difficult to produce" };
const StringArray bassClarinetRoles = { "Mostly notated in the treble clef nowadays", "Very agile, but not as incisively as the smaller relative" };

//Bassoon
constexpr auto bassoonRange = "A#1 - D#5";
constexpr auto bassoonTransposition = "-";
const StringArray bassoonQualities = { "A#1 - G2 : Sonorous, dark, vibrant", "A2 - D4 : Sweet, more subdued, but expressive", "E4 - A#4 : Thin, but intense", "B4 - D#5 : Thin, often pinched" };
const StringArray bassoonRoles = { "Often in unsion with the Clarinet", "Lowest and Highest P5 intervals are quite difficult/not playable at low dynamics" };

//Contrabassoon
constexpr auto contraBassoonRange = "A#1 - A#4";
constexpr auto contraBassoonTranspositon = "One octave lower (A#0 - A#3)";
const StringArray contraBassoonQualities = { "Similar characteristics as the Bassoon, but slower and more stubborn and resistant in the lows" };
const StringArray contraBassoonRoles = { "Often doubled with Contrabasses and Bassoons / Celli at octave", "In its higher register it's a lot paler and weaker than the Bassoon", "Needs periodic rests due to its size" };

//Harp
constexpr auto harpRange = "B1 - F#7";
constexpr auto harpTransposition = "-";
const StringArray harpQualities = { "B1 - B3 : Dark, sonorous", "C3 - C5 : Righ, warm", "C#5 - F#7 : Bright, clear, nut much dynamic range" };
const StringArray harpRoles = { "Sometimes 2 harps are used", "Chords with 4 notes in each hand", "Pedals declaration order : DCB/EFGA", "pres-de-la-table (near the board) creates a guitar-like sound", "bisbligiando (whispering) -> alternating picking", "glissando -> heavenly sound" };

//Celeste
constexpr auto celesteRange = "C3 - C8";
constexpr auto celesteTransposition = "-";
const StringArray celesteQualities = { "Silvery, glistening, ethereal, sweet, shimmering", "The timbre is homogenous accross pitches", "Sounding warmer and rounder than the Glockenspiel", "Sound is not loud -> gets covered easily in the orchestra", "Though it's touch-responsive, the dynamic range is limited" };
const StringArray celesteRoles = { "Provides highlights in form of chords or single notes (similar to Triangle/Glockenspiel)", "Doubling other voices in (multiple) octaves, unsions or 5th", "Piano figures consisting of glissando-like scales, arpeggios or octave tremolos" };

//Timpani
constexpr auto timpaniRange = "B1 - C4";
constexpr auto timpaniTransposition = "-";
const StringArray timpaniQualities = { "Dull, thunderous, deep, heavy, velvety, dry", "Great dynamic range", "Timbre is determined by the mallet used, where the head is struck and how hard" };
const StringArray timpaniRoles = { "Doubled in unison with other bass instruments creates a homogenous blend", "Blends nicely with Trumpets and Horns (e.g. 2 Horns + Timpani in unsion + other Horns in octaves + Trumpets in 2 octaves playing the root", "Timpani rolls doubled with String tremolo chords have a tremendous effect", "Mixes nicely with pizzicato Strings and Harps" };

//Marimba
constexpr auto marimbaRange = "C2 - C7";
constexpr auto marimbaTransposition = "-";
const StringArray marimbaQualities = { "Dark, mellow, gentle, melodious, resonant", "Sound depends on the mallet : The harder the mallet, the louder the initial attack, and the more prominent the higher partials" };
const StringArray marimbaRoles = { "With Percussion : full sounding with Celeste and Glockenspiel in octaves or unison", "With Brass : as a accompaniment to Trumpet melodies", "With Woodwinds : mellow-sounding and sonorous, blends well in octaves, especially with deep clarinets", "With Strings : full sounding in unison and octaves with low Strings, yet blend is incomplete" };

