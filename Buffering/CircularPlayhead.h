#pragma once

struct CircularBufferContext
{
    int PlayPositionOne { 0 };
    int PlayPositionOneSize { 0 };
    int PlayPositionTwo { 0 };
    int PlayPositionTwoSize { 0 };
};

// Playhead class for wrapping samples around a buffer
class CircularBufferPlayhead final
{
public:
    void prepare (const int Size);
    CircularBufferContext UpdateCircularBuffer (const int IncrementBy);

private:
    int currentPlayPosition { 0 };
    int bufferSize { 0 };
};