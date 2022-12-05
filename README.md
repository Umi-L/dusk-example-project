# dusk-example-project
An example project made for myself using the DuSK framework for GBA development.

Based on [this](https://github.com/bmchtech/dusk/tree/main/) library for drawing. Much appriciated to all those that contribute to DuSK I have really enjoyed using the framework; for anyone trying to get into making gameboy advance games I reccomend trying it out. It's very minimalistic and easy to understand.

I'm very new to low level development (especially in C) but I figured the best way to learn is to just go for it. And I've been wanting to make some homebrew for a while now so here we are.

### Compiling & Running

This was made on linux though I'm sure with some tweaking you can get it to work on WSL.

It has all the same requirements as [DuSK](https://github.com/bmchtech/dusk/tree/main/) as its based on it.

The makefile expects there to be a `~/lib/dusk folder` with the dusk repo cloned.

Finally just run `make` and you should get a .gba file sitting in your project folder.

All my debug logs expect you to be running mGBA.

On linux my run command is `mgba-qt dusk-example-project.gba` though on windows I think it may differ.

The debug output is sent to the console when running using the command above and the "logs" section of mGBA.

If there are any issues you can conact me on Discord which should be in my profile.
