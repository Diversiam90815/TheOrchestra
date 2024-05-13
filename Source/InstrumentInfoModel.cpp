/*
  ==============================================================================

	InstrumentInfoModel.cpp
	Created: 8 Apr 2024 6:23:51pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#include "InstrumentInfoModel.h"

InstrumentInfoModel::InstrumentInfoModel()
{
	addWoodwindInstruments();
	addBrassInstruments();
	addPercussionInstruments();
	addStringInstruments();
}

InstrumentInfoModel::~InstrumentInfoModel()
{
}


void InstrumentInfoModel::addInstrument(Family family, int instrumentId, const InstrumentInfo &info)
{
	int key			 = getInstrumentKey(family, instrumentId);
	instruments[key] = info;
}


InstrumentInfo InstrumentInfoModel::getInstrument(int key)
{
	auto it = instruments.find(key);
	if (it != instruments.end())
		return it->second;
}


int InstrumentInfoModel::getInstrumentKey(int family, int instrument)
{
	int key = family * 100 + instrument;
	return key;
}


void InstrumentInfoModel::addBrassInstruments()
{
	auto frenchHorn = InstrumentInfo(FrenchHornName, frenchHornRange, frenchHornQualities, frenchHornRoles, frenchHornFamousWorks, frenchHornTransposition, brassPlayingTechniques);
	auto trumpet	= InstrumentInfo(TrumpetName, trumpetRange, trumpetQualities, trumpetRoles, trumpetFamousWorks, trumpetTransposition, brassPlayingTechniques);
	auto tenorTrmb	= InstrumentInfo(TenorTromboneName, tenorTromboneRange, tenorTromboneQualities, tenorTromboneRoles, tenorTromboneFamousWorks, tenorTromboneTransposition,
									 brassPlayingTechniques);
	auto bassTrmb =
		InstrumentInfo(BassTromboneName, bassTromboneRange, bassTromboneQualities, bassTromboneRoles, bassTromboneFamousWorks, bassTromboneTransposition, brassPlayingTechniques);
	auto cimbasso = InstrumentInfo(CimbassoName, cimbassoRange, cimbassoQualities, cimbassoRoles, cimbassoFamousWorks, cimbassoTransposition, brassPlayingTechniques);
	auto tuba	  = InstrumentInfo(TubaName, tubaRange, tubaQualities, tubaRoles, tubaFamousWorks, tubaTransposition, brassPlayingTechniques);

	addInstrument(Family::Brass, Brass::FrenchHorn, frenchHorn);
	addInstrument(Family::Brass, Brass::Trumpet, trumpet);
	addInstrument(Family::Brass, Brass::TenorTrombone, tenorTrmb);
	addInstrument(Family::Brass, Brass::BassTrombone, bassTrmb);
	addInstrument(Family::Brass, Brass::Cimbasso, cimbasso);
	addInstrument(Family::Brass, Brass::Tuba, tuba);
}


void InstrumentInfoModel::addStringInstruments()
{
	auto violin = InstrumentInfo(ViolinName, violinRange, violinQualities, violinRoles, violinFamousWorks, violinTransposition, stringsPlayingTechniques);
	auto viola	= InstrumentInfo(ViolaName, violaRange, violaQualities, violaRoles, violaFamousWorks, violaTransposition, stringsPlayingTechniques);
	auto cello	= InstrumentInfo(VioloncelloName, celloRange, celloQualities, celloRoles, celloFamousWorks, celloTransposition, stringsPlayingTechniques);
	auto db		= InstrumentInfo(DoubleBassName, doubleBassRange, doubleBassQualities, doubleBassRoles, doubleBassFamousWorks, doubleBassTransposition, stringsPlayingTechniques);

	addInstrument(Family::Strings, Strings::Violin, violin);
	addInstrument(Family::Strings, Strings::Viola, viola);
	addInstrument(Family::Strings, Strings::Violoncello, cello);
	addInstrument(Family::Strings, Strings::DoubleBass, db);
}


void InstrumentInfoModel::addWoodwindInstruments()
{
	auto piccolo = InstrumentInfo(PiccoloName, piccoloRange, piccoloQualities, piccoloRoles, piccoloFamousWorks, piccoloTransposition, woodwindsPlayingTechniques);
	auto flute	 = InstrumentInfo(FluteName, fluteRange, fluteQualities, fluteRoles, fluteFamousWorks, fluteTransposition, woodwindsPlayingTechniques);
	auto oboe	 = InstrumentInfo(OboeName, oboeRange, oboeQualities, oboeRoles, oboeFamousWorks, oboeTransposition, woodwindsPlayingTechniques);
	auto coranglais =
		InstrumentInfo(CorAnglaisName, corAnglaisRange, corAnglaisQualities, corAnglaisRoles, corAnglaisFamousWorks, corAnglaisTransposition, woodwindsPlayingTechniques);
	auto clarinet	   = InstrumentInfo(ClarinetName, clarinetRange, clarinetQualities, clarinetRoles, clarinetFamousWorks, clarinetTransposition, woodwindsPlayingTechniques);
	auto bassClarinet  = InstrumentInfo(BassClarinetName, bassClarinetRange, bassClarinetQualities, bassClarinetRoles, bassClarinetFamousWorks, bassClarinetTransposition,
										woodwindsPlayingTechniques);
	auto bassoon	   = InstrumentInfo(BassoonName, bassoonRange, bassoonQualities, bassoonRoles, bassoonFamousWorks, bassoonTransposition, woodwindsPlayingTechniques);
	auto contrabassoon = InstrumentInfo(ContrabassonName, contrabassoonRange, contrabassoonQualities, contrabassoonRoles, contrabassoonFamousWorks, contrabassoonTransposition,
										woodwindsPlayingTechniques);

	addInstrument(Family::Woodwinds, Woodwinds::Piccolo, piccolo);
	addInstrument(Family::Woodwinds, Woodwinds::Flute, flute);
	addInstrument(Family::Woodwinds, Woodwinds::Oboe, oboe);
	addInstrument(Family::Woodwinds, Woodwinds::CorAnglais, coranglais);
	addInstrument(Family::Woodwinds, Woodwinds::Clarinet, clarinet);
	addInstrument(Family::Woodwinds, Woodwinds::BassClarinet, bassClarinet);
	addInstrument(Family::Woodwinds, Woodwinds::Basson, bassoon);
	addInstrument(Family::Woodwinds, Woodwinds::Contrabassoon, contrabassoon);
}


void InstrumentInfoModel::addPercussionInstruments()
{
	auto timpani = InstrumentInfo(TimpaniName, timpaniRange, timpaniQualities, timpaniRoles, timpaniFamousWorks, timpaniTransposition, timpaniPlayingTechniques);
	auto celeste = InstrumentInfo(CelesteName, celesteRange, celesteQualities, celesteRoles, celestaFamousWorks, celesteTransposition, celestaPlayingTechniques);
	auto marimba = InstrumentInfo(MarimbaName, marimbaRange, marimbaQualities, marimbaRoles, marimbaFamousWorks, marimbaTransposition, marimbaPlayingTechniques);
	auto harp	 = InstrumentInfo(HarpName, harpRange, harpQualities, harpRoles, harpFamousWorks, harpTransposition, harpPlayingTechniques);

	addInstrument(Family::Percussion, Percussion::Timpani, timpani);
	addInstrument(Family::Percussion, Percussion::Celeste, celeste);
	addInstrument(Family::Percussion, Percussion::Marimba, marimba);
	addInstrument(Family::Percussion, Percussion::Harp, harp);
}
