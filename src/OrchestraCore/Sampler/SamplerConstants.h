/*
  ==============================================================================
	Module			SamplerConstants
	Description		Tuning constants used internally by the sampler modules
  ==============================================================================
*/

#pragma once


namespace ArticulationVoiceConstants
{
static constexpr int   MaxDynamicLayers = 8;

static constexpr float AttackSeconds	= 0.002f;
static constexpr float ShortRelease		= 0.010f;
static constexpr float SustainRelease	= 0.120f;
} // namespace ArticulationVoiceConstants


namespace MIDI
{
constexpr int ModWheelCC   = 1;
constexpr int ExpressionCC = 11;

constexpr int MinCCValue   = 0;
constexpr int MaxCCValue   = 127;
} // namespace MIDI
