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
    " 2nd Violins complements first violins in octaves"
};
const StringArray violinFamousWorks = {
    "Beethoven - Violin Concerto in D major, Op. 61",
    "Tchaikovsky - Violin Concerto in D major, Op. 35",
    "Mendelssohn - Violin Concerto in E minor, Op. 64"
};
const StringArray violinPlayingTechniques = {
    "Vibrato: Varying pitch slightly for warmth",
    "Pizzicato: Plucking the strings",
    "Spiccato: Bouncing the bow for light, short notes"
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
const StringArray violaFamousWorks = 
{
    "Walton - Viola Concerto",
    "Bartok - Viola Concerto",
    "Hindemith - Der Schwanendreher"
};
const StringArray violaPlayingTechniques = 
{
    "Tremolo: Rapid back-and-forth bowing",
    "Sul tasto: Playing over the fingerboard for a softer sound",
    "Col legno: Tapping the strings with the wood of the bow"
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
const StringArray celloFamousWorks = 
{
    "Dvořák - Cello Concerto in B minor, Op. 104",
    "Elgar - Cello Concerto in E minor, Op. 85",
    "Haydn - Cello Concerto No. 1 in C major"
};
const StringArray celloPlayingTechniques = 
{
    "Sul ponticello: Playing near the bridge for a tense sound",
    "Sul tasto: Playing over the fingerboard for a flute-like tone",
    "Con sordino: Using a mute to soften the sound"
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
const StringArray doubleBassFamousWorks = 
{
    "Koussevitzky - Double Bass Concerto in F# minor, Op. 3",
    "Bottesini - Double Bass Concerto No. 2 in B minor",
    "Dittersdorf - Double Bass Concerto No. 2 in E major"
};
const StringArray doubleBassPlayingTechniques = 
{
    "Pizzicato: Plucking the strings with fingers",
    "Slap bass: A technique used in jazz, slapping the strings against the fingerboard",
    "Arco: Using the bow to produce sound"
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
const StringArray frenchHornFamousWorks = 
{
    "Mozart - Horn Concerto No. 4 in E flat major, K. 495",
    "Strauss - Horn Concerto No. 1 in E flat major, Op. 11",
    "Schumann - Konzertstück for Four Horns and Orchestra"
};
const StringArray frenchHornPlayingTechniques = 
{
    "Stopped Horn: Hand in the bell to alter pitch/timbre",
    "Rip: Quick, glissando-like rise to a higher note",
    "Bell Up: Raising the bell for a louder, more projected sound"
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
const StringArray trumpetFamousWorks = 
{
    "Haydn - Trumpet Concerto in E-flat major",
    "Hummel - Trumpet Concerto in E major",
    "Dmitri Shostakovich - Concerto No. 1 for Piano, Trumpet, and String Orchestra"
};
const StringArray trumpetPlayingTechniques = 
{
    "Mute: Inserting a mute into the bell to alter the sound",
    "Sforzando: A sudden forceful emphasis",
    "Rip: A rapid ascending glissando"
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
const StringArray tenorTromboneFamousWorks = 
{
    "Rimsky-Korsakov - Trombone Concerto in B-flat major",
    "David - Concertino in E flat major, Op. 4",
    "Grøndahl - Trombone Concerto"
};
const StringArray tenorTrombonePlayingTechniques = 
{
    "Legato slide: Smooth transition between notes",
    "Mute use: Employing different mutes to alter the timbre",
    "Glissando: Slide between notes for a smooth sound"
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
const StringArray bassTromboneFamousWorks = 
{
    "Lebedev - Concerto in One Movement",
    "Ewazen - Concerto for Bass Trombone",
    "Schnyder - SubZERO Bass Trombone Concerto"
};
const StringArray bassTrombonePlayingTechniques = 
{
    "Pedal tones: Playing the very low notes of the instrument's range",
    "Blatt: A rapid articulation technique",
    "Multiphonics: Singing and playing at the same time to create chords"
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
const StringArray cimbassoFamousWorks = 
{
    "Verdi - Operas like Aida and Otello, where it often replaces the bass trombone and tuba",
    "Puccini - Turandot",
    "Contemporary film scores and symphonic works that require a unique brass tone"
};
const StringArray cimbassoPlayingTechniques = 
{
    "Valve technique: For rapid passage work",
    "Mute use: To alter the sound for different effects",
    "Blending: Mixing with the trombone section for a cohesive sound"
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
const StringArray tubaFamousWorks = 
{
    "Vaughan Williams - Tuba Concerto in F minor",
    "John Williams - Concerto for Tuba and Orchestra",
    "Hindemith - Sonata for Bass Tuba and Piano"
};
const StringArray tubaPlayingTechniques = 
{
    "Circular breathing: For continuous play without taking a breath",
    "Multiphonics: Producing multiple notes at once",
    "Flutter tonguing: Rolling the 'R' for a trembling effect"
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
const StringArray piccoloFamousWorks = 
{
    "Vivaldi - Piccolo Concerto in C Major, RV 443",
    "Tchaikovsky - Symphony No. 4 (2nd movement)",
    "Rimsky-Korsakov - Scheherazade"
};
const StringArray piccoloPlayingTechniques = 
{
    "Flutter tonguing: Producing a fluttering sound by rolling the 'R'",
    "Double tonguing: Articulation technique for fast passages",
    "High register control: Mastery of the instrument's uppermost notes"
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
const StringArray fluteFamousWorks = 
{
    "Mozart - Flute Concerto No. 2 in D major, K. 314",
    "Debussy - Syrinx for solo flute",
    "Quantz - Flute Concertos"
};
const StringArray flutePlayingTechniques = 
{
    "Double Tonguing: Articulation for rapid notes",
    "Flutter Tonguing: Rolling 'R' sound for a fluttery effect",
    "Glissando: Sliding between pitches"
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
const StringArray oboeFamousWorks = 
{
    "Strauss - Oboe Concerto in D Major",
    "Mozart - Oboe Concerto in C major, K. 314",
    "Vaughan Williams - Concerto for Oboe and Strings"
};
const StringArray oboePlayingTechniques = 
{
    "Circular breathing: Technique to produce a continuous tone without interruption",
    "Half-holing: Technique for playing notes that are not fully covered by the finger pads",
    "Multiphonics: Producing more than one note simultaneously"
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
const StringArray corAnglaisFamousWorks = 
{
    "Dvořák - Symphony No. 9 'From the New World' (2nd movement)",
    "Rossini - William Tell Overture (3rd part, Ranz des Vaches)",
    "Berlioz - Roman Carnival Overture"
};
const StringArray corAnglaisPlayingTechniques = 
{
    "Circular breathing: For sustained notes without breaks",
    "Half-hole technique: For smooth transitions in the upper register",
    "Vibrato: Modulating pitch slightly for a warmer sound"
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
const StringArray clarinetFamousWorks = 
{
    "Mozart - Clarinet Concerto in A major, K. 622",
    "Weber - Clarinet Concerto No. 2 in E-flat major, Op. 74",
    "Copland - Clarinet Concerto"
};
const StringArray clarinetPlayingTechniques = 
{
    "Legato: Smooth and connected style of play",
    "Staccato: Short, detached notes",
    "Slur: Smoothly connecting two or more notes without rearticulating"
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
const StringArray bassClarinetFamousWorks = 
{
    "Stravinsky - The Rite of Spring",
    "Wagner - Lohengrin (Act III Prelude)",
    "Holst - The Planets"
};
const StringArray bassClarinetPlayingTechniques = 
{
    "Extended techniques: Including multiphonics and flutter tonguing",
    "Glissando: Smoothly sliding from one pitch to another",
    "Cross-fingering: Achieving alternate fingerings for microtonal effects"
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
const StringArray bassoonFamousWorks = 
{
    "Mozart - Bassoon Concerto in B flat major, K.191",
    "Vivaldi - Bassoon Concertos",
    "Weber - Bassoon Concerto in F major, Op. 75"
};
const StringArray bassoonPlayingTechniques = 
{
    "Flutter tonguing: Rolling the tongue to create a trembling sound",
    "Glissando: Sliding from one note to another",
    "Staccato: Playing notes sharply and detached"
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
const StringArray contraBassoonFamousWorks = 
{
    "Strauss - Eine Alpensinfonie, Op. 64",
    "Stravinsky - The Rite of Spring",
    "Prokofiev - Symphony No. 5, Op. 100"
};
const StringArray contraBassoonPlayingTechniques = 
{
    "Extended techniques like multiphonics and flutter tonguing for contemporary pieces",
    "Reinforcing bass lines, often doubling them an octave lower",
    "Using the extreme low register for special effects in orchestral textures"
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
const StringArray timpaniFamousWorks = 
{
    "Beethoven - Symphony No. 9",
    "Tchaikovsky - 1812 Overture",
    "Mahler - Symphony No. 1"
};
const StringArray timpaniPlayingTechniques = 
{
    "Tuning changes: Adjusting pitch during performance",
    "Rolls: Rapid hits to create a sustained sound",
    "Muffling: Dampening the drum head to stop the sound"
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
const StringArray harpFamousWorks = 
{
    "Debussy - Danses sacrée et profane",
    "Ravel - Introduction and Allegro for Harp, Flute, Clarinet and String Quartet",
    "Tchaikovsky - Swan Lake"
};
const StringArray harpPlayingTechniques = 
{
    "Pres de la table: Playing close to the soundboard for a muted effect",
    "Bisbigliando: A whispering effect achieved by repeating notes or chords",
    "Glissando: Running the fingers across the strings for a sweeping sound"
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
const StringArray celestaFamousWorks = 
{
    "Tchaikovsky - The Dance of the Sugar Plum Fairy from The Nutcracker",
    "Bartók - Music for Strings, Percussion and Celesta",
    "Harry Potter Theme (Hedwig's Theme) by John Williams"
};
const StringArray celestaPlayingTechniques = 
{
    "Delicate touch: For the instrument's gentle, bell-like tones",
    "Pedaling: To sustain or dampen the sound",
    "Layering: Often used in combination with other instruments to add texture"
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
const StringArray marimbaFamousWorks = 
{
    "Keiko Abe - Prism Rhapsody for Marimba and Orchestra",
    "Emmanuel Séjourné - Concerto for Marimba and Strings",
    "Ney Rosauro - Concerto for Marimba and Orchestra No. 1"
};
const StringArray marimbaPlayingTechniques = 
{
    "Four-mallet grip: Using two mallets in each hand",
    "Rolls: Rapidly alternating mallets to create a sustained note",
    "Dead stroke: Letting the mallet rest on the bar after striking for a muted effect"
};

