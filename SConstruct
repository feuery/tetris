import os
import glob

env = Environment(ENV = {'PATH' : os.environ['PATH']})
env.ParseConfig('sdl2-config --cflags')
env.ParseConfig('sdl2-config --libs')
SOURCES = glob.glob('src/cpp/*.cpp')
HEADERS = glob.glob('src/headers/*.h')

env.Append(CCFLAGS = ['-g', '-Wall', '-std=c++11', '-Isrc/headers/'])

env.Append(LIBS = ['SDL2_gfx'])

env.Program(target = 'bin/tetris', source = SOURCES)
