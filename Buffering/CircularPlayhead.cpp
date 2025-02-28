void CircularBufferPlayhead::prepare (const int Size)
{
    bufferSize = Size;
}

CircularBufferContext CircularBufferPlayhead::UpdateCircularBuffer (const int IncrementBy)
{
    CircularBufferContext bufferContext{};

    bufferContext.PlayPositionOne = currentPlayPosition;
    currentPlayPosition += IncrementBy;

    const auto bufferSizeTwo = (currentPlayPosition > bufferSize) ? currentPlayPosition % bufferSize: 0;

    currentPlayPosition %= bufferSize;

    bufferContext.PlayPositionTwo = 0;
    bufferContext.PlayPositionTwo = bufferSizeTwo;

    return bufferContext;
}