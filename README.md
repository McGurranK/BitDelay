# What is BitDelay?

One day, I had the idea "what would it sound like to throw a bit-crusher in a 
feedback loop?" and this is the horrific outcome of that.

# What's currently missing?

- No state loading code (oops).
- No finalised GUI spec (Personally trying to use this to learn figma).
- Where are the flashy visuals? (Currently working on that).
- Sarcasm :'(

# Build

- git clone this repo.
- Go to project folder in terminal
- Run "git submodule init" to init the JUCE submodule.
- Building with Cmake (I'm currently using Clion on MacOS)
  - For Xcode run "Cmake -B Build -G Xcode"
  - For Visual studio 2022 run "Cmake -B Build -G "Visual Studio 17 2022""