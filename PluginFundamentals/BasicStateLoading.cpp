BasicStateLoading::BasicStateLoading (juce::AudioProcessor& ProcessorRef)
: processorRef (ProcessorRef)
{
}

void BasicStateLoading::getStateInformation (juce::MemoryBlock& destData)
{
    juce::XmlElement stateXML (xmlStringName);

    for (auto& parameter : processorRef.getParameters())
    {
        if (const auto* rangeParameterCast = dynamic_cast<juce::RangedAudioParameter*>(parameter))
        {
            const auto parameterName = rangeParameterCast->paramID;
            const auto parameterValue = rangeParameterCast->getValue();
            const auto range = rangeParameterCast->getNormalisableRange();

            const auto parameterValueString = rangeParameterCast->getText (parameterValue, 5);

            const auto state = stateXML.createNewChildElement(parameterName);
            state->setAttribute (xmlValueAttribruteString , parameterValueString);
        }
    }

    processorRef.copyXmlToBinary (stateXML, destData);
}

void BasicStateLoading::setParameterInformation (const void* data, const int sizeInBytes)
{
    const auto xmlElement = processorRef.getXmlFromBinary (data, sizeInBytes);
    const auto parameterList = processorRef.getParameters();

    if (xmlElement.get())
    {
      auto parameter = xmlElement->getFirstChildElement();

        while (parameter != nullptr)
        {
          const auto parameterName = parameter->getTagName();
          const auto parameterText = parameter->getStringAttribute (xmlValueAttribruteString);

            for (auto& parameters : parameterList)
            {
                if (const auto* rangeParameterCast = dynamic_cast<juce::RangedAudioParameter*>(parameters))
                {
                    if (rangeParameterCast->getParameterID().equalsIgnoreCase (parameterName))
                    {
                      const auto realParameterValue = parameters->getValueForText (parameterText);
                      parameters->setValue (realParameterValue);

                      break;
                    }
                }
            }

            parameter = parameter->getNextElement();
        }
    }
}
