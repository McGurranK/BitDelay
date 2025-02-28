void CircularBuffer::Prepare (const int TimeInSamples, const int NumberOfChannels)
{
    circularPlayHead.prepare (TimeInSamples);
    circularSampleBuffer.setSize (NumberOfChannels, TimeInSamples);
    circularSampleBuffer.clear();
}

void CircularBuffer::processNewSamples (const juce::AudioBuffer<float>& BufferRef)
{
    const auto BufferSize = BufferRef.getNumSamples();
    const auto bufferContext = circularPlayHead.UpdateCircularBuffer (BufferSize);

    const auto bufferContextUpdate = [&](int PlayStart, int NumberOfSamples, int ReadOffset)
    {
        for (int ChannelIndex  = 0; ChannelIndex < BufferRef.getNumChannels(); ++ChannelIndex)
            circularSampleBuffer.copyFrom (ChannelIndex, PlayStart, BufferRef, ChannelIndex, ReadOffset, NumberOfSamples);
    };

    if (bufferContext.PlayPositionOne > 0)
        bufferContextUpdate (bufferContext.PlayPositionOne, bufferContext.PlayPositionOneSize, 0);

    if (bufferContext.PlayPositionTwo > 0)
        bufferContextUpdate (bufferContext.PlayPositionTwo, bufferContext.PlayPositionTwoSize, 0);
}