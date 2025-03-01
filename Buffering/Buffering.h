/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.md file.

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 Buffering
  vendor:             Me
  version:            8.0.6
  name:               Audio Buffering Module
  description:        Classes for buffering samples for visuals
  website:
  license:
  minimumCppStandard: 17

  dependencies:       juce_audio_basics juce_core

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once

// Todo Pull in catch two to unit test this code

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>

#include "CircularPlayhead.h"
#include "CircularBuffer.h"
#include "LockFreeFifo.h"