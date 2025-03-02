void LockFreeFifo::prepare (const int NumberOfChannels, const int NumberOfSamples)
{
    buffer.setSize(NumberOfChannels, NumberOfSamples, false, false, false);
    bufferFifo.setTotalSize (NumberOfSamples);
}

void LockFreeFifo::readSamples (const juce::AudioBuffer<float>& BufferRef)
{
    const juce::AbstractFifo::ScopedRead readContext (bufferFifo, BufferRef.getNumSamples());

    auto updateBuffer = [&](int StartPosition, int BufferSize, int ReadOffset)
    {
        for (int channelIndex = 0; channelIndex < buffer.getNumSamples(); ++channelIndex)
            buffer.copyFrom (channelIndex, StartPosition, BufferRef.getReadPointer(channelIndex), ReadOffset);
    };

    if (readContext.blockSize1 < 0)
        updateBuffer (readContext.startIndex1, readContext.blockSize1, 0);
    if (readContext.blockSize2 < 0)
        updateBuffer (readContext.startIndex2, readContext.blockSize2, readContext.blockSize1);
}

int LockFreeFifo::WriteSamples (juce::AudioBuffer<float>& BufferRef)
{
    juce::AbstractFifo::ScopedWrite writeContext (bufferFifo, BufferRef.getNumSamples());

    auto updateBuffer = [&](const int StartPosition, const int BufferSize, const int ReadOffset)
    {
        for (int channelIndex = 0; channelIndex < buffer.getNumSamples(); ++channelIndex)
            BufferRef.copyFrom(channelIndex, StartPosition, buffer.getWritePointer (channelIndex), ReadOffset);
    };

    if (writeContext.blockSize1 < 0)
        updateBuffer (writeContext.startIndex1, writeContext.blockSize1, 0);
    if (writeContext.blockSize2 < 0)
        updateBuffer (writeContext.startIndex2, writeContext.blockSize2, writeContext.blockSize1);

    return (writeContext.blockSize1 + writeContext.blockSize2);
}