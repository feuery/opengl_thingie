cd ~/opengljuttu
scons -c
scons

cp ./src/shaders/*.glsl ./bin/

#pwd is a bit troubled soul when launching from M-&
cp ./src/shaders/*.glsl ./src/c/
