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
StringArray violinQualities = {"G3 - thickest, and most sonorous", "D4: least distinctive, yet can exude warmth and lyricism", "A4 : -", "E5 : most brilliant, gets a mysterious qualities at low dynamics"};
StringArray violinRoles = { "Violin 1 : Melody", "Violin 2: Supporting Harmony or doubling the 1st Violins in octaves" };

//Viola
constexpr auto violaRange = "C3 - E6";
constexpr auto violaTransposition = "-";
StringArray violaQualities = { "C3 - most characteristic viola sound; somber, austere, sometimes a bit forbidding", 
"G3: dark", "D4 : dark ", "A4 : piercing and nasal; combines beautifully with woodwinds (in some cases also with soft trumpet and trombones)" };
StringArray violaRoles = { "Often used to double the bassline or fill the harmony in the center (often coupling 2nd Violins)" };

// Violoncello
constexpr auto celloRange = "C2 - C6";
constexpr auto celloTransposition = "-";
StringArray celloQualities = { "C2 : richly, sonorous bass", "G2 : least strong, carries less well than the others",
"D3 : The most musically captivating, exuding warm and lyrical quality", "A4 : Most brilliant and piercing" };
StringArray celloRoles = { "Often doubled with: Bassoon, Contrabass, Horns, Clarinet, Trombone, Tuba or pizzicato Cello with Timpani" };

// Contrabass
constexpr auto contrabassRange = "E2 - C5";
constexpr auto contrabassTransposition = "One octave lower : E1 - C4";
StringArray contrabassQualities = { "E2 : Weighty, dark, powerful -> sonorous fundamental bass", 
"A2 : Sonorous timbre, clearer and more precise", "D3 : Shares Cellos range, but fuller, more powerful and darker",
"G3 : Shares Cello range, but fuller, more powerful and darker" };
StringArray contrabassRoles = { "Often identical to Cello part (especially mid 18th century)" };

//French Horn
constexpr auto frenchHornRange = "F#2 - C6";
constexpr auto frenchHornTransposition = "F: Perfect 5th lower : B1 - F5";
StringArray frenchHornQualities = { "C3 - G3 : dark, a bit unfocused", "G3 - C4 : deep and solid",
"C4 - G5 : bright and heroic", "G5 - C6 : brilliant and loud" };
StringArray frenchHornRoles = { "Can play chromatically with walves", "Creates a feeling of heroism (since the 18th century)", "2 Horns = 1 Trumpet in power" };

//Trumpet
constexpr auto trumpetRange = "F#3 - B3";
constexpr auto trumpetTransposition = "C : as written; Bb : Maj2nd lower (E3 - C6)";
StringArray trumpetQualities = { "F#3 - B3 : rather dull", "C4 - A5 : clear, bright and most articulate", "B5 - D6 : brilliant, but shrill" };
StringArray trumpetRoles = { "Most agile of the brass choir", " Creates an aura of anticipation and excitement", "Often doubled in Oboe and Timpani" };

//Tenor Trombone
constexpr auto tenorTromboneRange = "E2 - A#4";
constexpr auto tenorTromboneTransposition = "-";
StringArray tenorTromboneQualities = { "E2 - G2 : dark, less strong", "A2 - F4 : firm and powerful", "G4 - A#4 : very intense" };
StringArray tenorTromboneRoles = { "Notes below G#3 are only available in 1st position -> fast changing positions are difficult, if the positions are extreme", "Can play glissandi very well", "great for harmony, contrapuntal lines or doubling" };

//Bass Trombone
constexpr auto bassTromboneRange = "A#1 - A#4";
constexpr auto bassTromboneTransposition = "-";
StringArray bassTromboneQualities = { "A#1 - F2 : Heavy and quite strong", "G2 - G3 : Deep and solid", "A3 - A#4 : Very powerful" };
StringArray bassTromboneRoles = { "Can be light and delicate, or hard and menacing", "Pedal tones (lowest harmonic) are easier than on the tenor trombone", "Contrabass Trombone is hard to play and today its parts are mostly assigned to the Tuba" };

//Cimbasso
constexpr auto cimbassoRange = "F1 - F4";
constexpr auto cimbassoTransposition = "-";
StringArray cimbassoQualities = { "F1 - G2 : Full, clear and concise", "G#2 - G3 : Soft, round and bright", "G#3 - F4 : Softer and brighter" };
StringArray cimbassoRoles = { "Similar to the Tuba and Bass Trombone, yet not as metallic as the Bass Trombone and not as sluggish as the Tuba",
"Mixes nicely with Trombones and Trumpets, Horns, Tuba and the Contrabassoon" };

//Tuba
constexpr auto tubaRange = "D1 - G4";
constexpr auto tubaTransposition = "-";
StringArray tubaQualities = { "D1 - A#1 : Deep and heavy", "B2 - E3 : Very strong", "F3 - G4 : Getting weaker, but quite intense" };
StringArray tubaRoles = { "Can play lyrical soft lines as well", "Sometimes 2 Tubas to compensate for the oversized Horn/Trumpet sections",
"Mixes nicely with Trumpets and Horns", "Sluggish in the lows, but very agile in the middle and up" };




/*


"Woodwinds":
{
    "piccolo":
    {
        "Range": f'{ret("D", 4)} - {ret("C", 7)}',
            "RangeM_low" : f'{retM("D", 5)}',
            "RangeM_high" : f'{retM("C", 8)}',
            "Qualities" :
        {
            f'{ret("D", 4)} - {ret("G", 4)}': "quiet, hauntingly hallow",
                f'{ret("A", 4)} - {ret("G", 5)}' : "soft & mellow",
                f'{ret("A", 5)} - {ret("G", 6)}' : "bright & clear",
                f'{ret("A", 6)} - {ret("C", 7)}' : "shrill, edgy"
        },
            "Transposition": f'one octave higher: {ret("D", 5)} - {ret("C", 8)}',
            "Roles" : "--"
    },

        "flute":
    {
        "Range": f'{ret("C", 4)} - {ret("D", 7)}',
            "RangeM_low" : f'{retM("C", 4)}',
            "RangeM_high" : f'{retM("D", 7)}',
            "Qualities" :
        {
            f'{ret("C", 4)} - {ret("G", 4)}': "weak, but lucious",
                f'{ret("A", 4)} - {ret("G", 5)}' : "sweet, but little power",
                f'{ret("A", 5)} - {ret("G", 6)}' : "clear, brilliant",
                f'{ret("A", 6)} - {ret("D", 7)}' : "a bit shrill"
        },
            "Transposition": "None",
            "Roles" : "--"
    },

        "oboe":
    {
        "Range": f'{ret("A#", 3)} - {ret("A", 6)}',
            "RangeM_low" : f'{retM("A#", 3)}',
            "RangeM_high" : f'{retM("A", 6)}',
            "Qualities" :
        {
            f'{ret("A#", 3)} - {ret("F", 4)}': "thick, heavy",
                f'{ret("G", 4)} - {ret("A", 5)}' : "warm, prominent, reedy, poignant",
                f'{ret("B", 5)} - {ret("E", 6)}' : "thin, but clear",
                f'{ret("F", 6)} - {ret("A", 6)}' : "pinched & ineffective"
        },
            "Transposition": "None",
            "Roles" : "avoid ppp / pp in very low or high registers;\n"
            "can hold longer notes, but not very fast repeating staccato notes"
    },

        "cor_anglais":
    {
        "Range": f'{ret("B", 3)} - {ret("G", 6)}',
            "RangeM_low" : f'{retM("E", 2)}',
            "RangeM_high" : f'{retM("C", 6)}',
            "Qualities" :
        {
            f'{ret("B", 3)} - {ret("G", 4)}': "deep, rich, intense",
                f'{ret("A", 4)} - {ret("A", 5)}' : "mellow, reedy, sonorous",
                f'{ret("A", 6)} - {ret("G", 6)}' : "thin, pinched"
        },
            "Transposition": f'P5th lower: {ret("E", 2)} - {ret("C", 6)}',
            "Roles" : "melancholic touch, most used for sadness;\n"
            "much more mellow than the oboe -> does not cut through \n"
            " as easily as the oboe"
    },

        "clarinet":
    {
        "Range": f'{ret("E", 3)} - {ret("C", 7)}',
            "RangeM_low" : f'{retM("D", 3)}', # here : Bb Clarinet
            "RangeM_high" : f'{retM("B", 6)}',
            "Qualities" :
        {
            f'{ret("E", 3)} - {ret("F#", 4)}': "Chalumeau Register: deep & rich",
                f'{ret("G", 4)} - {ret("A#", 4)}' : "Throat Tones: rather pale",
                f'{ret("B", 4)} - {ret("C", 6)}' : "Clarino Register: bright, incisive, expressive",
                f'{ret("D", 6)} - {ret("C", 7)}' : "shrill, piercing"
        },
            "Transposition": f'Bb: Maj2nd lower: {ret("D", 3)} - {ret("B", 6)};\n'
            f'A: min3rd lower: {ret("C#", 3)} - {ret("A#", 6)}',
            "Roles" : f'homogenous across all pitches-dynamics;\n'
            f'fingering break between: {ret("A#", 4)} - {ret("B", 4)};\n'
            f'"Clarinet in A better for sharp keys;\n'
            f'Clarinet in Bb better for flat keys;\n'
            f'"Nightingale of the orchestra"'
    },

        "bass_clarinet":
    {
        "Range": f'{ret("D#", 3)} - {ret("G", 6)}',
            "RangeM_low" : f'{retM("C#", 2)}',
            "RangeM_high" : f'{retM("E", 5)}',
            "Qualities" :
        {
            f'{ret("D#", 3)} - {ret("G", 3)}': "Chalumeau Register, mysterious, shadowy, sinister",
                f'{ret("A", 3)} - {ret("G", 4)}' : "Clarino Register",
                f'{ret("A", 4)} - {ret("G", 6)}' : "thin, difficult to produce"
        },
            "Transposition": f'treble clef: Maj9th lower: {ret("C#", 2)} - {ret("E", 5)} ->  most common;\n'
            f'bass clef: Maj2nd lower: {ret("D", 3)} - {ret("F", 6)}',
            "Roles" : "mostly notated in the treble clef nowadays;\n"
            "very agile, but not as incisively as the smaller relative"
    },

        "bassoon":
    {
        "Range": f'{ret("A#", 1)} - {ret("D#", 5)}',
            "RangeM_low" : f'{retM("A#", 1)}',
            "RangeM_high" : f'{retM("D#", 5)}',
            "Qualities" :
        {
            f'{ret("A#", 1)} - {ret("G", 2)}': "sonorous, dark, vibrant",
                f'{ret("A", 2)} - {ret("D", 4)}' : "sweet, more subdued, but expressive",
                f'{ret("E", 4)} - {ret("A#", 4)}' : "thin, but intense",
                f'{ret("B", 4)} - {ret("D#", 5)}' : "thin, often pinched"
        },
            "Transposition": "None",
            "Roles" : "often in unison with the clarinet;\n"
            "lowest & highest P5 intervals are quite difficult/not playable \n"
            " at low dynamics"
    },

        "contrabassoon":
    {
        "Range": f'{ret("A#", 1)} - {ret("A#", 4)}',
            "RangeM_low" : f'{retM("A#", 0)}',
            "RangeM_high" : f'{retM("A#", 3)}',
            "Qualities" : f'similar characteristics as the bassoon, but slower and more \n'
            f' stubborn and resistant in the lows;\n'
            f'most effective range is its lowest 12th: {ret("A#", 1)} - {ret("F", 3)}',
            "Transposition" : f'Octave lower: {ret("A#", 0)} - {ret("A#", 3)}',
            "Roles" : "often doubled with double basses & bassoons / celli at octave;\n"
            "in its higher register it's a lot paler and weaker than the bassoon;\n"
            "needs periodic rests due to its size"
    }
},
"Percussion":
{
    "harp":
    {
        "Range": f'{ret("B", 1)} - {ret("F#", 7)}',
            "RangeM_low" : f'{retM("B", 1)}',
            "RangeM_high" : f'{retM("F#", 7)}',
            "Qualities" :
        {
            f'{ret("B", 1)} - {ret("B", 3)}': "dark, sonorous",
                f'{ret("C", 3)} - {ret("C", 5)}' : "rich, warm",
                f'{ret("C#", 5)} - {ret("F#", 7)}' : "bright, clear, not much dynamic range",
        },
            "Transposition": "None",
            "Roles" : f'Sometimes 2 harps are used;\n'
            f'chords with 4 notes in each hand;\n'
            f'pedals: DCB/EFGA;\n'
            f'pres-de-la-table -> near the board -> creates a guitar like sound;\n'
            f'bisbigliando (transl.: whispering) -> alternating picking;\n'
            f'glissando -> heavenly sound'
    },

        "celeste":
    {
        "Range": f'{ret("C", 3)} - {ret("C", 8)}',
            "RangeM_low" : f'{retM("C", 3)}',
            "RangeM_high" : f'{retM("C", 8)}',
            "Qualities" : f'silvery, glistening, ethereal, sweet, shimmering;\n'
            f'the timbre is homogenous across the pitches;\n'
            f'sounding warmer and rounder than the glockenspiel;\n'
            f'sound is not load -> gets covered easily by the orchestra;\n'
            f'though it is touch-responsive, the dynamic range is limited',
            "Transposition" : "None",
            "Roles" : "provides highlights in form of chords or single notes \n"
            "(similar to triangle/glockenspiel);\n"
            "doubling other voices in (multiple) octaves, unison or fifth;\n"
            "piano figures consisting of glissando-like scales, arpeggios or \n"
            "  octave tremolos"
    },

        "timpani":
    {
        "Range": f'{ret("B", 1)} - {ret("C", 4)}',
            "RangeM_low" : f'{retM("B", 1)}',
            "RangeM_high" : f'{retM("C", 4)}',
            "Qualities" : f'dull, thunderous, deep, heavy, velvety, dry;\n'
            f'great dynamic range;\n'
            f'timbre is determined by the mallet, where the head is struck\n'
            f' and how hard',
            "Transposition" : "None",
            "Roles" : "doubled in unison with other bass instruments creates a \n"
            "  homogeneous blend;\n"
            "blends nicely with trumpets and horns (e.g. 2 horns + \n"
            "  timpani in unison with other horns in octaves and \n"
            "  trumpets in 2 octaves playing the root;\n"
            "timpani rolls doubled with string tremolo chords have a \n"
            "  tremendous effect;\n"
            "mixes nicely with pizz. strings and harps "
    },

        "marimba":
    {
        "Range": f'{ret("C", 2)} - {ret("C", 7)}',
            "RangeM_low" : f'{retM("C", 2)}',
            "RangeM_high" : f'{retM("C", 7)}',
            "Qualities" : f'dark, mellow,gentle, melodious, resonant;\n'
            f'sound depends on the mallet: the harder the mallet, the louder the\n'
            f' initial attack, and the more prominent the higher partials',
            "Transposition" : "None",
            "Roles" : "with percussion -> full sounding with celeste and glockenspiel \n"
            "  in octaves or unison;\n"
            "with brass -> as an accompaniment to trumpet melodies;\n"
            "with woodwinds -> mellow-sounding and sonorous, blends well \n"
            "  in octaves, especially with deep clarinets;\n"
            "with strings -> full-sounding in unison and octaves with low strings,\n"
            "  yet blend is incomplete"
    },
}

    }

*/