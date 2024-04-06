/*
  ==============================================================================

    InstrumentData.h
    Created: 5 Apr 2024 6:49:24pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Violin
constexpr auto violinRange = "G3 - A7";
constexpr auto violinTransposition = "-";
const StringArray violinQualities = 
{
    "G3: Rich and resonant, foundational for warmth and depth",
    "D4: Subtly vibrant, a balance of warmth and lyrical expression",
    "A4: Versatile, blends smoothly across ensembles",
    "E5: Bright and penetrating, carries a mysterious quality at softer dynamics"
};
const StringArray violinRoles = 
{
    "Leads with melody, expressive and prominent",
    "Provides harmonic support",
    "Enriches texture",
    "Complements first violins in octaves"
};

// Viola
constexpr auto violaRange = "C3 - E6";
constexpr auto violaTransposition = "-";
const StringArray violaQualities = 
{
    "C3: Most characteristic viola sound; somber, austere, sometimes a bit forbidding",
    "G3: Rich and dark, capable of profound depth",
    "D4: Dark and resonant, with a velvety quality",
    "A4: Piercing and nasal; blends well with woodwinds, soft trumpets, and trombones"
};
const StringArray violaRoles = 
{
    "Fills harmony in the center",
    "Often doubling second violins or basslines",
    "Enriches the orchestral texture"
};

// Violoncello (Cello)
constexpr auto celloRange = "C2 - C6";
constexpr auto celloTransposition = "-";
const StringArray celloQualities = 
{
    "C2: Richly sonorous bass, profound and enveloping",
    "G2: Subtler strength, carries warmth and expressiveness",
    "D3: Musically captivating, warm and lyrical quality",
    "A3: Brilliant and piercing, with a vibrant upper register"
};
const StringArray celloRoles = 
{
    "Versatile in melody and harmony",
    "Often doubled with bassoon",
    "Frequently coupled with contrabass",
    "Complements horns and clarinets",
    "Supports trombone and tuba lines",
    "Effective in pizzicato alongside timpani"
};

// Contrabass
constexpr auto contrabassRange = "E1 - C4";
constexpr auto contrabassTransposition = "Sounds one octave lower than written";
const StringArray contrabassQualities = 
{
    "E1: Weighty, dark, and powerful with a sonorous fundamental bass",
    "A1: Clear and precise with a sonorous timbre",
    "D2: Fuller, more powerful, and darker, sharing the cello's range",
    "G2: Similarly full and powerful, darker than the cello"
};
const StringArray contrabassRoles = 
{
    "Provides foundational bass",
    "Often doubling the cello, especially in mid 18th-century music"
};

// French Horn
constexpr auto frenchHornRange = "F2 - C6";
constexpr auto frenchHornTransposition = "F: Sounds a perfect 5th lower";
const StringArray frenchHornQualities = 
{
    "F2 - G3: Dark and a bit unfocused, with a mysterious depth",
    "A3 - C4: Deep and solid, the core of the horn's range",
    "C4 - G5: Bright and heroic, capable of stirring emotions",
    "G5 - C6: Brilliant and loud, cutting through the orchestra with clarity"
};
const StringArray frenchHornRoles = 
{
    "Capable of playing chromatically with valves",
    "Emblematic of heroism since the 18th century",
    "Equivalent in power to two trumpets"
};

// Trumpet
constexpr auto trumpetRange = "F#3 - D6";
constexpr auto trumpetTransposition = "C: as written; Bb: Major 2nd lower";
const StringArray trumpetQualities = 
{
    "F#3 - B3: Warm but can be dull, foundational",
    "C4 - A5: Clear, bright, and articulate, the trumpet's sweet spot",
    "B5 - D6: Brilliant but can be shrill at the extreme upper range"
};
const StringArray trumpetRoles = 
{
    "Agile within the brass choir",
    "Creates anticipation and excitement",
    "Often doubled with oboe and timpani"
};

// Tenor Trombone
constexpr auto tenorTromboneRange = "E2 - Bb4";
constexpr auto tenorTromboneTransposition = "-";
const StringArray tenorTromboneQualities = 
{
    "E2 - G2: Dark and commanding, with a foundational depth",
    "A2 - F4: Firm, powerful, and resonant across its core range",
    "G4 - Bb4: Intense and commanding, with a significant presence"
};
const StringArray tenorTromboneRoles = 
{
    "Excels in glissandi and legato passages",
    "Effective in harmony and contrapuntal lines",
    "Useful for doubling",
    "Fast position changes can be challenging"
};

// Bass Trombone
constexpr auto bassTromboneRange = "Bb1 - Bb4";
constexpr auto bassTromboneTransposition = "-";
const StringArray bassTromboneQualities = 
{
    "Bb1 - F2: Heavy and strong, with a profound bass foundation",
    "G2 - G3: Deep and solid, adding weight to the ensemble",
    "A3 - Bb4: Very powerful, with a commanding upper register"
};
const StringArray bassTromboneRoles = 
{
    "Can be light and agile or hard and menacing",
    "Pedal tones more accessible than on the tenor trombone",
    "Often parts now assigned to the tuba"
};

// Cimbasso
constexpr auto cimbassoRange = "F1 - F4";
constexpr auto cimbassoTransposition = "-";
const StringArray cimbassoQualities = 
{
    "F1 - G2: Full, clear, and concise, with a robust foundation",
    "G#2 - G3: Soft, round, and bright, adding a unique color",
    "G#3 - F4: Softer and brighter, lending subtlety to the ensemble"
};
const StringArray cimbassoRoles = 
{
    "Combines qualities of tuba and bass trombone without the metallic edge",
    "Mixes well with low brass and woodwinds"
};

// Tuba
constexpr auto tubaRange = "D1 - F4";
constexpr auto tubaTransposition = "-";
const StringArray tubaQualities = 
{
    "D1 - Bb1: Deep and heavy, anchoring the orchestra",
    "B1 - E3: Strong and resonant, with a commanding presence",
    "F3 - F4: Weaker in the upper register but still intense"
};
const StringArray tubaRoles = 
{
    "Capable of lyrical lines and providing foundation",
    "Often paired with a second tuba for balance against large horn and trumpet sections"
};


// Piccolo
constexpr auto piccoloRange = "D4 - C8";
constexpr auto piccoloTransposition = "Sounds one octave higher than written";
const StringArray piccoloQualities = 
{
    "D4 - G4: Quiet, hauntingly hollow",
    "A4 - G5: Soft and mellow",
    "A5 - G6: Bright and clear",
    "A6 - C8: Shrill, edgy"
};
const StringArray piccoloRoles = 
{
    "Excels in adding brightness and flair to the upper register",
    "Effective in punctuating musical phrases",
    "Used for special coloristic effects"
};

// Flute
constexpr auto fluteRange = "C4 - D7";
constexpr auto fluteTransposition = "-";
const StringArray fluteQualities = 
{
    "C4 - G4: Weak, but luscious",
    "A4 - G5: Sweet, with little power",
    "A5 - G6: Clear and brilliant",
    "A6 - D7: A bit shrill"
};
const StringArray fluteRoles = 
{
    "Carries the melody in higher registers",
    "Provides light and agile articulations",
    "Used for lyrical passages and fast runs"
};

// Oboe
constexpr auto oboeRange = "Bb3 - A6";
constexpr auto oboeTransposition = "-";
const StringArray oboeQualities = 
{
    "Bb3 - F4: Thick and heavy",
    "G4 - A5: Warm, prominent, reedy, poignant",
    "B5 - E6: Thin, but clear",
    "F6 - A6: Pinched and effective"
};
const StringArray oboeRoles = 
{
    "Avoids very soft dynamics in the extreme registers",
    "Excels in carrying the melodic line with its distinctive timbre",
    "Suitable for long, sustained notes and expressive solos"
};

// Cor Anglais (English Horn)
constexpr auto corAnglaisRange = "B3 - G6";
constexpr auto corAnglaisTransposition = "Sounds a perfect 5th lower than written";
const StringArray corAnglaisQualities = {
    "B3 - G4: Deep, rich, and intense",
    "A4 - A5: Mellow, reedy, sonorous",
    "A6 - G6: Thin, pinched"
};
const StringArray corAnglaisRoles = 
{
    "Imparts a melancholic touch, often used to convey sadness",
    "More mellow than the oboe, blending well without dominating",
    "Excellent for solo passages requiring depth and emotion"
};

// Clarinet
constexpr auto clarinetRange = "E3 - C7";
constexpr auto clarinetTransposition = "Bb: Major 2nd lower; A: Minor 3rd lower";
const StringArray clarinetQualities = 
{
    "E3 - F#4: Chalumeau Register: deep and rich",
    "G4 - A#4: Throat Tones: rather pale",
    "B4 - C6: Clarino Register: bright, incisive, expressive",
    "D6 - C7: Shrill, piercing"
};
const StringArray clarinetRoles = 
{
    "Homogenous across all pitches and dynamics",
    "Features a fingering break between A#4 and B4",
    "The A clarinet is better for sharp keys, while the Bb clarinet favors flat keys",
    "Known for its lyrical qualities and flexibility"
};

// Bass Clarinet
constexpr auto bassClarinetRange = "D3 - G6";
constexpr auto bassClarinetTransposition = "Bb: Sounds a major ninth lower";
const StringArray bassClarinetQualities = 
{
    "D3 - G3: Chalumeau Register: mysterious, shadowy, sinister",
    "A3 - G4: Clarino Register: versatile and expressive",
    "A4 - G6: Thin, challenging to produce"
};
const StringArray bassClarinetRoles = 
{
    "Notated in treble clef, sounding a major ninth lower",
    "Agile, capable of blending or standing out",
    "Suitable for bass lines as well as melodic passages in its mid to upper range"
};

// Bassoon
constexpr auto bassoonRange = "Bb1 - Eb5";
constexpr auto bassoonTransposition = "-";
const StringArray bassoonQualities = 
{
    "Bb1 - G2: Sonorous, dark, vibrant",
    "A2 - D4: Sweet, subdued, but expressive",
    "E4 - Bb4: Thin, but intense",
    "B4 - Eb5: Thin, often pinched"
};
const StringArray bassoonRoles = 
{
    "Often unison with clarinet",
    "The lowest and highest P5 intervals are challenging/not playable at low dynamics",
    "Versatile for both foundational bass lines and melodic solos"
};

// Contrabassoon
constexpr auto contraBassoonRange = "Bb0 - Bb4";
constexpr auto contraBassoonTransposition = "Sounds one octave lower than written";
const StringArray contraBassoonQualities = 
{
    "Similar characteristics as the Bassoon but slower and more stubborn in the lows"
};
const StringArray contraBassoonRoles = 
{
    "Doubles with contrabasses and bassoons/celli at octave",
    "In its higher register, it's paler and weaker than the bassoon",
    "Requires periodic rests due to its size and breath demands"
};

// Timpani
constexpr auto timpaniRange = "D2 - C4";
constexpr auto timpaniTransposition = "-";
const StringArray timpaniQualities = 
{
    "Can vary from dull to thunderous, deep, heavy, velvety, to dry, depending on mallet and technique used"
};
const StringArray timpaniRoles = 
{
    "Unison with bass instruments creates a homogenous blend",
    "Blends nicely with trumpets and horns, adding depth and resonance",
    "Rolls combined with string tremolo chords produce a tremendous effect",
    "Works well with pizzicato strings and harps for rhythmic elements"
};

// Harp
constexpr auto harpRange = "C1 - G7";
constexpr auto harpTransposition = "-";
const StringArray harpQualities = 
{
    "C1 - B3: Deep and sonorous",
    "C4 - C6: Rich, warm",
    "C#6 - G7: Bright, clear, with limited dynamic range"
};
const StringArray harpRoles = 
{
    "Sometimes used in pairs for fuller sound",
    "Chords and arpeggios lend a unique texture",
    "Pedal adjustments allow for chromaticism and modulation",
    "Special techniques like pres de la table and bisbigliando add color",
    "Glissandi create ethereal soundscapes"
};

// Celesta
constexpr auto celesteRange = "C4 - C8";
constexpr auto celesteTransposition = "-";
const StringArray celesteQualities = 
{
    "Silvery, glistening, ethereal, sweet, shimmering across its range",
    "Warmer and rounder than the glockenspiel",
    "Not very loud, can be easily covered by the orchestra",
    "Limited dynamic range but responsive to touch"
};
const StringArray celesteRoles = 
{
    "Highlights in chords or single notes, akin to triangle/glockenspiel",
    "Effective for doubling voices in octaves, unisons, or fifths",
    "Used for dreamlike scales, arpeggios, or octave tremolos"
};

// Marimba
constexpr auto marimbaRange = "C2 - C7";
constexpr auto marimbaTransposition = "-";
const StringArray marimbaQualities = 
{
    "Dark, mellow, gentle, melodious, resonant",
    "Sound character varies with mallet hardness: harder mallets emphasize higher partials"
};
const StringArray marimbaRoles = 
{
    "Pairs well with percussion, especially celeste and glockenspiel",
    "Accompanies brass melodies, particularly trumpet",
    "Blends with woodwinds, adding warmth in octaves",
    "Complements low strings in unison and octaves, though blend may vary"
};
