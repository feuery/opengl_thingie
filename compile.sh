cd ~/Dropbox/opengl_thingie/
scons -c
scons

rm ./bin/*.glsl
cp ./src/shaders/*.glsl ./bin/

rm -r ./bin/assets/*
cp -r ./assets ./bin

#pwd is a bit troubled soul when launching from M-&
rm ./src/c/*.glsl
cp ./src/shaders/*.glsl ./src/c/
