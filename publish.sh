scons -c
scons

os=`uname`

if [[ "$os" == "Darwin" ]]; then
    rm ./tetris.dmg
    hdiutil create tetris.dmg -volname "Tetris" -fs HFS+ -srcfolder ./bin/
    # echo "Tetris.dmg ready!"
else
    echo "Error, publishing system not written for $os"
fi
