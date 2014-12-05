# This is a tetris.
This is a tetris that began it's life in a local Game Jam a few weeks ago, when I saw few friends fighting with Visual C++13 and SDL. I wondered if the joy of doing games on SDL would be as horrible on Linux as I remember it being on Windows back in -11.

# It wasn't.

Actually, it was quite nice. This repo is a result of that idea. I retrofitted the game to compile on Windows too, that patch lies on windows-branch, but because of VC++'s braindead library model, it doesn't actually work anywhere but on my mac.

Download the game for mac or windows from the [releases - area](https://github.com/feuery/tetris/releases). Linux binaries fill arrive when I care enough, but if I won't, the compilation of these codes should be pretty straightforward:

* Install sdl2.devel and sdl2_ttf.devel
* Clone the repo and make sure you're on master-branch
* Run `scons` on the root of this repo