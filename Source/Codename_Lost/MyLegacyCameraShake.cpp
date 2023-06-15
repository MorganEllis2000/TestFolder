// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLegacyCameraShake.h"

UMyLegacyCameraShake::UMyLegacyCameraShake()
{
    OscillationDuration = -4.f;
    OscillationBlendInTime = 2.f;
    OscillationBlendOutTime = 0.2f;

    LocOscillation.Z.Amplitude = 3.0;
    LocOscillation.Z.Frequency = 12.0;
    
    LocOscillation.Z.Waveform = EOscillatorWaveform::SineWave;
}