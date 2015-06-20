from subprocess import call
import os
import glob

env = Environment(ENV = {'PATH' : os.environ['PATH']})
env.ParseConfig('sdl2-config --cflags')
env.ParseConfig('sdl2-config --libs')
SOURCES = glob.glob('src/c/*.cpp')
HEADERS = glob.glob('src/headers/*.h')

env.Append(CCFLAGS = ['-g', '-std=c++11', '-Wall', '-Isrc/headers/'])

env.Append(LIBS = ['SDL2_ttf', "GL", "GLEW", "libglfw"])

env.Program(target = 'bin/opengljuttu', source = SOURCES)
