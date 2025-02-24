cmake_minimum_required(VERSION 3.22)

project (BitDelay VERSION 0.0.1)

add_subdirectory(JUCE)

juce_add_plugin(BitDelay
    COMPANY_NAME Devekusu Devices               # Specify the name of the plugin's author
    IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE            # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE                # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE DXKU               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE BTDL                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "Bit Delay")        # The name of the final executable, which can differ from the target name

set(SourceFiles
	source/PluginEditor.h
	source/PluginProcessor.h
	source/PluginEditor.cpp
	source/PluginProcessor.cpp)

target_sources(BitDelay PRIVATE ${SourceFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/source PREFIX Source FILES ${SourceFiles})

target_compile_definitions(BitDelay
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(BitDelay
PUBLIC
        juce::juce_audio_utils
		juce::juce_dsp
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)