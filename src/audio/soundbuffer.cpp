//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (��������� �����) ***
//				Copyright (C) 2018-2020
//
// ����������� ������:  https://github.com/BSOD-GameEdition/lifeEngine
// ������:				���� �������� (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <al.h>
#include <alc.h>

#include "engine/iparsersoundbuffer.h"

#include "global.h"
#include "audiodevice.h"
#include "soundbuffer.h"

// ------------------------------------------------------------------------------------ //
// Constructor
// ------------------------------------------------------------------------------------ //
le::SoundBuffer::SoundBuffer() :
	countReferences( 0 ),
	handle( 0 ),
	sampleRate( 0 )
{}

// ------------------------------------------------------------------------------------ //
// Destructor
// ------------------------------------------------------------------------------------ //
le::SoundBuffer::~SoundBuffer()
{
	Delete();
}

// ------------------------------------------------------------------------------------ //
// Increment references
// ------------------------------------------------------------------------------------ //
void le::SoundBuffer::IncrementReference()
{
	++countReferences;
}

// ------------------------------------------------------------------------------------ //
// Decrement references
// ------------------------------------------------------------------------------------ //
void le::SoundBuffer::DecrementReference()
{
	--countReferences;
}

// ------------------------------------------------------------------------------------ //
// Release
// ------------------------------------------------------------------------------------ //
void le::SoundBuffer::Release()
{
	delete this;
}

// ------------------------------------------------------------------------------------ //
// Get count references
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::SoundBuffer::GetCountReferences() const
{
	return countReferences;
}

// ------------------------------------------------------------------------------------ //
// Create
// ------------------------------------------------------------------------------------ //
void le::SoundBuffer::Create()
{
	if ( handle != 0 )		return;
	alGenBuffers( 1, &handle );
}

// ------------------------------------------------------------------------------------ //
// Append
// ------------------------------------------------------------------------------------ //
void le::SoundBuffer::Append( SAMPLE_FORMAT SampleFormat, const Byte_t* Samples, UInt32_t SamplesSize, UInt32_t SampleRate )
{
	if ( handle == 0 || !Samples )		return;
	
	alBufferData( handle, AudioDevice::GetSampleFormat( SampleFormat ), Samples, SamplesSize, SampleRate );	
	sampleRate = SampleRate;
}

// ------------------------------------------------------------------------------------ //
// Delete
// ------------------------------------------------------------------------------------ //
void le::SoundBuffer::Delete()
{
	if ( handle == 0 )		return;

	alDeleteBuffers( 1, &handle );

	handle = 0;
	sampleRate = 0;
	samples.size();
}

// ------------------------------------------------------------------------------------ //
// Get count samples
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::SoundBuffer::GetCountSamples() const
{
	return samples.size();
}

// ------------------------------------------------------------------------------------ //
// Get samples
// ------------------------------------------------------------------------------------ //
float* le::SoundBuffer::GetSamples() const
{
	return ( float* ) samples.data();
}

// ------------------------------------------------------------------------------------ //
// Get sample rate
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::SoundBuffer::GetSampleRate() const
{
	return sampleRate;
}